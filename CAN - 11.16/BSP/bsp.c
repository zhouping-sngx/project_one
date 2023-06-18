#include "bsp.h"

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
	Can_Init();
	USART1_Init();
	Beep_On_Time(50);
	printf("start\n");
}
void Bsp_test(short* p1, short* p2,unsigned char* p3)
{
	USART1_test(p1, p2, p3);
}
void Bsp_test1(uint8_t* Rece1, uint8_t* Rece2)
{
	USART1_test1(Rece1, Rece2);
}
// main.c中循环调用此函数，避免多次修改main.c文件。
// This function is called in a loop in main.c to avoid multiple modifications to the main.c file
void Bsp_Loop(void)
{
	// Detect button down events   检测按键按下事件
	if (Key1_State(KEY_MODE_ONE_TIME))
	{
		Beep_On_Time(50);
		Can_Test_Send();
	}

	Bsp_Led_Show_State_Handle();
	// The buzzer automatically shuts down when times out   蜂鸣器超时自动关闭
	Beep_Timeout_Close_Handle();
	HAL_Delay(10);
}
void Bsp_Loop1(int rece1, int rece2)
{
	// Detect button down events   检测按键按下事件
	if (Key1_State(KEY_MODE_ONE_TIME))
	{
		Beep_On_Time(50);
		Can_Test_Send();
	}
	Can_Test_Send1(rece1, rece2);
	Bsp_Led_Show_State_Handle();
	// The buzzer automatically shuts down when times out   蜂鸣器超时自动关闭
	Beep_Timeout_Close_Handle();
	HAL_Delay(20);
}
