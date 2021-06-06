#include "../tm4c123gh6pm.h"
#include "stdint.h"

void UART_init(void);

uint8_t UART7_Available(void);

uint8_t UART7_Read(void);

void UART7_Write(uint8_t data);