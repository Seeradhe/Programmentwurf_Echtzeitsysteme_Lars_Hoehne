#include "main_include.h"

void Setup(void){
	Timer3_Init();
	Timer4_Init();
	Timer5_Init();
	User_Button_Interrupt_Init();
	LED_Init();
}
