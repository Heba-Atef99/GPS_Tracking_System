#include "UART.h"


//UART0 function for communicating with pc through A0 & A1
void init_UART0(void){
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
	while((SYSCTL_PRGPIO_R&0x00000010) == 0){};
	UART0_CTL_R &= ~UART_CTL_UARTEN;
	UART0_IBRD_R = 104;    
  UART0_FBRD_R = 11;
	UART0_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
	UART0_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
	
	GPIO_PORTA_AFSEL_R |= GPIO_PA10_M;
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00) | (GPIO_PCTL_PA1_U0TX | GPIO_PCTL_PA0_U0RX);
	GPIO_PORTA_DEN_R |= GPIO_PA10_M;
}

uint8_t available_UART0(void){
	return ((UART0_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
}

uint8_t read_UART0(void){
	while(available_UART0() != 1);
	return (uint8_t)(UART0_DR_R&0xFF);
}

void write_UART0(uint8_t data){
	while((UART0_FR_R&UART_FR_TXFF) != 0);
	UART0_DR_R = data;
}

//UART7 function for communicating with gps module through E0 & E1
void init_UART7(void)
{	
	//activate PORT_E
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R7;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
	//disable UART_7 during setup
	UART7_CTL_R &=~ 0x00000001;
	//The 2 registers adjusting the Baudrate of 9600 assuming 80 MHz bus clock
	UART7_IBRD_R = 104;
	UART7_FBRD_R = 11;
	//8 bits data, no parity, one stop bit
	UART7_LCRH_R=0x00000070;
	
	//enable the UART
	UART7_CTL_R|= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
	
	//enable alternate function of port_E
	GPIO_PORTE_AFSEL_R |= 0x03;
	
	//make P0.P1 in port E as digital enable
	GPIO_PORTE_DEN_R |=0x03;
	
	//make P0,P1 UART
	GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFFFFFF00) | (GPIO_PCTL_PE1_U7TX | GPIO_PCTL_PE0_U7RX);
	
	//disable the analog of port E
	GPIO_PORTE_AMSEL_R&=~0x03;
}

uint8_t available_UART7(void){
	return ((UART7_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
}

uint8_t read_UART7(void){
	while(available_UART7() != 1);
	return (uint8_t)(UART7_DR_R&0xFF);
}

void write_UART7(uint8_t data){
	while((UART7_FR_R&UART_FR_TXFF) != 0);
	UART7_DR_R = data;
}
