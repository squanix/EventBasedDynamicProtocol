#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <AsyncMqttClient.h>
#include <string.h>
#include "common.h"
#include "OTA.h"
#include "MQTT_const.h"
#include "EventDynamic.h"
#include <ESP_EEPROM.h>
#include "eeprom.h"

#define timetoreboot 300          // Initial reboot time in 300 seconds
unsigned long previousMillis = 0;
const long interval = 10000;      // interval time to send data (10 seconds)

/*
  Define the MQTT broker address here. 
*/
#define MQTT_HOST IPAddress(180, 250, 135, 101)
#define MQTT_PORT 1883

AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;

// Some WiFi handle need
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;

/*
  If the device can't connect to the WiFi, then the device make himself become access point. You can upload the new configuration throught OTA
*/
String ssidStock = "Event-Dynamic-dev-01";
const char* passwordStock    = "12345678";

const int prime = 19;
const int qprime = 13;
const int m = 100;

// Some variables that we need to make sure the device algorithm work
boolean PIR_t = false, stock = false, startingstock = false, led = false;
uint8_t counter = 0;
unsigned long osstarttime = 0;
String seed_t = "";
String R_t = "";
int intseed, intR;

void setup() {

  /*
    Get the seed and the R from the flash or EEPROM
  */
  seed_t = readSeed();
  R_t = readR();
  intseed = seed_t.toInt();
  intR = R_t.toInt();

  /*
    STOCK is flag to indicate that the device can't connect to the predefine network. Here I want to make sure that, in the future, the device is able to receive new firmware through OTA.
  */
  if(stock)
  {
    WiFi.disconnect(true);
    WiFi.mode(WIFI_AP);
    IPAddress stocklocal_IP(10, 30, 60, 200);
    IPAddress stockgateway(10, 30, 60, 1);
    IPAddress stocksubnet(255, 255, 255, 0);
    WiFi.softAPConfig(stocklocal_IP, stockgateway, stocksubnet);
    WiFi.softAP(ssidStock, passwordStock, 5 , false, 8);
    setnewnetwork();                                                          // This is instance for OTA. Please don't delete it what ever your new algorithm is
    startingstock = true;
    osstarttime = millis();
  }
  else
  {
    /*
      WiFi Handler
    */
    wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
    wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
    connectToWifi();

    mqttClient.onConnect(onMqttConnect);
    mqttClient.onDisconnect(onMqttDisconnect);
    mqttClient.onSubscribe(onMqttSubscribe);
    mqttClient.onUnsubscribe(onMqttUnsubscribe);
    mqttClient.onMessage(onMqttMessage);
    mqttClient.onPublish(onMqttPublish);
    mqttClient.setServer(MQTT_HOST, MQTT_PORT);

    setnewnetwork();                                                        // This is instance for OTA. Please don't delete it whatever your new algorithm is
    
  }
}

void loop() {

  if(stock){
    if(startingstock && (millis() - osstarttime > (timetoreboot*1000)))
        {
          ESP.restart();
        }
  }
  else
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      // Save the last time a new reading was published
      int n = random();
      computedEV(intseed, prime, qprime, n, m);
    }
  }
}