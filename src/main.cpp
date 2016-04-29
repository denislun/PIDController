#include <Arduino.h>
#include "thermocouple.h"
#include "pid.h"
#include "relay.h"
#include "display.h"
#include "encoder.h"

void setup() {
  setupRelay();
  setupEncoder();
  setupThermocouple();
  setupPID();
  setupDisplay();
}

void loop() {
  loopEncoder();
  loopThermocouple();
  loopPID();
  delay(1000);
}
