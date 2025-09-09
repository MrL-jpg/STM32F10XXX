#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "InputCampture.h"
#include "OLED.h"
int main(void){
	OLED_Init();
	OLED_ShowString(1,1,"Freq:00000Hz");
	OLED_ShowString(2,1,"Duty:00%");
	PWM_Init();
	IC_Init();
	PWM_SetFreq(1000);
	PWM_SetDuty(1);
	while(1){
		OLED_ShowNum(1,6,IC_GetFreq(),5);
		OLED_ShowNum(2,6,IC_GetDuty(),2);
	}
}
