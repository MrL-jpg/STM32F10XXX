#include "stm32f10x.h"

void Encoder_Init(void){

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    GPIO_InitTypeDef GPIO_InitStucture;
    GPIO_InitStucture.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStucture.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStucture);

    TIM_TimeBaseInitTypeDef TimeBase_InitStucture;
    TimeBase_InitStucture.TIM_ClockDivision = TIM_CKD_DIV1;
    TimeBase_InitStucture.TIM_Period = 65535;
    TimeBase_InitStucture.TIM_Prescaler = 0;
    TimeBase_InitStucture.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TimeBase_InitStucture);

    TIM_ICInitTypeDef IC_InitStucture;
    TIM_ICStructInit(&IC_InitStucture);
    IC_InitStucture.TIM_Channel = TIM_Channel_1;
    IC_InitStucture.TIM_ICFilter = 0x0F;
    TIM_ICInit(TIM2,&IC_InitStucture);
    IC_InitStucture.TIM_Channel = TIM_Channel_2;
    IC_InitStucture.TIM_ICFilter = 0x0F;
    TIM_ICInit(TIM2,&IC_InitStucture);    

    TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

    TIM_Cmd(TIM2,ENABLE);

} 

int16_t GetEncoder(void){
    return TIM_GetCounter(TIM2);
}
