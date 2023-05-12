#include "main_include.h"

void Setup(void){
	Timer4_Init();
	User_Button_Interrupt_Init();
	LED_Init();
}
