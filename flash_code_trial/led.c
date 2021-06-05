#include "C:\Keil\TExaSware\tm4c123gh6pm.h"
#include "stdint.h"
	
void SystemInit(){}

void LED_Init(){
  SYSCTL_RCGCGPIO_R |= 0x00000020;
  while ((SYSCTL_PRGPIO_R & 0x00000020) == 0) {};
  GPIO_PORTF_CR_R=0x1F;
  GPIO_PORTF_DIR_R=0x0E;
	GPIO_PORTF_PUR_R=0x11;
	GPIO_PORTF_DEN_R=0x1F;
 }
void LED_Out (uint32_t data){
  GPIO_PORTF_DATA_R = data;
}

void Delay(uint32_t time)
{
	while(time)
	{
		time--;
	}
}

int main ()
{
	LED_Init();
	while(1)
	{
		LED_Out(2);
		Delay(2500000);
		LED_Out(0);
		Delay(2500000);
		LED_Out(4);
		Delay(2500000);		
	}
}
