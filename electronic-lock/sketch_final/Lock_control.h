#ifndef LOCK_CONTROL_H
#define LOCK_CONTROL_H

#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ArduinoJson.h>
#include "WIFI.h"

extern bool locked;
extern uint32_t lockTimeout;
extern MFRC522 rfid;
extern Servo doorServo;
extern const char* serverName;
extern const char* ueid;

#define DECLINE 0
#define SUCCESS 1
#define OPEN 1
#define CLOSE 0

bool isOpen() {
  return analogRead(DOOR_PIN) != 1024;
}

void lock() {
  doorServo.attach(SERVO_PIN);
  doorServo.write(180);
  delay(1000);
  doorServo.detach();
  Serial.println("lock");
}

void unlock() {
  doorServo.attach(SERVO_PIN);
  doorServo.write(0);
  delay(1000);
  doorServo.detach();
  Serial.println("unlock");
}

void ledSetup(uint8_t state) {
  switch (state) {
    case OPEN:
      digitalWrite(RED_LED_PIN, LOW);
      break;
    case CLOSE:
      digitalWrite(RED_LED_PIN, HIGH);
      break;
  }
}

void indicate(uint8_t signal) {
  switch (signal) {
    case DECLINE:
      Serial.println("DECLINE");
      for (uint8_t i = 0; i < 2; i++) {
        tone(BUZZER_PIN, 100);
        delay(300);
        noTone(BUZZER_PIN);
        delay(100);
      }
      return;
    case SUCCESS:
      Serial.println("SUCCESS");
      tone(BUZZER_PIN, 890);
      delay(330);
      noTone(BUZZER_PIN);
      return;
  }
}

bool compareUIDs(uint8_t* in1, uint8_t* in2, uint8_t size) {
  for (uint8_t i = 0; i < size; i++) {
    if (in1[i] != in2[i]) return false;
  }
  return true;
}

bool foundTag(uint8_t* key, uint8_t size) {
  String payload = httpRequest(serverName);
  if (payload.length() == 0) return false;

  DynamicJsonDocument doc(2048);
  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return false;
  }

  JsonArray uids = doc["uid"];
  for (const char* uid_str : uids) {
    uint8_t uid[4];
    sscanf(uid_str, "0x%hhx, 0x%hhx, 0x%hhx, 0x%hhx", &uid[0], &uid[1], &uid[2], &uid[3]);
    if (compareUIDs(uid, key, size)) {
      return true;
    }
  }
  return false;
}

void handleButtonPress() {
  if (locked && !digitalRead(BTN_PIN)) {
    indicate(SUCCESS);
    unlock();
    lockTimeout = millis();
    locked = false;
  }
}

void handleDoorSensor() {
  if (isOpen()) {
    lockTimeout = millis();
  }
}

void handleLockTimeout() {
  if (!locked && millis() - lockTimeout >= LOCK_TIMEOUT) {
    ledSetup(CLOSE);
    lock();
    locked = true;
  }
}

void handleRFID() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial() && locked) {
    if (foundTag(rfid.uid.uidByte, rfid.uid.size)) {
      indicate(SUCCESS);
      unlock();
      lockTimeout = millis();
      locked = false;
    } else {
      httpRequest2();
    }
  }
}

void rebootRFID() {
  static uint32_t rfidRebootTimer = millis();
  if (millis() - rfidRebootTimer > 500) {
    rfidRebootTimer = millis();
    digitalWrite(RST_PIN, HIGH);
    delay(1);
    digitalWrite(RST_PIN, LOW);
    rfid.PCD_Init();
  }
}

void state_led() {
  if (locked) {
    ledSetup(CLOSE);
  } else {
    ledSetup(OPEN);
  }
}

String getRfidTag() {
    String cardUID = "";
    for (uint8_t i = 0; i < rfid.uid.size; i++) {
        cardUID += "0x";
        cardUID += (rfid.uid.uidByte[i] < 0x10 ? "0" : "");
        cardUID += String(rfid.uid.uidByte[i], HEX);
        if (i < 3) {
            cardUID += ", ";
        }
    }
    return cardUID;
}

#endif 
