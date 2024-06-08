#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "Lock_control.h"

extern String getRfidTag();
const char* serverUrl = "http://192.168.43.122:8000/api/uid";
extern const char* ueid; 

void connect_to_wifi(const char *ssid, const char *password) {
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  int timeout = 10;
  while (WiFi.status() != WL_CONNECTED && timeout > 0) {
    delay(1000);
    Serial.print(".");
    timeout--;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");
  } else {
    Serial.println("\nFailed to connect to WiFi");
  }
}

String httpRequest(const char *serverName) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    String url = String(serverName) + "?ueid=" + ueid; 
    http.begin(client, url);
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

void httpRequest2() {
  if (WiFi.status() == WL_CONNECTED) {
    String cardUID = getRfidTag();
    if (cardUID.length() > 0) {
      String postData = "uid=" + cardUID + "&ueid=" + ueid;
      Serial.println(postData);
      WiFiClient client;
      HTTPClient http;
      http.begin(client, serverUrl);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      Serial.println(postData);
      int httpCode = http.POST(postData);
      if (httpCode > 0) {
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      } else {
        Serial.println("Error on HTTP request");
      }
      http.end();
    }
  } else {
    Serial.println("WiFi not connected");
  }
}

void setupWiFiAP() {
  WiFi.softAP(ap_ssid, ap_password);
  Serial.println("Access Point Started");
}

#endif 
