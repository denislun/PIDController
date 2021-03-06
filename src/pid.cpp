#include <Arduino.h>
#include <PID_v1.h>
#include <PID_AutoTune_v0.h>
#include "pid.h"
#include "temperature.h"
#include "encoder.h"
#include "relay.h"
#include "settings.h"
#include "display.h"

#define OFF    "OFF    "
#define ON     "RUNNING"
#define TUNING "TUNING "

double setPoint = 100;
double output;
double Kp=2, Ki=5, Kd=1;
unsigned int windowSize = 5000;
unsigned long windowStartTime = millis();
PID pid(&currentTemperature, &output, &setPoint, Kp, Ki, Kd, DIRECT);

PID_ATune autoTuner(&currentTemperature, &output);
double autoTuneStep = 500;
double autoTuneNoise = 1;
int autoTuneLookback = 20;
bool autoTuning = false;

void pidStartAutoTune() {
  autoTuner.SetNoiseBand(autoTuneNoise);
  autoTuner.SetOutputStep(autoTuneStep);
  autoTuner.SetLookbackSec(autoTuneLookback);
  autoTuning = true;
}

void pidFinishAutotune() {
  autoTuning = false;

  // Extract the auto-tune calculated parameters
  Kp = autoTuner.GetKp();
  Ki = autoTuner.GetKi();
  Kd = autoTuner.GetKd();

  saveKp(Kp);
  saveKi(Ki);
  saveKd(Kd);

  pid.SetTunings(Kp, Ki, Kd);
  pid.SetMode(MANUAL);
}

void setupPID() {
  Kp = loadKp();
  Ki = loadKi();
  Kd = loadKd();

  pid.SetOutputLimits(0, windowSize);
  pid.SetMode(MANUAL);
  pid.SetControllerDirection(DIRECT);

  displayStatus(OFF);
  displayTargetTemperature(setPoint);
}

void loopPID() {
  if(encoderButtonWasPressed) {
    if(pid.GetMode() == AUTOMATIC) {
      // Turn off
      pid.SetMode(MANUAL);
      setRelay(false);
      displayStatus(OFF);
    }
    else {
      // Turn on
      pid.SetMode(AUTOMATIC);
      displayStatus(ON);
    }
  } else if(encoderButtonWasHeld) {
    // Autotune
    pidStartAutoTune();
    displayStatus(TUNING);
  }

  if(autoTuning) {
    if(autoTuner.Runtime()) {
      pidFinishAutotune();
      displayStatus(OFF);
    }
    else {
      setRelay(output < (millis() - windowStartTime));
    }
  }
  else if(pid.GetMode() == AUTOMATIC) {
    pid.Compute();
    setRelay(output < (millis() - windowStartTime));
  }

  encoderButtonWasHeld = false;
  encoderButtonWasPressed = false;
}
