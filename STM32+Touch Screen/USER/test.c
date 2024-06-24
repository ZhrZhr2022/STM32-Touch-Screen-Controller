#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "delay.h"
#include "gui.h"
#include "test.h"
#include "touch.h"
#include "pic.h"
#include "ft6336.h"
#include "led.h"
#include "rtc.h"

//========================variable==========================//
u16 ColorTab[5]={RED,GREEN,BLUE,YELLOW,BRED};//定义颜色数组
u16 ColornTab[8]={RED,MAGENTA,GREEN,DARKBLUE,BLUE,BLACK,LIGHTGREEN};
const u16 POINT_COLOR_TBL = RED;

int flag_on_off = 0;
int flag_press = 0;
int flag_press_lock = 0;
int flag_press_lock_on = 0;
int flag_press_num = 0;
int flag_press_next_time = 0;
int flag_press_next_time_on = 0;
int flag_press_duration = 0;
int flag_press_duration_on = 0;
int flag_press_num_times = 0;
int flag_press_back = 0;
int flag_press_ok = 0;
int flag_status = 0;

int flag_press_rtc = 0;
int flag_press_rtc_on = 0;

int flag_lock = 0;

int new_time[22];
int pwd[6] = {1, 2, 3, 4, 5, 6};
//=====================end of variable======================//

void DrawTestPage(u8 *str)
{
	//绘制固定栏up
	LCD_Clear(WHITE);
	LCD_Fill(0,0,lcddev.width,20,BLUE);
	//绘制固定栏down
	//LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
	POINT_COLOR=WHITE;
	Gui_StrCenter(0,2,WHITE,BLUE,str,16,1);//居中显示
	//Gui_StrCenter(0,lcddev.height-18,WHITE,BLUE,"Status:Normal",16,1);//居中显示
	//绘制测试区域
	//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
}


