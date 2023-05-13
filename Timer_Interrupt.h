#include "stm32f407xx.h"

#define SHORTBUTTONPRESS 500
#define REGULARBUTTONPRESS 1500
#define LONGBUTTONPRESS 1500

extern uint8_t InterruptStatusBit;
extern uint8_t RegelbetriebStatusBit;
extern uint8_t BrennerstartStatusBit;

/*
*	\brief Init function that sets basic registers for the Timer 3, Timer 3 is used to control the Watchdog Timer
*/
void Timer3_Init(void);
/*
*	\brief Init function that sets basic registers for the Timer 4, Timer 4 is used to control the Signal "Soll-Drehzahl"
*/
void Timer4_Init(void);
/*
*	\brief Init function that sets basic registers for the Timer 5, Timer 5 is used to determine the length of a button press on PA0
*/
void Timer5_Init(void);
/*
*	\brief Init function that sets up the registers for the Interrupt on PA0
*/
void User_Button_Interrupt_Init(void);
/*
*	\brief Function that gets called within the button interrupt function after a falling edge to determine the action
*				 after a button press of a given length
*
* \param msButtonPressLength length of the button press in ms - though the duration is determined by the timer setup
*/
void ButtonInputAction(uint32_t msButtonPressLength);
