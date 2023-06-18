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




void USART1_Init(void);
void USART1_Send_U8(uint8_t ch);
void USART1_Send_ArrayU8(uint8_t *BufferPtr, uint16_t Length);
void usartSendData1(unsigned char velMode, short vel);
void USART1_Data_Init(unsigned char* p1, short* p2);
void USART1_Data_Init1(short* p1, short* p2, short* p3);
void usartSendData(short leftVel, short rightVel,short angle,unsigned char ctrlFlag);
unsigned char getCrc8(unsigned char *ptr, unsigned short len);
void USART_Send_String(uint8_t *p,uint16_t sendSize);
void USART1_Revice_Speed(uint8_t Rx_Temp);
uint8_t USART1_Parse_Speed(void);
uint8_t USART1_Parse_Robot_Speed(void);
void USART1_Revice_Robot_Speed(uint8_t Rx_Temp);
void usartSendMeterData(int16_t ax, int16_t ay, int16_t az,int16_t gx, int16_t gy, int16_t gz,int16_t mx, int16_t my, int16_t mz);
#endif /* BSP_UART_H_ */
