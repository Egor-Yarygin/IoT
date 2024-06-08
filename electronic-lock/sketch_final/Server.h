#ifndef SERVER_H
#define SERVER_H

#include <ESP8266WebServer.h>
#include "Config.h"
#include "WIFI.h"

ESP8266WebServer server(80);

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found");
}

void handle_connect_wifi_page() {
  server.send(200, "text/html", index_html);
}

void handle_wifi_config() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");

  connect_to_wifi(ssid.c_str(), password.c_str());

  if (WiFi.status() == WL_CONNECTED) {
    server.send(200, "text/html", success_connect);
  } else {
    server.send(200, "text/html", failed_connect);
  }
}

void server_init() {
  server.on("/", HTTP_GET, handle_connect_wifi_page);
  server.on("/connect", HTTP_GET, handle_wifi_config);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

#endif // SERVER_H
