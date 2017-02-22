#ifndef _DISPLAY_H
#define _DISPLAY_H

extern bool displayNeedsUpdate;

void setupDisplay();
void displayStatus(String);
void displayCurrentTemperature(double);
void displayTargetTemperature(double);
void displayRelayState(bool);
void loopDisplay();

#endif
