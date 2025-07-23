/*
	Copyright 2025 Lu Zhihao

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef STM32F103_LCD_SOFT_IIC_PORT_H
#define STM32F103_LCD_SOFT_IIC_PORT_H

#include "stm32f10x.h"



/*------------------------------------------------------
** 标准情况下,I2C最大通讯速率控制在400k
** 在屏幕通讯速率耐受较低时,建议使用"库函数"操作IO通讯,亦可减小上拉电阻
** 在屏幕通讯速率耐受较高时,建议使用"寄存器"操作IO通讯,亦可增加I2C驱动延时

------------------------------------------------------*/

/*------------------------------------------------------
** 建议在主频>24MHz时,建议使用"库函数"操作IO通讯
** 建议在主频=24MHz时,建议使用"寄存器"操作IO通讯
------------------------------------------------------*/



//-----------------IO接口定义---------------- 

//-----SCL-----
//#define LCD_SCL_Clr() do{GPIO_ResetBits(GPIOB,GPIO_Pin_10);}while(0)//库函数操作IO
//#define LCD_SCL_Set() do{GPIO_SetBits(GPIOB,GPIO_Pin_10);}while(0)//库函数操作IO
#define LCD_SCL_Clr() do{GPIOB->BRR = GPIO_Pin_10;}while(0)//寄存器操作,节省函数调用时间
#define LCD_SCL_Set() do{GPIOB->BSRR = GPIO_Pin_10;}while(0)//寄存器操作,节省函数调用时间
#define LCD_SCL_IO_Init() \
	do{\
		GPIO_InitTypeDef GPIO_InitStruct;\
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);\
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;\
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;\
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;\
		GPIO_Init(GPIOB, &GPIO_InitStruct);\
		LCD_SCL_Set();\
	}while(0)

//-----SDA-----
//#define LCD_SDA_Clr() do{GPIO_ResetBits(GPIOB,GPIO_Pin_11);}while(0)//库函数操作IO
//#define LCD_SDA_Set() do{GPIO_SetBits(GPIOB,GPIO_Pin_11);}while(0)//库函数操作IO
#define LCD_SDA_Clr() do{GPIOB->BRR = GPIO_Pin_11;}while(0)//寄存器操作,节省函数调用时间
#define LCD_SDA_Set() do{GPIOB->BSRR = GPIO_Pin_11;}while(0)//寄存器操作,节省函数调用时间
#define LCD_SDA_IO_Init() \
do{\
		GPIO_InitTypeDef GPIO_InitStruct;\
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);\
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_11;\
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;\
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_OD;\
		GPIO_Init(GPIOB, &GPIO_InitStruct);\
		LCD_SDA_Set();\
	}while(0)
	
//-----RES-----(部分屏幕可选)
//#define LCD_RES_Clr() do{GPIO_ResetBits(GPIOA,GPIO_Pin_6);}while(0)//库函数操作IO
//#define LCD_RES_Set() do{GPIO_SetBits(GPIOA,GPIO_Pin_6);}while(0)//库函数操作IO
#define LCD_RES_Clr() do{GPIOA->BRR = GPIO_Pin_6;}while(0)//寄存器操作,节省函数调用时间
#define LCD_RES_Set() do{GPIOA->BSRR = GPIO_Pin_6;}while(0)//寄存器操作,节省函数调用时间
#define LCD_RES_IO_Init() \
	do{\
		GPIO_InitTypeDef GPIO_InitStruct;\
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);\
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_6;\
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;\
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;\
		GPIO_Init(GPIOA, &GPIO_InitStruct);\
		LCD_RES_Set();\
	}while(0)

	
#define LCD_is_Busy() (0)
void LCD_delay_ms(volatile uint32_t ms);
void LCD_Send_1Cmd(uint8_t dat);//向屏幕发送1个命令
void LCD_Send_1Dat(uint8_t dat);//向屏幕发送1个数据
void LCD_Send_nDat(uint8_t *p,uint16_t num);//向屏幕发送num个数据
void LCD_Send_nCmd(uint8_t *p,uint16_t num);//向屏幕发送num个命令
void LCD_Port_Init(void);//接口初始化	
uint8_t LCD_Refresh(void);


#endif
	
	
	
