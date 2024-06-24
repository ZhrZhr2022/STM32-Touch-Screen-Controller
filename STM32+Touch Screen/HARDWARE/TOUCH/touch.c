#include "touch.h" 
#include "lcd.h"
#include "delay.h"
#include "stdlib.h"
#include "math.h"
#include "gui.h"	    

_m_tp_dev tp_dev=
{
	TP_Init,
	NULL,
	0,
	0,
 	0,	
};					
//Ĭ��Ϊtouchtype=0������.
 
/*****************************************************************************
 * @name       :u8 TP_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialization touch screen
 * @parameters :None
 * @retvalue   :0-no calibration
								1-Has been calibrated
******************************************************************************/  
u8 TP_Init(void)
{			    		   
	if(FT6336_Init())
	{
		return 1;
	}
	tp_dev.scan=FT6336_Scan;	//ɨ�躯��ָ��GT911������ɨ��
	return 0;
}


