#include <Arduino.h>
#include "encoder.h"
#include "pins.h"
#include "pid.h"
#include "display.h"

#define HOLD_TIME 5000

#define TEMP_MIN 0
#define TEMP_MAX 250

volatile int movement = 0;
volatile bool encoderButtonWasPressed = false;
volatile bool encoderButtonWasHeld = false;
volatile unsigned long encoderButtonPressedAt;

void encoderInterrupt() {
  if(digitalRead(ENCODER_A) && digitalRead(ENCODER_B)) // b is leading
    movement += 1;
  else // a is leading
    movement -= 1;
}

void encoderButtonInterrupt() {
  if(digitalRead(ENCODER_BTN)) {
    if(millis() - encoderButtonPressedAt > HOLD_TIME)
      encoderButtonWasHeld = true;
    else
      encoderButtonWasPressed = true;
  }
  else
    encoderButtonPressedAt = millis();
}

double limitValue(double value, double min, double max) {
  if(value < min)
    return min;
  else if(value > max)
    return max;
  else
    return value;
}

void setupEncoder() {
  pinMode(ENCODER_BTN, INPUT_PULLUP);
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER_B), encoderInterrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_BTN), encoderButtonInterrupt, CHANGE);
}

void loopEncoder() {
  if(movement != 0) {
    setPoint = limitValue(setPoint + movement, TEMP_MIN, TEMP_MAX);
    movement = 0;
    displayTargetTemperature(setPoint);
  }
}
