#ifndef __DHT20_H
#define __DHT20_H


#include "stm32f10x.h"
#include "sys.h"


void DHT20_W_Reg(uint8_t RegAddress, uint8_t Data);
uint8_t DHT20_R_Reg(uint8_t RegAddress);
void DHT20_S_Reg(uint8_t RegAddress, uint8_t Data[]);
uint8_t DHT20_Init(void);

#endif
