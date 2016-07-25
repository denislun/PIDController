#include <Arduino.h>
#include "pins.h"
#include "temperature.h"
#include "display.h"

Thermocouple thermocouple = Thermocouple(THERMOCOUPLE_CS);
double currentTemperature;

void setupThermocouple() {
  currentTemperature = thermocouple.readC();
}

void loopThermocouple() {
  currentTemperature = thermocouple.readC();
  displayCurrentTemperature(currentTemperature);
}
