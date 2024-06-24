#ifndef __CTPIIC_H
#define __CTPIIC_H
#include "sys.h"	    
  	   		   
//IIC IO��������
#define CTP_SDA_IN()  {GPIOA->CRH&=0XFFFFFF0F;GPIOA->CRH|=8<<4*1;}
#define CTP_SDA_OUT() {GPIOA->CRH&=0XFFFFFF0F;GPIOA->CRH|=3<<4*1;}

//IO��������	 
#define CTP_IIC_SCL    PBout(5) 			//SCL     
#define CTP_IIC_SDA    PAout(9) 			//SDA	 
#define CTP_READ_SDA   PAin(9)  			//����SDA 

//IIC���в�������
void CTP_IIC_Init(void);                	//��ʼ��IIC��IO��				 
void CTP_IIC_Start(void);				//����IIC��ʼ�ź�
void CTP_IIC_Stop(void);	  				//����IICֹͣ�ź�
void CTP_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 CTP_IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
u8 CTP_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void CTP_IIC_Ack(void);					//IIC����ACK�ź�
void CTP_IIC_NAck(void);					//IIC������ACK�ź�

#endif







