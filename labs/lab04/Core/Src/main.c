#include "GPIO.h"
#include "stm32f401xc.h"
#include "stm32f401cc_interface.h"

int main(void) {
	for(unsigned char i = 0; i < 7; i++){
		GPIO_Init('A', i , OUTPUT, PUSH_PULL);
	}
	unsigned char numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
  while (1) {
	  for(unsigned char num_idx = 0; num_idx < 10; num_idx++){
		  for(unsigned char i = 0; i < 7; i++){
			  GPIO_WritePin('A', i, (numbers[num_idx] >> i) & 0x01);
		  }
		  for(int i = 0; i < 1000000; i++){}
	  }

  }
  return 0;
}
