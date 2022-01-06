/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 2/1/2021				*************/
/*********** Version	: V01					*************/
/************************************************************/
#include "MATH_macros.h"
#include "STD_types.h"

#include "svn_segment.h"
#include "gpio.h"


static unsigned char numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void svn_segment_write(unsigned char number){
  for(unsigned char i = 0; i < 7; i++){
	  GPIO_WritePin('A', i, (numbers[number] >> i) & 0x01);
  }
  for(int i = 0; i < 20000; i++);
}

void svn_segment_init(void){
	for(unsigned char i = 0; i < 7; i++){
		GPIO_Init('A', i , OUTPUT, PUSH_PULL, NO_PULLING);
	}
}
