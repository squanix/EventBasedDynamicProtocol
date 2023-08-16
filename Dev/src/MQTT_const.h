#ifndef _MQTT_CONST_H_
#define _MQTT_CONST_H_

#include "common.h"

#define WIFI_SSID "WiFi"
#define WIFI_PASSWORD "wifiandwife"

#define MQTT_CIMA_PUB "eventdynamic/device"
#define MQTT_CIMA_SUB "eventdynamic/device"


void connectToWifi();
void connectToMqtt();
void onWifiConnect(const WiFiEventStationModeGotIP& event);
void onWifiDisconnect(const WiFiEventStationModeDisconnected& event);
void onMqttConnect(bool sessionPresent);
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
void onMqttSubscribe(uint16_t packetId, uint8_t qos);
void onMqttUnsubscribe(uint16_t packetId);
void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
void onMqttPublish(uint16_t packetId);


#endif