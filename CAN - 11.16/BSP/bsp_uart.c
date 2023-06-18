/*
 * bsp_uart.c
 *
 *  Created on: Mar 4, 2022
 *      Author: Administrator
 */

#include "bsp_uart.h"
#include "bsp.h"

#define ENABLE_UART_DMA    1

uint8_t RxTemp = 0;
short * ptr1 = NULL;
short * ptr2 = NULL;
unsigned char * ptr3 = NULL;
uint8_t * ptr4 = NULL;
uint8_t * ptr5 = NULL;
unsigned char  receiveBuff[2] = {0};

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
union receiveVel
{
	uint8_t d;
	unsigned char data[1];
}lowVelSet,highVelSet;
// Initialize USART1  初始化串口1
void USART1_Init()
{

    //HAL_UART_Receive_IT(&huart1, (uint8_t *)&RxTemp, 1);

	//HAL_UART_Receive_IT(&huart1, (uint8_t *)&leftVelSet.data, 2);
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&receiveBuff, 2);
}
void USART1_test(short* p1, short* p2,unsigned char* p3)
{
	ptr1 = p1;
	ptr2 = p2;
	ptr3 = p3;
	return ;
}
void USART1_test1(uint8_t* p1, uint8_t* p2)
{
	ptr4 = p1;
	ptr5 = p2;
}

int Recetest(void)
{
	for(int i = 0; i < 2; ++i)
	{
		 leftVelSet.data[i] = receiveBuff[i];
		 rightVelSet.data[i] = receiveBuff[i+2];
	}
	*ptr1 = leftVelSet.d;
	*ptr2 = rightVelSet.d;
	*ptr3 = receiveBuff[4];
	return 0;
}
int Recetest1(void)
{
	lowVelSet.data[0] = receiveBuff[0];
	highVelSet.data[0] = receiveBuff[1];
	*ptr4 = lowVelSet.d;
	*ptr5 = highVelSet.d;
	return 0;
}
// The serial port sends one byte  串口发送一个字节
void USART1_Send_U8(uint8_t ch)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
}

// The serial port sends a string of data  串口发送一串数据
void USART1_Send_ArrayU8(uint8_t *BufferPtr, uint16_t Length)
{
    #if ENABLE_UART_DMA
    HAL_UART_Transmit_DMA(&huart1, BufferPtr, Length);
    #else
    while (Length--)
    {
        USART1_Send_U8(*BufferPtr);
        BufferPtr++;
    }
    #endif
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
// The serial port receiving is interrupted. Procedure  串口接收完成中断
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(huart);
    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_UART_RxCpltCallback can be implemented in the user file
     */
    // 测试发送数据，实际应用中不应该在中断中发送数据
    // Test sending data. In practice, data should not be sent during interrupts  
    //USART1_Send_U8(RxTemp);
    //usartReceData(Rece1,Rece2,Rece3);
    Recetest1();
    //HAL_UART_Receive_IT(&huart1, (uint8_t *)&receiveBuff, 5);
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&receiveBuff, 2);

}



#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}
