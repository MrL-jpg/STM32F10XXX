#include "stm32f10x.h"

uint16_t counterNum;

void CounterInit(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

    GPIO_InitTypeDef GPIO_InitStucture;
    GPIO_InitStucture.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStucture.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStucture);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);//映射GPIO到EXTI

    EXTI_InitTypeDef EXTI_InitStucture;
    EXTI_InitStucture.EXTI_Line = EXTI_Line0;
    EXTI_InitStucture.EXTI_LineCmd = ENABLE;
    EXTI_InitStucture.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStucture.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStucture);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStucture;
    NVIC_InitStucture.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStucture.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStucture.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStucture.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStucture);
}

uint16_t counter(void)
{
    return counterNum;
}
void EXTI0_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line0) == SET){

        counterNum ++;
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
