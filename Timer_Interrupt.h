#include "stm32f407xx.h"

#pragma once

#define SHORTBUTTONPRESS 125
#define REGULARBUTTONPRESS 375
#define LONGBUTTONPRESS 375

extern int InterruptStatusBit;

void Timer4_Init(void);

void User_Button_Interrupt_Init(void);

void actOnTimer(uint32_t counter);
