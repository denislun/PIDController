#ifndef _PID_H
#define _PID_H

extern double setPoint;
extern bool autoTuning;

void setupPID();
void loopPID();

#endif
