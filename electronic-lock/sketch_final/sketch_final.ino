#include <ESP8266WiFi.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ArduinoJson.h>

#define LOCK_TIMEOUT 3000
#define SERVO_PIN D2
#define BUZZER_PIN D3
#define RED_LED_PIN D14
#define RST_PIN D9
#define CS_PIN D10
#define BTN_PIN D8
#define DOOR_PIN A0

#include "Config.h"
#include "Lock_control.h"
#include "Server.h"
#include "WIFI.h"

bool locked = true;
uint32_t lockTimeout;
MFRC522 rfid(CS_PIN, RST_PIN);
Servo doorServo;

const char* serverName = "http://192.168.43.122:8000/uid";
const char* ueid = "r32r32r32r32";

void setup() {
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(DOOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  SPI.begin();
  rfid.PCD_Init();
  Serial.begin(9600);
  setupWiFiAP();
  server_init();
  lock();
}

void loop() {
  server.handleClient();
  
  state_led();
  handleButtonPress();
  handleDoorSensor();
  handleLockTimeout();
  handleRFID();
  rebootRFID();
}
