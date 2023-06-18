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


// main.c中循环调用此函数，避免多次修改main.c文件。
// This function is called in a loop in main.c to avoid multiple modifications to the main.c file
void Bsp_Loop(int i)
{

	// Detect button down events   检测按键按下事件
	if (Key1_State(KEY_MODE_ONE_TIME))
	{

		Beep_On_Time(50);
		if(i % 5 == 0)
		{
			Can_Test_Send3();
		}
		else if(i % 5 == 1)
		{
			Can_Test_Send4();
		}
		else if(i % 5 == 2)
		{
			Can_Test_Send5();
		}
		else if(i % 5 == 3)
		{
			Can_Test_Send6();
		}
		else
		{
			Can_Test_Send2();
		}


	}

	Bsp_Led_Show_State_Handle();
	// The buzzer automatically shuts down when times out   蜂鸣器超时自动关闭
	Beep_Timeout_Close_Handle();
	HAL_Delay(10);
}
void Bsp_Loop1(int i)
{

	// Detect button down events   检测按键按下事件
	if (Key1_State(KEY_MODE_ONE_TIME))
	{
		if(i % 2 == 0)
		{
			Can_Test_Send3();
		}
		else
		{
			Can_Test_Send7();
		}
	}

	Bsp_Led_Show_State_Handle();
	// The buzzer automatically shuts down when times out   蜂鸣器超时自动关闭
	Beep_Timeout_Close_Handle();
	HAL_Delay(10);
}