void Touch_Button_Test(void)
{ 
	char duration_str[10]; 
	int i = 0;
	
	DrawTestPage("");
	
	POINT_COLOR = BLACK;
	LCD_ShowString(44,44,16,"Next Time",1);	
	POINT_COLOR = BLACK;
	LCD_DrawRectangle(30, 70, 130, 120);
	POINT_COLOR = BLUE;
	LCD_DrawFillRectangle(29, 69, 129, 119);
	
	Disp_Next_Time(30, 70, 16);
	
	POINT_COLOR = BLACK;
	LCD_ShowString(202,44,16,"CountDown",1);	
	POINT_COLOR = BLACK;
	LCD_DrawRectangle(190, 70, 290, 120);
	POINT_COLOR = BLUE;
	LCD_DrawFillRectangle(189, 69, 289, 119);
	
	POINT_COLOR = BLACK;
	LCD_ShowString(48,174,16,"Duration",1);	
	POINT_COLOR = BLACK;
	LCD_DrawRectangle(30, 200, 130, 250);
	POINT_COLOR = BLUE;
	LCD_DrawFillRectangle(29, 199, 129, 249);
		
	Disp_Duration();
	
	POINT_COLOR = BLACK;
	LCD_ShowString(196,174,16,"Hand Switch",1);	
	POINT_COLOR = BLACK;
	LCD_DrawRectangle(190, 200, 290, 250);
	POINT_COLOR = RED;
	LCD_DrawFillRectangle(189, 199, 289, 249);

	POINT_COLOR = WHITE;
	LCD_ShowString(228,217,16,"OFF",1);	
	
	POINT_COLOR = BLUE;
	LCD_DrawFillRectangle(0, 142, 320, 144);
	POINT_COLOR = BLUE;
	LCD_DrawFillRectangle(159, 20, 161, 267);
	POINT_COLOR = BLUE;
	LCD_DrawFillRectangle(0, 266, 320, 268);

	POINT_COLOR = RED;
	LCD_DrawFillRectangle(120, 123, 200, 173);
	POINT_COLOR = WHITE;
	LCD_ShowString(136,140,16,"LOCKED",1);

	gui_circle(225, 310, BLACK, 30, 1);
	POINT_COLOR = WHITE;
	LCD_ShowString(217,302,16,"<-",1);	
	gui_circle(290, 310, BLACK, 30, 1);
	POINT_COLOR = WHITE;
	LCD_ShowString(282,302,16,"OK",1);	
	gui_circle(30, 375, BLACK, 30, 1);
	POINT_COLOR = WHITE;
	LCD_ShowString(26,367,16,"0",1);	
	gui_circle(95, 375, BLACK, 30, 1);
	POINT_COLOR = WHITE;
	LCD_ShowString(91,367,16,"1",1);	
	gui_circle(160, 375, BLACK, 30, 1);
	POINT_COLOR = WHITE;
	LCD_ShowString(156,367,16,"2",1);	
	gui_circle(225, 375, BLACK, 30, 1);
	POINT_COLOR = WHITE;
	LCD_ShowString(221,367,16,"3",1);	
	gui_circle(290, 375, BLACK, 30, 1);
	POINT_COLOR = WHITE;
	LCD_ShowString(286,367,16,"4",1);	
	gui_circle(30, 440, BLACK, 30, 1);
	POINT_COLOR = WHITE;
	LCD_ShowString(26,432,16,"5",1);	
	gui_circle(95, 440, BLACK, 30, 1);
	POINT_COLOR = WHITE;
	LCD_ShowString(91,432,16,"6",1);	
	gui_circle(160, 440, BLACK, 30, 1);
	POINT_COLOR = WHITE;
	LCD_ShowString(156,432,16,"7",1);	
	gui_circle(225, 440, BLACK, 30, 1);
	POINT_COLOR = WHITE;
	LCD_ShowString(221,432,16,"8",1);	
	gui_circle(290, 440, BLACK, 30, 1);
	POINT_COLOR = WHITE;
	LCD_ShowString(286,432,16,"9",1);	
	

	while(1)
	{
		duration_ok();
		Disp_Time(10, 2, 16); // 显示时间
		Countdown_To_Next(); //倒计时计算
		if(flag_status){
			led_on();
		}else{
			led_off();
		}
		
		if(calendar.w_year == close_calendar.w_year && calendar.w_month == close_calendar.w_month && calendar.w_date == close_calendar.w_date && calendar.hour == close_calendar.hour && calendar.min == close_calendar.min && calendar.sec == close_calendar.sec){
			// 2分钟没有触摸，关锁
			if(flag_lock == 1){
				POINT_COLOR = RED;
				LCD_DrawFillRectangle(120, 123, 200, 173);
				POINT_COLOR = WHITE;
				LCD_ShowString(136,140,16,"LOCKED",1);
			
				LCD_Fill(10, 285, 170, 335, WHITE);
				
				POINT_COLOR = BLUE;
				LCD_DrawFillRectangle(29, 69, 129, 119);
				Disp_Next_Time(30, 70, 16);
				
				LCD_Fill(30, 285, 110, 315, WHITE); 
				POINT_COLOR = BLUE;
				LCD_DrawFillRectangle(29, 199, 129, 249);
				Disp_Duration();
				
				flag_press_next_time_on = 0;
				flag_press_duration_on = 0;
				flag_press_rtc_on = 0;
				flag_press_lock_on = 0;
				flag_lock = 0;
				
				for (i = 0; i < 20; i++) {
						new_time[i] = 0;
				}
				flag_press_num_times = 0;
			}
		}
		
		tp_dev.scan();
		if((tp_dev.sta)&(1<<0))//判断是否有点触摸？
		{
			if(flag_lock == 1){
				set_locked_time(2);
			}
			if(!(flag_press_duration_on == 1 || flag_press_next_time_on == 1)){
				if((tp_dev.y[0]>0)&&(tp_dev.y[0]<20) && flag_lock == 1)
				{
					if((tp_dev.x[0]>0)&&(tp_dev.x[0]<230))
					{
						flag_press_rtc=1;
					}
				}
			}
			if((tp_dev.y[0]>200)&&(tp_dev.y[0]<250)  && flag_lock == 1)
			{
				if((tp_dev.x[0]>190)&&(tp_dev.x[0]<290))
				{
					flag_press=1;
				}
			}
			if((tp_dev.y[0]>123)&&(tp_dev.y[0]<173))
			{
				if((tp_dev.x[0]>120)&&(tp_dev.x[0]<200))
				{
					flag_press_lock=1;
				}
			}
			if(!(flag_press_duration_on == 1 || flag_press_rtc_on == 1 || flag_status == 1)){
				if((tp_dev.y[0]>70)&&(tp_dev.y[0]<120)&&(tp_dev.x[0]>30)&&(tp_dev.x[0]<130) && flag_lock == 1)
				{
						flag_press_next_time=1;
				}
			}
			
			if(!(flag_press_rtc_on == 1 || flag_press_next_time_on == 1 || flag_status == 1)){
				if((tp_dev.y[0]>200)&&(tp_dev.y[0]<250)&&(tp_dev.x[0]>30)&&(tp_dev.x[0]<130) && flag_lock == 1)
				{
						flag_press_duration=1;
				}
			}
			if((tp_dev.x[0]>=0)&&(tp_dev.x[0]<=60))
			{
				if((tp_dev.y[0]>335)&&(tp_dev.y[0]<395)){
					flag_press_num = 10;
				}
				if((tp_dev.y[0]>400)&&(tp_dev.y[0]<460)){
					flag_press_num = 5;
				}
			}
			if((tp_dev.x[0]>=65)&&(tp_dev.x[0]<=125))
			{
				if((tp_dev.y[0]>335)&&(tp_dev.y[0]<395)){
					flag_press_num = 1;
				}
				if((tp_dev.y[0]>400)&&(tp_dev.y[0]<460)){
					flag_press_num = 6;
				}
			}
			if((tp_dev.x[0]>=130)&&(tp_dev.x[0]<=190))
			{
				if((tp_dev.y[0]>335)&&(tp_dev.y[0]<395)){
					flag_press_num = 2;
				}
				if((tp_dev.y[0]>400)&&(tp_dev.y[0]<460)){
					flag_press_num = 7;
				}
			}
			if((tp_dev.x[0]>=195)&&(tp_dev.x[0]<=255))
			{
				if((tp_dev.y[0]>335)&&(tp_dev.y[0]<395)){
					flag_press_num = 3;
				}
				if((tp_dev.y[0]>400)&&(tp_dev.y[0]<460)){
					flag_press_num = 8;
				}
				if((tp_dev.y[0]>270)&&(tp_dev.y[0]<330)){
					flag_press_back = 1;
				}
			}
			if((tp_dev.x[0]>=260)&&(tp_dev.x[0]<=320))
			{
				if((tp_dev.y[0]>335)&&(tp_dev.y[0]<395)){
					flag_press_num = 4;
				}
				if((tp_dev.y[0]>400)&&(tp_dev.y[0]<460)){
					flag_press_num = 9;
				}
				if((tp_dev.y[0]>270)&&(tp_dev.y[0]<330)){
					flag_press_ok = 1;
				}
			}
		}else{
			if(flag_press_rtc == 1 && flag_lock == 1 && flag_press_next_time_on == 0){
				if(flag_press_rtc_on == 0){
					flag_press_rtc_on = 1;
					
					POINT_COLOR = BLACK;
					LCD_DrawFillRectangle(10, 285, 170, 315);
					POINT_COLOR = WHITE;
					LCD_ShowString(14,292,16,"0000-00-00 00:00:00",1);	
				}
				flag_press_rtc = 0;
				flag_press_duration = 0;
				flag_press_next_time = 0;
			}
			
			if(flag_press == 1 && flag_lock == 1){
				if(flag_on_off == 0){
					flag_on_off = 1;
					POINT_COLOR = BLACK;
					LCD_DrawRectangle(190, 200, 290, 250);
					POINT_COLOR = BLUE;
					LCD_DrawFillRectangle(189, 199, 289, 249);
					POINT_COLOR = WHITE;
					LCD_ShowString(232,217,16,"ON",1);	
					flag_status = 1;
				}else{
					flag_on_off = 0;
					POINT_COLOR = BLACK;
					LCD_DrawRectangle(190, 200, 290, 250);
					POINT_COLOR = RED;
					LCD_DrawFillRectangle(189, 199, 289, 249);
					POINT_COLOR = WHITE;
					LCD_ShowString(228,217,16,"OFF",1);	
					flag_status = 0;
				}
				flag_press = 0;
			}
			if(flag_press_lock == 1){
				if(flag_press_lock_on == 0){
					if(flag_lock == 0){
						flag_press_num_times = 0;
						
						LCD_Fill(10, 285, 170, 335, WHITE);
						POINT_COLOR = BLACK;
						LCD_DrawFillRectangle(10, 285, 170, 315);
						POINT_COLOR = WHITE;
						LCD_ShowString(14,292,16,"|",1);
					}
					flag_press_lock_on = 1;
				}else{
					if(flag_lock == 1){
						POINT_COLOR = RED;
						LCD_DrawFillRectangle(120, 123, 200, 173);
						POINT_COLOR = WHITE;
						LCD_ShowString(136,140,16,"LOCKED",1);
					
						LCD_Fill(10, 285, 170, 335, WHITE);
						
						POINT_COLOR = BLUE;
						LCD_DrawFillRectangle(29, 69, 129, 119);
						Disp_Next_Time(30, 70, 16);
						
						LCD_Fill(30, 285, 110, 315, WHITE); 
						POINT_COLOR = BLUE;
						LCD_DrawFillRectangle(29, 199, 129, 249);
						Disp_Duration();
						
						flag_press_next_time_on = 0;
						flag_press_duration_on = 0;
						flag_press_rtc_on = 0;
						flag_lock = 0;
					}
					flag_press_lock_on = 0;
				}
				//flag_lock = 1;
				flag_press_lock = 0;
			}
			if(flag_press_num != 0){
				// 根据数字做处理
				if(flag_press_next_time_on == 1){
					if(flag_press_num_times < 19){
						LCD_Fill(14+flag_press_num_times*8, 292, 22+flag_press_num_times*8, 308, BLACK); 
						
						POINT_COLOR = BLUE;
						BACK_COLOR = BLACK;
						LCD_ShowNum(14+flag_press_num_times*8,292,(flag_press_num%10),1,16);
						
						new_time[flag_press_num_times] = (flag_press_num%10);
						
						flag_press_num_times++;
						if(flag_press_num_times == 4 || flag_press_num_times == 7|| flag_press_num_times == 10|| flag_press_num_times == 13|| flag_press_num_times == 16){
							flag_press_num_times++;
						}
					}else if(flag_press_num_times < 21){
						LCD_Fill(70+(flag_press_num_times % 19)*8, 308, 78+(flag_press_num_times % 19)*8, 324, BLACK); 
						
						POINT_COLOR = BLUE;
						BACK_COLOR = BLACK;
						LCD_ShowNum(70+(flag_press_num_times % 19)*8, 308,(flag_press_num%10),1,16);
						
						new_time[flag_press_num_times] = (flag_press_num%10);
						flag_press_num_times++;
					}
				}
				if(flag_press_rtc_on == 1 && flag_press_num_times < 19){
					LCD_Fill(14+flag_press_num_times*8, 292, 22+flag_press_num_times*8, 308, BLACK); 
					
					POINT_COLOR = BLUE;
					BACK_COLOR = BLACK;
					LCD_ShowNum(14+flag_press_num_times*8,292,(flag_press_num%10),1,16);
					
					new_time[flag_press_num_times] = (flag_press_num%10);
					
					flag_press_num_times++;
					if(flag_press_num_times == 4 || flag_press_num_times == 7|| flag_press_num_times == 10|| flag_press_num_times == 13|| flag_press_num_times == 16){
						flag_press_num_times++;
					}
				}
				if(flag_press_duration_on == 1 && flag_press_num_times < 2){
					LCD_Fill(50+flag_press_num_times*8, 292, 58+flag_press_num_times*8, 308, BLACK); 
					
					POINT_COLOR = BLUE;
					BACK_COLOR = BLACK;
					LCD_ShowNum(50+flag_press_num_times*8,292,(flag_press_num%10),1,16);
					
					new_time[flag_press_num_times] = (flag_press_num%10);
					
					flag_press_num_times++;
				}
				if(flag_press_lock_on == 1 && flag_press_num_times < 6 && flag_lock == 0){
					LCD_Fill(22+flag_press_num_times*8, 292, 30+flag_press_num_times*8, 308, BLACK); 
					
					POINT_COLOR = WHITE;
					LCD_ShowString(22+flag_press_num_times*8,292,16,"*",1); 
					
					new_time[flag_press_num_times] = (flag_press_num%10);
					
					flag_press_num_times++;
				}
				flag_press_num = 0;
			}
			if(flag_press_next_time != 0 && flag_press_duration_on == 0 && flag_lock == 1 && flag_press_rtc_on == 0){
				if(flag_press_next_time_on == 0){
					POINT_COLOR = RED;
					LCD_DrawFillRectangle(29, 69, 129, 119);
					
					Disp_Next_Time(30, 70, 16);
					
					POINT_COLOR = BLACK;
					LCD_DrawFillRectangle(10, 285, 170, 330);
					POINT_COLOR = WHITE;
					LCD_ShowString(14,292,16,"0000-00-00 00:00:00",1);	
					LCD_ShowString(70,308,16,"00 Day",1);	
					
					flag_press_next_time_on = 1;
				}
				flag_press_rtc = 0;
				flag_press_duration = 0;
				flag_press_next_time = 0;
			}	
			if(flag_press_duration != 0 && flag_press_next_time_on == 0 && flag_lock == 1 && flag_press_rtc_on == 0){
				if(flag_press_duration_on == 0){
					POINT_COLOR = RED;
					LCD_DrawFillRectangle(29, 199, 129, 249);
					
					Disp_Duration();
					
					LCD_Fill(10, 285, 170, 315, WHITE); 
					
					POINT_COLOR = BLACK;
					LCD_DrawFillRectangle(30, 285, 110, 315);
					
					POINT_COLOR = WHITE;
					sprintf(duration_str, "%02d:Min", Duration);
					LCD_ShowString(50,292,16,(u8 *)duration_str,1);	
					
					flag_press_duration_on = 1;
				}
				flag_press_rtc = 0;
				flag_press_duration = 0;
				flag_press_next_time = 0;
			}
			if(flag_press_back != 0){
				if(flag_press_next_time_on == 1){
					if(flag_press_num_times <= 19){
						if(flag_press_num_times > 0){
							flag_press_num_times--;
						}
						if(flag_press_num_times == 4 || flag_press_num_times == 7|| flag_press_num_times == 10|| flag_press_num_times == 13|| flag_press_num_times == 16){
							flag_press_num_times--;
						}
						
						new_time[flag_press_num_times] = 0;
						
						LCD_Fill(14+flag_press_num_times*8, 292, 22+flag_press_num_times*8, 308, BLACK); 
						
						POINT_COLOR = WHITE;
						BACK_COLOR = BLACK;
						LCD_ShowNum(14+flag_press_num_times*8,292,0,1,16);
					}else if(flag_press_num_times <= 21){
						if(flag_press_num_times > 0){
							flag_press_num_times--;
						}
						
						new_time[flag_press_num_times] = 0;
						LCD_Fill(70+(flag_press_num_times % 19)*8, 308, 78+(flag_press_num_times % 19)*8, 324, BLACK); 
						
						POINT_COLOR = WHITE;
						BACK_COLOR = BLACK;
						LCD_ShowNum(70+(flag_press_num_times % 19)*8,308,0,1,16);
					}
				}
				if(flag_press_rtc_on == 1){
					if(flag_press_num_times > 0){
						flag_press_num_times--;
					}
					if(flag_press_num_times == 4 || flag_press_num_times == 7|| flag_press_num_times == 10|| flag_press_num_times == 13|| flag_press_num_times == 16){
						flag_press_num_times--;
					}
					
					new_time[flag_press_num_times] = 0;
					
					LCD_Fill(14+flag_press_num_times*8, 292, 22+flag_press_num_times*8, 308, BLACK); 
					
					POINT_COLOR = WHITE;
					BACK_COLOR = BLACK;
					LCD_ShowNum(14+flag_press_num_times*8,292,0,1,16);
				}
				if(flag_press_duration_on == 1){
					if(flag_press_num_times > 0){
						flag_press_num_times--;
					}
					
					new_time[flag_press_num_times] = 0;
					
					LCD_Fill(50+flag_press_num_times*8, 292, 58+flag_press_num_times*8, 308, BLACK); 
					
					POINT_COLOR = WHITE;
					BACK_COLOR = BLACK;
					LCD_ShowNum(50+flag_press_num_times*8,292,0,1,16);
				}
				if(flag_press_lock_on == 1){
					if(flag_press_num_times > 0){
						flag_press_num_times--;
					}
					
					new_time[flag_press_num_times] = 0;
					
					LCD_Fill(22+flag_press_num_times*8, 292, 30+flag_press_num_times*8, 308, BLACK); 
				}
				
				flag_press_back = 0;
			}
			if(flag_press_ok != 0){
				if(flag_press_next_time_on == 1 && flag_press_num_times == 21){
					flag_press_num_times = 0;
					flag_press_next_time_on = 0;
					
					//做提交的操作
					//判断日期合不合法
					if(judge_date(new_time[0]*1000 + new_time[1]*100 + new_time[2]*10 + new_time[3], new_time[5]*10 + new_time[6], new_time[8]*10 + new_time[9], new_time[11]*10 + new_time[12], new_time[14]*10 + new_time[15], new_time[17]*10 + new_time[18])){
						Set_Next_Time(new_time[0]*1000 + new_time[1]*100 + new_time[2]*10 + new_time[3], new_time[5]*10 + new_time[6], new_time[8]*10 + new_time[9], new_time[11]*10 + new_time[12], new_time[14]*10 + new_time[15], new_time[17]*10 + new_time[18], RTC_Get_Week(new_time[0]*1000 + new_time[1]*100 + new_time[2]*10 + new_time[3], new_time[5]*10 + new_time[6], new_time[8]*10 + new_time[9]));
						
						T = new_time[19] * 10 + new_time[20]; 
						
						LCD_Fill(10, 285, 170, 330, WHITE); 
					}else{
						LCD_Fill(10, 285, 170, 330, WHITE); 
						POINT_COLOR = BLACK;
						LCD_DrawFillRectangle(10, 285, 170, 315);
						POINT_COLOR = RED;
						LCD_ShowString(70,292,16,"ERROR!",1);	
					}		
					POINT_COLOR = BLUE;
					LCD_DrawFillRectangle(29, 69, 129, 119);
					
					Disp_Next_Time(30, 70, 16);
					
					for (i = 0; i < 22; i++) {
						new_time[i] = 0;
					}
				}
				if(flag_press_rtc_on == 1 && flag_press_num_times == 19){
					flag_press_num_times = 0;
					flag_press_rtc_on = 0;
					//做提交的操作
					//判断日期合不合法
					if(judge_date(new_time[0]*1000 + new_time[1]*100 + new_time[2]*10 + new_time[3], new_time[5]*10 + new_time[6], new_time[8]*10 + new_time[9], new_time[11]*10 + new_time[12], new_time[14]*10 + new_time[15], new_time[17]*10 + new_time[18])){
						RTC_Set(new_time[0]*1000 + new_time[1]*100 + new_time[2]*10 + new_time[3], new_time[5]*10 + new_time[6], new_time[8]*10 + new_time[9], new_time[11]*10 + new_time[12], new_time[14]*10 + new_time[15], new_time[17]*10 + new_time[18]);
						LCD_Fill(10, 285, 170, 315, WHITE); 
					}else{
						POINT_COLOR = BLACK;
						LCD_DrawFillRectangle(10, 285, 170, 315);
						POINT_COLOR = RED;
						LCD_ShowString(70,292,16,"ERROR!",1);	
					}
					
					for (i = 0; i < 20; i++) {
						new_time[i] = 0;
					}
				}
				if(flag_press_duration_on == 1 && flag_press_num_times == 2){
					flag_press_num_times = 0;
					flag_press_duration_on = 0;
					//做提交的操作
					Duration = new_time[0]*10 + new_time[1];
					
					LCD_Fill(30, 285, 110, 315, WHITE); 
					POINT_COLOR = BLUE;
					LCD_DrawFillRectangle(29, 199, 129, 249);
					
					Disp_Duration();
					
					for (i = 0; i < 20; i++) {
						new_time[i] = 0;
					}
				}
				if(flag_press_lock_on == 1 && flag_press_num_times == 6){
					flag_press_num_times = 0;
					flag_press_lock_on = 0;
					//做提交的操作
					if(new_time[0] == pwd[0] && new_time[1] == pwd[1] && new_time[2] == pwd[2] && new_time[3] == pwd[3] && new_time[4] == pwd[4] && new_time[5] == pwd[5]){
						LCD_Fill(10, 285, 170, 315, WHITE);
											
						POINT_COLOR = BLUE;
						LCD_DrawFillRectangle(120, 123, 200, 173);
						POINT_COLOR = WHITE;
						LCD_ShowString(136,140,16,"UNLOCK",1);
					
						flag_lock = 1;
					}else{
						POINT_COLOR = BLACK;
						LCD_DrawFillRectangle(10, 285, 170, 315);
						POINT_COLOR = RED;
						LCD_ShowString(70,292,16,"ERROR!",1);	
					}
					
					for (i = 0; i < 20; i++) {
						new_time[i] = 0;
					}
				}
				flag_press_ok = 0;
			}
		}
	} 
}

