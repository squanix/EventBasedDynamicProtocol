#include "OTA.h"
#include "common.h"
#include <AsyncElegantOTA.h>

AsyncElegantOtaClass AsyncElegantOTAEEPROM;
AsyncWebServer serverstock(80);

void setnewnetwork()
{
    AsyncElegantOTAEEPROM.setID(ssidStock.c_str());
    AsyncElegantOTAEEPROM.begin(&serverstock);
    serverstock.begin();  
}