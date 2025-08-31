#include "stm32f10x.h"

uint16_t counter;

void Timer_Init(void){
    TIM_InternalClockConfig(TIM2);

    TIM_TimeBaseInitTypeDef TIMBase_initStucture;
    TIMBase_initStucture.TIM_ClockDivision = TIM_CKD_DIV1;
    TIMBase_initStucture.TIM_CounterMode = TIM_CounterMode_Up;
    TIMBase_initStucture.TIM_Period = 10000 - 1;
    TIMBase_initStucture.TIM_Prescaler = 7200 - 1;
    TIMBase_initStucture.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TIMBase_initStucture);

    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStucture;
    NVIC_InitStucture.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStucture.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStucture.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStucture.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStucture);

    TIM_Cmd(TIM2,ENABLE);
}

uint16_t Timer_counter(void){
    return counter;
}

void TIM2_IRQHandler(void){
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET){
        counter ++;
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}
