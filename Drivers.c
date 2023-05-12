#pragma once

#include "Drivers.h"

void toggle_Pin(GPIO_TypeDef *Port, uint8_t Pin){
	if((Port->ODR & (0x1 << Pin)) > 1){
		Port->BSRR |= (0x1 << (Pin + 16));
	}
	else{
		Port->BSRR |= (0x1 << Pin);
	}
}
void set_Pin(GPIO_TypeDef *Port, uint8_t Pin){
	Port->BSRR |= (0x1 << Pin);
}
void reset_Pin(GPIO_TypeDef *Port, uint8_t Pin){
	Port->BSRR |= (0x1 << (Pin + 16));
}
void LED_Init(void){
	// LED Init
	RCC->AHB1ENR |= 0x8;
	
	GPIOD->MODER |= 0x55000000;
	
	GPIOD->BSRR |= 0xF000;
}
