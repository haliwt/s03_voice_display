#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H
#include "main.h"

void delay_init(uint16_t sysclk);
void delay_us(uint32_t nus);

#endif 

