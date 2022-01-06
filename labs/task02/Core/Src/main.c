/*********************************************************
 * Author: Ahmed mohamed mohamed mohamed
 * section: 1
 * BN: 07
 * Task: 02
 **********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

int main(void)
{


	RCC->AHB1ENR |= (0x2 << 0);	/* enable GPIOB clock */
	GPIOB->MODER &= ~(0x11 << 6); /* pin 3 is input mode */
	GPIOB->MODER |= (0x01 << 10); /* pin 5 is output mode */
	GPIOB->MODER |= (0x01 << 12);	/* pin 6 is output mode */
	GPIOB->MODER |= (0x01 << 14);	/* pin 7 is output mode */

	GPIOB->OTYPER &= ~((1 << 5)|(1 << 6)|(1 << 7)); // port B 5,6and 7 are push pull

	GPIOB->PUPDR |= (1 << 6) ;  /* pin 3 button set as PULL UP */
	GPIOB->ODR = (1 << 5);	/* init the RGB to red color */

  while (1)
  {
	   while ((GPIOB->IDR & (1 << 3)) != 0); /* if the button not pressed, don't proceed */

	   for(int i=  0; i < 70000; i++){		/*	 delay in milliseconds for debouncing */
		   __asm__("NOP");
	   }
	   if((GPIOB->IDR & (1 << 3)) == 0){
		   switch  ( GPIOB->ODR >> 5  )
		   {
		   case  0x1 :
			   GPIOB->ODR = (0x2 << 5);
			   break ;
		   case  0x2 :
			   GPIOB->ODR = (0x3 << 5);
					   break ;
		   case  0x3 :
			   GPIOB->ODR = (0x4 << 5);
					   break ;
		   case  0x4 :
			   GPIOB->ODR = (0x5 << 5);
					   break ;
		   case  0x5 :
			   GPIOB->ODR = (0x6 << 5);
					   break ;
		   case  0x6 :
			   GPIOB->ODR = (0x7 << 5);
					   break ;
		   case  0x7 :
			   GPIOB->ODR = (0x0 << 5);
					   break ;
		   case  0x0 :
			   GPIOB->ODR = (0x1 << 5);
					   break ;
		   }
		   while ((GPIOB->IDR & (1 << 3)) == 0); /* if the button still pressed, don't proceed */
	   }

  }

  return 0;
  }
