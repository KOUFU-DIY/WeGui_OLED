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

#include "ssd1312.h"
#include "lcd_wegui_driver.h"






/*--------------------------------------------------------------
  * 名称: SSD1312_Set_Address_x(unsigned char x)
  * 传入: unsigned char x
  * 返回: 无
  * 功能: 向屏幕设置x方向的"光标"
----------------------------------------------------------------*/
void SSD1312_Set_Address_x(unsigned char x)
{
	LCD_Send_1Cmd(0x10|(x>>4));//高3字节
	LCD_Send_1Cmd(x&0x0f);//低4字节
}

/*--------------------------------------------------------------
  * 名称: SSD1312_Set_Address_ypage(unsigned char page)
  * 传入: page
  * 返回: 无
  * 功能: 向屏幕设置y方向的"页page"
  * 说明: 页1page = 8个像素点
----------------------------------------------------------------*/
void SSD1312_Set_Address_ypage(unsigned char page)
{
		LCD_Send_1Cmd(0xb0+page);
}

/*--------------------------------------------------------------
  * 名称: SSD1312_Set_Address_x_ypage(unsigned char x,unsigned char page)
  * 传入: x,page坐标
  * 返回: 无
  * 功能: 向屏幕设置x和ypage坐标
  * 说明: 
----------------------------------------------------------------*/
void SSD1312_Set_Address_x_ypage(unsigned char x,unsigned char page)
{
	//方式1:单字节发送
	//SSD1312_Set_Address_x(x);
	//SSD1312_Set_Address_ypage(page);
	
	//方式2:连续发送
	uint8_t i[]={((x>>4) | 0x10),(x&0x0f),0xb0+page};
	LCD_Send_nCmd(i,3);
}


/*--------------------------------------------------------------
  * 名称: SSD1312_Clear()
  * 传入: 无
  * 返回: 无
  * 功能: 清空IC内部图像寄存器
  * 说明: 
----------------------------------------------------------------*/
void SSD1312_Clear()
{
	unsigned char page,x;
	for(page=0;page<16;page++)
	{
		SSD1312_Set_Address_ypage(page);
		SSD1312_Set_Address_x(0);
		for(x=0;x<128;x++)
		{
			LCD_Send_1Dat(0x00);
			//LCD_Send_1Dat(0xff);//测试
		}
	}
}



void SSD1312_Init(void)
{
	
	LCD_Send_1Cmd(0xAE);//--turn off oled panel

	LCD_Send_1Cmd(0xA8);    /*multiplex ratio*/
	LCD_Send_1Cmd(0x3F);    /*duty = 1/64*/

	LCD_Send_1Cmd(0xAD);    
	LCD_Send_1Cmd(0x40);
	
	LCD_Send_1Cmd(0xD3);    /*set display offset*/
	LCD_Send_1Cmd(0x00);    /*   0x20   */	
	
	LCD_Send_1Cmd(0xA4);    /*Disable Entire Display On (0xA4/0xA5)*/ 

	LCD_Send_1Cmd(0xA6);    /*normal / reverse*/
  LCD_Send_1Cmd(0x40); 	
	LCD_Send_1Cmd(0x81);    /*contract control*/
	LCD_Send_1Cmd(0x57);    /*128*/

	LCD_Send_1Cmd(0xD9);    /*set pre-charge period*/
	LCD_Send_1Cmd(0x42);

	LCD_Send_1Cmd(0xD5);  
	LCD_Send_1Cmd(0x90);

	LCD_Send_1Cmd(0xDA);    /* Set SEG Pins Hardware Configuration */
	LCD_Send_1Cmd(0x10);


	//方向1
	{
//		LCD_Send_1Cmd(0x20);    /* Set Memory addressing mode (0x20/0x21) */
//		LCD_Send_1Cmd(0x09);     /* 0x09 */
//		LCD_Send_1Cmd(0xA1);    /*set segment remap  0XA1 */
//		LCD_Send_1Cmd(0xC8);    /*Com scan direction   0Xc8  */
	}
	//方向2
	{
//		LCD_Send_1Cmd(0x20);    /* Set Memory addressing mode (0x20/0x21) */
//		LCD_Send_1Cmd(0x02);     /* 0x02 */
//		LCD_Send_1Cmd(0xA1);    /*set segment remap  0XA1 */
//		LCD_Send_1Cmd(0xC0);    /*Com scan direction   0Xc0  */
	}
	//方向3
	{
//		LCD_Send_1Cmd(0x20);    /* Set Memory addressing mode (0x20/0x21) */
//		LCD_Send_1Cmd(0x09);     /* 0x09 */
//		LCD_Send_1Cmd(0xA0);    /*set segment remap  0XA0 */
//		LCD_Send_1Cmd(0xC0);    /*Com scan direction   0Xc0  */
	}
	//方向5
	{
		LCD_Send_1Cmd(0x20);    /* Set Memory addressing mode (0x20/0x21) */
		LCD_Send_1Cmd(0x02);     /* 0x02 */
		LCD_Send_1Cmd(0xA0);    /*set segment remap  0XA0 */
		LCD_Send_1Cmd(0xC8);    /*Com scan direction   0Xc8  */
	}
	
	LCD_Send_1Cmd(0xdb);    /*set vcomh*/
	LCD_Send_1Cmd(0x30);

	LCD_Send_1Cmd(0x8d);    /*set charge pump enable*/
	LCD_Send_1Cmd(0x14);    

	LCD_Send_1Cmd(0x00);    /*set lower column address*/       
	LCD_Send_1Cmd(0x10);    /*set higher column address*/	
	
	SSD1312_Clear();
	LCD_Send_1Cmd(0xAF);
}
