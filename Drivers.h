#include "stm32f407xx.h"



void toggle_Pin(GPIO_TypeDef *Port, uint8_t Pin);
void set_Pin(GPIO_TypeDef *Port, uint8_t Pin);
void reset_Pin(GPIO_TypeDef *Port, uint8_t Pin);
void LED_Init(void);
