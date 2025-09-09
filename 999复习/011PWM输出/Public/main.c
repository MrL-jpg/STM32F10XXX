#include "stm32f10x.h"                  // Device header
#include "PWM.h"

int main(void){
	OLED_Init();
	PWM_Init();
	OLED_ShowString(1,1,"debug mode:");
	while(1){
		LED_BreathLight();
	}
}
