/************************************************************/
/*********** Author		: Ahmed Mohamed Badra	*************/
/*********** Date		: 24/11/2020			*************/
/*********** Version	: V01					*************/
/************************************************************/

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#define GPIOA_ADDRESS		0x40020000
#define GPIOB_ADDRESS		0x40020400
#define GPIOC_ADDRESS		0x40020800
#define GPIOD_ADDRESS		0x40020C00
#define GPIOE_ADDRESS		0x40021000
#define GPIOH_ADDRESS		0x40021C00

static unsigned int gpio_port[] = {GPIOA_ADDRESS, GPIOB_ADDRESS, GPIOC_ADDRESS, GPIOD_ADDRESS, GPIOE_ADDRESS, GPIOH_ADDRESS};

#define GPIO_REG(PORT_ADDR, REG_OFFSET)		(*(unsigned int*)(PORT_ADDR + REG_OFFSET))

#define RCC_AHB1ENR				GPIO_REG(0x40023800, 0x30)
#define GPIO_MODER(PORT_ID)		GPIO_REG(gpio_port[PORT_ID], 0x00)
#define GPIO_OTYPER(PORT_ID)	GPIO_REG(gpio_port[PORT_ID], 0x04)
#define GPIO_OSPEEDR(PORT_ID)	GPIO_REG(gpio_port[PORT_ID], 0x08)
#define GPIO_PUPDR(PORT_ID)		GPIO_REG(gpio_port[PORT_ID], 0x0C)
#define GPIO_IDR(PORT_ID)		GPIO_REG(gpio_port[PORT_ID], 0x10)
#define GPIO_ODR(PORT_ID)		GPIO_REG(gpio_port[PORT_ID], 0x14)
#define GPIO_BSRR(PORT_ID)		GPIO_REG(gpio_port[PORT_ID], 0x18)
#define GPIO_LCKR(PORT_ID)		GPIO_REG(gpio_port[PORT_ID], 0x1C)
#define GPIO_AFRL(PORT_ID)		GPIO_REG(gpio_port[PORT_ID], 0x20)
#define GPIO_AFRH(PORT_ID)		GPIO_REG(gpio_port[PORT_ID], 0x24)

typedef enum{
	AF0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
}AF_dtype;

//write result
#define OK  ((unsigned char)0)
#define NOK ((unsigned char)1)

//mode types
#define INPUT ((unsigned int)0x00)
#define OUTPUT ((unsigned int)0x01)
#define ALTERNATE_FUN ((unsigned int)0x02)
#define ANALOG ((unsigned int)0x03)

//output modes
#define PUSH_PULL ((unsigned int)0x00)
#define OPEN_DRAIN ((unsigned int)0x01)

#define PULL_UP		((unsigned char)0x01)
#define PULL_DOWN	((unsigned char)0x02)
#define NO_PULLING	((unsigned char)0x00)

void GPIO_Init(char port_id, unsigned int PIN_NO, unsigned int PIN_Dir, unsigned int Default_State, unsigned char Pulling_State);
unsigned char GPIO_WritePin(char port_id, unsigned int PIN_NO, unsigned int Data);
unsigned char GPIO_togglePin(char port_id, unsigned int PIN_NO);
unsigned char GPIO_ReadPin(char port_id, unsigned int PIN_NO);
void GPIO_setAlternateFunction(char port_id, unsigned int PIN_NO, AF_dtype selected_function);



#endif /* INC_GPIO_H_ */
