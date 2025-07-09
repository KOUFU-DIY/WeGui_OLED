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

#ifndef __SH1108_H__
#define __SH1108_H__



#define SH1108_Set_Column_Address(x) 												do{LCD_Send_1Cmd(x>>4);LCD_Send_1Cmd(0x10|(x&0x0F));}while(0)//[0~127]
//工作模式
#define Page_addressing_mode			0				
#define Vertical_addressing_mode	1			
#define SH1108_Set_Memory_addressing_mode(x)								do{LCD_Send_1Cmd(0x20+x);}while(0)//[0~127]0:水平扫描模式 1:垂直扫描模式
//对比度
#define SH1108_Set_Contrast(x) 															do{LCD_Send_1Cmd(0x81);LCD_Send_1Cmd(x);}while(0)//[0~127]
		
#define SH1108_Set_Segment_Remap_dir0() 										do{LCD_Send_1Cmd(0xA0);}while(0)															//设置屏幕X扫描方向,column地址0对SEG0(默认)
#define SH1108_Set_Segment_Remap_dir1() 										do{LCD_Send_1Cmd(0xA1);}while(0)	
		
//全亮测试			
#define SH1108_Entire_Display_Off() 												do{LCD_Send_1Cmd(0xA4);}while(0)	
#define SH1108_Entire_Display_On() 													do{LCD_Send_1Cmd(0xA5);}while(0)		
//反色显示			                                                  
#define SH1108_Set_Reverse_Display_Off() 										do{LCD_Send_1Cmd(0xA6);}while(0)
#define SH1108_Set_Reverse_Display_On() 										do{LCD_Send_1Cmd(0xA7);}while(0)						
//设置屏幕驱动路数	
#define COM64_SEG160  0	
#define COM96_SEG160  1	
#define COM128_SEG160 2	
#define COM160_SEG160 3	
#define SH1108_Display_Resolution_Control(x)								do{LCD_Send_1Cmd(0xA9);LCD_Send_1Cmd(x);}while(0)		
			
//设置DCDC,过于复杂看规格书			
#define SH1108_Set_DCDC(x)																	do{LCD_Send_1Cmd(0xAD);LCD_Send_1Cmd(x);}while(0)	
//开关屏幕			
#define SH1108_Display_Off()																do{LCD_Send_1Cmd(0xAE);}while(0)															//屏幕关,休眠(默认)
#define SH1108_Display_On()																	do{LCD_Send_1Cmd(0xAF);}while(0)						
//COM扫描方向			
#define SH1108_Set_COM_Scan_Dir0() 													do{LCD_Send_1Cmd(0xC0);}while(0)															//设置屏幕Y扫描方向,COM0到COMn-1(默认)
#define SH1108_Set_COM_Scan_Dir1() 													do{LCD_Send_1Cmd(0xC8);}while(0)
//分频和时钟
#define SH1108_Set_Frequency(F_OSC,Divide_ratio)						do{LCD_Send_1Cmd(0xD5);LCD_Send_1Cmd((F_OSC<<4)|Divide_ratio);}while(0)			//([0:15],[0:15])设置内部晶振频率,设置时钟分频, 默认(7,0)
//充放电
#define SH1108_Set_Pre_charge_Period(dis_charge,pre_charge)	do{LCD_Send_1Cmd(0xD9);LCD_Send_1Cmd((dis_charge<<4)|pre_charge);}while(0)			//设置预充电(第一阶段时间,第二阶段时间), 默认(2,2)
//设定VCOM [0:63] 默认21
#define SH1108_Set_VCOMH(x)																	do{LCD_Send_1Cmd(0xDB);LCD_Send_1Cmd(x);}while(0)
//设定VSEGM [0:63] 默认21
#define SH1108_Set_VSEGM(x)																	do{LCD_Send_1Cmd(0xDC);LCD_Send_1Cmd(x);}while(0)
//设定VSL [0:15] 默认0
#define SH1108_Discharge_VSL(x)															do{LCD_Send_1Cmd(0x30+x);}while(0)

	


void SH1108_Set_Address_x(unsigned char x);
void SH1108_Set_Address_ypage(unsigned char page);
void SH1108_Set_Address_x_ypage(unsigned char x,unsigned char page);
void SH1108_Init(void);




	
	
#endif

