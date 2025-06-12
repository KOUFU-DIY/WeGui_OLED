#ifndef STM32F103_OLED_DMA_IIC_PORT_H
#define STM32F103_OLED_DMA_IIC_PORT_H

#include "stm32f10x.h"











//-----------------IO接口定义---------------- 

//-----SCL-----
//#define OLED_SCL_Clr() do{GPIO_ResetBits(GPIOB,GPIO_Pin_10);}while(0)//库函数操作IO
//#define OLED_SCL_Set() do{GPIO_SetBits(GPIOB,GPIO_Pin_10);}while(0)//库函数操作IO
#define OLED_SCL_Clr() do{GPIOB->BRR = GPIO_Pin_10;}while(0)//寄存器操作,节省函数调用时间
#define OLED_SCL_Set() do{GPIOB->BSRR = GPIO_Pin_10;}while(0)//寄存器操作,节省函数调用时间
#define OLED_SCL_IO_Init() \
	do{\
		GPIO_InitTypeDef GPIO_InitStruct;\
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);\
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;\
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;\
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;\
		GPIO_Init(GPIOB, &GPIO_InitStruct);\
		OLED_SCL_Set();\
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;\
		GPIO_Init(GPIOB, &GPIO_InitStruct);\
	}while(0)

//-----SDA-----
//#define OLED_SDA_Clr() do{GPIO_ResetBits(GPIOB,GPIO_Pin_11);}while(0)//库函数操作IO
//#define OLED_SDA_Set() do{GPIO_SetBits(GPIOB,GPIO_Pin_11);}while(0)//库函数操作IO
#define OLED_SDA_Clr() do{GPIOB->BRR = GPIO_Pin_11;}while(0)//寄存器操作,节省函数调用时间
#define OLED_SDA_Set() do{GPIOB->BSRR = GPIO_Pin_11;}while(0)//寄存器操作,节省函数调用时间
#define OLED_SDA_IO_Init() \
do{\
		GPIO_InitTypeDef GPIO_InitStruct;\
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);\
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_11;\
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;\
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;\
		GPIO_Init(GPIOB, &GPIO_InitStruct);\
		OLED_SDA_Set();\
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_OD;\
		GPIO_Init(GPIOB, &GPIO_InitStruct);\
	}while(0)

	
//-----RES-----(可选)
//#define OLED_RES_Clr() do{GPIO_ResetBits(GPIOA,GPIO_Pin_6);}while(0)//库函数操作IO
//#define OLED_RES_Set() do{GPIO_SetBits(GPIOA,GPIO_Pin_6);}while(0)//库函数操作IO
#define OLED_RES_Clr() do{GPIOA->BRR = GPIO_Pin_6;}while(0)//寄存器操作,节省函数调用时间
#define OLED_RES_Set() do{GPIOA->BSRR = GPIO_Pin_6;}while(0)//寄存器操作,节省函数调用时间
#define OLED_RES_IO_Init() \
	do{\
		GPIO_InitTypeDef GPIO_InitStruct;\
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);\
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_6;\
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;\
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;\
		GPIO_Init(GPIOA, &GPIO_InitStruct);\
		OLED_RES_Set();\
	}while(0)

	
	
	
void OLED_delay_ms(uint32_t ms);
void OLED_send_1Cmd(uint8_t dat);//向屏幕发送1个命令
void OLED_send_1Data(uint8_t dat);//向屏幕发送1个数据
void OLED_send_numData(uint8_t *p,uint16_t num);//向屏幕发送num个数据
void OLED_send_numCmd(uint8_t *p,uint16_t num);//向屏幕发送num个命令
//void OLED_Set_Address_x(uint8_t x);
//void OLED_Set_Address_ypage(uint8_t page);
void OLED_port_Init(void);//接口初始化	


#endif
	
	
	
