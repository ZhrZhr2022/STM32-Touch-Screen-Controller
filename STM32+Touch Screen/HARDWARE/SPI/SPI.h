#include "sys.h"

#ifndef _SPI_H_
#define _SPI_H_

//本测试程序使用的是硬件SPI接口驱动
//除了SPI时钟信号以及SPI读、写信号引脚不可更改，其他引脚都可以更改
//SPI的时钟引脚定义固定为PA5
//SPI的读数据引脚定义固定为PA6
//SPI的写数据引脚定义固定为PA7
 
u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte);
void SPI1_Init(void);
void SPI_SetSpeed(SPI_TypeDef* SPIx,u8 SpeedSet);

#endif
