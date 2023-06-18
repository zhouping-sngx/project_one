/*
 * bsp_uart.c
 *
 *  Created on: Mar 4, 2022
 *      Author: Administrator
 */

#include "bsp_uart.h"
#include "bsp.h"

#define ENABLE_UART_DMA    1
#define RX_MAX_BUF 12

uint8_t New_Frame = 0;
uint8_t RxTemp = 0;
uint8_t Rx_Data[RX_MAX_BUF] = {0};
uint8_t Rx_index = 0;
uint8_t Rx_Flag = 0;

short* receVelPtr = NULL;
unsigned char* receModePtr = NULL;
short* VxPtr = NULL;
short* VyPtr = NULL;
short* VwPtr = NULL;
const unsigned char header[2]  = {0x55, 0xaa};
const unsigned char ender[2]   = {0x0d, 0x0a};


union readVel
{
	short d;
	unsigned char data[2];
}VelSet;
union sendVel
{
	short d;
	unsigned char data[2];
}VelNow;
// Initialize USART1  初始化串口1
void USART1_Init()
{

    HAL_UART_Receive_IT(&huart1, (uint8_t *)&RxTemp, 1);
}
void USART1_Data_Init(unsigned char* p1, short* p2)
{
	receVelPtr = p2;
	receModePtr = p1;
}
void USART1_Data_Init1(short* p1, short* p2, short* p3)
{
	 VxPtr = p1;
	 VyPtr = p2;
	 VwPtr = p3;
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
void USART1_Revice_Speed(uint8_t Rx_Temp)
{
    switch (Rx_Flag)
    {
    case 0:
        if (Rx_Temp == header[0])
        {
            Rx_Data[0] = header[0];
            Rx_Flag = 1;
        }
        break;

    case 1:
        if (Rx_Temp == header[1])
        {
            Rx_Data[1] = header[1];
            Rx_Flag = 2;
            Rx_index = 2;
        }
        else
        {
            Rx_Flag = 0;
            Rx_Data[0] = 0x0;
        }
        break;

    case 2:
        Rx_Data[Rx_index] = Rx_Temp;
        Rx_index++;
        if (Rx_index >= RX_MAX_BUF)
        {
            Rx_Flag = 0;
            New_Frame = 1;
        }
        break;
    default:
        break;
    }
}
void USART1_Revice_Robot_Speed(uint8_t Rx_Temp)
{
    switch (Rx_Flag)
    {
    case 0:
        if (Rx_Temp == header[0])
        {
            Rx_Data[0] = header[0];
            Rx_Flag = 1;
        }
        break;

    case 1:
        if (Rx_Temp == header[1])
        {
            Rx_Data[1] = header[1];
            Rx_Flag = 2;
            Rx_index = 2;
        }
        else
        {
            Rx_Flag = 0;
            Rx_Data[0] = 0x0;
        }
        break;

    case 2:
        Rx_Data[Rx_index] = Rx_Temp;
        Rx_index++;
        if (Rx_index >= RX_MAX_BUF)
        {
            Rx_Flag = 0;
            New_Frame = 1;
        }
        break;
    default:
        break;
    }
}
uint8_t USART1_Parse_Speed(void)
{
    uint8_t result = 0;
    int length = 0;
    if (New_Frame)
    {
        result = 1;
        New_Frame = 0;
        length = Rx_Data[2];
        uint8_t checknum = getCrc8(Rx_Data, 3 + length);;
        if (checknum == Rx_Data[6])
        {
        	*receModePtr = Rx_Data[3];
        	VelSet.data[0] = Rx_Data[4];
        	VelSet.data[1] = Rx_Data[5];
        	*receVelPtr = VelSet.d;
        }
    }
    return result;
}


union Ctrl_Vel
{
	short d;
	unsigned char data[2];
}Vx, Vy , Vw;
uint8_t USART1_Parse_Robot_Speed(void)
{
    uint8_t result = 0;
    int length = 0;
    if (New_Frame)
    {
        result = 1;
        New_Frame = 0;
        length = Rx_Data[2];
        uint8_t checknum = getCrc8(Rx_Data, 3 + length);;
        if (checknum == Rx_Data[9])
        {
        	for(int i = 0; i < 2; ++i)
        	{
        		Vx.data[i] = Rx_Data[3+i];
        		Vy.data[i] = Rx_Data[5+i];
        		Vw.data[i] = Rx_Data[7+i];
        	}
        	*VxPtr = Vx.d;
        	*VyPtr = Vy.d;
        	*VwPtr = Vw.d;
        }
    }
    return result;
}
void usartSendData1(unsigned char velMode, short vel)
{
	unsigned char buf[9] = {0};
	int i, length = 0;
	VelNow.d  = vel;

	for(i = 0; i < 2; i++)
		buf[i] = header[i]; // buf[0] buf[1]
	length = 3;
	buf[2] = length;
	buf[3] = velMode;

	buf[4] = VelNow.data[0];
	buf[5] = VelNow.data[1];

	buf[3 + length] = getCrc8(buf, 3 + length);  // buf[10]
	buf[3 + length + 1] = ender[0];              // buf[11]
	buf[3 + length + 2] = ender[1];              // buf[12]

	USART_Send_String(buf,sizeof(buf));
}
void usartSendData(short leftVel, short rightVel,short angle,unsigned char ctrlFlag)
{

	unsigned char buf[13] = {0};
	int i, length = 0;


	//leftVelNow.d  = leftVel;
	//rightVelNow.d = rightVel;
	//angleNow.d    = angle;


	for(i = 0; i < 2; i++)
		buf[i] = header[i];                      // buf[0] buf[1]


	length = 7;
	buf[2] = length;                             // buf[2]
	for(i = 0; i < 2; i++)
	{
		//buf[i + 3] = leftVelNow.data[i];         // buf[3] buf[4]
		//buf[i + 5] = rightVelNow.data[i];        // buf[5] buf[6]
		//buf[i + 7] = angleNow.data[i];           // buf[7] buf[8]
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
union Gyroscope
{
	int16_t d;
	unsigned char data[2];
}axData, ayData, azData,gxData, gyData, gzData,mxData, myData, mzData;
void usartSendMeterData(int16_t ax, int16_t ay, int16_t az,int16_t gx, int16_t gy, int16_t gz,int16_t mx, int16_t my, int16_t mz)
{
	unsigned char buf[24] = {0};
	int i, length = 0;
	axData.d  = ax;
	ayData.d  = ay;
	azData.d  = az;
	gxData.d  = gx;
	gyData.d  = gy;
	gzData.d  = gz;
	mxData.d  = mx;
	myData.d  = my;
	mzData.d  = mz;
	for(i = 0; i < 2; i++)
		buf[i] = header[i]; // buf[0] buf[1]
	length = 18;
	buf[2] = length;
	for(i = 0; i < 2; ++i)
	{
		buf[3+i]  = axData.data[i];
		buf[5+i]  = ayData.data[i];
		buf[7+i]  = azData.data[i];
		buf[9+i]  = gxData.data[i];
		buf[11+i] = gyData.data[i];
		buf[13+i] = gzData.data[i];
		buf[15+i] = mxData.data[i];
		buf[17+i] = myData.data[i];
		buf[19+i] = mzData.data[i];
	}
	buf[3 + length] = getCrc8(buf, 3 + length);  // buf[10]
	buf[3 + length + 1] = ender[0];              // buf[11]
	buf[3 + length + 2] = ender[1];              // buf[12]

	USART_Send_String(buf,sizeof(buf));
	//USART1_Send_ArrayU8(buf,sizeof(buf));
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
    //USART1_Revice_Speed(RxTemp);
    USART1_Revice_Robot_Speed(RxTemp);
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&RxTemp, 1);

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
