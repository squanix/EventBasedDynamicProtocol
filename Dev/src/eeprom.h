#ifndef _EEPROM_H_
#define _EEPROM_H_

#include <ESP_EEPROM.h>
#include <Arduino.h>

int seed(char *SEED);
int fisheryates(char* R);
String readSeed();
String readR();

#endif