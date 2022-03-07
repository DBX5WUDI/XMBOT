#ifndef DELAY_H
#define DELAY_H

#include "stm32f4xx.h"	

void System_Timer_Init(void);
void delay_us(uint16_t t);
void delay_ms(uint16_t t);
#endif
