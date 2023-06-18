#include "bsp_can.h"
#include "bsp.h"

// Define related variables  定义相关变量
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
CAN_FilterTypeDef sFilterConfig;


// Initialize the CAN  初始化CAN
void Can_Init(void)
{
    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    sFilterConfig.SlaveStartFilterBank = 27;
    sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;

    // Setting the CAN Filter  设置CAN过滤器
    if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }

    // Start the CAN peripheral  启动CAN
    if (HAL_CAN_Start(&hcan) != HAL_OK)
    {
        Error_Handler();
    }

    // Activate CAN RX notification  启动CAN RX通知
    if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        Error_Handler();
    }
}


// The test sends data through CAN  测试通过CAN发送数据
void Can_Test_Send(void)
{
	uint8_t TxData[8];
	uint32_t TxMailbox = 0;
	TxHeader.StdId = 0x000F;
	TxHeader.ExtId = 0x00;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.DLC = 8;
	TxHeader.TransmitGlobalTime = DISABLE;

	for (int i = 0; i < 8; i++)
	{
		TxData[i] = 1 << i;
	}
	printf("CAN Send:%02X %02X %02X %02X %02X %02X %02X %02X \n",
			TxData[0], TxData[1], TxData[2], TxData[3],
			TxData[4], TxData[5], TxData[6], TxData[7]);
    // Send Data  发送数据
    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
    {
        Error_Handler();
    }
}

void Can_set_RobotMoving_Txheader(void)
{
	 TxHeader.StdId = 0x00;
	 TxHeader.ExtId = 0x1ff46f00;
	 TxHeader.RTR = CAN_RTR_DATA;
	 TxHeader.IDE = CAN_ID_EXT;
	 TxHeader.DLC = 8;
	 TxHeader.TransmitGlobalTime = DISABLE;
}
void Can_send_Data(uint8_t * TxData, uint32_t *pTxMailbox)
{
	if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, pTxMailbox) != HAL_OK)
	    {
	        Error_Handler();
	    }
}
//mvMode : 0x00 停止， 0x11 前进， 0x22 后退， 0x33 左平移， 0x44 右平移， 0x54 原地左旋转， 0x56 原地右旋转，
//         0x66 左前移动， 0x77 右前移动， 0x88 左后移动， 0x99 右后移动
void Can_Send_VelAndMode(unsigned char mvMode, short vel)
{
	if(mvMode == 0x11)
	{
		Can_Send_Robot_Forward(vel);
	}
	else if(mvMode == 0x22)
	{
		Can_Send_Robot_Backward(vel);
	}
	else if(mvMode == 0x33)
	{
		Can_Send_Robot_LeftMoving(vel);
	}
	else if(mvMode == 0x44)
	{
		Can_Send_Robot_RightMoving(vel);
	}
	else if(mvMode == 0x54)
	{
		Can_Send_Robot_LeftRotating(vel);
	}
	else if(mvMode == 0x56)
	{
		Can_Send_Robot_RightRotating(vel);
	}
	else if(mvMode == 0x66)
	{
		Can_Send_Robot_ForwadLeftMoving(vel);
	}
	else if(mvMode == 0x77)
	{
		Can_Send_Robot_ForwardRightMoving(vel);
	}
	else if(mvMode == 0x88)
	{
		Can_Send_Robot_BackwardLeftMoving(vel);
	}
	else if(mvMode == 0x99)
	{
		Can_Send_Robot_BackwardRightMoving(vel);
	}

	else{
		Can_Send_Robot_Stop();
	}
}

void Can_Send_Robot_Stop(void)
{
	uint8_t TxData[8] = {0};
	uint32_t TxMailbox = 0;
	Can_set_RobotMoving_Txheader();
	Can_send_Data(TxData, &TxMailbox);
}

void Can_Send_Robot_Forward(short vel)
{
	uint8_t TxData[8] = {0};
	uint32_t TxMailbox = 0;
	Can_set_RobotMoving_Txheader();

	TxData[0] = 0x60;
	TxData[1] = 0xFF;

	TxData[2] = 0xA0;
	TxData[3] = 0x00;

	TxData[4] = 0xA0;
	TxData[5] = 0x00;

	TxData[6] = 0x60;
	TxData[7] = 0xFF;

	Can_send_Data(TxData, &TxMailbox);
}

void Can_Send_Robot_Backward(short vel)
{
	uint8_t TxData[8] = {0};
	uint32_t TxMailbox = 0;
	Can_set_RobotMoving_Txheader();

	TxData[0] = 0xA0;
	TxData[1] = 0x00;

	TxData[2] = 0x60;
	TxData[3] = 0xFF;

	TxData[4] = 0x60;
	TxData[5] = 0xFF;

	TxData[6] = 0xA0;
	TxData[7] = 0x00;

	Can_send_Data(TxData, &TxMailbox);
}

