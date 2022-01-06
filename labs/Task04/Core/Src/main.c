/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 2/1/2021				*************/
/*********** Version	: V01					*************/
/************************************************************/

#include "MATH_macros.h"
#include "STD_types.h"

#include "gpio.h"
#include "svn_segment.h"
#include "nvic.h"
#include "exti.h"

unsigned char counter = 0;

void EXTI0_IRQHandler(void){
	__asm__("CPSID i");		/* disable interrupts */
	EXTI_getPendingBit(0);	/* reset the flag */

	counter++;

	__asm__("CPSIE i");		/* enable interrupts */
}

void EXTI1_IRQHandler(void){
	__asm__("CPSID i");		/* disable interrupts */
	EXTI_getPendingBit(1);	/* reset the flag */

	counter--;

	__asm__("CPSIE i");		/* enable interrupts */
}

int main(void) {

	/* initiate the seven segment pins */
	svn_segment_init();

	/* initiate the buttons */
	GPIO_Init('B', P0 , INPUT, PUSH_PULL, PULL_UP);
	GPIO_Init('B', P1 , INPUT, PUSH_PULL, PULL_UP);

	/* set EXTI0 and EXTI1 interrupts*/
	EXTI_enableInterruptChannel(0, FALLING_EDGE, PB);		/* EXTI0, falling edge triggering activated in PB0 */
	EXTI_enableInterruptChannel(1, FALLING_EDGE, PB);		/* EXTI1, falling edge triggering activated in PB1 */

	/* enable EXTI0 and EXTI1 interrupts in NVIC */
	NVIC_voidEnableInterrupt(_EXTI0_VECTOR_IRQ);
	NVIC_voidEnableInterrupt(_EXTI1_VECTOR_IRQ);

  while (1) {
	  if(counter > 9){
		  counter = 0;
	  }
	  svn_segment_write(counter);
  }
  return 0;
}
