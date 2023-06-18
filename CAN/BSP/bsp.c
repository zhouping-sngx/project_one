#include "bsp.h"

unsigned char ReceVelMode = 0x00;
short ReceVel =0;
short Ctrl_Vx =0;
short Ctrl_Vy =0;
short Ctrl_Vw =0;
// LED显示当前运行状态，每10毫秒调用一次，LED灯每200毫秒闪烁一次。
// The LED displays the current operating status, which is invoked every 10 milliseconds, and the LED blinks every 200 milliseconds.  
void Bsp_Led_Show_State_Handle(void)
{
	static uint8_t led_count = 0;
	led_count++;
	if (led_count > 20)
	{
		led_count = 0;
		LED_TOGGLE();
	}
}


// The peripheral device is initialized  外设设备初始化
void Bsp_Init(void)
{
	uint8_t res = 0;
	Can_Init();
	Bsp_Data_Init(&ReceVelMode, &ReceVel);
	Bsp_Data_Init1(&Ctrl_Vx, &Ctrl_Vy, &Ctrl_Vw);
	USART1_Init();
	res = MPU9250_Init();
	if (res != 0)
	{
		printf("MPU9250 INIT ERROR\n");
		while(1);
	}
	Beep_On_Time(50);
	printf("start\n");




}
void Bsp_Data_Init(unsigned char* p1, short* p2)
{
	USART1_Data_Init(p1, p2);
}
void Bsp_Data_Init1(short* p1, short* p2, short* p3)
{
	USART1_Data_Init1(p1, p2, p3);
}
void Ctrl_robot_moving(void)
{
	int result = USART1_Parse_Robot_Speed();
	static uint8_t count = 0;
	if(result == 0)
	{
		count++;
	}
	else
		count = 0;
	if(count > 20)
	{
		count = 0;
		Ctrl_Vx = 0;
		Ctrl_Vy = 0;
		Ctrl_Vw = 0;
	}
	Can_Robot_Moving(Ctrl_Vx, Ctrl_Vy, Ctrl_Vw);
}
// main.c中循环调用此函数，避免多次修改main.c文件。
// This function is called in a loop in main.c to avoid multiple modifications to the main.c file
void Bsp_Loop(void)
{
	// Detect button down events   检测按键按下事件
	if (Key1_State(KEY_MODE_ONE_TIME))
	{
		Beep_On_Time(50);
		MPU_Get_Deviation_gyro();
	}
	Ctrl_robot_moving();
	MPU9250_Data_Send();
	Bsp_Led_Show_State_Handle();
	// The buzzer automatically shuts down when times out   蜂鸣器超时自动关闭
	Beep_Timeout_Close_Handle();
	HAL_Delay(6);
}

