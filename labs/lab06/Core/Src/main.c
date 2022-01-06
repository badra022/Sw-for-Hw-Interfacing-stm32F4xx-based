#include "GPIO.h"
#include "keypad.h"

static unsigned char numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void Keypad_callback(void)
{
	if(Keypad_GetKey() != 0xFF){
	  for(unsigned char i = 0; i < 7; i++){
		  GPIO_WritePin('A', i, (numbers[Keypad_GetKey()] >> i) & 0x01);
	  }
	}
}

void svn_segment_init(void){
	for(unsigned char i = 0; i < 7; i++){
		GPIO_Init('A', i , OUTPUT, PUSH_PULL, NO_PULLING);
	}
}

int main(void) {
	KEYPAD_init();
	Keypad_setCallBack(Keypad_callback);
	svn_segment_init();

  while (1) {

	  Keypad_manage();

  }
  return 0;
}
