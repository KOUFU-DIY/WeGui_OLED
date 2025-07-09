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

#include "st7796s.h"
#include "lcd_wegui_driver.h"



void ST7796S_Set_Addr(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{

	//发送数据
	uint8_t i[]={0x2a,x1>>8,x1&0xff,x2>>8,x2&0xff};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	uint8_t j[]={0x2b,y1>>8,y1&0xff,y2>>8,y2&0xff};
	LCD_Send_nCmd((uint8_t*)j,sizeof(j)/sizeof(uint8_t));
	const uint8_t k[]={0x2c};
	LCD_Send_nCmd((uint8_t*)k,sizeof(k)/sizeof(uint8_t));

	
}



void ST7796S_Soft_Reset()
{
	const uint8_t i[]={0x01};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7796S_Sleep_In()
{
	//Sleep out
	const uint8_t i[]={0x10};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7796S_Sleep_Out()
{
	//Sleep out
	const uint8_t i[]={0x11};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7796S_Partial_Mode_On()
{
	const uint8_t i[]={0x12};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7796S_Partial_Mode_Off()
{
	const uint8_t i[]={0x13};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7796S_Inversion_Off()
{
	const uint8_t i[]={0x20};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7796S_Inversion_On()
{
	const uint8_t i[]={0x21};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7796S_Display_Off()
{
	const uint8_t i[]={0x28};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7796S_Display_On()
{
	const uint8_t i[]={0x29};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7796S_TE_Line_Off()
{
	const uint8_t i[]={0x34};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7796S_TE_Line_On()
{
	#define TELOM 1//[0:1]When TELOM =’0’: The Tearing Effect output line consists of V-Blanking information only
	const uint8_t i[]={0x35,TELOM};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7796S_Idle_Off()
{
	const uint8_t i[]={0x38};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7796S_Idle_On()
{
	const uint8_t i[]={0x39};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7796S_Set_RGB565_Mode()
{
	uint8_t i[]={0x3A,0x05};//65k(RGB565)
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7796S_Set_RGB666_Mode()
{
	uint8_t i[]={0x3A,0x06};//262k(RGB666)
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7796S_Set_RGB888_Mode()
{
	uint8_t i[]={0x3A,0x07};//16M(RGB888)
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7796S_Clear()//清除IC显示缓存
{
	uint32_t i;
	
//	ST7796S_Set_Addr(0,0,320-1,480-1);
//	i=0;
//	while(i++<320*480)
//	{
//		//LCD_Send_1Dat(0x33);LCD_Send_1Dat(0x33);//测试
//		LCD_Send_1Dat(0x00);LCD_Send_1Dat(0x00);
//	}
	
	ST7796S_Set_Addr(0,0,480-1,480-1);
	i=0;
	while(i++<480*480)
	{
		//LCD_Send_1Dat(0x33);LCD_Send_1Dat(0x33);//测试
		LCD_Send_1Dat(0x00);LCD_Send_1Dat(0x00);
	}
	
}



//自定义初始化示例
//void ST7796S_Init()
//{
//	ST7735_Soft_Reset();
//	LCD_RES_Clr();
//	LCD_Delay(100);
//	LCD_RES_Set();
//	LCD_Delay(100);
//	
//  LCD_delay_ms(100);
//	
//	LCD_Send_1Cmd(0x11);//Sleep exit 
//	LCD_delay_ms(120);
//		
//	//ST7735R Frame Rate
//	LCD_Send_1Cmd(0xB1); 
//	LCD_Send_1Dat(0x01); 
//	LCD_Send_1Dat(0x2C); 
//	LCD_Send_1Dat(0x2D); 

//	LCD_Send_1Cmd(0xB2); 
//	LCD_Send_1Dat(0x01); 
//	LCD_Send_1Dat(0x2C); 
//	LCD_Send_1Dat(0x2D); 

//	LCD_Send_1Cmd(0xB3); 
//	LCD_Send_1Dat(0x01); 
//	LCD_Send_1Dat(0x2C); 
//	LCD_Send_1Dat(0x2D); 
//	LCD_Send_1Dat(0x01); 
//	LCD_Send_1Dat(0x2C); 
//	LCD_Send_1Dat(0x2D); 
//	
//	LCD_Send_1Cmd(0xB4); //Column inversion 
//	LCD_Send_1Dat(0x07); 
//	
//	//ST7735R Power Sequence
//	LCD_Send_1Cmd(0xC0); 
//	LCD_Send_1Dat(0xA2); 
//	LCD_Send_1Dat(0x02); 
//	LCD_Send_1Dat(0x84); 
//	LCD_Send_1Cmd(0xC1); 
//	LCD_Send_1Dat(0xC5); 

//	LCD_Send_1Cmd(0xC2); 
//	LCD_Send_1Dat(0x0A); 
//	LCD_Send_1Dat(0x00); 

//	LCD_Send_1Cmd(0xC3); 
//	LCD_Send_1Dat(0x8A); 
//	LCD_Send_1Dat(0x2A); 
//	LCD_Send_1Cmd(0xC4); 
//	LCD_Send_1Dat(0x8A); 
//	LCD_Send_1Dat(0xEE); 
//	
//	LCD_Send_1Cmd(0xC5); //VCOM 
//	LCD_Send_1Dat(0x0E); 
//	
//	//方向选择其一
//	LCD_Send_1Cmd(0x36);
//	LCD_Send_1Dat(0xC8);//方向1
//	//LCD_Send_1Dat(0x08);//方向2
//	//LCD_Send_1Dat(0x78);//方向3
//	//LCD_Send_1Dat(0xA8);//方向4
//	
//	//ST7735R Gamma Sequence
//	LCD_Send_1Cmd(0xe0); 
//	LCD_Send_1Dat(0x0f); 
//	LCD_Send_1Dat(0x1a); 
//	LCD_Send_1Dat(0x0f); 
//	LCD_Send_1Dat(0x18); 
//	LCD_Send_1Dat(0x2f); 
//	LCD_Send_1Dat(0x28); 
//	LCD_Send_1Dat(0x20); 
//	LCD_Send_1Dat(0x22); 
//	LCD_Send_1Dat(0x1f); 
//	LCD_Send_1Dat(0x1b); 
//	LCD_Send_1Dat(0x23); 
//	LCD_Send_1Dat(0x37); 
//	LCD_Send_1Dat(0x00); 	
//	LCD_Send_1Dat(0x07); 
//	LCD_Send_1Dat(0x02); 
//	LCD_Send_1Dat(0x10); 

//	LCD_Send_1Cmd(0xe1); 
//	LCD_Send_1Dat(0x0f); 
//	LCD_Send_1Dat(0x1b); 
//	LCD_Send_1Dat(0x0f); 
//	LCD_Send_1Dat(0x17); 
//	LCD_Send_1Dat(0x33); 
//	LCD_Send_1Dat(0x2c); 
//	LCD_Send_1Dat(0x29); 
//	LCD_Send_1Dat(0x2e); 
//	LCD_Send_1Dat(0x30); 
//	LCD_Send_1Dat(0x30); 
//	LCD_Send_1Dat(0x39); 
//	LCD_Send_1Dat(0x3f); 
//	LCD_Send_1Dat(0x00); 
//	LCD_Send_1Dat(0x07); 
//	LCD_Send_1Dat(0x03); 
//	LCD_Send_1Dat(0x10);  
//	
//	LCD_Send_1Cmd(0x2a);
//	LCD_Send_1Dat(0x00);
//	LCD_Send_1Dat(0x00);
//	LCD_Send_1Dat(0x00);
//	LCD_Send_1Dat(0x7f);

//	LCD_Send_1Cmd(0x2b);
//	LCD_Send_1Dat(0x00);
//	LCD_Send_1Dat(0x00);
//	LCD_Send_1Dat(0x00);
//	LCD_Send_1Dat(0x9f);
//	
//	LCD_Send_1Cmd(0xF0); //Enable test command  
//	LCD_Send_1Dat(0x01); 
//	LCD_Send_1Cmd(0xF6); //Disable ram power save mode 
//	LCD_Send_1Dat(0x00); 
//	
//	LCD_Send_1Cmd(0x3A); //65k mode 
//	LCD_Send_1Dat(0x05); 

//	ST7735_Clear();//清除IC显示缓存
//	LCD_Send_1Cmd(0x29);//Display on	 
//}



void ST7796S_Init()    
{
	LCD_RES_Clr();
	LCD_delay_ms(100);
	LCD_RES_Set();
	LCD_delay_ms(100);
	
	//ST7796S_Soft_Reset();
	ST7796S_Sleep_Out();
	LCD_delay_ms(120);
	
	{
		//CSCON (F0h): Command Set Control
		//使能设置1
		const uint8_t i[]={0xF0,0xC3};//C3h enable command 2 part I
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		//CSCON (F0h): Command Set Control
		//使能设置2
		const uint8_t i[]={0xF0,0x96};//96h enable command 2 part II
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	
	{
		//MADCTL (36h): Memory Data Access Control
		//设置显示方向
		#define MADCTL_MY 0//[0:1]Row Address Order
		#define MADCTL_MX 1//[0:1]Column Address Order
		#define MADCTL_MV 0//[0:1]Row/Column Exchange
		#define MADCTL_ML 0//[0:1]Vertical Refresh Order 0="LCD vertical refresh Top to Bottom" 1="LCD vertical refresh Bottom to Top"
		#define MADCTL_RGB 1//[0:1]Color selector switch control 0=RGB 1=BGR
		#define MADCTL_MH 0//[0:1]Horizontal Refresh Order 0="LCD horizontal refresh Left to right" 1="LCD horizontal refresh right to left"
		const uint8_t i[]={0x36,(MADCTL_MY<<7)|(MADCTL_MX<<6)|(MADCTL_MV<<5)|(MADCTL_ML<<4)|(MADCTL_RGB<<3)|(MADCTL_MH<<2)};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	

	
	
	{
		//FRMCTR1 (B1h): Frame Rate Control (In normal mode/ Full colors)
		
		//默认
		//#define FRMCTR1_FRS 10//[0~31]
		//#define FRMCTR1_DIVA 0//[0~2] 0=FOSC 1=FOSC/2 2=FOSC/4 3=FOSC/8
		//#define FRMCTR1_RTNA 16//[0~31]
		
		//自定义 数值越小, 刷新越快
		#define FRMCTR1_FRS 10//[0~31]
		#define FRMCTR1_DIVA 0//[0~2] 0=FOSC 1=FOSC/2 2=FOSC/4 3=FOSC/8
		#define FRMCTR1_RTNA 16//[0~31]
		
		//刷新率=1/(138*RTNA+(32*15*FRS)*(480+VFP+VBP))
		const uint8_t i[]={0xB1,(FRMCTR1_FRS<<4)|FRMCTR1_DIVA,FRMCTR1_RTNA};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	/*
	{
		//FRMCTR2 (B2h): Frame Rate Control (In Idle mode/ 8-colors)
		const uint8_t i[]={0xB2,0x00,0x10};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
		while(Get_DMA_Busy_State()!=0){};
	}
	{
		//FRMCTR3 (B3h): Frame Rate Control (In Partial mode/ full colors)
		const uint8_t i[]={0xB3,0x10};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
		while(Get_DMA_Busy_State()!=0){};
	}
	
	{
		//INVCTR (B4h): Display Inversion Control
		//Display inversion control
		//0=Column inversion
		//1= 1-dot inversion
		//2= 2-dot inversion
		const uint8_t i[]={0xB4,0x01};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
		while(Get_DMA_Busy_State()!=0){};
	}
	{
		//BPC(B5): Blanking Porch Control
		const uint8_t i[]={0xB4,0x02,0x02,0x00,0x04};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
		while(Get_DMA_Busy_State()!=0){};
	}
	
	{
		//DFC(B6): Display Function Control
		//行排列模式 控制模式等
		//#define DFC_RM  0 //0="System Interface" 1="RGB interface"
		//#define DFC_RCM 0 //RGB transfer mode 0="DE Mode" 1="SYNC Mode"
		//#define DFC_BYPASS 0 //Display data path 0="Memory" 1="Direct to shift register"
		//#define DFC_PTG 0 //Display data path 0="Memory" 1="Direct to shift register"
		const uint8_t i[]={0xB6,0x80,0x02,0x3B};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
		while(Get_DMA_Busy_State()!=0){};
	}
	
	{
		//EM(B7): Entry Mode Setl
		//行排列模式 控制模式等
		const uint8_t i[]={0xB7,0x06};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
		while(Get_DMA_Busy_State()!=0){};
	}
	{
		//PWR1(C0h): Power Control 1
		const uint8_t i[]={0xC0,0x80,0x25};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
		while(Get_DMA_Busy_State()!=0){};
			
	} 
	
	{
		//Power Control 2
		const uint8_t i[]={0xC1,0x13};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
		while(Get_DMA_Busy_State()!=0){};
	} 

	{
		//Power Control 3 (in Normal mode/ Full colors)
		#define PWR3_SOP 2//[0:3]Source driving current level
		#define PWR3_GOP 2//[0:3]Gamma driving current level
		const uint8_t i[]={0xC2,((PWR3_SOP<<2)|PWR3_GOP)};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
		while(Get_DMA_Busy_State()!=0){};
	}

	{
		//VCM Offset (C6h): Vcom Offset Register
		const uint8_t i[]={0xC6,0x00};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
		while(Get_DMA_Busy_State()!=0){};
	}
	
	//NVMADW (D0h): NVM Address/Data Write
	//NVMBPROG (D1h): NVM Byte Program
	//NVM Status Read(D2h)
	//RDID4 (D3h): Read ID4

	*/

	{
		//GMCTRP1 (E0h): Gamma (‘+’polarity) Correction Characteristics Setting
		uint8_t i[]={0xE0,0xF0,0x03,0x0A,0x11,0x14,0x1C,0x3B,0x55,0x4A,0x0A,0x13,0x14,0x1C,0x1F};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		//GMCTRN1 (E1h): Gamma ‘-’polarity Correction Characteristics Setting
		uint8_t i[]={0xE1,0xF0,0x03,0x0A,0x0C,0x0C,0x09,0x36,0x54,0x49,0x0F,0x1B,0x18,0x1B,0x1F};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	
	
	
	{
		//CSCON (F0h): Command Set Control
		//关闭设置1
		const uint8_t i[]={0xF0,0x3C};//C3h enable command 2 part I
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		//CSCON (F0h): Command Set Control
		//关闭设置2
		const uint8_t i[]={0xF0,0x69};//96h enable command 2 part II
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	//DGC1(E2h): Digital Gamma Control 1
	//DGC2 (E3h): Digital Gamma Control 2
	//DOCA (E8h): Display Output Ctrl Adjust
	
	//ST7796S_TE_Line_On();
	ST7796S_Set_RGB565_Mode();
	//ST7796S_Set_RGB666_Mode();
	//ST7796S_Set_RGB888_Mode();
	
	{
		//CSCON (F0h): Command Set Control
		//关闭特殊设置1
		const uint8_t i[]={0xF0,0x3C};//C3h enable command 2 part I
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		//CSCON (F0h): Command Set Control
		//使能特殊设置2
		const uint8_t i[]={0xF0,0x69};//96h enable command 2 part II
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	
	ST7796S_Clear();//清除IC显示缓存
	
	
	{
		uint8_t i[]={0x29};//Display on
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
}
