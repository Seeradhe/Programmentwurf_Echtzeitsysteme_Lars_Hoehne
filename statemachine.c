#include "statemachine.h"
#include "Timer_Interrupt.h"
#include "Drivers.h"

uint8_t CurrentState = 0;

void Statemachine(void){
	
	switch(CurrentState){
		
		// Grundzustand (Brenner aus)
		case 0:{
			if(BrennerstartStatusBit == 1){
				CurrentState = 1;
			}
			break;
		}
		// Vorlueften
		case 1:{
			set_Pin(GPIOD, 13);
			// wait 5 seconds
			reset_Pin(GPIOD, 13);
			CurrentState = 2;
			break;
		}
		// Zuendstellung
		case 2:{
			// mindestens 3s warten
			if(RegelbetriebStatusBit == 1){
				CurrentState = 3;
			}
			break;
		}
		// Regelbetrieb
		case 3:{
			
			break;
		}
		// Fehler --> Gehe zurueck in Grundzustand
		default:{
			CurrentState = 0;
			break;
		}
	}
	
}
