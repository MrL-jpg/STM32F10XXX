#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "InputCampture.h"
#include "OLED.h"
#include "Encoder.h"
int main(void){
	Encoder_Init();
	OLED_Init();
	OLED_ShowString(1,1,"Counter:00000");
	while(1){
		OLED_ShowSignedNum(1,8,GetEncoder(),5);
	}
}
