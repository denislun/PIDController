#include <Arduino.h>
#include "relay.h"
#include "pid.h"
#include "pins.h"
#include "display.h"

int relayState = 0;

void setupRelay() {
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
}

void setRelay(bool state) {
  if(state && relayState == LOW) {
    digitalWrite(RELAY, relayState = HIGH);
    displayRelayState(true);
  }
  else if(relayState == HIGH){
    digitalWrite(RELAY, relayState = LOW);
    displayRelayState(false);
  }
}
