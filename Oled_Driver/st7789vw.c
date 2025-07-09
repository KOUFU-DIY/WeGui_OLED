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

#include "st7789vw.h"
#include "lcd_wegui_driver.h"





void ST7789VW_Set_Addr(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	uint8_t i[]={0x2a,x1>>8,x1&0xff,(x2)>>8,(x2)&0xff};
	uint8_t j[]={0x2b,y1>>8,(y1)&0xff,(y2)>>8,y2&0xff};
	const uint8_t k[]={0x2c};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	LCD_Send_nCmd((uint8_t*)j,sizeof(j)/sizeof(uint8_t));
	LCD_Send_nCmd((uint8_t*)k,sizeof(k)/sizeof(uint8_t));
}

void ST7789VW_Soft_Reset()//01
{
	const uint8_t i[]={0x01};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Sleep_In()//10
{
	const uint8_t i[]={0x10};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Sleep_Out()//11
{
	const uint8_t i[]={0x11};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Partial_Mode_On()//12
{
	const uint8_t i[]={0x12};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Partial_Mode_Off()//13
{
	const uint8_t i[]={0x13};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Inversion_Off()//20
{
	const uint8_t i[]={0x20};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Inversion_On()//21
{
	const uint8_t i[]={0x21};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Gamma_Set_Init()//26
{
	const uint8_t i[]={0x26,0x01};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Display_Off()//28
{
	const uint8_t i[]={0x28};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Display_On()//29
{
	const uint8_t i[]={0x29};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Partial_Area_Set()//30
{
	#define PARTAREA_PSL (0U)//起始x列
	#define PARTAREA_PEL (0U+240U)//结束x列
	const uint8_t i[5]={0x30,(PARTAREA_PSL>>8),(PARTAREA_PSL&0xff),(PARTAREA_PEL>>8),(PARTAREA_PEL&0xff)};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7789VW_Vertical_Scrolling_Definition_Set()//33
{
	/*
	#define ST7789VW_TFA 0//起始行
	#define ST7789VW_VSA 0//结束行
	#define ST7789VW_BFA 0//结束行
	const uint8_t i[5]={0x33,(ST7789VW_TFA>>8),(ST7789VW_TFA&0xff),(ST7789VW_VSA>>8),(ST7789VW_VSA&0xff),(ST7789VW_BFA>>8),(ST7789VW_BFA&0xff)};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
*/
}


void ST7789VW_TE_Line_Off()//34
{
	const uint8_t i[]={0x34};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_TE_Line_On()//35
{
	#define TELOM 0//[0:1]When TELOM =’0’: The Tearing Effect output line consists of V-Blanking information only
	const uint8_t i[]={0x35,TELOM};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Memory_Data_Access_Ctrl_Init()//36
{
	//“0” = Top to Bottom (When MADCTL D7=”0”).
	//“1” = Bottom to Top (When MADCTL D7=”1”).
	#define MADCTL_MY 0 //Y镜像
	
	//“0” = Left to Right (When MADCTL D6=”0”).
	//“1” = Right to Left (When MADCTL D6=”1”).
	#define MADCTL_MX 1 //X镜像
	
	//“0” = Normal Mode (When MADCTL D5=”0”).
	//“1” = Reverse Mode (When MADCTL D5=”1”)
	#define MADCTL_MV 0 //90度转
	
	//‘0’ =Decrement,(LCD refresh Top to Bottom, when MADCTL (36h) D4=’0’)
	//‘1’=Increment,(LCD refresh Bottom to Top, when MADCTL (36h) D4=’1’)
	#define MADCTL_ML 0
	
	//“0” = RGB (When MADCTL D3=”0”)
	//“1” = BGR (When MADCTL D3=”1”)
	#define MADCTL_RGB 1
	
	//“0” = LCD Refresh Left to Right (When MADCTL D2=”0”)
	//“1” = LCD Refresh Right to Left (When MADCTL D2=”1”)
	#define MADCTL_MH 1
	
	const uint8_t i[]={0x36,(MADCTL_MY<<7)|(MADCTL_MX<<6)|(MADCTL_MV<<5)|(MADCTL_ML<<4)|(MADCTL_RGB<<3)|(MADCTL_MH<<2)};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Vertical_Scroll_Start_Address_of_RAM(uint16_t vsp)//37
{
	uint8_t i[3]={0x37,vsp>>8,vsp&0xff};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7789VW_Idle_Off()//38
{
	const uint8_t i[]={0x38};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Idle_On()//39
{
	const uint8_t i[]={0x39};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Set_RGB444_Mode()//3A
{
	const uint8_t i[]={0x3A,0x03};//4k(RGB444)
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	
}
void ST7789VW_Set_RGB565_Mode()//3A
{
	const uint8_t i[]={0x3A,0x05};//65k(RGB565)
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	
}
void ST7789VW_Set_RGB666_Mode()//3A
{
	const uint8_t i[]={0x3A,0x06};//262k(RGB666)
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Set_RGB888_Mode()//3A
{
	const uint8_t i[]={0x3A,0x07};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7789VW_Set_Tear_Scanline()//44
{
	#define TEAR_SCANLINE 0
	const uint8_t i[]={0x44,TEAR_SCANLINE>>8U,TEAR_SCANLINE&0XFF};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Write_Display_Brightness(uint8_t bri)//51
{
	uint8_t i[]={0x51,bri};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7789VW_Write_CTRL_Display()//53
{
	//BCTRL: Brightness Control Block On/Off, This bit is always used to switch brightness for display.
	//0 = Off (Brightness register are 00h, DBV[7:0])
	//1 = On (Brightness register are active, according to the other parameters.)
	#define CTRL_BCTRL 0
	
	//DD: Display Dimming (Only for manual brightness setting)
	//DD = 0: Display Dimming is off.
	//DD = 1: Display Dimming is on.
	#define CTRL_DD 0
	
	//BL: Backlight Control On/Off
	//0 = Off (Completely turn off backlight circuit. Control lines must be low.)
	//1 = On
	#define CTRL_BL 0
	
	//Dimming function is adapted to the brightness registers for display when bit BCTRL is changed at DD=1.
	//When BL bit changed from ‘on’ to ‘off’, backlight is turned off without gradual dimming, 
	//even if dimming-on (DD=1) are selected.
	
	const uint8_t i[]={0x53,(CTRL_BCTRL<<5)|(CTRL_DD<<3)|(CTRL_BL<<2)};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7789VW_Write_Content_daptive_Brightness_Control_and_Color_Enhancement()//55
{
	const uint8_t i[]={0x55,0x00};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7789VW_Write_CABC_Minimum_Brightness()//5E
{
	const uint8_t i[]={0x5E,0x00};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_RAM_Control()//B0
{
	//RM : ram access selection.
	//RM=”0” : Ram access from MCU interface
	//RM=”1” : Ram access from RGB interface
	#define RAMCTRL_RM 0
	
	//DM[1:0] : Display operation selection.
	//0 : MCU interface
	//1 : RGB interface
	//2 : VSYNC interface
	//3 : Reserved
	#define RAMCTRL_DM 0
	
	//ENDIAN :
	//0 : Normal (MSB first)
	//1 : Little Endian (LSB first)
	//Note: Little Endian only can be supported in 65K 8-bit and 9-bit interface.
	#define RAMCTRL_ENDIAN 00
	
	//MDT[1:0] : Method of pixel data transfer
	//Please refer to section 8.8 Data Color Coding
	#define RAMCTRL_MDT 0
	
	
	
	//RIM: Specify RGB interface bus width.
	//RIM=”0”: 18 bit bus width.
	//RIM=”1”: 6 bit bus width
	#define RAMCTRL_RIM 0
	
	//EPF[1:0] : Data translate of 65k and 4k to frame data.
	#define RAMCTRL_EPF 0
	
	const uint8_t i[]={0xB0,(RAMCTRL_RM<<4)|RAMCTRL_DM,(RAMCTRL_EPF<<4)|(RAMCTRL_ENDIAN<<3)|(RAMCTRL_RIM<<2)|(RAMCTRL_MDT)};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_RGB_Interface_Control()//B1
{
	//WO : Direct RGB mode.
	//0 : Memory
	//1 : Shift register
	#define RGBINTF_WO 0
	
	//RCM[1:0]: RGB I/F enable mode selection.
	//0 : MCU interface
	//1 : MCU interface
	//2 : RGB DE mode
	//3 : RGB HV mode
	#define RGBINTF_RCM 0
	
	//VSPL : Sets the signal polarity of the VSYNC pin.
	//VSPL=”0”, Low active
	//VSPL=”1”, High active
	#define RGBINTF_VSPL 0
	
	//HSPL : Sets the signal polarity of the HSYNC pin.
	//HSPL=”0”, Low active
	//HSPL=”1”, High active
	#define RGBINTF_HSPL 0
	
	//DPL : Sets the signal polarity of the DOTCLK pin.
	//DPL = “0” The data is input on the positive edge of DOTCLK
	//DPL = “1” The data is input on the negative edge of DOTCLK
	#define RGBINTF_DPL 0
	
	//EPL : Sets the signal polarity of the ENABLE pin.
	//EPL = “0” The data DB17-0 is written when ENABLE = “1”. Disable data write operation when ENABLE = “0”.
	//EPL = “1” The data DB17-0 is written when ENABLE = “0”. Disable data write operation when ENABLE = “1”.
	#define RGBINTF_EPL 0
	
	//VBP[6:0]: RGB interface Vsync back porch setting. Minimum setting is 0x02.
	#define RGBINTF_VBP 0x02
	
	//HBP[4:0]: RGB interface Hsync back porch setting. Please refer to the section 8.9.3 for minimum setting.
	#define RGBINTF_HBP 0x12
	
	const uint8_t i[]={0xB1,(RGBINTF_WO<<7)|(RGBINTF_RCM<<5)|(RGBINTF_VSPL<<3)|(RGBINTF_HSPL<<2)|(RGBINTF_DPL<<1)|(RGBINTF_EPL),RGBINTF_VBP,RGBINTF_HBP};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Porch_Setting_Init()//B2
{
	//BPA[6:0]: Back porch setting in normal mode. The minimum setting is 0x01.
	#define PORCH_BPA 0x01

	//FPA[6:0]: Front porch setting in normal mode. The minimum setting is 0x01.
	#define PORCH_FPA 0x01

	//PSEN: Enable separate porch control.
	//0:Disable separate porch control
	//1:Enable separate porch control
	#define PORCH_PSEN 0

	//BPB[3:0]: Back porch setting in idle mode. The minimum setting is 0x01.
	#define PORCH_BPB 0x01
	
	//FPB[3:0]: Front porch setting in idle mode. The minimum setting is 0x01.
	#define PORCH_FPB 0x01
	
	//BPC[3:0]: Back porch setting in partial mode. The minimum setting is 0x01.
	#define PORCH_BPC 0x01
	
	//FPC[3:0]: Front porch setting in partial mode. The minimum setting is 0x01.
	#define PORCH_FPC 0x01
	
#if(SCREEN_MODEL ==_ZJY147TP)
	const uint8_t i[]={0xB2,0x0C,0x0C,0x00,0x33,0x33};
#else
	const uint8_t i[]={0xB2,PORCH_BPA,PORCH_FPA,PORCH_PSEN,(PORCH_BPB<<4)|PORCH_FPB,(PORCH_BPC<<4)|PORCH_FPC};
#endif
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7789VW_Frame_Rate_Control_1_Init()//B3
{
	//FRSEN: Enable separate frame rate control.
	//When FRSEN=0, Frame rate of idle and partial mode are determined by C6h
	//When FRSEN=1, Frame rate of idle and partial mode are determined by B3h
	//0:Disable separate FR control
	//1:Enable separate FR control
	#define FRC1_FRSEN 0
	
	//DIV[1:0]: Frame rate divided control
	//0 Divide by 1
	//1 Divide by 2
	//2 Divide by 4
	//3 Divide by 8
	#define FRC1_DIV 0
	
	//NLB[2:0]: Inversion selection in idle mode.
	//0x00: dot inversion.
	//0x07: column inversion.
	#define FRC1_NLB 0
	
	//RTNB[4:0]: Frame rate control in idle mode.
	//RTNB[4:0] FR in idle mode (Hz)
	//RTNB=00h		FR in idle mode = 119 Hz
	//RTNB=01h		FR in idle mode = 111 Hz	 
	//RTNB=02h		FR in idle mode = 105 Hz	 
	//RTNB=03h		FR in idle mode = 99 Hz	 
	//RTNB=04h		FR in idle mode = 94 Hz	 
	//RTNB=05h		FR in idle mode = 90 Hz	 
	//RTNB=06h		FR in idle mode = 86 Hz	 
	//RTNB=07h		FR in idle mode = 82 Hz	 
	//RTNB=08h		FR in idle mode = 78 Hz	 
	//RTNB=09h		FR in idle mode = 75 Hz	 
	//RTNB=0Ah		FR in idle mode = 72 Hz	 
	//RTNB=0Bh		FR in idle mode = 69 Hz	 
	//RTNB=0Ch		FR in idle mode = 67 Hz	 
	//RTNB=0Dh		FR in idle mode = 64 Hz	 
	//RTNB=0Eh		FR in idle mode = 62 Hz	 
	//RTNB=0Fh		FR in idle mode = 60 Hz	 
	//RTNB=10h		FR in idle mode = 58 Hz
	//RTNB=11h		FR in idle mode = 57 Hz
	//RTNB=12h		FR in idle mode = 55 Hz
	//RTNB=13h		FR in idle mode = 53 Hz
	//RTNB=14h		FR in idle mode = 52 Hz
	//RTNB=15h		FR in idle mode = 50 Hz
	//RTNB=16h		FR in idle mode = 49 Hz
	//RTNB=17h		FR in idle mode = 48 Hz
	//RTNB=18h		FR in idle mode = 46 Hz
	//RTNB=19h		FR in idle mode = 45 Hz
	//RTNB=1Ah		FR in idle mode = 44 Hz
	//RTNB=1Bh		FR in idle mode = 43 Hz
	//RTNB=1Ch		FR in idle mode = 42 Hz
	//RTNB=1Dh		FR in idle mode = 41 Hz
	//RTNB=1Eh		FR in idle mode = 40 Hz
	//RTNB=1Fh		FR in idle mode = 39 Hz
	//Note:
	//1. If FRSEN=1, Frame rate in idle mode=10MHz/(320+(FPB[3:0]+BPB[3:0])*4)*(250+RTNB[4:0]*16).
	//2. FPB[6:0] and BPB[6:0] are in command B2h
	//3. In this frame rate table, FPB[3:0]=03h, BPB[3:0]=03h
	#define FRC1_RTNB 0x00
	
	//NLC[2:0]: Inversion setting in partial mode.
	//0x00: dot inversion.
	//0x07: column inversion.
	#define FRC1_NLC 0x00
	
	//RTNC[4:0]: Frame rate control in partial mode. This setting is equal to RTNB.
	#define FRC1_RTNC 0x00
	
	const uint8_t i[]={0xB3,(FRC1_FRSEN<<4)|FRC1_DIV, (FRC1_NLB<<5)|FRC1_RTNB,(FRC1_NLC<<5)|FRC1_RTNC};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Partial_Control_Init()//B5
{
	//NDL: Source output level in non display area in partial mode.
	//When NDL=0, source output level is V63.
	//When NDL=1, source output level is V0.
	#define PARTCTRL_NDL 0
	
	
	//PTGISC: Non display area scan mode.
	//When PTGISC=0, non-display area is normal scan.
	//When PTGISC=1, non-display area is interval scan.
	#define PARTCTRL_PTGISC 0
	
	
	//ISC[3:0]: non-display area scan cycle selection.
	//ISC[3:0] Scan cycle for non-display area
	//00h Normal scan
	//01h Every 3 cycles scan 1 time
	//02h Every 5 cycles scan 1 time
	//03h Every 7 cycles scan 1 time
	//…
	//…
	//0Fh Every 31 cycles scan 1 time
	#define PARTCTRL_ISC 0x00
	
	const uint8_t i[]={0xB5,(PARTCTRL_NDL<<7)|(PARTCTRL_PTGISC<<4)|PARTCTRL_ISC};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7789VW_GCTRL_Gate_Control_Init()//B7
{
	//VGHS[2:0]: VGH Setting.
	//VGHS[2:0] VGH (V)
	//00h 12.2
	//01h 12.54
	//02h 12.89
	//03h 13.26
	//04h 13.65
	//05h 14.06
	//06h 14.5
	//07h 14.97
	#define GATECTRL_VGHS 3
	
	
	//VGLS[2:0]: VGL Setting.
	//VGLS[2:0] VGL (V)
	//00h -7.16
	//01h -7.67
	//02h -8.23
	//03h -8.87
	//04h -9.6
	//05h -10.43
	//06h -11.38
	//07h -12.5
	#define GATECTRL_VGLS 5
	
#if(SCREEN_MODEL ==_ZJY147TP)
	const uint8_t i[]={0xB7,0x00};
#else
	const uint8_t i[]={0xB7,(GATECTRL_VGHS<<4)|GATECTRL_VGLS};
#endif
	
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7789VW_Gate_On_Timing_Adjustment_Init()//B8
{
	//GTA[5:0]: Gate on timing adjustment.
	//Gate on timing=300ns+GTA[5:0]*400ns
	//In 18bit RGB interface:
	//Gate on timing=7dotclk+GTA[5:0]*4dotclk
	//In 6bit RGB interface:
	//Gate on timing=7*3dotclk+GTA[5:0]*4*3dotclk
	#define GATEONTIMINGADJ_GTA 0x22
	
	//GOFR[3:0]: Gate off timing adjustment only for RGB interface
	//In 18bit RGB interface:
	//Gate off timing=516.5dotclk-16dotclk*GOFR[3:0]
	//In 6bit RGB interface:
	//Gate off timing=512*3dotclk-16dotclk*3*GOFR[3:0]
	//Note:In rgb interface, if the setting of gate off timing is more than the number of 
	//dotclk in one line, the gate offtiming is determined by hsync.
	#define GATEONTIMINGADJ_GOFR 0x7
	
	//GOF[3:0]: Gate off timing adjustment
	//Gate off timing=-GOF[3:0]*400ns
	#define GATEONTIMINGADJ_GOF 0x5
	
	const uint8_t i[]={0xB8,0x2A,0x2B,GATEONTIMINGADJ_GTA,(GATEONTIMINGADJ_GOFR<<4)|GATEONTIMINGADJ_GOF};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}


void ST7789VW_Digital_Gamma_Enable()//BA
{
	const uint8_t i[]={0xBA,1<<2};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7789VW_VCOM_Setting_Init()//BB
{
	//VCOMS[5:0] VCOM (V) VCOMS[5:0] VCOM (V)
	//00h	0.1  	
	//01h	0.125	
	//02h	0.15 	
	//03h	0.175	
	//04h	0.2  	
	//05h	0.225	
	//06h	0.25 	
	//07h	0.275	
	//08h	0.3	 	
	//09h	0.325	
	//0Ah	0.35 	
	//0Bh	0.375	
	//0Ch	0.4	 	
	//0Dh	0.425	
	//0Eh	0.45 	
	//0Fh	0.475	
	//10h	0.5  	
	//11h	0.525	
	//12h	0.55 	
	//13h	0.575	
	//14h	0.6  	
	//15h	0.625	
	//16h	0.65 	
	//17h	0.675	
	//18h	0.7  	
	//19h	0.725	
	//1Ah	0.75 	
	//1Bh	0.775	
	//1Ch	0.8  	
	//1Dh	0.825	
	//1Eh	0.85 	
	//1Fh	0.875
	//20h	0.9
	//21h	0.925
	//22h	0.95
	//23h	0.975
	//24h	1.0
	//25h	1.025
	//26h	1.05
	//27h	1.075
	//28h	1.1
	//29h	1.125
	//2Ah	1.15
    //2Bh	1.175
    //2Ch	1.2
    //2Dh	1.225
    //2Eh	1.25
    //2Fh	1.275
    //30h	1.3
    //31h	1.325
    //32h	1.35
    //33h	1.375
    //34h	1.4
    //35h	1.425
    //36h	1.45
    //37h	1.475
    //38h	1.5
    //39h	1.525
    //3Ah	1.55
    //3Bh	1.575
    //3Ch	1.6
    //3Dh	1.625
    //3Eh	1.65
    //3Fh	1.675
	#define VCOMS 0x20
	
	#if(SCREEN_MODEL==_ZJY147TP)
	const uint8_t i[]={0xBB,0x34};
#else
	const uint8_t i[]={0xBB,0x20};
#endif
	
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7789VW_Power_Saving_Mode_Init()//BC
{
	//NS: Power save for normal mode.
	//When NS=0, power consumption in normal mode will be saved.
	#define POWERSAV_NS 0
	
	//IS: Power save for Idle mode.
	//When IS=0, power consumption in idle mode will be saved.
	#define POWERSAV_IS 0
	
	const uint8_t i[]={0xBC,0xEC|(POWERSAV_NS<<1)|POWERSAV_IS};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Display_off_power_save_Init()//BD
{
	//DOFSAVE: Power save for display off mode.
	//When DOFSAVE=0, power consumption in display off mode will be saved.
	#define DISPOFF_POWERSAVE_DOFSAVE 0
	
	const uint8_t i[]={0xBD,0xFE|DISPOFF_POWERSAVE_DOFSAVE};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_LCM_Control_Init()//C0
{
	//XMY: XOR MY setting in command 36h.
	#define LCM_XMY 0
	//XBGR: XOR RGB setting in command 36h.
	#define LCM_XBGR 0
	//XREV: XOR inverse setting in command 21h
	#define LCM_XREV 1
	//XMH: this bit can reverse source output order and only support for RGB interface without RAM mode
	#define LCM_XMH 0
	//XMV: XOR MV setting in command 36h
	#define LCM_XMV 0
	//XMX: XOR MX setting in command 36h.
	#define LCM_XMX 0
	//XGS: XOR GS setting in command E4h.
	#define LCM_XGS 0
	
	const uint8_t i[]={0xC0,(LCM_XMY<<6)|(LCM_XBGR<<5)|(LCM_XREV<<4)|(LCM_XMX<<3)|(LCM_XMH<<2)|(LCM_XMV<<1)|LCM_XGS};
	
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_VDV_and_VRH_Cmd_Enable_Init()//C2
{
	//CMDEN: VDV and VRH command write enable.
	//CMDEN=”0”: VDV and VRH register value comes from NVM.
	//CMDEN=”1”, VDV and VRH register value comes from command write.
	#define VDV_VRH_CMDEN 1
		
#if(SCREEN_MODEL==_ZJY147TP)
	const uint8_t i[]={0xC2,0x01};
#else
	const uint8_t i[]={0xC2,VDV_VRH_CMDEN,0xFF};
#endif
	
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_VRH_Set_Init()//C3
{
	//VRHS[5:0]: VRH Set.
	//VRHS[5:0] VAP(GVDD) (V) VRHS[5:0] VAP(GVDD) (V)
	//00h 3.55+(vcom+vcom offset+vdv)  
	//01h 3.6 +( vcom+vcom offset+vdv)  
	//02h 3.65+( vcom+vcom offset+vdv) 
	//03h 3.7 +( vcom+vcom offset+vdv)  
	//04h 3.75+( vcom+vcom offset+vdv) 
	//05h 3.8+( vcom+vcom offset+vdv)  
	//06h 3.85+( vcom+vcom offset+vdv) 
	//07h 3.9 +( vcom+vcom offset+vdv)  
	//08h 3.95+( vcom+vcom offset+vdv) 
	//09h 4   +( vcom+vcom offset+vdv)    
	//0Ah 4.05+( vcom+vcom offset+vdv) 
	//0Bh 4.1 +( vcom+vcom offset+vdv)  
	//0Ch 4.15+( vcom+vcom offset+vdv) 
	//0Dh 4.2 +( vcom+vcom offset+vdv)  
	//0Eh 4.25+( vcom+vcom offset+vdv) 
	//0Fh 4.3 +( vcom+vcom offset+vdv)  
	//10h 4.35+( vcom+vcom offset+vdv) 
	//11h 4.4 +( vcom+vcom offset+vdv)  
	//12h 4.45+( vcom+vcom offset+vdv) 
	//13h 4.5 +( vcom+vcom offset+vdv)  
	//14h 4.55+( vcom+vcom offset+vdv)
	//15h 4.6 +( vcom+vcom offset+vdv)
	//16h 4.65+( vcom+vcom offset+vdv)
	//17h 4.7 +( vcom+vcom offset+vdv)
	//18h 4.75+( vcom+vcom offset+vdv)
	//19h 4.8 +( vcom+vcom offset+vdv)
	//1Ah 4.85+( vcom+vcom offset+vdv)
	//1Bh 4.9 +( vcom+vcom offset+vdv)
	//1Ch 4.95+( vcom+vcom offset+vdv)
	//1Dh 5   +( vcom+vcom offset+vdv)
	//1Eh 5.05+( vcom+vcom offset+vdv)
	//1Fh 5.1 +( vcom+vcom offset+vdv)
	//20h 5.15+( vcom+vcom offset+vdv)
	//21h 5.2 +( vcom+vcom offset+vdv)
	//22h 5.25+( vcom+vcom offset+vdv)
	//23h 5.3 +( vcom+vcom offset+vdv)
	//24h 5.35+( vcom+vcom offset+vdv)
	//25h 5.4 +( vcom+vcom offset+vdv)
	//26h 5.45+( vcom+vcom offset+vdv)
	//27h 5.5 +( vcom+vcom offset+vdv)
	//28h~3Fh Reserved
	
	//VRHS[5:0] VAN(GVCL) (V) VRHS[5:0] VAN(GVCL) (V)
	//00h -3.55+( vcom+vcom offset-vdv) 
	//01h -3.6 +( vcom+vcom offset-vdv) 
	//02h -3.65+( vcom+vcom offset-vdv) 
	//03h -3.7 +( vcom+vcom offset-vdv) 
	//04h -3.75+( vcom+vcom offset-vdv) 
	//05h -3.8 +( vcom+vcom offset-vdv) 
	//06h -3.85+( vcom+vcom offset-vdv) 
	//07h -3.9 +( vcom+vcom offset-vdv) 
	//08h -3.95+( vcom+vcom offset-vdv) 
	//09h -4   +( vcom+vcom offset-vdv) 
	//0Ah -4.05+( vcom+vcom offset-vdv) 
	//0Bh -4.1 +( vcom+vcom offset-vdv) 
	//0Ch -4.15+( vcom+vcom offset-vdv) 
	//0Dh -4.2 +( vcom+vcom offset-vdv) 
	//0Eh -4.25+( vcom+vcom offset-vdv) 
	//0Fh -4.3 +( vcom+vcom offset-vdv) 
	//10h -4.35+( vcom+vcom offset-vdv) 
	//11h -4.4 +( vcom+vcom offset-vdv) 
	//12h -4.45+( vcom+vcom offset-vdv) 
	//13h -4.5 +( vcom+vcom offset-vdv) 
	//14h -4.55+( vcom+vcom offset-vdv)
	//15h -4.6+( vcom+vcom offset-vdv)
	//16h -4.65+( vcom+vcom offset-vdv)
	//17h -4.7+( vcom+vcom offset-vdv)
	//18h -4.75+( vcom+vcom offset-vdv)
	//19h -4.8+( vcom+vcom offset-vdv)
	//1Ah -4.85+( vcom+vcom offset-vdv)
	//1Bh -4.9+( vcom+vcom offset-vdv)
	//1Ch -4.95+( vcom+vcom offset-vdv)
	//1Dh -5+( vcom+vcom offset-vdv)
	//1Eh -5.05+( vcom+vcom offset-vdv)
	//1Fh -5.1+( vcom+vcom offset-vdv)
	//20h -5.15+( vcom+vcom offset-vdv)
	//21h -5.2+( vcom+vcom offset-vdv)
	//22h -5.25+( vcom+vcom offset-vdv)
	//23h -5.3+( vcom+vcom offset-vdv)
	//24h -5.35+( vcom+vcom offset-vdv)
	//25h -5.4+( vcom+vcom offset-vdv)
	//26h -5.45+( vcom+vcom offset-vdv)
	//27h -5.5+( vcom+vcom offset-vdv)
	//28h~3Fh Reserved

	#define VRH_VRHS 0x0B
		
#if(SCREEN_MODEL==_ZJY147TP)
	const uint8_t i[]={0xC3,0x09};
#else
	const uint8_t i[]={0xC3,VRH_VRHS};
#endif
	
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_VDV_Set_Init()//C4
{
	//VDVS[5:0]: VDV Set.
	//VDVS[5:0] VDV (V) VDVS[5:0] VDV (V)
	//00h -0.8   20h 0
	//01h -0.775 21h 0.025
	//02h -0.75  22h 0.05
	//03h -0.725 23h 0.075
	//04h -0.7   24h 0.1
	//05h -0.675 25h 0.125
	//06h -0.65  26h 0.15
	//07h -0.625 27h 0.175
	//08h -0.6   28h 0.2
	//09h -0.575 29h 0.225
	//0Ah -0.55  2Ah 0.25
	//0Bh -0.525 2Bh 0.275
	//0Ch -0.5   2Ch 0.3
	//0Dh -0.475 2Dh 0.325
	//0Eh -0.45  2Eh 0.35
	//0Fh -0.425 2Fh 0.375
	//10h -0.4   30h 0.4
	//11h -0.375 31h 0.425
	//12h -0.35  32h 0.45
	//13h -0.325 33h 0.475
	//14h -0.3   34h 0.5
	//15h -0.275 35h 0.525
	//16h -0.25  36h 0.55
	//17h -0.225 37h 0.575
	//18h -0.2   38h 0.6
	//19h -0.175 39h 0.625
	//1Ah -0.15  3Ah 0.65
	//1Bh -0.125 3Bh 0.675
	//1Ch -0.1   3Ch 0.7
	//1Dh -0.075 3Dh 0.725
	//1Eh -0.05  3Eh 0.75
	//1Fh -0.025 3Fh 0.775

	#define VDV_VDVS 0x20
		
	const uint8_t i[]={0xC4,VDV_VDVS};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7789VW_VCOM_Offset_Set_Init()//C5
{
	//VCOM offset setting:
	//VCMOFS[5:0] VCOM OFFSET (V) VCMOFS[5:0] VCOM OFFSET(V)
	//00h -0.8   20h 0
	//01h -0.775 21h 0.025
	//02h -0.75  22h 0.05
	//03h -0.725 23h 0.075
	//04h -0.7   24h 0.1
	//05h -0.675 25h 0.125
	//06h -0.65  26h 0.15
	//07h -0.625 27h 0.175
	//08h -0.6   28h 0.2
	//09h -0.575 29h 0.225
	//0Ah -0.55  2Ah 0.25
	//0Bh -0.525 2Bh 0.275
	//0Ch -0.5   2Ch 0.3
	//0Dh -0.475 2Dh 0.325
	//0Eh -0.45  2Eh 0.35
	//0Fh -0.425 2Fh 0.375
	//10h -0.4   30h 0.4
	//11h -0.375 31h 0.425
	//12h -0.35  32h 0.45
	//13h -0.325 33h 0.475
	//14h -0.3   34h 0.5
	//15h -0.275 35h 0.525
	//16h -0.25  36h 0.55
	//17h -0.225 37h 0.575
	//18h -0.2   38h 0.6
	//19h -0.175 39h 0.625
	//1Ah -0.15  3Ah 0.65
	//1Bh -0.125 3Bh 0.675
	//1Ch -0.1   3Ch 0.7
	//1Dh -0.075 3Dh 0.725
	//1Eh -0.05  3Eh 0.75
	//1Fh -0.025 3Fh 0.775
	
	#define VCOM_VCMOFS 0x20
	const uint8_t i[]={0xC5,VCOM_VCMOFS};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}


void ST7789VW_Frame_Rate_Control_in_Normal_Mode_Init()//C6
{
	
	//NLA[2 :0] : Inversion selection in normal mode.
	//0x00 : dot inversion.
	//0x07: column inversion.
	#define FRCTRL_INNORMAL_NLA 0x00
	
	
	//RTNA[4:0]:
	//RTNA[4:0] FR in normal mode (Hz) RTNA[4:0] FR in normal mode (Hz)
	//00h 119 10h 58
	//01h 111 11h 57
	//02h 105 12h 55
	//03h 99  13h 53
	//04h 94  14h 52
	//05h 90  15h 50
	//06h 86  16h 49
	//07h 82  17h 48
	//08h 78  18h 46
	//09h 75  19h 45
	//0Ah 72  1Ah 44
	//0Bh 69  1Bh 43
	//0Ch 67  1Ch 42
	//0Dh 64  1Dh 41
	//0Eh 62  1Eh 40
	//0Fh 60  1Fh 39
	#define FRCTRL_INNORMAL_RTNA 0x0F
	
#if(SCREEN_MODEL==_ZJY147TP)
	const uint8_t i[]={0xC6,0x19};
#else
	const uint8_t i[]={0xC6,(FRCTRL_INNORMAL_NLA<<4)|FRCTRL_INNORMAL_RTNA};
#endif
	
	
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7789VW_CABC_Control_Init()//C7
{
	//LEDONREV: Reverse the status of LED_ON:
	//“0”: keep the status of LED_ON.
	//“1”: reverse the status of LED_ON.
	#define CABC_LEDONREV 0
	
	//DPOFPWM: initial state control of LEDPWM.
	//“0”: The initial state of LEDPWM is low.
	//“1”: The initial state of LEDPWM is high.
	#define CABC_DPOFPWM 0
	
	//PWMFIX: LEDPWM fix control.
	//“0”: LEDPWM control by CABC.
	//“1”: fix LEDPWM in “ON” status.
	#define CABC_PWMFIX 0
	
	
	//PWMPOL: LEDPWM polarity control.
	//“0”: polarity high.
	//“1”: polarity low.
	#define CABC_PWMPOL 0
	
	const uint8_t i[]={0xC7,(CABC_LEDONREV<<3)|(CABC_DPOFPWM<<2)|(CABC_PWMFIX<<1)|CABC_PWMPOL};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7789VW_PWM_Frequency_Selection_Init()//CC
{
// |----------------------------------------------------|
// |          |                 CS[2:0]                 |
// | CLK[2:0] |-----------------------------------------|
// |          |00h   |01h   |02h   |03h   |04h   |05h   |
// |----------------------------------------------------|
// |   00h    |39.2  |78.7  |158.7 |322.6 |666.7 |1428.6|
// |   01h    |19.6  |39.4  |79.4  |161.3 |333.3 |714.3 |
// |   02h    |9.8   |19.7  |39.7  |80.6  |166.7 |357.1 |
// |   03h    |4.9   |9.8   |19.8  |40.3  |83.3  |178.6 |
// |   04h    |2.45  |4.9   |9.9   |20.2  |41.7  |89.3  |
// |   05h    |1.23  |2.5   |5     |10.1  |20.8  |44.6  |
// |   06h    |0.61  |1.23  |2.48  |5     |10.4  |22.3  |
// |   07h    |0.31  |0.62  |1.24  |2.5   |5.2   |11.2  |
// |----------------------------------------------------|
// Unit:kHz
	
	#define PWM_Fr_CLK 0x00
	#define PWM_Fr_CS  0x02
	
	const uint8_t i[]={0xCC,(PWM_Fr_CLK<<3)|PWM_Fr_CS};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7789VW_Power_Control_1_Init()//D0
{
	//AVDD[1:0] AVDD (V)
	//00h 6.4
	//01h 6.6
	//02h 6.8
	//03h Reserved
	#define POWER_CTRL_1_AVDD 2
	
	//AVCL[1:0] AVCL (V)
	//00h -4.4
	//01h -4.6
	//02h -4.8
	//03h -5.0
	#define POWER_CTRL_1_AVCL 2
	
	//VDS[1:0] VDDS (V)
	//00h 2.19
	//01h 2.3
	//02h 2.4
	//03h 2.51
	//VDDS: Power of source OP
	#define POWER_CTRL_1_VDDS 1
	
#if(SCREEN_MODEL==_ZJY147TP)
	const uint8_t i[]={0xD0,0xA4,0xA1};
#else
	const uint8_t i[]={0xD0,0xA4,(POWER_CTRL_1_AVDD<<6)|(POWER_CTRL_1_AVCL<<4)|POWER_CTRL_1_VDDS};
#endif
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7789VW_VAP_VAN_signal_output_Enable()//D2
{
	const uint8_t i[]={0xD2,0x4C};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Command_2_Enable_Init()//DF
{
	//EN:
	//“0”: Commands in Command table 2 cannot be executed when EXTC level is “Low”.
	//“1”: Commands in command table 2 can be executed when EXTC level is “Low”.
	#define CMD2_EN 0
	const uint8_t i[]={0xDF,0x5A,0x69,0x02,CMD2_EN};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Positive_Voltage_Gamma_Control_Init()//E0
 {
	//Please refer to 8.19.
#if(SCREEN_MODEL ==_ZJY147TP)
	const uint8_t i[]={0xE0,0xF0,0x04,0x08,0x0A,0x25,0x33,0x3C,0x0E,0x0F,0x27,0x2F};
#else
	const uint8_t i[]={0xE0,0xF0,0x04,0x08,0x0A,0x25,0x33,0x3C,0x0E,0x0F,0x27,0x2F};
#endif
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Negative_Voltage_Gamma_Control_Init()//E1
{
	//Please refer to 8.19.
#if(SCREEN_MODEL==_ZJY147TP)
	const uint8_t i[]={0xE0,0xF0,0x02,0x06,0x04,0x22,0x25,0x32,0x3B,0x3A,0x15,0x17,0x2D,0x37};
#else
	const uint8_t i[]={0xE0,0xF0,0x02,0x06,0x04,0x22,0x25,0x32,0x3B,0x3A,0x15,0x17,0x2D,0x37};
#endif
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Digital_Gamma_Lookup_Table_for_Red_Init()//E2
{
	//Please refer to 8.20.
	//const uint8_t i[]={0xE2,};
	//LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Digital_Gamma_Lookup_Table_for_Blue_Init()//E3
{
	//Please refer to 8.20.
	//const uint8_t i[]={0xE3,};
	//LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_GATECTRL_Gate_Control_Init()//E4
{
	//const uint8_t i[]={0xE4,0x27,0x00,00x10};
	//LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_SPI2_Enable_Init()//E7
{
	//const uint8_t i[]={0xE7,0x00};
	//LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Power_Control_2_Init()//E8
{
	const uint8_t i[]={0xE8,0x93};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Equalize_time_control_Init()//E9
{
	//const uint8_t i[]={0xE9,0x11,0x11,0x08};
	//LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Program_Mode_Control()//EC
{
	const uint8_t i[]={0xE9,0x01};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Program_Mode_Enable()//FA
{
	const uint8_t i[]={0xFA,0x5A,0x69,0xEE,0x04};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Program_Mode_Disable()//FA
{
	const uint8_t i[]={0xFA,0x5A,0x69,0xEE,0x00};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_NVM_Setting_Init()//FC
{
	//const uint8_t i[]={0xFC,0x00,0x00};
	//LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7789VW_Clear()//清除IC显示缓存
{
	uint32_t i;
	
//	ST7789VW_Set_Addr(0,0,320-1,480-1);
//	i=0;
//	while(i++<240*320)
//	{
//		//LCD_Send_1Dat(0x33);LCD_Send_1Dat(0x33);//测试
//		LCD_Send_1Dat(0x00);LCD_Send_1Dat(0x00);
//	}
//	
	
	ST7789VW_Set_Addr(0,0,320-1,320-1);
	i=0;
	while(i++<320*320)
	{
		//LCD_Send_1Dat(0x33);LCD_Send_1Dat(0x33);//测试
		LCD_Send_1Dat(0x00);LCD_Send_1Dat(0x00);
	}
	
}





//自定义初始化示例
//void ST7789VW_Init()
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




void ST7789VW_Init()
{
	LCD_RES_Clr();
	LCD_delay_ms(100);
	LCD_RES_Set();
	LCD_delay_ms(100);

	
	ST7789VW_Sleep_Out();//11
	LCD_delay_ms(120);
	//----设置显示方向和RGB顺序和反色----
	ST7789VW_Memory_Data_Access_Ctrl_Init();//36
	//注意：一般芯片不支持c0设置,为了程序兼容其他款芯片,设置反色和RGB顺序时,建议优先设置C0,而36保持默认
	ST7789VW_LCM_Control_Init();//C0
	//---------选择默认颜色深度---------
	//ST7789VW_Set_RGB444_Mode();//3A
	ST7789VW_Set_RGB565_Mode();//3A
	//ST7789VW_Set_RGB666_Mode();//3A
	//ST7789VW_Set_RGB888_Mode();//3A
	

	
	//-------------次要设置-------------
//	ST7789VW_Write_Display_Brightness(0);//51
//	ST7789VW_Write_CTRL_Display();//53
//	ST7789VW_Write_Content_daptive_Brightness_Control_and_Color_Enhancement();//55
//	ST7789VW_Write_CABC_Minimum_Brightness();//5E
//	ST7789VW_RAM_Control();//B0
//	//ST7789VW_Frame_Rate_Control_1_Init();//B3
//	ST7789VW_Partial_Control_Init();//B5
//	ST7789VW_Gate_On_Timing_Adjustment_Init();//B8
//	ST7789VW_Digital_Gamma_Enable();//BA
//	ST7789VW_Power_Saving_Mode_Init();//BC
//	ST7789VW_VDV_Set_Init();//C4
//	ST7789VW_VCOM_Offset_Set_Init();//C5
//	ST7789VW_CABC_Control_Init();//C7
//	ST7789VW_PWM_Frequency_Selection_Init();//CC
//	ST7789VW_VAP_VAN_signal_output_Enable();//D2
//	ST7789VW_Command_2_Enable_Init();//DF
//	ST7789VW_Digital_Gamma_Lookup_Table_for_Red_Init();//E2
//	ST7789VW_Digital_Gamma_Lookup_Table_for_Blue_Init();//E3
//	ST7789VW_GATECTRL_Gate_Control_Init();//E4
//	ST7789VW_SPI2_Enable_Init();//E7

//	ST7789VW_Equalize_time_control_Init();//E9
//	ST7789VW_Program_Mode_Control();//EC
//	//ST7789VW_Program_Mode_Enable();//FA
//	ST7789VW_Program_Mode_Disable();//FA
//	ST7789VW_NVM_Setting_Init();//FC
	
	
	//------------基础设置----------
	
	ST7789VW_Porch_Setting_Init();//B2
	ST7789VW_GCTRL_Gate_Control_Init();//B7
	ST7789VW_VCOM_Setting_Init();//BB
	ST7789VW_LCM_Control_Init();//C0
	ST7789VW_VDV_and_VRH_Cmd_Enable_Init();//C2
	ST7789VW_VRH_Set_Init();//C3
	ST7789VW_Frame_Rate_Control_in_Normal_Mode_Init();//C6
	ST7789VW_Power_Control_1_Init();//D0
	ST7789VW_Positive_Voltage_Gamma_Control_Init();//E0
	ST7789VW_Negative_Voltage_Gamma_Control_Init();//E1
	ST7789VW_Power_Control_2_Init();//E8
	
	
	
	//ST7789VW_Partial_Control_Init();//B5
	//ST7789VW_Partial_Area_Set();//30
	//ST7789VW_Partial_Mode_On();//12
	
	ST7789VW_Sleep_Out();//11
	ST7789VW_Clear();//清除IC显示缓存
	ST7789VW_Display_On();//29
}
