#include "main_include.h"

void Setup(void){
	Timer2_Init();
	Timer3_Init();
	Timer4_Init();
	Timer5_Init();
	User_Button_Interrupt_Init();
	LED_Init();
	sleep_ms(100);
}

__attribute__((noreturn)) void Loop(void){
	while(1){
		Statemachine();
		sleep_ms(100);
	}
}
