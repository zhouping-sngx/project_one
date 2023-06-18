#include "bsp.h"

unsigned char ReceVelMode = 0x00;
short ReceVel = 2000;
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
	USART1_Init();
	Bsp_Data_Init(&ReceVelMode, &ReceVel);
	res = MPU9250_Init();
	if (res != 0)
	{
		printf("MPU9250 INIT ERROR\n");
		//while(1);
	}
	Beep_On_Time(50);
}

void Bsp_Data_Init(unsigned char* p1, short* p2)
{
	USART1_Data_Init(p1, p2);
}
// main.c中循环调用此函数，避免多次修改main.c文件。
// This function is called in a loop in main.c to avoid multiple modifications to the main.c file
void Bsp_Loop(void)
{
	// Detect button down events   检测按键按下事件
	if (Key1_State(KEY_MODE_ONE_TIME))
	{
		Beep_On_Time(50);
		static int press = 0;
		press++;
		printf("press:%d\n", press);
	}
	MPU9250_Read_Data_Handle();
	usartSendMeterData(100,200,300);
	Bsp_Led_Show_State_Handle();
	// The buzzer automatically shuts down when times out   蜂鸣器超时自动关闭
	Beep_Timeout_Close_Handle();
	HAL_Delay(10);
}
