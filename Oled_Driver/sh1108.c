#include "sh1108.h"
#include "oled_wegui_driver.h"


//默认8位IIC接口地址为:0x78



/*--------------------------------------------------------------
  * 名称: SH1108_Set_Address_x(unsigned char x)
  * 传入: unsigned char x
  * 返回: 无
  * 功能: 向屏幕设置x方向的"光标"
----------------------------------------------------------------*/
void SH1108_Set_Address_x(unsigned char x)
{
	//方式1:单字节发送
	OLED_send_1Cmd((x>>4) | 0x10);//高4字节
	OLED_send_1Cmd(x&0x0f);//低4字节
	
	//方式2:连续发送
	//uint8_t i[]={(x>>4),(x&0x0f)};
	//OLED_send_numCmd(i,2);
}

/*--------------------------------------------------------------
  * 名称: SH1108_Set_Address_ypage(unsigned char page)
  * 传入: page
  * 返回: 无
  * 功能: 向屏幕设置y方向的"页page"
  * 说明: 页1page = 8个像素点
----------------------------------------------------------------*/
void SH1108_Set_Address_ypage(unsigned char page)
{
	//方式1:单字节发送
	OLED_send_1Cmd(0xb0);
	OLED_send_1Cmd(page);
	
	//方式2:连续发送
	//uint8_t i[]={0xb0,page};
	//OLED_send_numCmd(i,2);
}

/*--------------------------------------------------------------
  * 名称: SH1108_Set_Address_x_ypage(unsigned char x,unsigned char page)
  * 传入: x,page坐标
  * 返回: 无
  * 功能: 向屏幕设置x和ypage坐标
  * 说明: 
----------------------------------------------------------------*/
void SH1108_Set_Address_x_ypage(unsigned char x,unsigned char page)
{
	//方式1:单字节发送
	//SH1108_Set_Address_x(x);
	//SH1108_Set_Address_ypage(page);
	
	//方式2:连续发送
	uint8_t i[]={((x>>4) | 0x10),(x&0x0f),0xb0,page};
	OLED_send_numCmd(i,4);
}


/*--------------------------------------------------------------
  * 名称: SH1108_Clear()
  * 传入: 无
  * 返回: 无
  * 功能: 清空IC内部图像寄存器
  * 说明: 
----------------------------------------------------------------*/
void SH1108_Clear()
{
	unsigned char page,x;
	for(page=0;page<20;page++)
	{
		SH1108_Set_Address_ypage(page);
		SH1108_Set_Address_x(0);
		for(x=0;x<160;x++)
		{
			//OLED_send_1Data(0x00);
			OLED_send_1Data(0xff);
		}
	}
}

//void SH1108_Init(void)
//{
//  OLED_send_1Cmd(0xAE); /*display off*/ 
//  OLED_send_1Cmd(0x00); /*set lower column address*/ 
//  OLED_send_1Cmd(0x10); /*set higher column address*/
//	OLED_send_1Cmd(0xB0); /*set page address*/ 
//	OLED_send_1Cmd(0x40); /*set display start lines*/ 
//	OLED_send_1Cmd(0x81); /*contract control*/ 
//	OLED_send_1Cmd(0x88); /*4d*/ 
//	OLED_send_1Cmd(0x82); /* iref resistor set and adjust ISEG*/ 
//	OLED_send_1Cmd(0x00); 
//	OLED_send_1Cmd(0xA1); /*set segment remap 0xA0*/ 
//	OLED_send_1Cmd(0xA2); /*set seg pads hardware configuration*/ 
//	OLED_send_1Cmd(0xA4); /*Disable Entire Display On (0xA4/0xA5)*/ 
//	OLED_send_1Cmd(0xA6); /*normal / reverse*/ 
//	OLED_send_1Cmd(0xA8); /*multiplex ratio*/ 
//	OLED_send_1Cmd(0x3F); /*duty = 1/64*/ 
//	OLED_send_1Cmd(0xC8); /*Com scan direction 0XC0*/ 
//	OLED_send_1Cmd(0xD3); /*set display offset*/ 
//	OLED_send_1Cmd(0x00); /* */ 
//	OLED_send_1Cmd(0xD5); /*set osc division*/ 
//	OLED_send_1Cmd(0xa0); 
//	OLED_send_1Cmd(0xD9); /*set pre-charge period*/ 
//	OLED_send_1Cmd(0x22); 
//	OLED_send_1Cmd(0xdb); /*set vcomh*/ 
//	OLED_send_1Cmd(0x40); 
//	OLED_send_1Cmd(0x31); /* Set pump 7.4v */ 
//	OLED_send_1Cmd(0xad); /*set charge pump enable*/ 
//	OLED_send_1Cmd(0x8b); /*Set DC-DC enable (0x8a=disable; 0x8b=enable) */ 
//	SH1108_Clear();
//	OLED_send_1Cmd(0xAF);
//}

void SH1108_Init(void)
{
			//开关屏幕				
			SH1108_Display_Off();	
			//SH1108_Display_On();	
				
			//对比度
			SH1108_Set_Contrast(0xd0);
				
			//全亮测试				
			SH1108_Entire_Display_Off();	
			//SH1108_Entire_Display_On();	
				
			//反色显示				
			SH1108_Set_Reverse_Display_Off();	
			//SH1108_Set_Reverse_Display_On();	
				
			//设置屏幕驱动路数		
			//SH1108_Display_Resolution_Control(COM64_SEG160);	
			//SH1108_Display_Resolution_Control(COM96_SEG160);	
			SH1108_Display_Resolution_Control(COM128_SEG160);	
			//SH1108_Display_Resolution_Control(COM160_SEG160);

			//设置DCDC,过于复杂看规格书				
			SH1108_Set_DCDC(0x80);	
			
			//显示方向1 正向显示
			SH1108_Set_COM_Scan_Dir0();//0xC0
			SH1108_Set_Segment_Remap_dir0();//0xA0
			//显示方向2
			//SH1108_Set_COM_Scan_Dir1();//0xC8
			//SH1108_Set_Segment_Remap_dir1();//0xA1
			//显示方向3
			//SH1108_Set_COM_Scan_Dir0();//0xC0
			//SH1108_Set_Segment_Remap_dir1() ;//0xA1
			//显示方向4
			//SH1108_Set_COM_Scan_Dir1();//0xC8
			//SH1108_Set_Segment_Remap_dir0();//0xA0
			
			
			//分频和时钟	
			SH1108_Set_Frequency(15,0);	//([0:15],[0:15])设置内部晶振频率,设置时钟分频, 默认(7,0)
			
			
			
			//充放电		
			SH1108_Set_Pre_charge_Period(0x02,0x0F);	
			
			
			//设定VCOM [0:63] 默认21	
			SH1108_Set_VCOMH(0x3F);
			
			//工作模式			
			SH1108_Set_Memory_addressing_mode(Page_addressing_mode);	
			//SH1108_Set_Memory_addressing_mode(Vertical_addressing_mode);	
			
			//设定VSEGM [0:63] 默认21	
			SH1108_Set_VSEGM(0x35);
			
			//设定VSL [0:15] 默认0	
			SH1108_Discharge_VSL(0);
			

			
			//清屏
			SH1108_Clear();
				
				OLED_delay_ms(200);
			SH1108_Display_On();	

}
