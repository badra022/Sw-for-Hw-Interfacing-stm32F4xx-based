#include "GPIO.h"
#include "stm32f401xc.h"
#include "stm32f401cc_interface.h"

void set_RGB(unsigned char value){		/* value from 0 to 7 */
	for(unsigned char i = 5; i < 8; i++){
		GPIO_WritePin('B', i, value & 1);
		value >>= 1;
	}
}

int main(void) {
	GPIO_Init('B', 5 , OUTPUT, PUSH_PULL, NO_PULLING);
	GPIO_Init('B', 6 , OUTPUT, PUSH_PULL, NO_PULLING);
	GPIO_Init('B', 7 , OUTPUT, PUSH_PULL, NO_PULLING);
	GPIO_Init('B', 3, INPUT, PUSH_PULL, PULL_UP);

	unsigned char rgb_value = 1;
	set_RGB(0);
  while (1) {

	  while(GPIO_ReadPin('B', 3)){}

	  for(int i = 0; i < 50000; i++){}

	  if(!GPIO_ReadPin('B', 3)){
		  set_RGB(rgb_value++);
		  while(!GPIO_ReadPin('B', 3)){}
	  }
  }
  return 0;
}
