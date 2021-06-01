#include "Timer.h"

void init_timer (void)
{
	// disable the timer during setup
	NVIC_ST_CTRL_R=0;
	//reset the reload with the max value
	NVIC_ST_RELOAD_R=0x00FFFFFF;
	//clear the current reg
	NVIC_ST_CURRENT_R=0;
	// enable the clock of the processor 
	NVIC_ST_CTRL_R=0x05;
}
//delay function

void delay(uint32_t time)
{
	while(time)
	{
		time--;
	}
}