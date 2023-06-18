#ifndef MBOTLINUXUSART_H_
#define MBOTLINUXUSART_H_

#include "stdint.h"

int usartReceiveOneData(int *p_leftSpeedSet,int *p_rightSpeedSet,unsigned char *p_crtlFlag);
void usartSendData(short leftVel, short rightVel,short angle,unsigned char ctrlFlag);
void USART_Send_String(uint8_t *p,uint16_t sendSize);

unsigned char getCrc8(unsigned char *ptr, unsigned short len);
#endif /* MBOTLINUXUSART_H_ */
