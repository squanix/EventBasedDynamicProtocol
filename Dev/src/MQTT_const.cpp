#include "common.h"
#include "MQTT_const.h"

void connectToWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  stock = false;
}

void connectToMqtt() {
  mqttClient.connect();
}

void onWifiConnect(const WiFiEventStationModeGotIP& event) {
  connectToMqtt();
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
  wifiReconnectTimer.detach();
  stock = true;
  setup();
}

void onMqttConnect(bool sessionPresent) {
  uint16_t packetIdSub = mqttClient.subscribe("eventdynamic/device", 2);
  
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {

  if (WiFi.isConnected()) {
    mqttReconnectTimer.once(2, connectToMqtt);
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {

}

void onMqttUnsubscribe(uint16_t packetId) {
}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  Serial.println(atoi(payload));
  digitalWrite(RELAY, atoi(payload));
}

void onMqttPublish(uint16_t packetId) {

}