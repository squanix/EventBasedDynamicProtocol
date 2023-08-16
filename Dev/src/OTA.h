#ifndef _OTA_H_
#define _OTA_H_

#if defined(ESP8266)
    #include <ESP8266WiFi.h>
    #include <ESPAsyncTCP.h>
#elif defined(ESP32)
    #include <WiFi.h>
    #include <AsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>

void setnewnetwork();

const char index_html[] PROGMEM = R"rawliteral(
    <!DOCTYPE HTML><html>
        <head>
            <title>Smart Light Controller</title>
            <meta name="viewport" content="width=device-width, initial-scale=1">
        </head>
        <body>
            <h1 style="font-size:300%;text-align:center;">CIMA Device</h1>
        </body>
    </html>)rawliteral";


#endif