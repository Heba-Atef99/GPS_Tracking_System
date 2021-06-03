#include "stdint.h"
#include "GPIO/GPIO.h"
#include "Timer/Timer.h"


void SystemInit()
{
	//initalize GPIO
	init_GPIO_portA();
	init_GPIO_portB();
	init_GPIO_portF();
	
	
}
	
int main()
{
}
