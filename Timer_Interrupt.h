#include "stm32f407xx.h"

#define SHORTBUTTONPRESS 500
#define REGULARBUTTONPRESS 1500
#define LONGBUTTONPRESS 1500

extern uint8_t InterruptStatusBit;
extern uint8_t RegelbetriebStatusBit;
extern uint8_t BrennerstartStatusBit;
extern uint8_t SleepStatusBit;
/*
*	\brief Init function that sets basic registers for the Timer 2, Timer 2 is used to put a function to sleep for a set amount of ms
*/
void Timer2_Init(void);
/*
*	\brief Init function that sets basic registers for the Timer 3, Timer 3 is used to control the Watchdog Timer
*
* \REQ REQ22 REQ21
*
* \Signal S4
*/
void Timer3_Init(void);
/*
*	\brief Init function that sets basic registers for the Timer 4, Timer 4 is used to control the Signal "Soll-Drehzahl" with an accuracy of +/- 100us
*
* \REQ REQ1
*
* \Signal S1
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
*
* \Actuator A1, A2, A3
*/
void ButtonInputAction(uint32_t msButtonPressLength);
/*
*	\brief Function to implement a delay for a given time
*
* \param msDuration Duration for the time to sleep in ms, the maximum lenght is 6553 ms
*/
void sleep_ms(uint16_t msDuration);
