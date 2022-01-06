/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 2/1/2021				*************/
/*********** Version	: V01					*************/
/************************************************************/

#include "MATH_macros.h"
#include "STD_types.h"

#include "gpio.h"
#include "nvic.h"
#include "exti.h"

unsigned char counter = 0;

void EXTI0_IRQHandler(void){
	EXTI_getPendingBit(0);	/* reset the flag */
	GPIO_togglePin('B', P0);
}

int main(void) {
	/* initiate the pins */
	GPIO_Init('A', P0 , INPUT, PUSH_PULL, PULL_UP);
	GPIO_Init('B', P0 , OUTPUT, PUSH_PULL, NO_PULLING);

	/* set EXTI0 interrupt*/
	EXTI_enableInterruptChannel(0, FALLING_EDGE, PA);		/* EXTI0, falling edge triggering activated in PA0 */

	/* enable EXTI0 interrupt in NVIC */
	NVIC_voidEnableInterrupt(_EXTI0_VECTOR_IRQ);

  while (1) {}

  return 0;
}
