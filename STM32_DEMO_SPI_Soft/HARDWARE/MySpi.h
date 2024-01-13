#ifndef __MySii_h
#define __MySii_h


#include "stm32f10x.h"                  // Device header


void MySpi_Init(void);
void MySPI_Start(void);
void MySPI_Stop(void);
uint8_t MySPI_SwapByte(uint8_t ByteSend);


#endif



