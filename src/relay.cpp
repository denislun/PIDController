#include <Arduino.h>
#include "relay.h"
#include "pid.h"
#include "pins.h"
#include "display.h"

bool relayState = HIGH; // So we can immediately set it low

void setupRelay() {
  pinMode(RELAY, OUTPUT);
  setRelay(false);
}

void setRelay(bool state) {
  // NOOP if the relay is already in the given state
  if(state == relayState)
    return;

  if(state) {
    digitalWrite(RELAY, relayState = HIGH);
    displayRelayState(true);
  } else {
    digitalWrite(RELAY, relayState = LOW);
    displayRelayState(false);
  }
}
