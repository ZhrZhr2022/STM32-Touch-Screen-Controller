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
u16 ColorTab[5]={RED,GREEN,BLUE,YELLOW,BRED};//������ɫ����
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
	//���ƹ̶���up
	LCD_Clear(WHITE);
	LCD_Fill(0,0,lcddev.width,20,BLUE);
	//���ƹ̶���down
	//LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
	POINT_COLOR=WHITE;
	Gui_StrCenter(0,2,WHITE,BLUE,str,16,1);//������ʾ
	//Gui_StrCenter(0,lcddev.height-18,WHITE,BLUE,"Status:Normal",16,1);//������ʾ
	//���Ʋ�������
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
		Disp_Time(10, 2, 16); // ��ʾʱ��
		Countdown_To_Next(); //����ʱ����
		if(flag_status){
			led_on();
		}else{
			led_off();
		}
		
		if(calendar.w_year == close_calendar.w_year && calendar.w_month == close_calendar.w_month && calendar.w_date == close_calendar.w_date && calendar.hour == close_calendar.hour && calendar.min == close_calendar.min && calendar.sec == close_calendar.sec){
			// 2����û�д���������
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
		if((tp_dev.sta)&(1<<0))//�ж��Ƿ��е㴥����
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
				// ��������������
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
					
					//���ύ�Ĳ���
					//�ж����ںϲ��Ϸ�
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
					//���ύ�Ĳ���
					//�ж����ںϲ��Ϸ�
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
					//���ύ�Ĳ���
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
					//���ύ�Ĳ���
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
	RTC_Get();  // ��ȡ��ǰʱ��

	// �������û�б仯���򲻸�����ʾ
	if (calendar.sec != prev_sec) {
		// ��ȡ����
		char week_str[10];
		const char* week_days[] = {" Sun", " Mon", " Tue", " Wed", " Thu", " Fri", " Sat"};
		sprintf(week_str, "%s", week_days[calendar.week]);

		// ��ȡ�����պ�ʱ���ַ���
		sprintf(time_str, "%04d-%02d-%02d %02d:%02d:%02d", calendar.w_year, calendar.w_month, calendar.w_date,
															 calendar.hour, calendar.min, calendar.sec);

		// ���֮ǰ��ʾ��ʱ��
		LCD_Fill(x, y, x + 8 * 23, y + size, BLUE); // �����ַ���С�����������
		LCD_Fill(x + 256, y, 320, y + size, BLUE);
		// ��ʾ�µ�ʱ��
		POINT_COLOR = WHITE;
		LCD_ShowString(x, y, size, (u8 *)time_str, 1);
		
		if(flag_status == 0){
			LCD_ShowString(x + 200, y, size, (u8 *)"STATUS:Normal", 1);
		}else{
			LCD_ShowString(x + 200, y, size, (u8 *)"STATUS:Working", 1);
		}
		
		LCD_ShowString(x + 150, y, size, (u8 *)week_str, 1);

		// ����֮ǰ������
		prev_sec = calendar.sec;
	}
}

void Disp_Next_Time(u8 x, u8 y, u8 size) {
	char data_str[20];
	char time_str[20];

	// ��ȡ����
	char T_str[10];
	sprintf(T_str, "%d Day", T);

	sprintf(data_str, "%04d-%02d-%02d", next_calendar.w_year, next_calendar.w_month, next_calendar.w_date);
	sprintf(time_str, "%02d:%02d:%02d", next_calendar.hour, next_calendar.min, next_calendar.sec);

	// ��ʾʱ��
	POINT_COLOR = WHITE;
	LCD_ShowString(x+10, y+1, size, (u8 *)data_str, 1);
	LCD_ShowString(x+18, y+1+16, size, (u8 *)time_str, 1);
	LCD_ShowString(x+30, y+1+32, size, (u8 *)T_str, 1);
}

void Disp_Duration() {
	char str[10];

	sprintf(str, "%2d Min", Duration);

	// ��ʾʱ��
	POINT_COLOR = WHITE;
	LCD_ShowString(56, 217, 16, (u8 *)str, 1);
}

static int prev_sec2 = -1;

