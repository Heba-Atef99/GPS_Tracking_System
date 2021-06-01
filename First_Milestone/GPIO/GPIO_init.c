#include "GPIO_init.h"

void init_GPIO_portA(void)
{
	//to enable portA
	SYSCTL_RCGCGPIO_R|=0x01;
	//delay
	while ((SYSCTL_PRGPIO_R & 0x00000001) == 0) {};
	//make the last 6 bits as GPIO
	GPIO_PORTA_AFSEL_R &=~0xFc;
	//make the last 6 bits output
	GPIO_PORTA_DIR_R |=0xFC;
	//make the last 6 bits digital
	GPIO_PORTA_DEN_R|=0xFC;
	//disable the analog of the last 6 bits
	GPIO_PORTA_AMSEL_R&=~0xFC;
	// reset the data reg
	GPIO_PORTA_DATA_R&=~0xFC;
}
void init_GPIO_portB(void)
{
	//enable portB
	SYSCTL_RCGCGPIO_R|=0x02;
	//delay
	while ((SYSCTL_PRGPIO_R & 0x00000002) == 0) {};
	//make portB as GPIO
	GPIO_PORTB_AFSEL_R=0;
	//make portB as output
	GPIO_PORTB_DIR_R|=0xFF;
	//make portB digital
	GPIO_PORTB_DEN_R|=0xFF;
	//disable tha analog of portB
	GPIO_PORTB_AMSEL_R=0;
	// reset the data reg
	GPIO_PORTB_DATA_R&=~0xFF;
}	

void init_GPIO_portF(void)
{
	//enable portF
	SYSCTL_RCGCGPIO_R|=0x20;
	//delay
	while ((SYSCTL_PRGPIO_R & 0x00000020) == 0) {};
	//make bit 1 as GPIO
	GPIO_PORTF_AFSEL_R&=~0x02;
	//make bit 1 as output
	GPIO_PORTF_DIR_R|=0x02;
	//make bit digital
	GPIO_PORTF_DEN_R|=0x02;
	//disable the analog of bit 1
	GPIO_PORTF_AMSEL_R&=~0x02;
	//clear the data reg
	GPIO_PORTF_DATA_R&=~0x02;
}

void Seven_Segment(uint32_t distance)
{
	uint32_t H = 0;
	uint32_t T = 0;
	uint32_t U = 0;
	H = distance/100;
	T = (distance-(100*H))/10;
	U = distance - (100*H)-(10*T);
	H<<=4;
	U<<=4;
	
	GPIO_PORTA_DATA_R |= U;
	GPIO_PORTB_DATA_R |= T;
	GPIO_PORTB_DATA_R |= H;
}
