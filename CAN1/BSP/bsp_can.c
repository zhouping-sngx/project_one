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
void Can_Test_Send1(void)
{
	uint8_t TxData[8];
	uint32_t TxMailbox = 0;
	TxHeader.StdId = 0x00;
	TxHeader.ExtId = 0x1ff46f00;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_EXT;
	TxHeader.DLC = 8;
	TxHeader.TransmitGlobalTime = DISABLE;

	TxData[0] = 10;
	TxData[1] = 1;
	TxData[2] = 10;
	TxData[3] = 1;
	TxData[4] = 10;
	TxData[5] = 1;
	TxData[6] = 10;
	TxData[7] = 1;
	printf("CAN Send:%02X %02X %02X %02X %02X %02X %02X %02X \n",
			TxData[0], TxData[1], TxData[2], TxData[3],
			TxData[4], TxData[5], TxData[6], TxData[7]);
    // Send Data  发送数据
    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
    {
        Error_Handler();
    }
}

void Can_Test_Send2(void)
{
	uint8_t TxData[8];
	uint32_t TxMailbox = 0;
	TxHeader.StdId = 0x00;
	TxHeader.ExtId = 0x1ff46f00;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_EXT;
	TxHeader.DLC = 8;
	TxHeader.TransmitGlobalTime = DISABLE;

	TxData[0] = 0x00;
	TxData[1] = 0x00;
	TxData[2] = 0x00;
	TxData[3] = 0x00;
	TxData[4] = 0x00;
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = 0x00;
	printf("CAN Send:%02X %02X %02X %02X %02X %02X %02X %02X \n",
			TxData[0], TxData[1], TxData[2], TxData[3],
			TxData[4], TxData[5], TxData[6], TxData[7]);
    // Send Data  发送数据
    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
    {
        Error_Handler();
    }
}

void Can_Test_Send3(void)
{
	uint8_t TxData[8];
	uint32_t TxMailbox = 0;
	TxHeader.StdId = 0x00;
	TxHeader.ExtId = 0x1ff46f00;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_EXT;
	TxHeader.DLC = 8;
	TxHeader.TransmitGlobalTime = DISABLE;

	TxData[0] = 0x64;
	TxData[1] = 0x00;
	TxData[2] = 0x00;
	TxData[3] = 0x00;
	TxData[4] = 0x00;
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = 0x00;
	printf("CAN Send:%02X %02X %02X %02X %02X %02X %02X %02X \n",
			TxData[0], TxData[1], TxData[2], TxData[3],
			TxData[4], TxData[5], TxData[6], TxData[7]);
    // Send Data  发送数据
    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
    {
        Error_Handler();
    }
}
void Can_Test_Send4(void)
{
	uint8_t TxData[8];
	uint32_t TxMailbox = 0;
	TxHeader.StdId = 0x00;
	TxHeader.ExtId = 0x1ff46f00;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_EXT;
	TxHeader.DLC = 8;
	TxHeader.TransmitGlobalTime = DISABLE;

	TxData[0] = 0x64;
	TxData[1] = 0x00;
	TxData[2] = 0x64;
	TxData[3] = 0x00;
	TxData[4] = 0x00;
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = 0x00;
	printf("CAN Send:%02X %02X %02X %02X %02X %02X %02X %02X \n",
			TxData[0], TxData[1], TxData[2], TxData[3],
			TxData[4], TxData[5], TxData[6], TxData[7]);
    // Send Data  发送数据
    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
    {
        Error_Handler();
    }
}
void Can_Test_Send5(void)
{
	uint8_t TxData[8];
	uint32_t TxMailbox = 0;
	TxHeader.StdId = 0x00;
	TxHeader.ExtId = 0x1ff46f00;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_EXT;
	TxHeader.DLC = 8;
	TxHeader.TransmitGlobalTime = DISABLE;

	TxData[0] = 0x64;
	TxData[1] = 0x00;
	TxData[2] = 0x64;
	TxData[3] = 0x00;
	TxData[4] = 0x64;
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = 0x00;
	printf("CAN Send:%02X %02X %02X %02X %02X %02X %02X %02X \n",
			TxData[0], TxData[1], TxData[2], TxData[3],
			TxData[4], TxData[5], TxData[6], TxData[7]);
    // Send Data  发送数据
    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
    {
        Error_Handler();
    }
}
void Can_Test_Send6(void)
{
	uint8_t TxData[8];
	uint32_t TxMailbox = 0;
	TxHeader.StdId = 0x00;
	TxHeader.ExtId = 0x1ff46f00;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_EXT;
	TxHeader.DLC = 8;
	TxHeader.TransmitGlobalTime = DISABLE;

	TxData[0] = 0x64;
	TxData[1] = 0x00;
	TxData[2] = 0x64;
	TxData[3] = 0x00;
	TxData[4] = 0x64;
	TxData[5] = 0x00;
	TxData[6] = 0x64;
	TxData[7] = 0x00;
	printf("CAN Send:%02X %02X %02X %02X %02X %02X %02X %02X \n",
			TxData[0], TxData[1], TxData[2], TxData[3],
			TxData[4], TxData[5], TxData[6], TxData[7]);
    // Send Data  发送数据
    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
    {
        Error_Handler();
    }
}
void Can_Test_Send7(void)
{
	uint8_t TxData[8];
	uint32_t TxMailbox = 0;
	TxHeader.StdId = 0x00;
	TxHeader.ExtId = 0x1ff46f00;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_EXT;
	TxHeader.DLC = 8;
	TxHeader.TransmitGlobalTime = DISABLE;

	TxData[0] = 0x9C;
	TxData[1] = 0xFF;
	TxData[2] = 0x00;
	TxData[3] = 0x00;
	TxData[4] = 0x00;
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = 0x00;
	printf("CAN Send:%02X %02X %02X %02X %02X %02X %02X %02X \n",
			TxData[0], TxData[1], TxData[2], TxData[3],
			TxData[4], TxData[5], TxData[6], TxData[7]);
    // Send Data  发送数据
    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
    {
        Error_Handler();
    }
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
