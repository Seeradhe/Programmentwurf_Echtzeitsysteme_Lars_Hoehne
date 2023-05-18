#include "Timer_Interrupt.h"
#include "Drivers.h"
#include "statemachine.h"

#pragma once
/*
* \brief Contains all the required Setups from the different .h files to have a simpler viewport in the
*				 main.c file
*/
void Setup(void);
/*
* \brief Contains all the required Functions to be executed periodically to have a simpler viewport in the
*				 main.c file
*/
__attribute__((noreturn)) void Loop(void);
