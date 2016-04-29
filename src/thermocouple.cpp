#include <Arduino.h>
#include "pins.h"
#include "thermocouple.h"
#include "display.h"

MAX6675 thermocouple(SPI_CLK, THERMOCOUPLE_CS, SPI_MISO);
double currentTemperature;

void setupThermocouple() {
  delay(500);
  currentTemperature = thermocouple.readCelsius();
}

void loopThermocouple() {
  double temp = thermocouple.readCelsius();
  if(temp != currentTemperature) {
    currentTemperature = temp;
    displayCurrentTemperature(currentTemperature);
  }
}
