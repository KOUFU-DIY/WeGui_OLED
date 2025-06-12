#ifndef STM32F103_SOFT_4SPI_PORT_H
#define STM32F103_SOFT_4SPI_PORT_H

#include "stm32f10x.h"


/*------------------------------------------------------
** 但在屏幕通讯速率耐受较低时,建议使用"库函数"操作IO通讯
** 但在屏幕通讯速率耐受较高时,建议使用"寄存器"操作IO通讯
------------------------------------------------------*/




//-----------------IO接口定义---------------- 

//-----SCL-----
//#define OLED_SCL_Clr() do{GPIO_ResetBits(GPIOA,GPIO_Pin_5);}while(0)//库函数操作IO
//#define OLED_SCL_Set() do{GPIO_SetBits(GPIOA,GPIO_Pin_5);}while(0)//库函数操作IO
#define OLED_SCL_Clr() do{GPIOA->BRR = GPIO_Pin_5;}while(0)//直接寄存器操作,节省函数调用时间
#define OLED_SCL_Set() do{GPIOA->BSRR = GPIO_Pin_5;}while(0)//直接寄存器操作,节省函数调用时间
#define OLED_SCL_IO_Init() \
	do{\
		GPIO_InitTypeDef GPIO_InitStruct;\
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);\
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_5;\
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;\
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;\
		GPIO_Init(GPIOA, &GPIO_InitStruct);\
		OLED_SCL_Set();\
	}while(0)

//-----SDA-----
//#define OLED_SDA_Clr() do{GPIO_ResetBits(GPIOA,GPIO_Pin_7);}while(0)//库函数操作IO
//#define OLED_SDA_Set() do{GPIO_SetBits(GPIOA,GPIO_Pin_7);}while(0)//库函数操作IO
#define OLED_SDA_Clr() do{GPIOA->BRR = GPIO_Pin_7;}while(0)//寄存器操作,节省函数调用时间
#define OLED_SDA_Set() do{GPIOA->BSRR = GPIO_Pin_7;}while(0)//寄存器操作,节省函数调用时间
#define OLED_SDA_IO_Init() \
	do{\
		GPIO_InitTypeDef GPIO_InitStruct;\
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);\
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_7;\
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;\
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;\
		GPIO_Init(GPIOA, &GPIO_InitStruct);\
		OLED_SDA_Set();\
	}while(0)

//-----RES-----
//#define OLED_RES_Clr() do{GPIO_ResetBits(GPIOB,GPIO_Pin_10);}while(0)//库函数操作IO
//#define OLED_RES_Set() do{GPIO_SetBits(GPIOB,GPIO_Pin_10);}while(0)//库函数操作IO
#define OLED_RES_Clr() do{GPIOB->BRR = GPIO_Pin_10;}while(0)//寄存器操作,节省函数调用时间
#define OLED_RES_Set() do{GPIOB->BSRR = GPIO_Pin_10;}while(0)//寄存器操作,节省函数调用时间
#define OLED_RES_IO_Init() \
	do{\
		GPIO_InitTypeDef GPIO_InitStruct;\
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);\
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;\
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;\
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;\
		GPIO_Init(GPIOB, &GPIO_InitStruct);\
		OLED_RES_Set();\
	}while(0)

//-----DC-----
//#define OLED_DC_Clr()  do{GPIO_ResetBits(GPIOB,GPIO_Pin_11);}while(0)//库函数操作IO
//#define OLED_DC_Set()  do{GPIO_SetBits(GPIOB,GPIO_Pin_11);}while(0)//库函数操作IO
#define OLED_DC_Clr() do{GPIOB->BRR = GPIO_Pin_11;}while(0)//寄存器操作,节省函数调用时间
#define OLED_DC_Set() do{GPIOB->BSRR = GPIO_Pin_11;}while(0)//寄存器操作,节省函数调用时间
#define OLED_DC_IO_Init() \
	do{\
		GPIO_InitTypeDef GPIO_InitStruct;\
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);\
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_11;\
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;\
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;\
		GPIO_Init(GPIOB, &GPIO_InitStruct);\
		OLED_DC_Set();\
	}while(0)

//-----CS-----(可选)
//#define OLED_CS_Clr()  do{GPIO_ResetBits(GPIOA,GPIO_Pin_6);}while(0)//库函数操作IO
//#define OLED_CS_Set()  do{GPIO_SetBits(GPIOA,GPIO_Pin_6);}while(0)//库函数操作IO
#define OLED_CS_Clr() do{GPIOA->BRR = GPIO_Pin_6;}while(0)//寄存器操作,节省函数调用时间
#define OLED_CS_Set() do{GPIOA->BSRR = GPIO_Pin_6;}while(0)//寄存器操作,节省函数调用时间
#define OLED_CS_IO_Init() \
	do{\
		GPIO_InitTypeDef GPIO_InitStruct;\
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);\
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_6;\
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;\
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;\
		GPIO_Init(GPIOA, &GPIO_InitStruct);\
		OLED_CS_Set();\
	}while(0)

	
#define OLED_is_Busy() (0)
void OLED_delay_ms(volatile uint32_t ms);
void OLED_send_1Cmd(uint8_t dat);//向屏幕发送1个命令
void OLED_send_1Data(uint8_t dat);//向屏幕发送1个数据
void OLED_send_numData(uint8_t *p,uint16_t num);//向屏幕发送num个数据
void OLED_send_numCmd(uint8_t *p,uint16_t num);//向屏幕发送num个命令
void OLED_port_Init(void);//接口初始化	

//void OLED_Set_Address_x(unsigned char x);//设定光标x
//void OLED_Set_Address_ypage(unsigned char page);//设定光标page
void OLED_port_Init(void);//接口初始化	


#endif
	
	
