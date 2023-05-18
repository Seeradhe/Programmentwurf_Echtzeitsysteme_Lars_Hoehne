#include "stm32f407xx.h"

//extern uint8_t CurrentState;
extern uint8_t InterneLeistungsvorgabe;

/*
* \brief Runs a single cycle on the statemachine, dependant on the variable CurrentState and the extern variables
*				 depicting the actuators A1 "Leistungsvorgabe", A2 "Regelbetrieb" and A3 "Brennerstart", executed periodically
*				 within the RTOS
*/
void Statemachine(void);
uint16_t InterpoliereInterneLeistungsvorgabe(uint16_t Value);
