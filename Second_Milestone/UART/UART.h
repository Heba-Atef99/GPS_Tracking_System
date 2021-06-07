#include "../tm4c123gh6pm.h"
#include "stdint.h"
#include "../Timer/Timer.h"

#define GPIO_PA10_M 0x03

void init_UART0(void);

uint8_t available_UART0(void);

uint8_t read_UART0(void);

void write_UART0(uint8_t data);

void init_UART7(void);

uint8_t available_UART7(void);

uint8_t read_UART7(void);

void write_UART7(uint8_t data);
