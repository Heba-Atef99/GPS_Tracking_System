#include "stdint.h"
#include "GPIO/GPIO_init.h"
#include "Timer/Timer_init.h"


void SystemInit()
{
	//initalize GPIO
	init_GPIO_portA();
	init_GPIO_portB();
	init_GPIO_portF();
	
	//initialize Timer
	init_timer();
}
	
int main()
{
}
