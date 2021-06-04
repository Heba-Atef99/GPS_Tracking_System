#include "UART.h"

void UART_init(void)
{
	//activate UART_7
	SYSCTL_RCGCUART_R|=(1<<7);
	//activate PORT_E
	SYSCTL_RCGCGPIO_R|=(1<<5);
	//disable UART_7 during setup
	UART7_CTL_R&=~00000001;
	//The 2 registers adjusting the Baudrate of 9600 assuming 80 MHz bus clock
	UART7_IBRD_R=520;
	UART7_FBRD_R=53;
	//8 bits data, no parity, one stop bit
	UART7_LCRH_R=0x00000070;
	//enable the UART
	UART7_CTL_R|= 00000001;
	//enable alternate function of port_E
	GPIO_PORTE_AFSEL_R|=0x03;
	//make P0.P1 in port E as digital enable
	GPIO_PORTE_DEN_R |=0x03;
	//make P0,P1 UART
	GPIO_PORTE_PCTL_R=(GPIO_PORTE_PCTL_R &0xFFFFFF00)+ 0x00000011;
	//disable the analog of port E
	GPIO_PORTE_AMSEL_R&=~0x03;
	
}
