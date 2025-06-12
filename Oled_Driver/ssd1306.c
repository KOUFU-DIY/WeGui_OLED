#include "SSD1306.h"
#include "oled_wegui_driver.h"


//默认8位IIC接口地址为:0x78




/*--------------------------------------------------------------
  * 名称: SSD1306_Set_Address_x(unsigned char x)
  * 传入: unsigned char x
  * 返回: 无
  * 功能: 向屏幕设置x方向的"光标"
----------------------------------------------------------------*/
void SSD1306_Set_Address_x(unsigned char x)
{
	OLED_send_1Cmd(0x10|(x>>4));//高3字节
	OLED_send_1Cmd(x&0x0f);//低4字节
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
		OLED_send_1Cmd(0xb0+page);
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
	//方式1:单字节发送
	//SSD1306_Set_Address_x(x);
	//SSD1306_Set_Address_ypage(page);
	
	//方式2:连续发送
	uint8_t i[]={((x>>4) | 0x10),(x&0x0f),0xb0+page};
	OLED_send_numCmd(i,4);
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
			OLED_send_1Data(0x00);
			//OLED_send_1Data(0xff);
		}
	}
}



void SSD1306_Init(void)
{
	OLED_send_1Cmd(0xAE);//--turn off oled panel
	OLED_send_1Cmd(0x00);//---set low column address
	OLED_send_1Cmd(0x10);//---set high column address
	OLED_send_1Cmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_send_1Cmd(0x81);//--set contrast control register
	OLED_send_1Cmd(0xCF);// Set SEG Output Current Brightness
	OLED_send_1Cmd(0xA1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_send_1Cmd(0xC8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_send_1Cmd(0xA6);//--set normal display
	OLED_send_1Cmd(0xA8);//--set multiplex ratio(1 to 64)
	OLED_send_1Cmd(0x3f);//--1/64 duty
	OLED_send_1Cmd(0xD3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_send_1Cmd(0x00);//-not offset
	OLED_send_1Cmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_send_1Cmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_send_1Cmd(0xD9);//--set pre-charge period
	OLED_send_1Cmd(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_send_1Cmd(0xDA);//--set com pins hardware configuration
	OLED_send_1Cmd(0x12);
	OLED_send_1Cmd(0xDB);//--set vcomh
	OLED_send_1Cmd(0x30);//Set VCOM Deselect Level
	OLED_send_1Cmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_send_1Cmd(0x02);//
	OLED_send_1Cmd(0x8D);//--set Charge Pump enable/disable
	OLED_send_1Cmd(0x14);//--set(0x10) disable
	SSD1306_Clear();
	OLED_send_1Cmd(0xAF);
}


/*
void SSD1306_Init(void)
{
	
	SSD1306_Clear();

	OLED_delay_ms(200);
	SSD1306_Display_On();		//AF 屏幕开
	
}
*/