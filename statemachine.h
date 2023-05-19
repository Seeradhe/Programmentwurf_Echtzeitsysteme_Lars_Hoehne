#include "stm32f407xx.h"

extern uint8_t InterneLeistungsvorgabe;		// REQ18

/*
* \brief Runs a single cycle on the statemachine, dependant on the variable CurrentState and the extern variables
*				 depicting the actuators A1 "Leistungsvorgabe", A2 "Regelbetrieb" and A3 "Brennerstart", executed periodically
*				 within the RTOS
*
*	\REQ REQ4 REQ5 REQ6 REQ7 REQ8 REQ9 REQ10 REQ11 REQ12 REQ13 REQ14 REQ20
*/
void Statemachine(void);
/*
*	\brief Calculates the Value for the DutyCycle on the "Soll-Drehzahl FU" Signal on PD12
*
*	\param [in] PercentageLeistungsvorgabe Percentage of the InterneLeistungsvorgabe in the range of 0 to 100 as an uint16_t
*
* \S S1
*
*	\REQ REQ15 REQ16 REQ17
*/
uint16_t InterpoliereInterneLeistungsvorgabe(uint8_t PercentageLeistungsvorgabe);