void Touch_Test(void)
{
	if(tp_dev.init())
	{
		return;
	}
//	LED_Init();
	Touch_Button_Test();
}

static int prev_sec = -1;

void Disp_Time(u8 x, u8 y, u8 size) {
	char time_str[20];
	RTC_Get();  // 获取当前时间

	// 如果秒数没有变化，则不更新显示
	if (calendar.sec != prev_sec) {
		// 获取星期
		char week_str[10];
		const char* week_days[] = {" Sun", " Mon", " Tue", " Wed", " Thu", " Fri", " Sat"};
		sprintf(week_str, "%s", week_days[calendar.week]);

		// 获取年月日和时间字符串
		sprintf(time_str, "%04d-%02d-%02d %02d:%02d:%02d", calendar.w_year, calendar.w_month, calendar.w_date,
															 calendar.hour, calendar.min, calendar.sec);

		// 清除之前显示的时间
		LCD_Fill(x, y, x + 8 * 23, y + size, BLUE); // 根据字符大小计算填充区域
		LCD_Fill(x + 256, y, 320, y + size, BLUE);
		// 显示新的时间
		POINT_COLOR = WHITE;
		LCD_ShowString(x, y, size, (u8 *)time_str, 1);
		
		if(flag_status == 0){
			LCD_ShowString(x + 200, y, size, (u8 *)"STATUS:Normal", 1);
		}else{
			LCD_ShowString(x + 200, y, size, (u8 *)"STATUS:Working", 1);
		}
		
		LCD_ShowString(x + 150, y, size, (u8 *)week_str, 1);

		// 更新之前的秒数
		prev_sec = calendar.sec;
	}
}

