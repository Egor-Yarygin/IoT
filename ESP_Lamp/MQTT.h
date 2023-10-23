#include <PubSubClient.h>

PubSubClient mqtt_client(wifiClient);

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("There is message on topic");
  Serial.println(topic);
  Serial.print("Message is ");
  Serial.println((char)payload[0]);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

bool init_MQTT() {
  mqtt_client.setServer(mqtt_broker, mqtt_port);
  mqtt_client.setCallback(callback);
  while (!mqtt_client.connected()) {
    String client_id = "esp8266_" + id();
    if (mqtt_client.connect(client_id.c_str())) {
      Serial.println("MQTT client connected with id " + client_id);
    } else {
      Serial.println("Failed to connect MQTT client with id " + client_id);
      delay(500);
    }
  }
  return true;
}