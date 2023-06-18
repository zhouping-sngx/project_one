/*
 * mbotLinuxUsart.c
 *
 *  Created on: Nov 13, 2022
 *      Author: 86187
 */
#include "mbotLinuxUsart.h"
#include "usart.h"
#include "stdio.h"
unsigned char  receiveBuff[16] = {0};

const unsigned char header[2]  = {0x55, 0xaa};
const unsigned char ender[2]   = {0x0d, 0x0a};


union sendData
{
	short d;
	unsigned char data[2];
}leftVelNow,rightVelNow,angleNow;


union receiveData
{
	short d;
	unsigned char data[2];
}leftVelSet,rightVelSet;

/*
**************************************************************************/
int usartReceiveOneData(int *p_leftSpeedSet,int *p_rightSpeedSet,unsigned char *p_crtlFlag)
{
	unsigned char USART_Receiver              = 0;
	static unsigned char checkSum             = 0;
	static unsigned char USARTBufferIndex     = 0;
	static short j=0,k=0;
	static unsigned char USARTReceiverFront   = 0;
	static unsigned char Start_Flag           = START;
	static short dataLength                   = 0;

	USART_Receiver = USART_ReceiveData(USART1);
	if(Start_Flag == START)
	{
		if(USART_Receiver == 0xaa)
		{
			if(USARTReceiverFront == 0x55)
			{
				Start_Flag = !START;
				//printf("header ok\n");
				receiveBuff[0]=header[0];
				receiveBuff[1]=header[1];
				USARTBufferIndex = 0;
				checkSum = 0x00;
			}
		}
		else
		{
			USARTReceiverFront = USART_Receiver;
		}
	}
	else
    {
		switch(USARTBufferIndex)
		{
			case 0:
				receiveBuff[2] = USART_Receiver;
				dataLength     = receiveBuff[2];            //buf[2]
				USARTBufferIndex++;
				break;
			case 1:
				receiveBuff[j + 3] = USART_Receiver;        //buf[3] - buf[7]
				j++;
				if(j >= dataLength)
				{
					j = 0;
					USARTBufferIndex++;
				}
				break;
			case 2:
				receiveBuff[3 + dataLength] = USART_Receiver;
				checkSum = getCrc8(receiveBuff, 3 + dataLength);

				if (checkSum != receiveBuff[3 + dataLength]) //buf[8]
				{
					printf("Received data check sum error!");
					return 0;
				}
				USARTBufferIndex++;
				break;

			case 3:
				if(k==0)
				{

					k++;
				}
				else if (k==1)
				{

					 for(k = 0; k < 2; k++)
					{
						leftVelSet.data[k]  = receiveBuff[k + 3]; //buf[3]  buf[4]
						rightVelSet.data[k] = receiveBuff[k + 5]; //buf[5]  buf[6]
					}


					*p_leftSpeedSet  = (int)leftVelSet.d;
					*p_rightSpeedSet = (int)rightVelSet.d;


					*p_crtlFlag = receiveBuff[7];                //buf[7]


					USARTBufferIndex   = 0;
					USARTReceiverFront = 0;
					Start_Flag         = START;
					checkSum           = 0;
					dataLength         = 0;
					j = 0;
					k = 0;
					//-----------------------------------------------------------------
				}
				break;
			 default:break;
		}
	}
	return 0;
}

void usartSendData(short leftVel, short rightVel,short angle,unsigned char ctrlFlag)
{

	unsigned char buf[13] = {0};
	int i, length = 0;


	leftVelNow.d  = leftVel;
	rightVelNow.d = rightVel;
	angleNow.d    = angle;


	for(i = 0; i < 2; i++)
		buf[i] = header[i];                      // buf[0] buf[1]


	length = 7;
	buf[2] = length;                             // buf[2]
	for(i = 0; i < 2; i++)
	{
		buf[i + 3] = leftVelNow.data[i];         // buf[3] buf[4]
		buf[i + 5] = rightVelNow.data[i];        // buf[5] buf[6]
		buf[i + 7] = angleNow.data[i];           // buf[7] buf[8]
	}

	buf[3 + length - 1] = ctrlFlag;              // buf[9]


	buf[3 + length] = getCrc8(buf, 3 + length);  // buf[10]
	buf[3 + length + 1] = ender[0];              // buf[11]
	buf[3 + length + 2] = ender[1];              // buf[12]


	USART_Send_String(buf,sizeof(buf));
}

void USART_Send_String(uint8_t *p,uint16_t sendSize)
{
	static int length =0;
	while(length<sendSize)
	{

		while( !(USART1->SR&(0x01<<7)) );
		USART1->DR=*p;
		p++;
		length++;
	}
	length =0;
}

unsigned char getCrc8(unsigned char *ptr, unsigned short len)
{
	unsigned char crc;
	unsigned char i;
	crc = 0;
	while(len--)
	{
		crc ^= *ptr++;
		for(i = 0; i < 8; i++)
		{
			if(crc&0x01)
                crc=(crc>>1)^0x8C;
			else
                crc >>= 1;
		}
	}
	return crc;
}
/**********************************END***************************************/









