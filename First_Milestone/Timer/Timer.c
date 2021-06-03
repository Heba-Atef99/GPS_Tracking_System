#include "Timer.h"
void Systick_Wait_1ms ()
{
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 16000-1;
	NVIC_ST_CURRENT_R=0;
	NVIC_ST_CTRL_R = 0x05;
	while((NVIC_ST_CTRL_R & 0x00010000)==0){}
}	
void Systick_Wait_Multiples_1ms(uint32_t time)
{
	uint32_t i;
	for(i=0;i<time;i++)
	{
		Systick_Wait_1ms();
	}
}