void Display_Countdown(int days, int hours, int minutes, int seconds) {
	char countdown_str1[20]; // ���ڴ洢��ʽ���ĵ���ʱ�ַ���
	char countdown_str2[20]; // ���ڴ洢��ʽ���ĵ���ʱ�ַ���

	// ��ʽ������ʱ�ַ���
	sprintf(countdown_str1, "%3d Day %2d H", days, hours);
	sprintf(countdown_str2, "%2d Min  %2d S", minutes, seconds);
	
	// �������û�б仯���򲻸�����ʾ
	if (seconds != prev_sec2) {
		// ���֮ǰ��ʾ��ʱ��
		LCD_Fill(192, 75, 288, 115, BLUE); // �����ַ���С�����������
		
		// ��LCD����ʾ����ʱ�ַ���
		// ���滻����ĺ�������Ϊ��ʵ��ʹ�õ�LCD��ʾ����
		POINT_COLOR = WHITE; // ����������ɫ
		LCD_ShowString(192, 75, 16, (u8 *)countdown_str1, 1); // �滻Ϊʵ�ʵ�LCD��ʾ����
		LCD_ShowString(192, 99, 16, (u8 *)countdown_str2, 1); // �滻Ϊʵ�ʵ�LCD��ʾ����
		
		// ����֮ǰ������
		prev_sec2 = seconds;
	}
}

void Countdown_To_Next(void) {
    int days, hours, minutes, seconds;
    int year_diff, month_diff, day_diff, hour_diff, min_diff, sec_diff;
    int i = 0, j = 0;
    // ��ȡ��ǰʱ��
    RTC_Get();

    // ��� next_calendar ʱ��ȵ�ǰʱ�� calendar ����ֱ��ֹͣ����ʱ
    if (!(next_calendar.w_year > calendar.w_year ||
        (next_calendar.w_year == calendar.w_year && next_calendar.w_month > calendar.w_month) ||
        (next_calendar.w_year == calendar.w_year && next_calendar.w_month == calendar.w_month && next_calendar.w_date > calendar.w_date) ||
        (next_calendar.w_year == calendar.w_year && next_calendar.w_month == calendar.w_month && next_calendar.w_date == calendar.w_date && next_calendar.hour > calendar.hour) ||
        (next_calendar.w_year == calendar.w_year && next_calendar.w_month == calendar.w_month && next_calendar.w_date == calendar.w_date && next_calendar.hour == calendar.hour && next_calendar.min > calendar.min) ||
        (next_calendar.w_year == calendar.w_year && next_calendar.w_month == calendar.w_month && next_calendar.w_date == calendar.w_date && next_calendar.hour == calendar.hour && next_calendar.min == calendar.min && next_calendar.sec > calendar.sec))) {
        Display_Countdown(0, 0, 0, 0);
        return;
    }

    // ���㵱ǰʱ������һ��ʱ���ʱ���
    year_diff = next_calendar.w_year - calendar.w_year;
    month_diff = next_calendar.w_month - calendar.w_month;
    day_diff = next_calendar.w_date - calendar.w_date;
    hour_diff = next_calendar.hour - calendar.hour;
    min_diff = next_calendar.min - calendar.min;
    sec_diff = next_calendar.sec - calendar.sec;

    // ����������
    days = year_diff * 365; // ����ÿ����365��
    for (i = calendar.w_year; i < next_calendar.w_year; i++) {
        if (Is_Leap_Year(i)) {
            days++; // ��������꣬��������һ
        }
    }
    // �ۼ��·�����
    for (j = calendar.w_month; j < next_calendar.w_month; j++) {
        days += mon_table[j - 1]; // ʹ�� mon_table ������ȡÿ���µ�����
    }
    days += day_diff;

    // ����Сʱ�����ӡ����ӵĵ���ʱ��
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

    // ��ʾ����ʱ
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
	
	// ��ȡ��ǰʱ��
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
    // ��ȡ��ǰʱ��
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
    // ����������
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

    // �Ƚ�ʱ��
    if(calendar.w_year == years && calendar.w_month == months && calendar.w_date == days && calendar.hour == hours && calendar.min == mins && calendar.sec == secs){
        POINT_COLOR = BLACK;
        LCD_DrawRectangle(190, 200, 290, 250);
        POINT_COLOR = RED;
        LCD_DrawFillRectangle(189, 199, 289, 249);
        POINT_COLOR = WHITE;
        LCD_ShowString(228,217,16,"OFF",1);    
        flag_status = 0;
			
				// �������
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
	
	// ����������
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