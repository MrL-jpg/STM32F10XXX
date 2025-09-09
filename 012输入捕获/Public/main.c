#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "InputCampture.h"
#include "OLED.h"
int main(void){
	OLED_Init();
	OLED_ShowString(1,1,"Frequency:");
	PWM_Init();
	IC_Init();
	PWM_SetFreq(102);
	PWM_SetDuty(50);
	while(1){
		OLED_ShowNum(2,4,IC_GetFreq(),5);
	}
}
