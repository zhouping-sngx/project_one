/*
 * bsp_uart.h
 *
 *  Created on: Mar 4, 2022
 *      Author: Administrator
 */

#ifndef BSP_UART_H_
#define BSP_UART_H_

#include "stdint.h"
#include "stm32f103xe.h"



//void USART1_Init(void);
void USART1_Init(void);
void USART1_Send_U8(uint8_t ch);
void USART1_Send_ArrayU8(uint8_t *BufferPtr, uint16_t Length);
void usartSendData(short leftVel, short rightVel,short angle,unsigned char ctrlFlag);
unsigned char getCrc8(unsigned char *ptr, unsigned short len);
void USART_Send_String(uint8_t *p,uint16_t sendSize);

void USART1_test(short* p1, short* p2,unsigned char* p3);
void USART1_test1(uint8_t* p1, uint8_t* p2);
int Recetest(void);
int Recetest1(void);
#endif /* BSP_UART_H_ */
