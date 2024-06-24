#ifndef __CTPIIC_H
#define __CTPIIC_H
#include "sys.h"	    
  	   		   
//IIC IO方向设置
#define CTP_SDA_IN()  {GPIOA->CRH&=0XFFFFFF0F;GPIOA->CRH|=8<<4*1;}
#define CTP_SDA_OUT() {GPIOA->CRH&=0XFFFFFF0F;GPIOA->CRH|=3<<4*1;}

//IO操作函数	 
#define CTP_IIC_SCL    PBout(5) 			//SCL     
#define CTP_IIC_SDA    PAout(9) 			//SDA	 
#define CTP_READ_SDA   PAin(9)  			//输入SDA 

//IIC所有操作函数
void CTP_IIC_Init(void);                	//初始化IIC的IO口				 
void CTP_IIC_Start(void);				//发送IIC开始信号
void CTP_IIC_Stop(void);	  				//发送IIC停止信号
void CTP_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 CTP_IIC_Read_Byte(unsigned char ack);	//IIC读取一个字节
u8 CTP_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void CTP_IIC_Ack(void);					//IIC发送ACK信号
void CTP_IIC_NAck(void);					//IIC不发送ACK信号

#endif







