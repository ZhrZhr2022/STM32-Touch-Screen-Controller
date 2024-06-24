#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "touch.h"
#include "gui.h"
#include "test.h"
#include "stm32f10x.h"
#include "led.h"
#include "rtc.h"
#include "string.h"

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 配置中断优先级分组
	SystemInit();//初始化RCC 设置系统主频为72MHZ
  delay_init(72);	     //延时初始化
	LCD_Init();	   //液晶屏初始化
	
	led_init();
	
	// 初始化 RTC
	RTC_Init();


	
	while (1)
	{
		Touch_Test();		    //触摸屏手写测试  
	}
}
