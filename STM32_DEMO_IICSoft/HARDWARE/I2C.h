#ifndef _I2C_H_
#define _I2C_H_



#include "stm32f10x.h"                  // Device header

#define SCL_PORT	GPIOB
#define SCL_Pin	GPIO_Pin_10
#define SDA_PORT	GPIOB
#define SDA_Pin	GPIO_Pin_11


void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2C_SendByte(uint8_t Byte);
uint8_t MyI2C_ReceiveByte(void);
void MyI2C_SendAck(uint8_t AckBit);
uint8_t MyI2C_ReceiveAck(void);



#endif