void Disp_Next_Time(u8 x, u8 y, u8 size) {
	char data_str[20];
	char time_str[20];

	// 获取星期
	char T_str[10];
	sprintf(T_str, "%d Day", T);

	sprintf(data_str, "%04d-%02d-%02d", next_calendar.w_year, next_calendar.w_month, next_calendar.w_date);
	sprintf(time_str, "%02d:%02d:%02d", next_calendar.hour, next_calendar.min, next_calendar.sec);

	// 显示时间
	POINT_COLOR = WHITE;
	LCD_ShowString(x+10, y+1, size, (u8 *)data_str, 1);
	LCD_ShowString(x+18, y+1+16, size, (u8 *)time_str, 1);
	LCD_ShowString(x+30, y+1+32, size, (u8 *)T_str, 1);
}

void Disp_Duration() {
	char str[10];

	sprintf(str, "%2d Min", Duration);

	// 显示时间
	POINT_COLOR = WHITE;
	LCD_ShowString(56, 217, 16, (u8 *)str, 1);
}

static int prev_sec2 = -1;

void Display_Countdown(int days, int hours, int minutes, int seconds) {
	char countdown_str1[20]; // 用于存储格式化的倒计时字符串
	char countdown_str2[20]; // 用于存储格式化的倒计时字符串

	// 格式化倒计时字符串
	sprintf(countdown_str1, "%3d Day %2d H", days, hours);
	sprintf(countdown_str2, "%2d Min  %2d S", minutes, seconds);
	
	// 如果秒数没有变化，则不更新显示
	if (seconds != prev_sec2) {
		// 清除之前显示的时间
		LCD_Fill(192, 75, 288, 115, BLUE); // 根据字符大小计算填充区域
		
		// 在LCD上显示倒计时字符串
		// 请替换下面的函数调用为你实际使用的LCD显示函数
		POINT_COLOR = WHITE; // 设置字体颜色
		LCD_ShowString(192, 75, 16, (u8 *)countdown_str1, 1); // 替换为实际的LCD显示函数
		LCD_ShowString(192, 99, 16, (u8 *)countdown_str2, 1); // 替换为实际的LCD显示函数
		
		// 更新之前的秒数
		prev_sec2 = seconds;
	}
}

