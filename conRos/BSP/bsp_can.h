/*
 * bsp_can.h
 *
 *  Created on: Mar 7, 2022
 *      Author: Administrator
 */

#ifndef BSP_CAN_H_
#define BSP_CAN_H_
#include "stdint.h"
void Can_Init(void);
void Can_Test_Send(void);

void Can_set_RobotMoving_Txheader(void);
void Can_send_Data(uint8_t * TxData, uint32_t *pTxMailbox);
void Can_Send_VelAndMode(unsigned char mvMode, short vel);
void Can_Send_Robot_Stop(void);
void Can_Send_Robot_Forward(short vel);
void Can_Send_Robot_Backward(short vel);
void Can_Send_Robot_LeftMoving(short vel);
void Can_Send_Robot_RightMoving(short vel);
void Can_Send_Robot_LeftRotating(short vel);
void Can_Send_Robot_RightRotating(short vel);
void Can_Send_Robot_ForwadLeftMoving(short vel);
void Can_Send_Robot_ForwardRightMoving(short vel);
void Can_Send_Robot_BackwardLeftMoving(short vel);
void Can_Send_Robot_BackwardRightMoving(short vel);
#endif /* BSP_CAN_H_ */
