#include <Arduino.h>
#include <EEPROM.h>
#include "settings.h"

#define KP_ADDRESS 0
#define KI_ADDRESS 8
#define KD_ADDRESS 16

#define KP_DEFAULT 850
#define KI_DEFAULT 0.5
#define KD_DEFAULT 0.1

void write(int address, double value)
{
   byte* p = (byte*)(void*)&value;
   for (unsigned int i = 0; i < sizeof(value); i++)
   {
      EEPROM.write(address++, *p++);
   }
}

double read(int address)
{
   double value = 0.0;
   byte* p = (byte*)(void*)&value;
   for (unsigned int i = 0; i < sizeof(value); i++)
   {
      *p++ = EEPROM.read(address++);
   }
   return value;
}

double loadKp() {
  double val = read(KP_ADDRESS);
  if(isnan(val))
    return KP_DEFAULT;
  else
    return val;
}

double loadKi() {
  double val = read(KI_ADDRESS);
  if(isnan(val))
    return KI_DEFAULT;
  else
    return val;
}

double loadKd() {
  double val = read(KD_ADDRESS);
  if(isnan(val))
    return KD_DEFAULT;
  else
    return val;
}

void saveKp(double val) {
  if(loadKp() != val)
    write(KP_ADDRESS, val);
}

void saveKi(double val) {
  if(loadKi() != val)
    write(KI_ADDRESS, val);
}

void saveKd(double val) {
  if(loadKd() != val)
    write(KD_ADDRESS, val);
}
