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

#include "ssd1327.h"
#include "lcd_wegui_driver.h"


/*--------------------------------------------------------------
  * 名称: SSD1327_Set_Address_x(unsigned char x)
  * 传入: unsigned char x
  * 返回: 无
  * 功能: 向屏幕设置x方向的"光标"
----------------------------------------------------------------*/
void SSD1327_Set_Addr_x(unsigned char x0,unsigned char x1)
{
	LCD_Send_1Cmd(0x15);//CMD
	LCD_Send_1Cmd(x0);//START
	LCD_Send_1Cmd(x1);//END
	//SSD1327_Set_Column_Address(0,127);//15h start[0:127]默认0,end[0:127]默认127
}

/*--------------------------------------------------------------
  * 名称: SSD1327_Set_Address_y(unsigned char page)
  * 传入: page
  * 返回: 无
  * 功能:
  * 说明:
----------------------------------------------------------------*/
void SSD1327_Set_Addr_y(unsigned char y0,unsigned char y1)
{
	LCD_Send_1Cmd(0x75);//CMD
	LCD_Send_1Cmd(y0);//START
	LCD_Send_1Cmd(y1);//END
}

void SSD1327_Set_Addr(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1)
{
	//方式1:单字节发送
	//SSD1327_Set_Addr_x(x0,x1);
	//SSD1327_Set_Addr_y(y0,y1);
	
	//方式2:连续发送(优化等级开高了可能有问题)
	uint8_t i[]={0x15,x0,x1,0x75,y0,y1};
	LCD_Send_nCmd(i,6);
}



/*--------------------------------------------------------------
  * 名称: SSD1327_Clear()
  * 传入: 无
  * 返回: 无
  * 功能: 清空IC内部图像寄存器
  * 说明: 
----------------------------------------------------------------*/
void SSD1327_Clear()
{
	uint32_t i;
	SSD1327_Set_Addr(0,0,127,127);
	for(i=0;i<128*128/2;i++)
	{
			LCD_Send_1Dat(0x00);
	}
}



void SSD1327_Init(void)
{
	LCD_Send_1Cmd(0xae);//Set display off
	
	//控制刷屏方向1
	#define A0_Bit0_SEG_REMAPPING      1
	#define A0_Bit1_NIBBLE_REMAPPING   0
	#define A0_Bit2_INC_MODE           1
	#define A0_Bit4_COM_REMAPPING      0
	#define A0_Bit6_SPLITTING_COM_MODE 1
	//控制刷屏方向2
//	#define A0_Bit0_SEG_REMAPPING      1 //SEG镜像
//	#define A0_Bit1_NIBBLE_REMAPPING   0 //根据屏幕制造商设置
//	#define A0_Bit2_INC_MODE           0 //90度旋转(连点不转,因此需要与驱动匹配)
//	#define A0_Bit4_COM_REMAPPING      1 //COM镜像
//	#define A0_Bit6_SPLITTING_COM_MODE 1 //根据屏幕制造商设置
	LCD_Send_1Cmd(0xa0);//Set re-map
	LCD_Send_1Cmd((A0_Bit6_SPLITTING_COM_MODE<<6)|(A0_Bit4_COM_REMAPPING<<4)|(A0_Bit2_INC_MODE<<2)|(A0_Bit1_NIBBLE_REMAPPING<<1)|A0_Bit0_SEG_REMAPPING);//
	
	LCD_Send_1Cmd(0xa1);//Set display start line
	LCD_Send_1Cmd(0x00);
	LCD_Send_1Cmd(0xa2);//Set display offset
	LCD_Send_1Cmd(0x00);
	LCD_Send_1Cmd(0xa4);//Normal Display
	LCD_Send_1Cmd(0xa8);//Set multiplex ratio
	LCD_Send_1Cmd(0x7f);
	LCD_Send_1Cmd(0xab);//Function Selection A
	LCD_Send_1Cmd(0x01);//Enable internal VDD regulator
	LCD_Send_1Cmd(0x81);//Set contrast
	LCD_Send_1Cmd(0x77);
	LCD_Send_1Cmd(0xb1);//Set Phase Length
	LCD_Send_1Cmd(0x31);
	LCD_Send_1Cmd(0xb3);//Set Front Clock Divider /Oscillator Frequency
	LCD_Send_1Cmd(0xb1);
  LCD_Send_1Cmd(0xb5);//
  LCD_Send_1Cmd(0x03);//0X03 enable
	LCD_Send_1Cmd(0xb6);//Set Second pre-charge Period
	LCD_Send_1Cmd(0x0d);
	LCD_Send_1Cmd(0xbc);//Set Pre-charge voltage
	LCD_Send_1Cmd(0x07);
	LCD_Send_1Cmd(0xbe);//Set VCOMH
	LCD_Send_1Cmd(0x07);
	LCD_Send_1Cmd(0xd5);//Function Selection B
	LCD_Send_1Cmd(0x02);//Enable second pre-charge
	SSD1327_Clear();
	LCD_Send_1Cmd(0xaf);//Display on
}



	
	

