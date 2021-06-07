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
int main(void){
	uint8_t in;
	uint8_t out;
	while(1){
		in = read_UART7();
		out = in - 0x20;
		write_UART7(out);
	}
}
