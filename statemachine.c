#include "statemachine.h"
#include "Timer_Interrupt.h"
#include "Drivers.h"

static uint8_t CurrentState = 0;
uint8_t InterneLeistungsvorgabe = 0;			// REQ19
static uint8_t HasWaited = 0; 

void Statemachine(void){
	
	switch(CurrentState){
		
		// Grundzustand (Brenner aus)
		case 0:{															// REQ5
			HasWaited = 0;
			if(BrennerstartStatusBit == 1){			// REQ6; REQ7
				CurrentState = 1;
			}
			TIM4->CCR1 = 0;											// REQ4
			break;
		}
		// Vorlueften
		case 1:{
			if(BrennerstartStatusBit != 1){			// REQ20
				CurrentState = 0;
				break;
			}
			set_Pin(GPIOD, 13);									// REQ9
			TIM4->CCR1 = 1000;									// REQ8
			sleep_ms(5000);											// REQ8
			TIM4->CCR1 = 100;										// REQ8; REQ10
			reset_Pin(GPIOD, 13);								// REQ9
			CurrentState = 2;										// REQ8
			break;
		}
		// Zuendstellung
		case 2:{
			if(BrennerstartStatusBit != 1){			// REQ20
				CurrentState = 0;
				break;
			}
			if(HasWaited == 0){									// REQ12
				sleep_ms(3000);
				HasWaited = 1;
			}			
			if(RegelbetriebStatusBit == 1){			// REQ11
				CurrentState = 3;
			}
			break;
		}
		// Regelbetrieb
		case 3:{
			if(BrennerstartStatusBit != 1){			// REQ20
				CurrentState = 0;
				reset_Pin(GPIOD, 14);							// REQ14
				break;
			}
			set_Pin(GPIOD, 14);									// REQ14
			TIM4->CCR1 = InterpoliereInterneLeistungsvorgabe(InterneLeistungsvorgabe);		// REQ13
			break;
		}
		// Fehler --> Gehe zurueck in Grundzustand
		default:{
			CurrentState = 0;
			break;
		}
	}
	
}

uint16_t InterpoliereInterneLeistungsvorgabe(uint8_t PercentageLeistungsvorgabe){
	return (uint16_t)(100 + (PercentageLeistungsvorgabe * 9));												//REQ16
}
