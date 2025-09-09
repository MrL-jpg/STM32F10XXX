#include "stm32f10x.h"                  // Device header
#include "CountSensor.h"
#include "OLED.h"
#include "Delay.h"

volatile static uint16_t count = 0;

void PWM_1S(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStucture;
	GPIO_InitStucture.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStucture.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStucture);
}

 int main(void){
	PWM_1S();
	OLED_Init();
	CountSensorInit();
	OLED_ShowString(2,1,"count:");
	while(1){
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		Delay_ms(50);
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		Delay_ms(50);		
		OLED_ShowNum(3,6,TIM_GetCounter(TIM2),8);
	}
}

void TIM2_IRQHandler(void){
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){


        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
