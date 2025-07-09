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

#include "ssd1306.h"
#include "lcd_wegui_driver.h"


//默认8位IIC接口地址为:0x78




/*--------------------------------------------------------------
  * 名称: SSD1306_Set_Address_x(unsigned char x)
  * 传入: unsigned char x
  * 返回: 无
  * 功能: 向屏幕设置x方向的"光标"
----------------------------------------------------------------*/
void SSD1306_Set_Address_x(unsigned char x)
{
	LCD_Send_1Cmd(0x10|(x>>4));//高3字节
	LCD_Send_1Cmd(x&0x0f);//低4字节
}

/*--------------------------------------------------------------
  * 名称: SSD1306_Set_Address_ypage(unsigned char page)
  * 传入: page
  * 返回: 无
  * 功能: 向屏幕设置y方向的"页page"
  * 说明: 页1page = 8个像素点
----------------------------------------------------------------*/
void SSD1306_Set_Address_ypage(unsigned char page)
{
		LCD_Send_1Cmd(0xb0+page);
}

/*--------------------------------------------------------------
  * 名称: SSD1306_Set_Address_x_ypage(unsigned char x,unsigned char page)
  * 传入: x,page坐标
  * 返回: 无
  * 功能: 向屏幕设置x和ypage坐标
  * 说明: 
----------------------------------------------------------------*/
void SSD1306_Set_Address_x_ypage(unsigned char x,unsigned char page)
{
	//方式1:单字节发送SSD1306_Set_Address_x(x);
	//SSD1306_Set_Address_ypage(page);
	
	//方式2:连续发送
	uint8_t i[]={((x>>4) | 0x10),(x&0x0f),0xb0+page};
	LCD_Send_nCmd(i,3);
}


/*--------------------------------------------------------------
  * 名称: SSD1306_Clear()
  * 传入: 无
  * 返回: 无
  * 功能: 清空IC内部图像寄存器
  * 说明: 
----------------------------------------------------------------*/
void SSD1306_Clear()
{
	unsigned char page,x;
	for(page=0;page<8;page++)
	{
		SSD1306_Set_Address_ypage(page);
		SSD1306_Set_Address_x(0);
		for(x=0;x<128;x++)
		{
			LCD_Send_1Dat(0x00);
			//LCD_Send_1Dat(0xff);//测试
		}
	}
}



void SSD1306_Init(void)
{
	LCD_Send_1Cmd(0xAE);//--turn off oled panel
	LCD_Send_1Cmd(0x00);//---set low column address
	LCD_Send_1Cmd(0x10);//---set high column address
	LCD_Send_1Cmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	LCD_Send_1Cmd(0x81);//--set contrast control register
	LCD_Send_1Cmd(0xCF);// Set SEG Output Current Brightness
	LCD_Send_1Cmd(0xA1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	LCD_Send_1Cmd(0xC8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	LCD_Send_1Cmd(0xA6);//--set normal display
	LCD_Send_1Cmd(0xA8);//--set multiplex ratio(1 to 64)
	LCD_Send_1Cmd(0x3f);//--1/64 duty
	LCD_Send_1Cmd(0xD3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	LCD_Send_1Cmd(0x00);//-not offset
	LCD_Send_1Cmd(0xd5);//--set display clock divide ratio/oscillator frequency
	LCD_Send_1Cmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	LCD_Send_1Cmd(0xD9);//--set pre-charge period
	LCD_Send_1Cmd(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	LCD_Send_1Cmd(0xDA);//--set com pins hardware configuration
	LCD_Send_1Cmd(0x12);
	LCD_Send_1Cmd(0xDB);//--set vcomh
	LCD_Send_1Cmd(0x30);//Set VCOM Deselect Level
	LCD_Send_1Cmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	LCD_Send_1Cmd(0x02);//
	LCD_Send_1Cmd(0x8D);//--set Charge Pump enable/disable
	LCD_Send_1Cmd(0x14);//--set(0x10) disable
	SSD1306_Clear();
	LCD_Send_1Cmd(0xAF);
}


/*
void SSD1306_Init(void)
{
	
	SSD1306_Clear();

	LCD_delay_ms(200);
	SSD1306_Display_On();		//AF 屏幕开
	
}
*/
