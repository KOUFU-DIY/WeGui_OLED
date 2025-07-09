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
#include "sh1106.h"
#include "lcd_wegui_driver.h"




/*--------------------------------------------------------------
  * 名称: SH1106_Set_Address_x(unsigned char x)
  * 传入: unsigned char x
  * 返回: 无
  * 功能: 向屏幕设置x方向的"光标"
----------------------------------------------------------------*/
void SH1106_Set_Address_x(unsigned char x)
{
	LCD_Send_1Cmd(x>>4);//高3字节
	LCD_Send_1Cmd(x&0x0f);//低4字节
}

/*--------------------------------------------------------------
  * 名称: SH1106_Set_Address_ypage(unsigned char page)
  * 传入: page
  * 返回: 无
  * 功能: 向屏幕设置y方向的"页page"
  * 说明: 页1page = 8个像素点
----------------------------------------------------------------*/
void SH1106_Set_Address_ypage(unsigned char page)
{
		LCD_Send_1Cmd(0xb0+page);
}

/*--------------------------------------------------------------
  * 名称: SH1106_Set_Address_x_ypage(unsigned char x,unsigned char page)
  * 传入: x,page坐标
  * 返回: 无
  * 功能: 向屏幕设置x和ypage坐标
  * 说明: 
----------------------------------------------------------------*/
void SH1106_Set_Address_x_ypage(unsigned char x,unsigned char page)
{
	//方式1:单字节发送
	//SH1106_Set_Address_x(x);
	//SH1106_Set_Address_ypage(page);
	
	//方式2:连续发送
	uint8_t i[]={((x>>4) | 0x10),(x&0x0f),0xb0+page};
	LCD_Send_nCmd(i,3);
}


/*--------------------------------------------------------------
  * 名称: SH1106_Clear()
  * 传入: 无
  * 返回: 无
  * 功能: 清空IC内部图像寄存器
  * 说明: 
----------------------------------------------------------------*/
void SH1106_Clear()
{
	unsigned char page,x;
	for(page=0;page<8;page++)
	{
		SH1106_Set_Address_ypage(page);
		SH1106_Set_Address_x(0);
		for(x=0;x<128;x++)
		{
			LCD_Send_1Dat(0x00);
			//LCD_Send_1Dat(0xff);
		}
	}
}



//void SH1106_Init(void)
//{
//	LCD_Send_1Cmd(0xAE); /*display off*/ 
//	LCD_Send_1Cmd(0x02); /*set lower column address*/ 
//	LCD_Send_1Cmd(0x10); /*set higher column address*/ 
//	LCD_Send_1Cmd(0x40); /*set display start line*/ 
//	LCD_Send_1Cmd(0xB0); /*set page address*/
//	LCD_Send_1Cmd(0x81); /*contract control*/ 
//	LCD_Send_1Cmd(0xcf); /*128*/ 
//	LCD_Send_1Cmd(0xA1); /*set segment remap*/ 
//	LCD_Send_1Cmd(0xA6); /*normal / reverse*/ 
//	LCD_Send_1Cmd(0xA8); /*multiplex ratio*/ 
//	LCD_Send_1Cmd(0x3F); /*duty = 1/64*/ 
//	LCD_Send_1Cmd(0xad); /*set charge pump enable*/ 
//	LCD_Send_1Cmd(0x8b); /* 0x8B 内供 VCC */ 
//	LCD_Send_1Cmd(0x33); /*0X30---0X33 set VPP 9V */ 
//	LCD_Send_1Cmd(0xC8); /*Com scan direction!!!!!!!!!!!!!!!!*/ 
//	LCD_Send_1Cmd(0xD3); /*set display offset*/ 
//	LCD_Send_1Cmd(0x00); /* 0x20 */ 
//	LCD_Send_1Cmd(0xD5); /*set osc division*/ 
//	LCD_Send_1Cmd(0x80); 
//	LCD_Send_1Cmd(0xD9); /*set pre-charge period*/ 
//	LCD_Send_1Cmd(0x1f); /*0x22*/ 
//	LCD_Send_1Cmd(0xDA); /*set COM pins*/ 
//	LCD_Send_1Cmd(0x12); 
//	LCD_Send_1Cmd(0xdb); /*set vcomh*/ 
//	LCD_Send_1Cmd(0x40);
//	SH1106_Clear();
//	LCD_Send_1Cmd(0xAF); /*display ON*/
//}



void SH1106_Init(void)
{
	SH1106_Display_OFF();//AE(默认)
	
	//-----------像素上下循环偏移-------------
	SH1106_Set_Column_Address(2);//0x00~0x07 0x20~0x27 起始位置[0:255]默认0
	//-----------像素上下循环偏移-------------
	
	
	SH1106_Set_Display_Start_Line(0);//40h~4fh [0h:Fh]默认0
	SH1106_Set_Contrast(0xcf);//81h [0H:FFH]默认80H
	
	//SH1106_Set_Segment_Remap_right();//A0 映射方向右(默认)
	SH1106_Set_Segment_Remap_left();//A1 映射方向左
	
	SH1106_Set_Normal_Display();//A6 正常显示
	//SH1106_Set_Reverse_Display();//A7 反色显示
	
	SH1106_Multiplex_Ration_Data_Set(0x3F);//A8 [0H:3FH]默认3FH
	
	//SH1106_DCDC_OFF();//AD 8A
	SH1106_DCDC_ON();//AD 8B(默认)
	
	SH1106_Set_Pump_voltage_value(3);//30h~33h [0h:2h]默认2
	
	//SH1106_Set_Common_Output_Scan_Direction_0();//C0 com扫描方向0(默认)
	SH1106_Set_Common_Output_Scan_Direction_1();//C8 com扫描方向1(默认)
	
	SH1106_Set_Display_Offset(0);//D3 [0:63]默认0
	SH1106_Set_Frequency(8,0);//D5 ([0:15],[0:15])设置内部晶振频率,设置时钟分频, 默认(5,0)
	
	SH1106_Set_charge_Period(0x1,0xf);//D9 设置预充电(第一阶段时间,第二阶段时间), 默认(2,2)
	
	//SH1106_Set_Common_Pads_Hardware_Configuration_Mode0();//da 02
	SH1106_Set_Common_Pads_Hardware_Configuration_Mode1();//da 12

	SH1106_Set_VCOM_Deselect_Level_Mode(0x40);//DB [0:255]默认0x35H

	SH1106_Set_Entire_Display_OFF();//A4 全亮测试关闭
	//SH1106_Set_Entire_Display_ON();//A5 全亮测试开启
	
	SH1106_Clear();
	LCD_delay_ms(200);
	SH1106_Display_ON();//AF
}