//void SSD1327_Init(void)
//{
//	SSD1327_Display_OFF();//AEh 屏幕关,休眠(默认)
//	
//	//---------------根据屏幕设置--------------
//	SSD1327_Set_Remap(0x66);//A0h 设置屏幕映射位置 默认0x00
//	//SSD1327_Set_Remap(0x55);//A0h 设置屏幕映射位置 默认0x00
//	//---------------根据屏幕设置--------------
//	
//	SSD1327_Set_Display_Start_Line(0);//A1h [0:127]默认0
//	SSD1327_Set_Display_Offset(0);//A2h [0:127]默认0
//	
//	SSD1327_Set_Display_Mode_A4();//A4h Normal display (默认)
//	//SSD1327_Set_Display_Mode_A5();//A5h All ON (All pixels have gray scale of 15, GS15)
//	//SSD1327_Set_Display_Mode_A6();//A6h All OFF (All pixels have gray scale of 0, GS0)
//	//SSD1327_Set_Display_Mode_A7();//A7h Inverse Display (GS0 -> GS15, GS1 -> GS14, GS2 -> GS13, ...)
//	
//	SSD1327_Set_MUX_Ratio(127);//A8h [15:127] 15=16MUX;127=128MUX(默认)
//	
//		//SSD1327_Func_A_Select_external_VDD();//ABh 0x00
//	SSD1327_Func_A_Select_internal_VDD();//ABh 0x01 默认
//	
//	SSD1327_Set_Contrast_Control(0x77);//81h 设置对比度[0:255]默认127
//	
//	SSD1327_Set_Phase_Length(3,1);//B1h 充放电周期(周期1[0:15],周期2[0:15]), 默认(7,8)
//	
//	Set_Front_Clock_Frequency(0xb1);//B3h [0x00:0xFF] 默认0x00 b7~b4设置晶振 b3~b0设置分频
//	
//	//GPIO_Hiz_input_dis()  ;//B5h 0x00
//	//GPIO_Hiz_input_en()   ;//B5h 0x01 
//	//GPIO_Hiz_output_Low() ;//B5h 0x02 默认
//	GPIO_Hiz_output_High();//B5h 0x03
//	
//	SSD1327_Set_VCOMH(0x07);//BEh [0x00,0x0F] 默认0x05
//	
//	//#define dis_2_precharge  0 //默认
//	//#define en_2_precharge   1
//	//#define Internal_VSL   0 //默认
//	//#define external_VSL   1
//	SSD1327_Func_Selection_B(en_2_precharge,Internal_VSL);//D5h 默认(0x0,0x0)
//	
//	SSD1327_Set_Pre_charge_voltage(0x07);//BCh [0x00,0x0F] 默认0x05
//	
//	
//	
//	//------非必要-----
//	//Set_Gray_Scale_Table(y0,y1,y2,y3,y4,y5,y6,y7,y8,y9,y10,y11,y12,y13,y14,y15);//B8h 灰度设置
//	//SSD1327_Set_Command_Lock()  ;//FDh 0x16
//	//SSD1327_Set_Command_unLock();//FDh 0x12 (默认)
//	//------非必要-----



//	SSD1327_Clear();
//	SSD1327_Display_ON();//AFh 屏幕开
//	

//}
