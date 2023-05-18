#include "Drivers.h"

void toggle_Pin(GPIO_TypeDef *Port, uint8_t Pin){
	/*
	First check the status of the Output (ODR) register, if a Pin is set the respective position
	is set it means the Pin is on --> set or reset the Pin depending on the output status
	*/
	if((Port->ODR & (0x1 << Pin)) > 1){
		Port->BSRR |= (0x1 << (Pin + 16));
	}
	else{
		Port->BSRR |= (0x1 << Pin);
	}
}
void set_Pin(GPIO_TypeDef *Port, uint8_t Pin){
	/*
	the first half of the 32bit BSRR register is used to set the pins, 
	the Pin number from 0-15 set the proper pin
	*/
	Port->BSRR |= (0x1 << Pin);
}
void reset_Pin(GPIO_TypeDef *Port, uint8_t Pin){
	/* 
	the second half of the 32bit BSRR register is used to reset the pins, 
	the Pin number from 0-15 bitshifted left with 16 will reset the proper pin
	*/
	Port->BSRR |= (0x1 << (Pin + 16));		
}
void LED_Init(void){
	RCC->AHB1ENR |= 0x8;						// enable the clock to access GPIOD module
	
	GPIOD->MODER |= 0x56000000;			// set the Pins 13, 14 and 15 to output, set Pin 12 to alternate function
	
	GPIOD->AFR[1] |= 0x00020000;		// declare which alternate function P12 should use, --> AF2 --> TIM4
}
