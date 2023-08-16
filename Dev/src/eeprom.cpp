#include <string.h>
#include "eeprom.h"
#include "common.h"

int seed(char *SEED)
{   
    EEPROM.begin(256);
    if(strlen(SEED) <= 31)
    {   
        uint8_t tmp = 0 ;
        for (uint8_t i = 0; i < strlen(SEED) ; ++i)     // from 0 to 30. There are 31 chars
        {
            EEPROM.put(i, SEED[i]);
            tmp = i;
        }
        EEPROM.put(tmp+1,"*");                          // in array 31
        return EEPROM.commit();
    }
    return false;
}

int fisheryates(char* R)
{
    EEPROM.begin(256);
    if( strlen(R) <= 31)
    {
        uint8_t tmp = 0;
        uint8_t pos = 0;
        for (uint8_t i = 32; i < (strlen(R) + 32) ; ++i)     // from 32 to 62. There are 32 chars
        {
            EEPROM.put(i, R[tmp]);
            tmp++;
            pos = i;
        }
        EEPROM.put(pos+1,"*");                          // in array 63
        return EEPROM.commit();
    }
    return false;
}

String readSeed()
{
    EEPROM.begin(256);
    String seed;
    char tmp;
    for (uint8_t i = 0; i <= 31; ++i)        // from 0 to 31. There are 32 char
    {
        EEPROM.get(i, tmp);
        if(tmp != '*'){
            seed += tmp;
        }
        else break;
    }
    return seed;
}

String readR()
{
    EEPROM.begin(256);
    String R;
    char tmp;
    for (uint8_t i = 32; i <= 63; ++i)       // from 32 to 63. There are 32 char
    {
        EEPROM.get(i, tmp);
        if(tmp != '*'){
            R += tmp;
        }
        else break;
    }
    return R;
}