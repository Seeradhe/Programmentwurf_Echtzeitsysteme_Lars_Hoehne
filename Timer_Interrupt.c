#include "stm32f407xx.h"
#include "Drivers.h"
#include "Timer_Interrupt.h"
#include "statemachine.h"
	
	uint8_t InterruptStatusBit = 0;
	uint8_t RegelbetriebStatusBit = 0;
	uint8_t BrennerstartStatusBit = 0;
	uint8_t SleepStatusBit = 0;
	
	void Timer2_Init(void){
		RCC->APB1ENR |= 0x1;
		
		TIM2->PSC = 16000;
		TIM2->ARR = 0xFFFF;
	}
	void Timer3_Init(void){
		RCC->APB1ENR |= 0x2; // Clock enable
		
		TIM3->PSC = 0x3E80;
		TIM3->ARR = 500;
		
		TIM3->DIER |= 0x0001;
		
		TIM3->CR1 |= 0x1;
		NVIC_EnableIRQ(TIM3_IRQn);
	}
	
	void Timer4_Init(void){
		RCC->APB1ENR |= 0x4;
	
		TIM4->PSC = 160;		// every increment in the cnt register is 100 us
		TIM4->ARR = 1000;			// 10 ms Period

		/*
			The following 4 lines implement the basic PWM functionality, and determine the PWM mode,
			the direction of counting, which channel of the timer is used for comparison and the DutyCycle
			for more information look up 18.3.9 "PWM Mode" in the reference manual for the STM32F407VGT6 on
			page 610
		*/
		TIM4->CCMR1 |= 0x0060;
		TIM4->CCR1 = 0;
		TIM4->CCER |= 0x0001;
		TIM4->CR1 |= 0x0080;
		
		TIM4->EGR |= 0x0001;	// bit to transfer the configuration of the previous lines of code into the shadow registers
		
		TIM4->CR1 |= 0x0001;	// start the timer to enable the PWM signal
	}
		
	void Timer5_Init(void){
		// Timer 5 Init --> used to determine how long the button was pressed to determine the different input signals
		RCC->APB1ENR |= 0x8;
	
		TIM5->PSC = 0x3E80;		// every increment in the cnt register is a ms
		TIM5->ARR = 100000;		// the maximum length of a button press (100s) before the counter resets
	}
		
	void User_Button_Interrupt_Init(void){
	// Interrupt Init --> used to listen for the Press of the User Button on the STM32
	EXTI->IMR |= 0x1;				// enable the interrupt on line 0
	EXTI->RTSR |= 0x1;			// enable falling edge interrupt detection for line 0
	EXTI->FTSR |= 0x1;			// enable rising edge interrupt detection for line 0
	
	NVIC_EnableIRQ(EXTI0_IRQn);		// enable the Interrupt on line 0
	}
	
	void ButtonInputAction(uint32_t msButtonPressLength){

	if(msButtonPressLength> 0 && msButtonPressLength< SHORTBUTTONPRESS){
		// Leistungsvorgabe + 10%, Overflow von 100% auf 0%
		if(InterneLeistungsvorgabe == 100){
			InterneLeistungsvorgabe = 0;
		}
		else{
			InterneLeistungsvorgabe += 10;
		}
	}
	else if(msButtonPressLength> SHORTBUTTONPRESS && msButtonPressLength< REGULARBUTTONPRESS){
		// toggelt Signal Regelbetrieb
		if(RegelbetriebStatusBit == 0){
			RegelbetriebStatusBit = 1;
		}
		else{
			RegelbetriebStatusBit = 0;
		}
	}
	else if (msButtonPressLength > LONGBUTTONPRESS){
		// toggelt Signal Brennerstart
		if(BrennerstartStatusBit == 0){
			BrennerstartStatusBit = 1;
		}
		else{
			BrennerstartStatusBit = 0;
		}
	}
}
	
void sleep_ms(uint16_t msDuration){
	TIM2->CR1 |= 0x1;
	do{
	}while(TIM2->CNT < msDuration);
	
	TIM2->CR1 &= 0xFFFE;
	TIM2->CNT = 0;
}

/*
	Pre-Processor directive removes the warning for the IRQHandlers that exists because of the
	initial decleration as weak --> warnings are not an issue but a result of the code structure
	within Keil and can not lead to an error
*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
	void TIM3_IRQHandler(void){
		// toggles the Watchdog Signal every 500ms
		toggle_Pin(GPIOD, 15);
		TIM3->SR &= 0xFFFE;
	}

	void EXTI0_IRQHandler(void){
		// Button interrupt
	NVIC_DisableIRQ(EXTI0_IRQn);
	
	if(InterruptStatusBit == 0){
		TIM5->CR1 |= 0x1;
		InterruptStatusBit = 1;
	}
	else{
		TIM5->CR1 &= 0xFFFE;
		ButtonInputAction(TIM5->CNT);
		TIM5->CNT &= 0;
		InterruptStatusBit = 0;
	}
	for(int i = 0; i < 10000; i++);
	
	EXTI->PR |= 0x1;
	NVIC_EnableIRQ(EXTI0_IRQn);
}
	
#pragma GCC diagnostic pop
