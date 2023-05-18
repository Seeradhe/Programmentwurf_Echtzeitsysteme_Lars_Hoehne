#include "stm32f407xx.h"

extern uint8_t CurrentState;

/*
* \brief Runs a single cycle on the statemachine, dependant on the variable CurrentState and the extern variables
*				 depicting the actuators A1 "Leistungsvorgabe", A2 "Regelbetrieb" and A3 "Brennerstart", executed periodically
*				 within the RTOS
*/
void Statemachine(void);
