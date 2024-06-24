#ifndef __FT6336_H
#define __FT6336_H	
#include "sys.h"	

#define CTP_MAX_TOUCH 2

//与电容触摸屏连接的芯片引脚(未包含IIC引脚) 
//IO操作函数	 
#define FT_RST    				PAout(10)	//FT5206复位引脚
#define FT_INT    				PAin(8)		//FT5206中断引脚	

//I2C读写命令	
#define FT_CMD_WR 				0X70    	//写命令
#define FT_CMD_RD 				0X71		//读命令
  
//FT5426 部分寄存器定义 
#define FT_DEVIDE_MODE 			0x00   		//FT6336模式控制寄存器
#define FT_REG_NUM_FINGER   0x02		  //触摸状态寄存器

#define FT_TP1_REG 				0X03	  	//第一个触摸点数据地址
#define FT_TP2_REG 				0X09		  //第二个触摸点数据地址

#define FT_ID_G_CIPHER_MID    0x9F      //芯片代号（中字节） 默认值0x26
#define FT_ID_G_CIPHER_LOW    0xA0      //芯片代号（低字节） 0x01: Ft6336G  0x02: Ft6336U 
#define	FT_ID_G_LIB_VERSION		0xA1		  //版本		
#define FT_ID_G_CIPHER_HIGH   0xA3      //芯片代号（高字节） 默认0x64 
#define FT_ID_G_MODE 			    0xA4   		//FT6636中断模式控制寄存器
#define FT_ID_G_FOCALTECH_ID  0xA8      //VENDOR ID 默认值为0x11
#define FT_ID_G_THGROUP			  0x80   		//触摸有效值设置寄存器
#define FT_ID_G_PERIODACTIVE	0x88   		//激活状态周期设置寄存器


u8 FT6336_WR_Reg(u16 reg,u8 *buf,u8 len);
void FT6336_RD_Reg(u16 reg,u8 *buf,u8 len);
u8 FT6336_Init(void);
u8 FT6336_Scan(void);

#endif

















