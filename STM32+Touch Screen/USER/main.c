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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // �����ж����ȼ�����
	SystemInit();//��ʼ��RCC ����ϵͳ��ƵΪ72MHZ
  delay_init(72);	     //��ʱ��ʼ��
	LCD_Init();	   //Һ������ʼ��
	
	led_init();
	
	// ��ʼ�� RTC
	RTC_Init();


	
	while (1)
	{
		Touch_Test();		    //��������д����  
	}
}
