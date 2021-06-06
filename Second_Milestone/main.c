#include "stdint.h"
#include "GPS_Functions/functions.h"
#include "GPIO/GPIO.h"
#include "Timer/Timer.h"
#include "UART/UART.h"

void SystemInit()
{
	//initalize GPIO
	init_GPIO_portA();
	init_GPIO_portB();
	init_GPIO_portF();
UART_init();

}
int main(void){
	uint8_t in;
	uint8_t out;
	while(1){
		in = UART7_Read();
		out = in - 0x20;
		UART7_Write(out);
	}
}
