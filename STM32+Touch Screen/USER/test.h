#ifndef __TEST_H__
#define __TEST_H__
#include "sys.h"

void DrawTestPage(u8 *str);
void Test_Color(void);
void Test_FillRec(void);
void Test_Circle(void);
void Test_Triangle(void);
void English_Font_test(void);
void Chinese_Font_test(void);
void Pic_test(void);
void Load_Drow_Dialog(void);
void Touch_Test(void);
void main_test(void);
void Rotate_Test(void);
void Test_Read(void);
void Test_Dynamic_Num(void);
void Disp_Next_Time(u8 x, u8 y, u8 size);
void Countdown_To_Next(void);
void Display_Countdown(int days, int hours, int minutes, int seconds);
void Disp_Duration() ;
void duration_ok(void);
void set_locked_time(int time);
#endif
