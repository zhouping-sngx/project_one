/*
 * bsp_can.h
 *
 *  Created on: Mar 7, 2022
 *      Author: Administrator
 */

#ifndef BSP_CAN_H_
#define BSP_CAN_H_

void Can_Init(void);
void Can_Test_Send(void);
void Can_Test_Send1(int recive1, int recive2);
#endif /* BSP_CAN_H_ */
