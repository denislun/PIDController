#include "pins.h"
#include "max6675.h"

#ifndef _THERMOCOUPLE_H
#define _THERMOCOUPLE_H

extern double currentTemperature;

void setupThermocouple();
void loopThermocouple();

#endif
