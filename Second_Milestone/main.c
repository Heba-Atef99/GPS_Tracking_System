#include "GPS_Functions/functions.h"
#include "GPIO/GPIO.h"
#include "Timer/Timer.h"
#include "UART/UART.h"

void SystemInit()
{
	//initalize GPIO
	//init_GPIO_portA();
	init_GPIO_portB();
	init_GPIO_portF();

  init_UART0();
  init_UART7();
}

int main(void)
{
		// To start when switch 2 is ON
	while((GPIO_PORTF_DATA_R & 0x01) ==1){};
		
	while(1)
	{
		//read from gps
		char gps_line [100];
		gps_read(gps_line);
		
		//wait a second
		Systick_Wait_Multiples_1ms(1000);
		
		// to finish when switch 1 in on
		if((GPIO_PORTF_DATA_R & 0X10) ==0)
			break;
	}
}
