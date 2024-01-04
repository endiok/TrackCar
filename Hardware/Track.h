#ifndef __TRACK_H
#define __TRACK_H

extern uint8_t PWMR,PWML;
extern float Pitch,Roll,Yaw;

void Track_Init(void);
void Track(void);

#endif
