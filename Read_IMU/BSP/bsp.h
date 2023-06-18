#ifndef __BSP_H__
#define __BSP_H__

#include "stdio.h"
#include "stdint.h"

/* Import HAL related library  导入HAL相关库 */
#include "main.h"
#include "gpio.h"
#include "usart.h"

#include "stm32f1xx_hal.h"
#include "stm32f103xe.h"


/* Import device driver library  导入设备驱动库 */
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_mpuiic.h"
#include "bsp_mpu9250.h"
#include "bsp_uart.h"


/* DEFINE */
#define LED_ON()         HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET)
#define LED_OFF()        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, RESET)
#define LED_TOGGLE()     HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin)


/* functions */
void Bsp_Init(void);
void Bsp_Loop(void);
void Bsp_Led_Show_State_Handle(void);
void Bsp_Data_Init(unsigned char* p1, short* p2);
#endif /* __BSP_H__ */
