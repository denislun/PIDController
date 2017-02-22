#include <Arduino.h>
#include "pins.h"
#include "temperature.h"
#include "display.h"

Thermocouple thermocouple = Thermocouple(THERMOCOUPLE_CS);
double currentTemperature = -100;

void setupThermocouple() {
  currentTemperature = thermocouple.readC();
}

void loopThermocouple() {
  double temp = thermocouple.readC();
  if(temp != currentTemperature) {
    currentTemperature = temp;
    displayCurrentTemperature(currentTemperature);
  }
}
