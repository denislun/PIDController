#ifndef _ENCODER_H
#define _ENCODER_H

void setupEncoder();
void loopEncoder();

volatile extern bool encoderButtonWasPressed;
volatile extern bool encoderButtonWasHeld;

#endif
