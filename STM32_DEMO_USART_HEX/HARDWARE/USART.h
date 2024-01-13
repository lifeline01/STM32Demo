#ifndef __USART_H
#define __USART_H


#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>


// 串口1初始化
void USARTInit(void);
// 串口发送一个字节
void USART_SendByte(USART_TypeDef *USARTx, uint8_t Byte);
// 串口发送字符串
void USART_SendString(USART_TypeDef *USARTx, char *String);
// 发送数组
void USART_SendArray(USART_TypeDef *USARTx, uint8_t *Array, uint16_t Length);
// 串口发送数字
void USART_SendNumber(USART_TypeDef *USARTx, uint32_t Number, uint8_t Length);

void USART_SendPacket(void);

uint8_t USART_GetRxFlag(void);



void Printf(char *format, ...);
#endif


