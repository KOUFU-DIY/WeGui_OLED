#include "ssd1315.h"
#include "oled_wegui_driver.h"


//默认8位IIC接口地址为:0x78




/*--------------------------------------------------------------
  * 名称: SSD1315_Set_Address_x(unsigned char x)
  * 传入: unsigned char x
  * 返回: 无
  * 功能: 向屏幕设置x方向的"光标"
----------------------------------------------------------------*/
void SSD1315_Set_Address_x(unsigned char x)
{
	OLED_send_1Cmd((x>>4) | 0x10);//高3字节
	OLED_send_1Cmd(x&0x0f);//低4字节
}

/*--------------------------------------------------------------
  * 名称: SSD1315_Set_Address_ypage(unsigned char page)
  * 传入: page
  * 返回: 无
  * 功能: 向屏幕设置y方向的"页page"
  * 说明: 页1page = 8个像素点
----------------------------------------------------------------*/
void SSD1315_Set_Address_ypage(unsigned char page)
{
		OLED_send_1Cmd(0xb0+page);
}

/*--------------------------------------------------------------
  * 名称: SSD1315_Set_Address_x_ypage(unsigned char x,unsigned char page)
  * 传入: x,page坐标
  * 返回: 无
  * 功能: 向屏幕设置x和ypage坐标
  * 说明: 
----------------------------------------------------------------*/
void SSD1315_Set_Address_x_ypage(unsigned char x,unsigned char page)
{
	//方式1:单字节发送
	//SSD1315_Set_Address_x(x);
	//SSD1315_Set_Address_ypage(page);
	
	//方式2:连续发送
	uint8_t i[]={((x>>4) | 0x10),(x&0x0f),0xb0+page};
	OLED_send_numCmd(i,4);
}


/*--------------------------------------------------------------
  * 名称: SSD1315_Clear()
  * 传入: 无
  * 返回: 无
  * 功能: 清空IC内部图像寄存器
  * 说明: 
----------------------------------------------------------------*/
void SSD1315_Clear()
{
	unsigned char page,x;
	for(page=0;page<8;page++)
	{
		SSD1315_Set_Address_ypage(page);
		SSD1315_Set_Address_x(0);
		for(x=0;x<128;x++)
		{
			OLED_send_1Data(0x00);
			//OLED_send_1Data(0xff);
		}
	}
}


/*
void SSD1315_Init(void)
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
	OLED_send_1Cmd(0x40);//Set VCOM Deselect Level
	OLED_send_1Cmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_send_1Cmd(0x02);//
	OLED_send_1Cmd(0x8D);//--set Charge Pump enable/disable
	OLED_send_1Cmd(0x14);//--set(0x10) disable
	OLED_send_1Cmd(0xA4);// Disable Entire Display On (0xa4/0xa5)
	OLED_send_1Cmd(0xA6);// Disable Inverse Display On (0xa6/a7) 
	SSD1315_Clear();
	OLED_send_1Cmd(0xAF);
}
*/


void SSD1315_Init(void)
{
	
	SSD1315_Display_Off();//AE 屏幕关,休眠(默认)
	
	SSD1315_Set_Lower_ColumnStart_Address_for_Page_Addressing_Mode(0) ;//[0:15]默认0
	SSD1315_Set_Higher_ColumnStart_Address_for_Page_Addressing_Mode(0);//[0:7]默认0
	
	SSD1315_Set_Display_Start_Line(0);//[0:63]默认0
	SSD1315_Set_Display_Offset(0);//D3 屏幕偏移显示[0:63]默认0
	
	SSD1315_Set_Contrast_Control(207);//81 设置对比度[0:255]默认127
	SSD1315_Set_Column_Address(0,127);//21 start[0:127]默认0,end[0:127]默认127
	SSD1315_Set_Page_Address(0,7);//22 start[0:7]默认0,end[0:127]默认7
	
	//SSD1315_Set_Segment_Remap_dir0();//A0 设置屏幕X扫描方向0
	SSD1315_Set_Segment_Remap_dir1();//A1 设置屏幕X扫描方向1
	
	//SSD1315_Set_COM_Scan_Dir0();//C0 设置屏幕Y扫描方向,COM0到COMn-1(默认)
	SSD1315_Set_COM_Scan_Dir1();//C8 设置屏幕Y扫描方向,COMn-1到COM0
	
	SSD1315_Set_Reverse_Display_Off();//A6正常显示
	//SSD1315_Set_Reverse_Display_On() ;//A7反色显示
	
	SSD1315_Set_Multiplex_Ratio(63);//A8 设置频率[0:63]默认63  0~14无效 15对应16MUX 63对应64MUX
	SSD1315_Set_Frequency(0x8,0x0);//D5 分频和时钟 F_OSC[0:15]默认8, Divide_ratio分频[0:15]默认0对应1分频
	SSD1315_Set_Pre_charge_Period(0xF,0x1);//D9 设置预充电(第一阶段时间,第二阶段时间), 默认(2,2)
	SSD1315_Set_COM_Pins_Hardware_Cfg(0x12);//DA 硬件连接方式(根据屏幕开发商走线配置) 0x02,0x12,0x32,0x42
	SSD1315_Set_VCOMH(0x40);//DB 设定VCOM 0x00=0.65VCC 0x10=0.71VCC 0x20=0.77VCC(默认) 0x30=0.83VCC
	SSD1315_Charge_Pump_Setting(0x14);//8D 设定电荷泵0x14=7.5V(默认) 0x94=8.5V 0x95=9.0V
	
	//工作模式
	//Horizontal_Addressing_Mode 	0x0	
	//Vertical_Addressing_Mode	 	0x1
	//Page_Addressing_Mode        0x2//默认 
	SSD1315_Set_Memory_addressing_mode(Page_Addressing_Mode);
	
	
	//配置参考电流	
	//external_IREF                  0x00//默认
	//internal_19uA_IREF_ISEG_150uA  0x10
	//internal_30uA_IREF_ISEG_240uAF 0x30
	SSD1315_Set_Internal_IREF(external_IREF);//AD 配置参考电流
	
		SSD1315_Entire_Display_Off();	//A4全亮测试关
	//SSD1315_Entire_Display_On();  //A5全亮测试开
	
	
	//Disable_Fade_Out_Blinking_mode //默认
	//Enable_Fade_Out_mode 
	//Enable_Blinking_mode 
	SSD1315_Set_Fade_Out_and_Blinking(Disable_Fade_Out_Blinking_mode,0);//23 消影参数: frames_set[0:15] 0对应8帧 1对应16帧 2对应24帧 15对应128帧
	
	SSD1315_Set_Zoom_In(0);//D6 放大模式 0关闭(默认) 1使能
	
	SSD1315_Clear();
	
	
	OLED_delay_ms(200);
	SSD1315_Display_On();		//AF 屏幕开
	
}
