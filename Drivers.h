#include "stm32f407xx.h"

/*
*	\brief Toggles a specific Pin on a specific Port on the Microcontroller
*
*	\param[in]	Port	specific port on the microcontroller of which a pin should be toggled, given as a GPIO_TypeDef, e.g. "GPIOD"
* \param[in]	Pin specific pin on a port to toggle, given as a uint8_t
*/
void toggle_Pin(GPIO_TypeDef *Port, uint8_t Pin);
/*
*	\brief Resets a specific Pin on a specific Port on the Microcontroller
*
*	\param[in]	Port	specific port on the microcontroller of which a pin should be reset, given as a GPIO_TypeDef, e.g. "GPIOD"
* \param[in]	Pin specific pin on a port to reset, given as a uint8_t
*/
void set_Pin(GPIO_TypeDef *Port, uint8_t Pin);
/*
*	\brief Sets a specific Pin on a specific Port on the Microcontroller
*
*	\param[in]	Port	specific port on the microcontroller of which a pin should be set, given as a GPIO_TypeDef, e.g. "GPIOD"
* \param[in]	Pin specific pin on a port to set, given as a uint8_t
*/
void reset_Pin(GPIO_TypeDef *Port, uint8_t Pin);
/*
*	\brief Initializes the LEDs on GPIOD on Pins 13, 14 and 15 to be used as outputs
*
* \Signal S1, S2, S3, S4
*/
void LED_Init(void);
