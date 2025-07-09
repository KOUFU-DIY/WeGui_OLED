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

#ifndef __SH1106_H__
#define __SH1106_H__


#define SH1106_Set_Column_Address(x) do{LCD_Send_1Cmd(x&0x0f);LCD_Send_1Cmd(0x10|(x>>4));}while(0) //0x00~0x07 0x20~0x27 起始位置[0:255]默认0

#define SH1106_Set_Pump_voltage_value(x) do{LCD_Send_1Cmd(0x30|x);}while(0) //30h~33h [0:2]默认2
#define SH1106_Set_Display_Start_Line(x) do{LCD_Send_1Cmd(0x40|x);}while(0) //40h~4fh [0:63]默认0
#define SH1106_Set_Contrast(x) do{LCD_Send_1Cmd(0x81);LCD_Send_1Cmd(x);}while(0) //81h [0H:FFH]默认80H

#define SH1106_Set_Segment_Remap_right() do{LCD_Send_1Cmd(0xA0);}while(0) //A0 映射方向右(默认)
#define SH1106_Set_Segment_Remap_left() do{LCD_Send_1Cmd(0xA1);}while(0) //A1 映射方向左

#define SH1106_Set_Entire_Display_OFF() do{LCD_Send_1Cmd(0xA4);}while(0) //A4 全亮测试关闭
#define SH1106_Set_Entire_Display_ON() do{LCD_Send_1Cmd(0xA5);}while(0) //A5 全亮测试开启

#define SH1106_Set_Normal_Display() do{LCD_Send_1Cmd(0xA6);}while(0) //A6 正常显示
#define SH1106_Set_Reverse_Display() do{LCD_Send_1Cmd(0xA6);}while(0) //A7 反色显示


#define SH1106_Multiplex_Ration_Data_Set(x) do{LCD_Send_1Cmd(0xA8);LCD_Send_1Cmd(x);}while(0) //A8 [0H:3FH]默认3FH

#define SH1106_DCDC_OFF() do{LCD_Send_1Cmd(0xAD);LCD_Send_1Cmd(0x8A);}while(0) //AD 8A
#define SH1106_DCDC_ON() do{LCD_Send_1Cmd(0xAD);LCD_Send_1Cmd(0x8B);}while(0) //AD 8B(默认)

#define SH1106_Display_OFF() do{LCD_Send_1Cmd(0xAE);}while(0) //AE(默认)
#define SH1106_Display_ON() do{LCD_Send_1Cmd(0xAF);}while(0) //AF

#define SH1106_Set_Common_Output_Scan_Direction_0() do{LCD_Send_1Cmd(0xC0);}while(0) //C0 com扫描方向0(默认)
#define SH1106_Set_Common_Output_Scan_Direction_1() do{LCD_Send_1Cmd(0xC8);}while(0) //C8 com扫描方向1(默认)

#define SH1106_Set_Display_Offset(x) do{LCD_Send_1Cmd(0xD3);LCD_Send_1Cmd(0);}while(0) //D3 [0:63]默认0


#define SH1106_Set_Frequency(F_OSC,Divide_ratio)	do{LCD_Send_1Cmd(0xD5);LCD_Send_1Cmd((F_OSC<<4)|Divide_ratio);}while(0)	//D5 ([0:15],[0:15])设置内部晶振频率,设置时钟分频, 默认(5,0)

#define SH1106_Set_charge_Period(dis_charge,pre_charge)	do{LCD_Send_1Cmd(0xD9);LCD_Send_1Cmd((dis_charge<<4)|pre_charge);}while(0)//D9 设置预充电(第一阶段时间,第二阶段时间), 默认(2,2)

#define SH1106_Set_Common_Pads_Hardware_Configuration_Mode0() do{LCD_Send_1Cmd(0xDA);LCD_Send_1Cmd(0x02);}while(0)//da 02
#define SH1106_Set_Common_Pads_Hardware_Configuration_Mode1() do{LCD_Send_1Cmd(0xDA);LCD_Send_1Cmd(0x12);}while(0)//da 12

#define SH1106_Set_VCOM_Deselect_Level_Mode(x) do{LCD_Send_1Cmd(0xDB);LCD_Send_1Cmd(x);}while(0)//DB [0:255]默认0x35H

#define SH1106_Read_Modify_Write()	do{LCD_Send_1Cmd(0xE0);}while(0)//E0
#define SH1106_End()	do{LCD_Send_1Cmd(0xEE);}while(0)//EE
#define SH1106_NOP()	do{LCD_Send_1Cmd(0xE3);}while(0)//E3




void SH1106_Set_Address_x(unsigned char x);
void SH1106_Set_Address_ypage(unsigned char page);
void SH1106_Set_Address_x_ypage(unsigned char x,unsigned char page);
void SH1106_Init(void);




	
	
#endif

