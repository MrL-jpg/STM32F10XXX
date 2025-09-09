#include "stm32f10x.h"                  // Device header
#include "delay.h"

void LED_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStucture;
	GPIO_InitStucture.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStucture.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStucture);	
}

int main(void){
	LED_Init();
	while(1){
		GPIO_WriteBit(GPIOA,GPIO_Pin_4, Bit_SET);
		Delay_ms(500);
		GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_RESET);
		Delay_ms(500);
	}
}
