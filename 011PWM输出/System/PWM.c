#include "stm32f10x.h"

/*
步骤:
    1、使能定时器和GPIO时钟
    2、配置时基单元
    3、配置CCR
    4、开启时钟(别忘了)
计算相关公式:
    PWM频率     Freq = CK_PSC / (PSC + 1) / (ARR + 1) //频率
    PWM占空比   Duty = CCR / (ARR + 1) //占空比
    PWM分辨率   Reso = 1 / (ARR + 1) //分辨率
*/

void PWM_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    TIM_InternalClockConfig(TIM2);
    TIM_TimeBaseInitTypeDef TimeBase_InitStructure;
    TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TimeBase_InitStructure.TIM_Period = 99;
    TimeBase_InitStructure.TIM_Prescaler = 1439;
    TimeBase_InitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TimeBase_InitStructure);

    TIM_OCInitTypeDef TIM_OCInitSttructure;
    TIM_OCStructInit(&TIM_OCInitSttructure);
    TIM_OCInitSttructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitSttructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitSttructure.TIM_Pulse = 20;
    TIM_OCInitSttructure.TIM_OCPolarity = TIM_OCPolarity_High ;
    TIM_OC1Init(TIM2,&TIM_OCInitSttructure);

    TIM_Cmd(TIM2,ENABLE);
}


