#ifndef __PWM_H__
#define __PWM_H__

void PWM_Init(void);
void PWM_SetDuty(uint16_t campare);
void PWM_SetFreq(uint16_t prescaler);

#endif
