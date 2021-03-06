#include <Arduino.h>
#include <SPI.h>

#include "temperature.h"
#include "pid.h"
#include "relay.h"
#include "display.h"
#include "encoder.h"

void setup() {
  SPI.begin();
  setupDisplay();
  setupRelay();
  setupEncoder();
  setupThermocouple();
  setupPID();
}

void loop() {
  loopEncoder();
  loopThermocouple();
  loopPID();
  loopDisplay();
}
