#include "stm32f10x.h"

void IC_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStucture;
    GPIO_InitStucture.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStucture.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStucture);

    TIM_InternalClockConfig(TIM3);

    TIM_TimeBaseInitTypeDef TimeBase_InitStucture;
    TimeBase_InitStucture.TIM_ClockDivision = TIM_CKD_DIV1;
    TimeBase_InitStucture.TIM_CounterMode = TIM_CounterMode_Up;
    TimeBase_InitStucture.TIM_Period = 65535;
    TimeBase_InitStucture.TIM_Prescaler = 72 -1; //1000 000
    TimeBase_InitStucture.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3,&TimeBase_InitStucture);

    TIM_ICInitTypeDef IC_InitStucture;
    IC_InitStucture.TIM_Channel = TIM_Channel_1;
    IC_InitStucture.TIM_ICFilter = 0x00;
    IC_InitStucture.TIM_ICPolarity = TIM_ICPolarity_Rising;
    IC_InitStucture.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    IC_InitStucture.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM3, &IC_InitStucture);

    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);

    TIM_Cmd(TIM3,ENABLE);
}

uint16_t IC_GetFreq(void){
    return 1000000/((TIM_GetCapture1(TIM3)) + 1);
}

