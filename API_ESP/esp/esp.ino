#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h> 

const char* ssid = "TP-Link_07EA";
const char* password = "96817209";
const char* serverNameGet = "http://192.168.0.103:8005/temperature?location=";
const char* serverNamePost = "http://192.168.0.103:8005/submit_temperature";
String location = "living_room"; 
float temperature = 0.0; 

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 8 * 3600, 60000); 

void getTemperature(); 
void submitTemperature(float value); 
void processSerialInput(); 

bool temperatureChanged = false; 

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected to WiFi, IP address: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();

  getTemperature();
}

void loop() {
  if (Serial.available() > 0) {
    processSerialInput();
  }

  timeClient.update(); 

  if (temperatureChanged) {
    submitTemperature(temperature);
    getTemperature();
    temperatureChanged = false;
  }
}

void processSerialInput() {
  String input = Serial.readStringUntil('\n');
  input.trim(); 

  if (input.startsWith("location ")) {
    location = input.substring(9);
    Serial.println();
    Serial.print("Location changed to: ");
    Serial.println(location);
    Serial.println();
    getTemperature(); 
  } else if (input.startsWith("temperature ")) {
    float value = input.substring(12).toFloat();
    Serial.println();
    temperature = value; 
    temperatureChanged = true; 
    Serial.println();
  } else {
    Serial.println();
    Serial.println();
    Serial.println("Invalid command. Use:");
    Serial.println("location <new_location>");
    Serial.println("temperature <value>");
    Serial.println();
    Serial.println();
  }
}

void getTemperature() {
  WiFiClient client;
  HTTPClient http;
  String serverPath = String(serverNameGet) + location;

  Serial.print("Connecting to GET: ");
  Serial.println(serverPath);
  http.begin(client, serverPath); 
  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.print("GET code: ");
    Serial.println(httpCode);
    String payload = http.getString();
    Serial.println(payload);

    
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.f_str());
      return;
    }

    JsonArray values = doc["values"];
    float sum = 0;
    for (float value : values) {
      sum += value;
    }
    float average = sum / values.size();
    Serial.print("Average value: ");
    Serial.println(average);
    temperature = average; 
  } else {
    Serial.print("Error on HTTP request, GET code: ");
    Serial.println(httpCode);
    Serial.println(http.errorToString(httpCode));  
  }

  http.end();

  Serial.println();
  Serial.println("Use:");
  Serial.println("location <new_location>");
  Serial.println("temperature <value>");
  Serial.println();
}

void submitTemperature(float value) {
  WiFiClient client;
  HTTPClient http;
  Serial.print("Connecting to POST: ");
  Serial.println(serverNamePost);
  http.begin(client, serverNamePost); 
  http.addHeader("Content-Type", "application/json");

  String device_id = String(ESP.getChipId());
  
  timeClient.update();
  String timestamp = String(timeClient.getEpochTime());

  String jsonData = "{\"value\": " + String(value, 1) + ", \"location\": \"" + location + "\", \"device_id\": \"" + device_id + "\", \"timestamp\": \"" + timestamp + "\"}";
  
  int httpCode = http.POST(jsonData);

  if (httpCode > 0) {
    Serial.print("POST code: ");
    Serial.println(httpCode);
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.print("Error on HTTP request, POST code: ");
    Serial.println(httpCode);
    Serial.println(http.errorToString(httpCode));  
  }

  http.end();
}
