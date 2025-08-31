#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "stdlib.h"
#include "CountSensor.h"
#include "LED.h"
int main(void){
	CounterInit();
	LED_Init();
	while(1){
		LED_ShowNum(counter());
	}
}
