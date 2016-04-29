#ifndef _ENCODER_H
#define _ENCODER_H

void setupEncoder();
void loopEncoder();

bool encoderButtonIsPressed();
extern bool encoderButtonWasPressed;

#endif
