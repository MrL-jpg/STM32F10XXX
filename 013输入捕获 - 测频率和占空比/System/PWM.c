#include "stm32f10x.h"

#define PWM_TIM_CLK_MHZ 72   // 假设系统时钟为72MHz
#define DEFAULT_ARR 99       // 默认自动重装载值，决定PWM周期和分辨率

void PWM_Init(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_InternalClockConfig(TIM2);

    //使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TimeBase_InitStructure;
    TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TimeBase_InitStructure.TIM_Period = DEFAULT_ARR; // 使用宏定义
    TimeBase_InitStructure.TIM_Prescaler = 1439;     // 初始预分频值，产生500Hz
    TimeBase_InitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TimeBase_InitStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure; // 修正拼写错误
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 20; // 初始占空比约为20%
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);

    // 使能ARR和CCR的预装载寄存器，确保更改平滑生效
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);

    TIM_Cmd(TIM2, ENABLE);
}

/**
 * @brief 设置PWM占空比
 * @param compare: 比较值，范围应在0到ARR（当前为99）之间
 */
void PWM_SetDuty(uint16_t compare) {
    // 边界检查，确保compare不超过ARR
    if (compare > DEFAULT_ARR) {
        compare = DEFAULT_ARR;
    }
    TIM_SetCompare1(TIM2, compare);
}

/**
 * @brief 设置PWM频率（通过调整预分频器PSC，保持ARR不变）
 * @param fre: 目标频率（Hz）
 * @note 由于ARR固定，改变频率会直接影响占空比分辨率。
 *        调用此函数后，可能需要重新设置占空比。
 */
void PWM_SetFreq(uint32_t fre) { // 使用uint32_t以防频率值过大
    // Fpwm = Fclk / ((PSC+1) * (ARR+1)) => PSC+1 = Fclk / (Fpwm * (ARR+1))
    // PSC = Fclk / (Fpwm * (ARR+1)) - 1
    uint32_t clock_in_hz = PWM_TIM_CLK_MHZ * 1000000;
    uint32_t arr_plus_one = DEFAULT_ARR + 1;
    uint32_t temp = clock_in_hz / (fre * arr_plus_one);

    // 检查计算出的PSC值是否在16位寄存器有效范围内（0-65535）
    if (temp == 0 || temp > 65536) {
        // 频率值不合理，无法设置，可在此添加错误处理（如设置默认值）
        return;
    }
    uint16_t psc_value = (uint16_t)(temp - 1);

    TIM_PrescalerConfig(TIM2, psc_value, TIM_PSCReloadMode_Update);
}