void Can_Send_Robot_LeftMoving(short vel)
{
	uint8_t TxData[8] = {0};
	uint32_t TxMailbox = 0;
	Can_set_RobotMoving_Txheader();

	TxData[0] = 0x60;
	TxData[1] = 0xFF;

	TxData[2] = 0x60;
	TxData[3] = 0xFF;

	TxData[4] = 0xA0;
	TxData[5] = 0x00;

	TxData[6] = 0xA0;
	TxData[7] = 0x00;

	Can_send_Data(TxData, &TxMailbox);
}

void Can_Send_Robot_RightMoving(short vel)
{
	uint8_t TxData[8] = {0};
	uint32_t TxMailbox = 0;
	Can_set_RobotMoving_Txheader();

	TxData[0] = 0xA0;
	TxData[1] = 0x00;

	TxData[2] = 0xA0;
	TxData[3] = 0x00;

	TxData[4] = 0x60;
	TxData[5] = 0xFF;

	TxData[6] = 0x60;
	TxData[7] = 0xFF;

	Can_send_Data(TxData, &TxMailbox);
}

void Can_Send_Robot_LeftRotating(short vel)
{
	uint8_t TxData[8] = {0};
	uint32_t TxMailbox = 0;
	Can_set_RobotMoving_Txheader();

	TxData[0] = 0x60;
	TxData[1] = 0xFF;

	TxData[2] = 0x60;
	TxData[3] = 0xFF;

	TxData[4] = 0x60;
	TxData[5] = 0xFF;

	TxData[6] = 0x60;
	TxData[7] = 0xFF;

	Can_send_Data(TxData, &TxMailbox);
}

void Can_Send_Robot_RightRotating(short vel)
{
	uint8_t TxData[8] = {0};
	uint32_t TxMailbox = 0;
	Can_set_RobotMoving_Txheader();

	TxData[0] = 0xA0;
	TxData[1] = 0x00;

	TxData[2] = 0xA0;
	TxData[3] = 0x00;

	TxData[4] = 0xA0;
	TxData[5] = 0x00;

	TxData[6] = 0xA0;
	TxData[7] = 0x00;

	Can_send_Data(TxData, &TxMailbox);
}

void Can_Send_Robot_ForwadLeftMoving(short vel)
{
	uint8_t TxData[8] = {0};
	uint32_t TxMailbox = 0;
	Can_set_RobotMoving_Txheader();

	TxData[0] = 0x60;
	TxData[1] = 0xFF;

	TxData[2] = 0x00;
	TxData[3] = 0x00;

	TxData[4] = 0xA0;
	TxData[5] = 0x00;

	TxData[6] = 0x00;
	TxData[7] = 0x00;

	Can_send_Data(TxData, &TxMailbox);
}

void Can_Send_Robot_ForwardRightMoving(short vel)
{
	uint8_t TxData[8] = {0};
	uint32_t TxMailbox = 0;
	Can_set_RobotMoving_Txheader();

	TxData[0] = 0x00;
	TxData[1] = 0x00;

	TxData[2] = 0xA0;
	TxData[3] = 0x00;

	TxData[4] = 0x00;
	TxData[5] = 0x00;

	TxData[6] = 0x60;
	TxData[7] = 0xFF;

	Can_send_Data(TxData, &TxMailbox);
}

void Can_Send_Robot_BackwardLeftMoving(short vel)
{
	uint8_t TxData[8] = {0};
	uint32_t TxMailbox = 0;
	Can_set_RobotMoving_Txheader();

	TxData[0] = 0x00;
	TxData[1] = 0x00;

	TxData[2] = 0x60;
	TxData[3] = 0xFF;

	TxData[4] = 0x00;
	TxData[5] = 0x00;

	TxData[6] = 0xA0;
	TxData[7] = 0x00;

	Can_send_Data(TxData, &TxMailbox);
}

void Can_Send_Robot_BackwardRightMoving(short vel)
{
	uint8_t TxData[8] = {0};
	uint32_t TxMailbox = 0;
	Can_set_RobotMoving_Txheader();

	TxData[0] = 0xA0;
	TxData[1] = 0x00;

	TxData[2] = 0x00;
	TxData[3] = 0x00;

	TxData[4] = 0x60;
	TxData[5] = 0xFF;

	TxData[6] = 0x00;
	TxData[7] = 0x00;

	Can_send_Data(TxData, &TxMailbox);
}
// CAN receives interrupt callbacks  CAN接收中断回调
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if (hcan->Instance == CAN1)
	{
		uint8_t RxData[8];
		if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
		{
			Error_Handler();
		}
		else
		{
			printf("CAN Receive:%02X %02X %02X %02X %02X %02X %02X %02X \n",
					RxData[0], RxData[1], RxData[2], RxData[3],
					RxData[4], RxData[5], RxData[6], RxData[7]);
		}
	}
}
