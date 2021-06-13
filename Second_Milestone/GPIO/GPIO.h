#include "stdint.h"
#include "../tm4c123gh6pm.h"

void init_GPIO_portA(void);
void init_GPIO_portB(void);
void init_GPIO_portF(void); // with led on p1 
void Seven_Segment(uint32_t);
void led_100distance(uint32_t);
void led_finish(void);