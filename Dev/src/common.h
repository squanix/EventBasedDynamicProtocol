#ifndef _COMMON_H_
#define _COMMON_H_

#include <Ticker.h>
#include <AsyncMqttClient.h>
#include <ESP8266WiFi.h>

#define PIR 14
#define RELAY 15
#define LED 2

extern String ssidStock;
extern uint8_t counter;
extern boolean stock;


extern AsyncMqttClient mqttClient;
extern Ticker mqttReconnectTimer;

extern WiFiEventHandler wifiConnectHandler;
extern WiFiEventHandler wifiDisconnectHandler;
extern Ticker wifiReconnectTimer;


#endif