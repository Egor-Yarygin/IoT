#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define LOCK_TIMEOUT 1000
#define SERVO_PIN D2      // Пин серво
#define BUZZER_PIN D3     // Пин баззера
#define RED_LED_PIN D14   // Пин красного светодиода
// #define GREEN_LED_PIN D15  // Пин зеленого светодиода
#define RST_PIN D9        // Пин RST MFRC522
#define CS_PIN D10        // Пин SDA MFRC522
#define BTN_PIN D8        // Пин кнопки
#define DOOR_PIN A0       // Пин геркона

const char* ssid = "OPPO A96";
const char* password = "00001234";
const char* serverName = "http://192.168.78.243:8000/uid";

bool locked = true;

MFRC522 rfid(CS_PIN, RST_PIN);
Servo doorServo;

#define DECLINE 0
#define SUCCESS 1
#define OPEN 1
#define CLOSE 0

bool isOpen() {
  return analogRead(DOOR_PIN) != 1024;
}

void lock() {
  doorServo.attach(SERVO_PIN);
  doorServo.write(170);
  delay(2000);
  doorServo.detach();
  Serial.println("lock");
}

void unlock() {
  doorServo.attach(SERVO_PIN);
  doorServo.write(0);
  delay(2000);
  doorServo.detach();
  Serial.println("unlock");
}

void ledSetup(uint8_t state) {
  switch (state) {
    case OPEN:
      // Serial.println("OPEN");
      // digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(RED_LED_PIN, LOW);
      break;
    case CLOSE:
      // Serial.println("CLOSE");
      // digitalWrite(GREEN_LED_PIN, LOW);
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

String httpRequest(const char* serverName) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, serverName);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
      http.end();
      return payload;
    } else {
      Serial.println("Error on HTTP request");
      http.end();
      return "";
    }
  } else {
    Serial.println("WiFi not connected");
    return "";
  }
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


void setup() {
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(DOOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  // pinMode(GREEN_LED_PIN, OUTPUT);

  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  lock();
}

void loop() {
  static uint32_t lockTimeout;

  // Установка состояния светодиода
  if (locked){
    ledSetup(CLOSE);
  }else{
    ledSetup(OPEN);
  }

  // Открытие по нажатию кнопки изнутри
  if (locked and !digitalRead(BTN_PIN)) {
    indicate(SUCCESS);
    unlock();
    lockTimeout = millis();
    locked = false;
  }

  // Проверка геркона двери
  if (isOpen()) {           
    lockTimeout = millis();
  }

  // Блокировка замка по таймауту
  if (!locked and millis() - lockTimeout >= LOCK_TIMEOUT) {
    ledSetup(DECLINE);
    lock();
    locked = true;
  }

  // Поднесение метки
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial() && locked) {
    if (foundTag(rfid.uid.uidByte, rfid.uid.size)) {
      indicate(SUCCESS);
      unlock();
      lockTimeout = millis();  
      locked = false;
    } else {  
      indicate(DECLINE);
    }
  }

  // Перезагружаем RFID каждые 0.5 сек (для надежности)
  static uint32_t rfidRebootTimer = millis();
  if (millis() - rfidRebootTimer > 500) {
    rfidRebootTimer = millis();
    digitalWrite(RST_PIN, HIGH);
    delay(1);
    digitalWrite(RST_PIN, LOW);
    rfid.PCD_Init();
  }
}