void Countdown_To_Next(void) {
    int days, hours, minutes, seconds;
    int year_diff, month_diff, day_diff, hour_diff, min_diff, sec_diff;
    int i = 0, j = 0;
    // 获取当前时间
    RTC_Get();

    // 如果 next_calendar 时间比当前时间 calendar 靠后，直接停止倒计时
    if (!(next_calendar.w_year > calendar.w_year ||
        (next_calendar.w_year == calendar.w_year && next_calendar.w_month > calendar.w_month) ||
        (next_calendar.w_year == calendar.w_year && next_calendar.w_month == calendar.w_month && next_calendar.w_date > calendar.w_date) ||
        (next_calendar.w_year == calendar.w_year && next_calendar.w_month == calendar.w_month && next_calendar.w_date == calendar.w_date && next_calendar.hour > calendar.hour) ||
        (next_calendar.w_year == calendar.w_year && next_calendar.w_month == calendar.w_month && next_calendar.w_date == calendar.w_date && next_calendar.hour == calendar.hour && next_calendar.min > calendar.min) ||
        (next_calendar.w_year == calendar.w_year && next_calendar.w_month == calendar.w_month && next_calendar.w_date == calendar.w_date && next_calendar.hour == calendar.hour && next_calendar.min == calendar.min && next_calendar.sec > calendar.sec))) {
        Display_Countdown(0, 0, 0, 0);
        return;
    }

    // 计算当前时间与下一个时间的时间差
    year_diff = next_calendar.w_year - calendar.w_year;
    month_diff = next_calendar.w_month - calendar.w_month;
    day_diff = next_calendar.w_date - calendar.w_date;
    hour_diff = next_calendar.hour - calendar.hour;
    min_diff = next_calendar.min - calendar.min;
    sec_diff = next_calendar.sec - calendar.sec;

    // 计算天数差
    days = year_diff * 365; // 假设每年有365天
    for (i = calendar.w_year; i < next_calendar.w_year; i++) {
        if (Is_Leap_Year(i)) {
            days++; // 如果是闰年，则天数加一
        }
    }
    // 累加月份天数
    for (j = calendar.w_month; j < next_calendar.w_month; j++) {
        days += mon_table[j - 1]; // 使用 mon_table 表来获取每个月的天数
    }
    days += day_diff;

    // 处理小时、分钟、秒钟的倒计时差
    if (sec_diff < 0) {
        sec_diff += 60;
        min_diff--;
    }
    if (min_diff < 0) {
        min_diff += 60;
        hour_diff--;
    }
    if (hour_diff < 0) {
        hour_diff += 24;
        days--;
    }

    // 显示倒计时
    Display_Countdown(days, hour_diff, min_diff, sec_diff);
}


