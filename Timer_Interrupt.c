#include "stm32f407xx.h"
#include "Drivers.h"
#include "Timer_Interrupt.h"
	
	int InterruptStatusBit = 0;
	
	void Timer4_Init(void){
	// Timer4 Init --> used to determine the length of a button press
		RCC->APB1ENR |= 0x4;
	
		TIM4->PSC |= 0x7FFF;
		TIM4->ARR |= 100000;

	}
		
	void User_Button_Interrupt_Init(void){
	// Interrupt Init --> used to listen for the Press of the User Button on the STM32
	EXTI->IMR |= 0x1;
	EXTI->RTSR |= 0x1;
	EXTI->FTSR |= 0x1;
	
	NVIC_EnableIRQ(EXTI0_IRQn);
	}
	
	void actOnTimer(uint32_t counter){

	if(counter> 0 && counter< SHORTBUTTONPRESS){
		// Leistungsvorgabe + 10%, Overflow von 100% auf 0%
		toggle_Pin(GPIOD, 12);
	}
	else if(counter> SHORTBUTTONPRESS && counter< REGULARBUTTONPRESS){
		// toggelt Signal Regelbetrieb
		toggle_Pin(GPIOD, 13);
	}
	else if (counter > LONGBUTTONPRESS){
		// toggelt Signal Brennerstart
		toggle_Pin(GPIOD, 14);
	}
}
	
	void EXTI0_IRQHandler(void){
	NVIC_DisableIRQ(EXTI0_IRQn);
	
	if(InterruptStatusBit == 0){
		TIM4->CR1 |= 0x1;
		InterruptStatusBit = 1;
	}
	else if(InterruptStatusBit == 1 && (GPIOA->IDR & 0x1) == 0){
		TIM4->CR1 &= 0xFFFE;
		actOnTimer(TIM4->CNT);
		TIM4->CNT &= 0;
		InterruptStatusBit = 0;
	}
	for(int i = 0; i < 50000; i++);
	
	EXTI->PR |= 0x1;
	NVIC_EnableIRQ(EXTI0_IRQn);
}
