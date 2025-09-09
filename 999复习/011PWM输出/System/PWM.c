#include "PWM.h"

typedef 
    enum{
        OC_UP = 0,
        OC_DN,
        OC_Delay
    }LED_BLStatus;

LED_BLStatus  NowLED = OC_UP;
static uint8_t Delay_Flag = 0;
static uint8_t Delay_Ctrl = 0;

void PWM_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    GPIO_InitTypeDef GPIO_InitStucture;
    GPIO_InitStucture.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStucture.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStucture);
    TIM_InternalClockConfig(TIM2);

    TIM_TimeBaseInitTypeDef TimeBase_InitStucture;
    TimeBase_InitStucture.TIM_ClockDivision = TIM_CKD_DIV1;
    TimeBase_InitStucture.TIM_CounterMode = TIM_CounterMode_Up;
    TimeBase_InitStucture.TIM_Period = 100-1; //arr
    TimeBase_InitStucture.TIM_Prescaler = 720;//psc  
    TimeBase_InitStucture.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TimeBase_InitStucture);

    TIM_OCInitTypeDef OC_InitStucture;
    OC_InitStucture.TIM_OCMode = TIM_OCMode_PWM1; // CNT < CCR 为有效电平，反之
    OC_InitStucture.TIM_OCPolarity = TIM_OCPolarity_High;
    OC_InitStucture.TIM_OutputState = TIM_OutputState_Enable;
    OC_InitStucture.TIM_Pulse =50;
    TIM_OC1Init(TIM2,&OC_InitStucture);
    TIM_Cmd(TIM2,ENABLE);
}

void LED_Delay(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    TIM_InternalClockConfig(TIM6);

    TIM_TimeBaseInitTypeDef TimeBase_InitStucture;
    TimeBase_InitStucture.TIM_ClockDivision = TIM_CKD_DIV2; //36MHz
    TimeBase_InitStucture.TIM_CounterMode = TIM_CounterMode_Up;
    TimeBase_InitStucture.TIM_Period = 40000;
    TimeBase_InitStucture.TIM_Prescaler =36000;   
    TimeBase_InitStucture.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM6, &TimeBase_InitStucture);
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);
    TIM_ITConfig(TIM6, TIM_IT_Update,ENABLE);//中断开

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStucture;
    NVIC_InitStucture.NVIC_IRQChannel = TIM6_IRQn;
    NVIC_InitStucture.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStucture.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStucture.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStucture);

    TIM_Cmd(TIM6,ENABLE);
}

void LED_BreathLight(void){
    static int16_t count = 0;
    static uint8_t Choose = 1;
    OLED_ShowChar(3,8,'U');
    switch (NowLED){
     case OC_UP:{
            count ++;
            if(count >= 100){
                NowLED = OC_DN;
                OLED_ShowChar(3,8,'D');
                count = 100;
            }
            NowLED = OC_Delay;
            Choose = 1;
        }break;       
    case OC_DN:{
            count --;
            if(count <= 0){
                count = 0;
                NowLED = OC_UP;
                OLED_ShowChar(3,8,'U');
            }
            NowLED = OC_Delay;
            Choose = 0;
        }break;
    case OC_Delay:{
        Delay_Ctrl = 1;
        if(Delay_Flag == 1){
            if(Choose == 1){
                NowLED = OC_UP;
            }else{
                NowLED = OC_DN;
            }
            Delay_Ctrl = 0;
            Delay_Flag = 0;
        }break;
    }    
    }
    OLED_ShowNum(2,8,count,8);
    TIM_SetCompare1(TIM2, count);
}

void TIM6_IRQHandler(void){
    if(TIM_GetITStatus(TIM6, TIM_IT_Update)){
        if(Delay_Ctrl == 1){
            Delay_Flag = 1;
        }
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    }
}
