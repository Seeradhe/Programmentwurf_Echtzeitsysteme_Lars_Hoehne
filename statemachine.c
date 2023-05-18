#include "statemachine.h"
#include "Timer_Interrupt.h"
#include "Drivers.h"

static uint8_t CurrentState = 0;
uint8_t InterneLeistungsvorgabe = 0;
static uint8_t HasWaited = 0; 

void Statemachine(void){
	
	switch(CurrentState){
		
		// Grundzustand (Brenner aus)
		case 0:{
			HasWaited = 0;
			if(BrennerstartStatusBit == 1){
				CurrentState = 1;
			}
			TIM4->CCR1 = 0;
			break;
		}
		// Vorlueften
		case 1:{
			if(BrennerstartStatusBit != 1){
				CurrentState = 0;
				break;
			}
			set_Pin(GPIOD, 13);
			TIM4->CCR1 = 1000;
			sleep_ms(5000);
			//for(int i = 0; i < 5000000; i++);
			TIM4->CCR1 = 100;
			reset_Pin(GPIOD, 13);
			CurrentState = 2;
			break;
		}
		// Zuendstellung
		case 2:{
			if(BrennerstartStatusBit != 1){
				CurrentState = 0;
				break;
			}
			if(HasWaited == 0){
				sleep_ms(3000);
				HasWaited = 1;
			}			
			if(RegelbetriebStatusBit == 1){
				CurrentState = 3;
			}
			break;
		}
		// Regelbetrieb
		case 3:{
			if(BrennerstartStatusBit != 1){
				CurrentState = 0;
				reset_Pin(GPIOD, 14);
				break;
			}
			set_Pin(GPIOD, 14);
			TIM4->CCR1 = InterpoliereInterneLeistungsvorgabe(InterneLeistungsvorgabe);
			break;
		}
		// Fehler --> Gehe zurueck in Grundzustand
		default:{
			CurrentState = 0;
			break;
		}
	}
	
}

uint16_t InterpoliereInterneLeistungsvorgabe(uint16_t Value){
	return (uint16_t)(100 + (Value * 9));
}
