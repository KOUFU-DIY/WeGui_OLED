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

#include "st7735.h"
#include "lcd_wegui_driver.h"


void ST7735_Set_Addr(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	
	//1.等待SPI空闲
	//while(b_dma_busy!=0){};//等待DMA完毕,空闲
	//Wait_Soft_spi_Done();
		
	//发送数据
	uint8_t i[]={0x2a,x1>>8,x1&0xff,(x2)>>8,(x2)&0xff};
	uint8_t j[]={0x2b,y1>>8,(y1)&0xff,(y2)>>8,y2&0xff};
	const uint8_t k[]={0x2c};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	LCD_Send_nCmd((uint8_t*)j,sizeof(j)/sizeof(uint8_t));
	LCD_Send_nCmd((uint8_t*)k,sizeof(k)/sizeof(uint8_t));

}



void ST7735_Soft_Reset()
{
	const uint8_t i[]={0x01};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7735_Sleep_In()
{
	const uint8_t i[]={0x10};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7735_Sleep_Out()
{
	const uint8_t i[]={0x11};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7735_Partial_Mode_On()
{
	const uint8_t i[]={0x12};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7735_Partial_Mode_Off()
{
	const uint8_t i[]={0x13};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7735_Inversion_Off()
{
	const uint8_t i[]={0x20};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7735_Inversion_On()
{
	const uint8_t i[]={0x21};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7735_Display_Off()
{
	const uint8_t i[]={0x28};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7735_Display_On()
{
	const uint8_t i[]={0x29};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7735_TE_Line_Off()
{
	const uint8_t i[]={0x34};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7735_TE_Line_On()
{
	#define TELOM 0//[0:1]When TELOM =’0’: The Tearing Efonly
	const uint8_t i[]={0x35,TELOM};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7735_Idle_Off()
{
	const uint8_t i[]={0x38};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7735_Idle_On()
{
	const uint8_t i[]={0x39};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7735_Set_RGB565_Mode()
{
	uint8_t i[]={0x3A,0x05};//65k(RGB565)
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7735_Set_RGB444_Mode()
{
	uint8_t i[]={0x3A,0x03};//4k(RGB444)
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void ST7735_Set_RGB666_Mode()
{
	uint8_t i[]={0x3A,0x06};//262k(RGB666)
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}

void ST7735_Clear()//清除IC显示缓存
{
	uint16_t i=0;
	ST7735_Set_Addr(0,0,132-1,162-1);
	while(i++<132*162)
	{
		//LCD_Send_1Dat(0x33);LCD_Send_1Dat(0x33);//测试
		LCD_Send_1Dat(0x00);LCD_Send_1Dat(0x00);
	}
}



//void ST7735_Init()
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


void ST7735_Init()
{
	ST7735_Soft_Reset();
	LCD_RES_Clr();
	LCD_delay_ms(100);
	LCD_RES_Set();
	LCD_delay_ms(100);
	
	
	ST7735_Sleep_Out();
	{
		//FRMCTR1 (B1h): Frame Rate Control (In normal mode/ Full colors)
		#define FRMCTR1_RTNA 	0x05	//set1-line period
		#define FRMCTR1_FPA 	0x3C  //front porch
		#define FRMCTR1_BPA 	0x3C  //back porch
		const uint8_t i[]={0xB1,FRMCTR1_RTNA,FRMCTR1_FPA,FRMCTR1_BPA};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		//FRMCTR2 (B2h): Frame Rate Control (In Idle mode/ 8-colors)
		#define FRMCTR2_RTNB 	0x05	//set1-line period
		#define FRMCTR2_FPB 	0x3C  //front porch
		#define FRMCTR2_BPB 	0x3C  //back porch
		const uint8_t i[]={0xB2,FRMCTR2_RTNB,FRMCTR2_FPB,FRMCTR2_BPB};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		//FRMCTR3 (B3h): Frame Rate Control (In Partial mode/ full colors)
		#define FRMCTR3_RTNC	0x05 //set1-line period
		#define FRMCTR3_FPC		0x3C //front porch
		#define FRMCTR3_BPC		0x3C //back porch
		#define FRMCTR3_RTND	0x05 //set1-line period
		#define FRMCTR3_FPD		0x3C //front porch
		#define FRMCTR3_BPD		0x3C //back porch
		const uint8_t i[]={0xB3,FRMCTR3_RTNC,FRMCTR3_FPC,FRMCTR3_BPC,FRMCTR3_RTND,FRMCTR3_FPD,FRMCTR3_BPD};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}

	{
		//INVCTR (B4h): Display Inversion Control
		//Display inversion control
		#define INVCTR_NLA 1
		#define INVCTR_NLB 0
		#define INVCTR_NLC 0
		const uint8_t i[]={0xB4,((INVCTR_NLA<<2)|(INVCTR_NLB<<1)|INVCTR_NLC)};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		//DISSET5 (B6h): Display Function set 5
		#define DISSET5_NO  1//[0:3]Set the amount of non-overlap of the gate output
		#define DISSET5_SDT 1//[0:3]Set delay amount from gate signal rising edge of the source output.
		#define DISSET5_EQ  2//Set the Equalizing period [0:3]0:NO_EQ 1:3clk_cycel 2:5clk_cycel 3:7clk_cycel
		#define DISSET5_PTG 0//Determine gate output in a non-display area in the partial mode 0:Normal scan 1:Fix on VGL
		#define DISSET5_PT  0//[0:3]Determine Source /VCOM output in a non-display area in the partial mode
		
		const uint8_t i[]={0xB6,((DISSET5_NO<<4)|(DISSET5_SDT<<2)|DISSET5_EQ),((DISSET5_PTG<<3)|(DISSET5_PT))};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}

	{
		//Power Control 1
		//Set the GVDD voltage
		//Note: AVDD=5.3V
		#define PWCTR1_VRH 0x28 //[0x00:0x1F]=5.00~3.00V
		#define PWCTR1_IBSEL 0 //[0:3] 0=2.5uA 1=2.0uA 2=1.5uA 3=1uA
		const uint8_t i[]={0xC0,PWCTR1_VRH,(PWCTR1_IBSEL<<4)};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	} 
	{
		//Power Control 2
		#define PWCTR2_BT 0//[0:7]Set the VGH and VGL supply power level
		const uint8_t i[]={0xC1,PWCTR2_BT};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	} 
	{
		//Power Control 3 (in Normal mode/ Full colors)
		#define PWCTR3_AP 1//[0:5]Adjust the amount of fixed current from the fixed current source in the operational amplifier for the source driver.
		#define PWCTR3_DC	1//[0:7]Set the Booster circuit Step-up cycle in Idle mode/8 colors.
		
		const uint8_t i[]={0xC2,PWCTR3_AP,PWCTR3_DC};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		//PWCTR4 (C3h): Power Control 4 (in Idle mode/ 8-colors)
		//Set the amount of current in Operational amplifier in normal mode/full colors.
		#define PWCTR4_DCB  0x226//[0x00:3FF]Set the Booster circuit Step-up cycle in Idle mode/8 colors.
		#define PWCTR4_SAPB 1//[0:7]Amount of Current in Operational Amplifier
		#define PWCTR4_APB  2//[0:5]Adjust the amount of fixed current from the fixed current source in the operational amplifier for the source driver.
		const uint8_t i[]={0xC3,(((PWCTR4_DCB>>2)&0xC0)|(PWCTR4_SAPB<<3)|PWCTR4_APB),(PWCTR4_DCB&0xFF)};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		//PWCTR5 (C4h): Power Control 5 (in Partial mode/ full-colors)
		//Set the amount of current in Operational amplifier in Partial mode/ full-colors.
		#define PWCTR5_AP 2//[0:5]Adjust the amount of fixed current from the fixed current source in the operational amplifier for the source driver.
		#define PWCTR5_DC	4//[0:7]Set the Booster circuit Step-up cycle in Partial mode/ full-colors.
		const uint8_t i[]={0xC4,PWCTR5_AP,PWCTR5_DC};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}

	{
		//VMCTR1 (C5h): VCOM Control 1
		#define VMCTR1_VMH 0x51//[0x00:0x64]Set VCOMH Voltage 0x00=2.5V 0x64=5.0V
		#define VMCTR1_VML 0x4D//[0x04:0x64]Set VCOML Voltage 0x00=-2.4V 0x64=0.0V
		const uint8_t i[]={0xC5,VMCTR1_VMH, VMCTR1_VML};//VCOM 
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		//VMOFCTR (C7h): VCOM Offset Control
		//Set VCOM Voltage level for reduce the flicker issue
		//0x00=VMH-16d,VML-16d 
		//0x10=VMH+0d,VML+0d 
		//0x1F=VMH+15d,VML+15d
		#define VMOFCTR_VMF 0xF0//[0x00:0x1F]Set VCOM Voltage level for reduce the flicker issue 
		const uint8_t i[]={0xC7,VMOFCTR_VMF};//VCOM 
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		//VMCTR1 (C5h): VCOM Control 1
		#define VMCTR1_VMH 0x51//[0x00:0x64]Set VCOMH Voltage 0x00=2.5V 0x64=5.0V
		#define VMCTR1_VML 0x4D//[0x04:0x64]Set VCOML Voltage 0x00=-2.4V 0x64=0.0V
		const uint8_t i[]={0xC5,VMCTR1_VMH, VMCTR1_VML};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		//PWCTR6 (FCh): Power Control 5 (in Partial mode + Idle mode)
		#define PWCTR6_Sapa 1//[0:7]
		#define PWCTR6_Sapb 1//[0:7]
		#define PWCTR6_Sapc 1//[0:7]
		#define PWCTR6_DCD 5//[0:7]
		const uint8_t i[]={0xFC,((PWCTR6_Sapa<<4)|PWCTR6_Sapb), ((PWCTR6_Sapc<<4)|PWCTR6_DCD)};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	
	
	{
		//MADCTL (36h): Memory Data Access Control
		#define MADCTL_MY 1//[0:1]Row Address Order
		#define MADCTL_MX 1//[0:1]Column Address Order
		#define MADCTL_MV 0//[0:1]Row/Column Exchange
		#define MADCTL_ML 0//[0:1]Vertical Refresh Order 0="LCD vertical refresh Top to Bottom" 1="LCD vertical refresh Bottom to Top"
		#define MADCTL_RGB 0//[0:1]Color selector switch control 0=RGB 1=BGR
		#define MADCTL_MH 0//[0:1]Horizontal Refresh Order 0="LCD horizontal refresh Left to right" 1="LCD horizontal refresh right to left"
		const uint8_t i[]={0x36,(MADCTL_MY<<7)|(MADCTL_MX<<6)|(MADCTL_MV<<5)|(MADCTL_ML<<4)|(MADCTL_RGB<<3)|(MADCTL_MH<<2)};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	//------------------------------------ST7735S Gamma Sequence---------------------------------//
	{
		//GMCTRP1 (E0h): Gamma (‘+’polarity) Correction Characteristics Setting
		uint8_t i[]={0xE0,0x04,0x22,0x07,0x0A,0x2E,0x30,0x25,0x2A,0x28,0x26,0x2E,0x3A,0x00,0x01,0x03,0x13};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		//GMCTRN1 (E1h): Gamma ‘-’polarity Correction Characteristics Setting
		uint8_t i[]={0xE1,0x04,0x16,0x06,0x0D,0x2D,0x26,0x23,0x27,0x27,0x25,0x2D,0x3B,0x00,0x01,0x04,0x13};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	//------------------------------------End ST7735S Gamma Sequence-----------------------------//
	//EXTCTRL (F0h): Extension Command Control
	//VCOM4L (FFh): Vcom 4 Level Control
	
	ST7735_Set_RGB565_Mode();
	//ST7735_Set_RGB444_Mode();
	//ST7735_Set_RGB666_Mode();
	{
		uint8_t i[]={0x29};//Display on
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	ST7735_Clear();//清除IC显示缓存
}
