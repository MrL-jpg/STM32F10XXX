#include "stm32f10x.h"

void CountSensorInit(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStucture;
    GPIO_InitStucture.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStucture.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStucture);

    TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_Inverted,0x0F);

    TIM_TimeBaseInitTypeDef TimeBase_InitStucture;
    TimeBase_InitStucture.TIM_ClockDivision = TIM_CKD_DIV1;
    TimeBase_InitStucture.TIM_CounterMode = TIM_CounterMode_Up;
    TimeBase_InitStucture.TIM_Period = 65536-1;
    TimeBase_InitStucture.TIM_Prescaler = 0;
    TimeBase_InitStucture.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TimeBase_InitStucture);

    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
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

// void TIM2_IRQHandler(void){
//     if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){

//         count ++;

//         TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//     }
// }
