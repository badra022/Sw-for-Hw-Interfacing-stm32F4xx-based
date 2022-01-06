#include "stm32f4xx_hal.h"

void delay_sec(void){
	for(int i = 0; i < 1500000; i++){
		__asm__("NOP");
	}
}

int main(void){

	RCC->AHB1ENR |= (1 << 0); /* enable GPIOA clock */
	GPIOA->MODER |= (1 << 0); /* configure PA0 as general purpose output */
	GPIOA->OTYPER &= ~(0 << 0); /* Output push-pull */

	while(1){
		GPIOA->ODR |= (1 << 0);
		delay_sec();
		GPIOA->ODR &= ~(1 << 0);
		delay_sec();
	}
}
