#include "config.h"
#include "wifi.h"
#include "server.h"
#include "MQTT.h"

bool last_mode = AP_mode;
bool is_wifi_on = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  is_wifi_on = init_WIFI(AP_mode);
  if (is_wifi_on) {
    server_init();
  }
}

void loop() {
  server.handleClient();
  if (last_mode != AP_mode) {
    last_mode = AP_mode;
    is_wifi_on = init_WIFI(AP_mode);
    Serial.println(is_wifi_on);
    if (is_wifi_on) {
      server_init();
      if (!AP_mode) {
        init_MQTT();
        String topic = "esp8266" + id() + "/command";
        String state_topic = "esp8266" + id() + "/command";
        mqtt_client.subscribe(topic.c_str());
        mqtt_client.publish(state_topic.c_str(), "hello");
        Serial.println("See me at " + state_topic);
      }
    }
  }
  if (!AP_mode) {
    mqtt_client.loop();
  } 
  delay(20);
}