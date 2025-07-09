#include "lcd_wegui_driver.h"
#include "gc9a01.h"


void GC9A01_Set_Addr(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	//发送数据
	uint8_t i[]={0x2a,x1>>8,x1&0xff,(x2)>>8,(x2)&0xff};
	uint8_t j[]={0x2b,y1>>8,(y1)&0xff,(y2)>>8,y2&0xff};
	const uint8_t k[]={0x2c};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	LCD_Send_nCmd((uint8_t*)j,sizeof(j)/sizeof(uint8_t));
	LCD_Send_nCmd((uint8_t*)k,sizeof(k)/sizeof(uint8_t));
	
}



void GC9A01_Soft_Reset()
{
	const uint8_t i[]={0x01};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));//DMA方式发送命令,在中断接口函数里有数据和命令(DC)切换
}
void GC9A01_Sleep_In()
{
	const uint8_t i[]={0x10};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));//DMA方式发送命令,在中断接口函数里有数据和命令(DC)切换
}
void GC9A01_Sleep_Out()
{
	const uint8_t i[]={0x11};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));//DMA方式发送命令,在中断接口函数里有数据和命令(DC)切换
}
void GC9A01_Partial_Mode_On()
{
	const uint8_t i[]={0x12};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));//DMA方式发送命令,在中断接口函数里有数据和命令(DC)切换
}
void GC9A01_Partial_Mode_Off()
{
	const uint8_t i[]={0x13};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));//DMA方式发送命令,在中断接口函数里有数据和命令(DC)切换
}
void GC9A01_Inversion_Off()
{
	const uint8_t i[]={0x20};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));//DMA方式发送命令,在中断接口函数里有数据和命令(DC)切换
}
void GC9A01_Inversion_On()
{
	const uint8_t i[]={0x21};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));//DMA方式发送命令,在中断接口函数里有数据和命令(DC)切换
}
void GC9A01_ALL_Pixel_Off()
{
	const uint8_t i[]={0x22};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));//DMA方式发送命令,在中断接口函数里有数据和命令(DC)切换
}
void GC9A01_ALL_Pixel_On()
{
	const uint8_t i[]={0x23};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));//DMA方式发送命令,在中断接口函数里有数据和命令(DC)切换
}
void GC9A01_Display_Off()
{
	const uint8_t i[]={0x28};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));//DMA方式发送命令,在中断接口函数里有数据和命令(DC)切换
}
void GC9A01_Display_On()
{
	const uint8_t i[]={0x29};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));//DMA方式发送命令,在中断接口函数里有数据和命令(DC)切换
}
void GC9A01_TE_Line_Off()
{
	const uint8_t i[]={0x34};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));//DMA方式发送命令,在中断接口函数里有数据和命令(DC)切换
}
void GC9A01_TE_Line_On()
{
	const uint8_t i[]={0x35,0x01};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));//DMA方式发送命令,在中断接口函数里有数据和命令(DC)切换
}
void GC9A01_Idle_Off()
{
	const uint8_t i[]={0x38};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));//DMA方式发送命令,在中断接口函数里有数据和命令(DC)切换
}
void GC9A01_Idle_On()
{
	const uint8_t i[]={0x39};
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));//DMA方式发送命令,在中断接口函数里有数据和命令(DC)切换
}
void GC9A01_Set_RGB565_Mode()
{
	const uint8_t i[]={0x3A,0x55};//65k(RGB565)
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void GC9A01_Set_RGB444_Mode()
{
	const uint8_t i[]={0x3A,0x03};//4k(RGB444)
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}
void GC9A01_Set_RGB666_Mode()
{
	const uint8_t i[]={0x3A,0x06};//262k(RGB666)
	LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
}




void GC9A01_Clear()//清除IC显示缓存
{
	uint32_t i;
	
	i=0;
	 GC9A01_Set_Addr(0,0,240-1,240-1);
	while(i++<240*240)
	{
		LCD_Send_1Dat(0x33);LCD_Send_1Dat(0x33);//测试
		//LCD_Send_1Dat(0x00);LCD_Send_1Dat(0x00);
	}
	
}



//自定义初始化示例
//void GC9A01_Init()
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



void GC9A01_Init()
{
	LCD_RES_Clr();
	LCD_delay_ms(100);
	LCD_RES_Set();
	LCD_delay_ms(100);
	
	
	{
		const uint8_t i[]={0xfe};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xef};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}

	{
		const uint8_t i[]={0xeb,0x14};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0x84,0x40};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
//	{
//		const uint8_t i[]={0x85,0xff};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x86,0xff};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x87,0xff};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x88,0xff};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x89,0x21};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x8A,0x00};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x8E,0xff};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x8F,0xff};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x88,0x0A};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x89,0x12};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	
//	
	
	
//	{
//		const uint8_t i[]={0x8B,0x80};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x8C,0x01};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x8D,0x01};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x8E,0xFF};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x8F,0xFF};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0xB6,0x00,0X20};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}

	{
		//显示方向
		//MADCTL (36h): Memory Data Access Control
		#define MADCTL_MY 0//[0:1]Row Address Order 垂直方向
		#define MADCTL_MX 1//[0:1]Column Address Order 水平方向
		#define MADCTL_MV 0//[0:1]Row/Column Exchange
		#define MADCTL_ML 0//[0:1]Vertical Refresh Order 0="LCD vertical refresh Top to Bottom" 1="LCD vertical refresh Bottom to Top"
		#define MADCTL_RGB 1//[0:1]Color selector switch control 0=RGB 1=BGR
		#define MADCTL_MH 1//[0:1]Horizontal Refresh Order 0="LCD horizontal refresh Left to right" 1="LCD horizontal refresh right to left"
		const uint8_t i[]={0x36,(MADCTL_MY<<7)|(MADCTL_MX<<6)|(MADCTL_MV<<5)|(MADCTL_ML<<4)|(MADCTL_RGB<<3)|(MADCTL_MH<<2)};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0x3A,0x05};//65k(RGB565)
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
//	{
//		const uint8_t i[]={0x90,0x08,0X08,0X08,0X08};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}

//	{
//		const uint8_t i[]={0xBD,0x06};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0xBC,0x00};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0xFF,0x60,0X01,0X04};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	
//	{
//		const uint8_t i[]={0xC3,0X13};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0xC4,0X13};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	
//	{
//		const uint8_t i[]={0xC9,0X22};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	
//	{
//		const uint8_t i[]={0xBE,0X11};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	
//	{
//		const uint8_t i[]={0xDF,0X21,0X0C,0X02};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	
//	

//	
//	{
//		const uint8_t i[]={0xF0,0X45,0X09,0X08,0X08,0X26,0X2A};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	
//	{
//		const uint8_t i[]={0xF1,0X43,0X70,0X72,0X36,0X37,0X6F};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0xF2,0X45,0X09,0X08,0X08,0X26,0X2A};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0xF3,0X43,0X70,0X72,0X36,0X37,0X6F};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0xED,0X1B,0X0B};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0xAE,0X77};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0xCD,0X63};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x70,0X07,0X07,0X04,0X0E,0X0F,0X09,0X07,0X08,0X03};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0xE8,0X34};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x62,0X18,0X0D,0X71,0XED,0X70,0X70,0X18,0X0F,0X71,0XEF,0X70,0X70};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x63,0X18,0X11,0X71,0XF1,0X70,0X70,0X18,0X13,0X71,0XF3,0X70,0X70};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	
	{
		const uint8_t i[]={0x64,0X28,0X29,0XF1,0X01,0XF1,0X00,0X07};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0x66,0X3C,0X00,0XCD,0X67,0X45,0X45,0X10,0X00,0X00,0X00};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	
	{
		const uint8_t i[]={0x67,0X00,0X3C,0X00,0X00,0X00,0X01,0X54,0X10,0X32,0X98};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	
	{
		const uint8_t i[]={0x74,0X10,0X85,0X80,0X00,0X00,0X4E,0X00};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	
//	{
//		const uint8_t i[]={0x98,0X3E,0X07};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	
//	{
//		const uint8_t i[]={0x35,0X21};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
	
//	
//	
//	
//	{
//		const uint8_t i[]={0x44,0X00,0X4A,0X21};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x2A,0X00,0X00,0X00,0XEF};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x2B,0X00,0X00,0X00,0XEF};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	{
//		const uint8_t i[]={0x2C};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
//	
//	
//	{
//		const uint8_t i[]={0x09,0X00,0X00,0X61,0X00,0X00};
//		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
//	}
	/*
	{
		const uint8_t i[]={0xF7,0xA9,0x51,0x2C,0x82};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xC0,0x11,0x09};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xC1,0x41};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xC5,0x00,0x2A,0x80};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xB1,0xB0,0x11};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xB4,0x02};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xB6,0x02,0x22};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xB7,0xC6};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xBE,0x00,0x04};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xE9,0x00};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0x36,0x08};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0x3A,0x55};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xE0,0x00,0x07,0x12,0x0B,0x3F,0x9B,0x4B,0x0B,0x0F0B,0x15,0x17,0x0F};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xE0,0x00,0x16,0x1B,0x02,0x0F,0x06,0x34,0x46,0x48,0x04,0x0D,0x0D,0x35,0x36,0x0F};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
		*/
	/*
	{
		const uint8_t i[]={0xE0,0x0F,0x13,0x1D,0x09,0x18,0x0A,0x43,0x66,0x4F,0x07,0x0F,0x0E,0x18,0x1A,0x03};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xE1,0x0F,0x1A,0x1D,0x04,0x0F,0x04,0x31,0x14,0x43,0x03,0x0D,0x0C,0x26,0x29,0x00};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		//const uint8_t i[]={0xC0,0x14,0x0E};
		const uint8_t i[]={0xC0,0x0E,0x0E};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		//const uint8_t i[]={0xC1,0x43};
		const uint8_t i[]={0xC1,0x44};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	
	{
		const uint8_t i[]={0xC5,0x00,0x36,0x80,0x40};
		//const uint8_t i[]={0xC5,0x00,0x40,0x00,0x40};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	//显示方向
	{
		const uint8_t i[]={0x36,0x48};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0x3A,0x55};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xB0,0x80};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xB4,0x02};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xB6,0x02,0x02,0x3B};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	*/
	
	
	{
		const uint8_t i[]={0xE9,0x00};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	{
		const uint8_t i[]={0xF7,0xA9,0x51,0x2C,0x82};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	
	{
		const uint8_t i[]={0x11};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	
	LCD_delay_ms(120);
	{
		const uint8_t i[]={0x29};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	GC9A01_Clear();//清除IC显示缓存
	{
		const uint8_t i[]={0x21};
		LCD_Send_nCmd((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
	}
	
	
	
	
	
	
	
	//GC9A01_Set_RGB565_Mode();
	//GC9A01_Set_RGB444_Mode();
	//GC9A01_Set_RGB666_Mode();
}