int judge_date(int year, int month, int day, int hour, int min, int sec)
{
	if(year < 2024 || year > 2099 || month < 1 || month > 12 || day < 1 || day > 31 || hour < 0 || hour > 24 || min < 0 || min > 60 || sec < 0 || sec > 60){
		return 0;
	}else{
		if(day == 31 && (month != 1 && month != 3 && month != 5 && month != 7 && month != 8 && month != 10 && month != 12)){
			return 0;
		}
		if(month == 2 && !Is_Leap_Year(year) && day == 29){
			return 0;
		}
	}
	
	// 获取当前时间
	RTC_Get();
	if(year < calendar.w_year){
		return 0;
	}else if(year == calendar.w_year){
		 if(month < calendar.w_month){
			return 0;
		 }else if(month == calendar.w_month){
			if(day < calendar.w_date){
				return 0;
			}else if(day == calendar.w_date){
				if(hour < calendar.hour){
					return 0;
				}else if (hour == calendar.hour){
					if(min < calendar.min){
						return 0;
					}else if(min == calendar.min){
						if(sec < calendar.sec){
							return 0;
						}
					}
				}
			}
		 }
	}
	return 1;
}

void duration_ok(void)
{
    int secs = 0 ,mins = 0, hours = 0, days = 0, months = 0, years = 0, months2 = 0;
    // 获取当前时间
    RTC_Get();
    
    if(calendar.w_date == next_calendar.w_date && calendar.w_year == next_calendar.w_year && calendar.w_month == next_calendar.w_month && calendar.hour == next_calendar.hour && calendar.min == next_calendar.min && calendar.sec == next_calendar.sec){
        POINT_COLOR = BLACK;
        LCD_DrawRectangle(190, 200, 290, 250);
        POINT_COLOR = BLUE;
        LCD_DrawFillRectangle(189, 199, 289, 249);
        POINT_COLOR = WHITE;
        LCD_ShowString(232,217,16,"ON",1);    
        flag_status = 1;
    }
    secs = next_calendar.sec;
    mins = next_calendar.min + Duration;
    hours = next_calendar.hour;
    days = next_calendar.w_date;
    months = next_calendar.w_month;
    years = next_calendar.w_year;
    // 处理分钟溢出
    if (mins >= 60)
    {
        mins -= 60;
        hours++;
        if (hours >= 24)
        {
            hours -= 24;
            days++;
            if (days > mon_table[next_calendar.w_month - 1])
            {
                days = 1;
                months++;
                if (months > 12)
                {
                    months = 1;
                    years++;
                }
            }
        }
    }

    // 比较时间
    if(calendar.w_year == years && calendar.w_month == months && calendar.w_date == days && calendar.hour == hours && calendar.min == mins && calendar.sec == secs){
        POINT_COLOR = BLACK;
        LCD_DrawRectangle(190, 200, 290, 250);
        POINT_COLOR = RED;
        LCD_DrawFillRectangle(189, 199, 289, 249);
        POINT_COLOR = WHITE;
        LCD_ShowString(228,217,16,"OFF",1);    
        flag_status = 0;
			
				// 处理溢出
				days += T;
				if (days > mon_table[months - 1])
				{
						months2 = months;
						months += days / mon_table[months - 1];
						days = days % mon_table[months2 - 1];
						
						if (months > 12)
						{
								months = months % 12;
								years += months / 12;
						}
				}

				Set_Next_Time(years, months, days, hours, mins, secs, RTC_Get_Week(years, months, days));
				POINT_COLOR = BLUE;
				LCD_DrawFillRectangle(29, 69, 129, 119);
				
				Disp_Next_Time(30, 70, 16);
		}
}

void set_locked_time(int time)
{
	int mins = 0, hours = 0, days = 0, months = 0, years = 0;
	RTC_Get();
	
	mins = calendar.min + time;
	hours = calendar.hour;
	days = calendar.w_date;
	months = calendar.w_month;
	years = calendar.w_year;
	
	// 处理分钟溢出
	if (mins >= 60)
	{
			mins -= 60;
			hours++;
			if (hours >= 24)
			{
					hours -= 24;
					days++;
					if (days > mon_table[next_calendar.w_month - 1])
					{
							days = 1;
							months++;
							if (months > 12)
							{
									months = 1;
									years++;
							}
					}
			}
	}
	
	close_calendar.w_year = years;
	close_calendar.w_month = months;
	close_calendar.w_date = days;
	close_calendar.hour = hours;
	close_calendar.min = mins;
	close_calendar.sec = calendar.sec;
}