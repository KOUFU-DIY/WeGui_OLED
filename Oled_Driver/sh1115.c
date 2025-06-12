#include "SH1115.h"
#include "oled_wegui_driver.h"

//兼容SSD1319
                                                                           



//默认8位IIC接口地址为:0x78




/*--------------------------------------------------------------
  * 名称: SH1115_Set_Address_x(unsigned char x)
  * 传入: unsigned char x
  * 返回: 无
  * 功能: 向屏幕设置x方向的"光标"
----------------------------------------------------------------*/
void SH1115_Set_Address_x(unsigned char x)
{
	OLED_send_1Cmd(x&0x0f);//低4字节
	OLED_send_1Cmd((x>>4) | 0x10);//高4字节
}

/*--------------------------------------------------------------
  * 名称: SH1115_Set_Address_ypage(unsigned char page)
  * 传入: page
  * 返回: 无
  * 功能: 向屏幕设置y方向的"页page"
  * 说明: 页1page = 8个像素点
----------------------------------------------------------------*/
void SH1115_Set_Address_ypage(unsigned char page)
{
		OLED_send_1Cmd(0xb0+page);
}

/*--------------------------------------------------------------
  * 名称: SH1108_Set_Address_x_ypage(unsigned char x,unsigned char page)
  * 传入: x,page坐标
  * 返回: 无
  * 功能: 向屏幕设置x和ypage坐标
  * 说明: 
----------------------------------------------------------------*/
void SH1115_Set_Address_x_ypage(unsigned char x,unsigned char page)
{
	//方式1:单字节发送
	//SH1115_Set_Address_x(x);
	//SH1115_Set_Address_ypage(page);
	
	//方式2:连续发送
	uint8_t i[]={((x>>4) | 0x10),(x&0x0f),0xb0+page};
	OLED_send_numCmd(i,4);
}

/*--------------------------------------------------------------
  * 名称: SH1115_Clear()
  * 传入: 无
  * 返回: 无
  * 功能: 清空IC内部图像寄存器
  * 说明: 
----------------------------------------------------------------*/
void SH1115_Clear()
{
	unsigned char page,x;
	for(page=0;page<8;page++)
	{
		SH1115_Set_Address_ypage(page);
		SH1115_Set_Address_x(0);
		for(x=0;x<128;x++)
		{
			//OLED_send_1Data(0x00);
			OLED_send_1Data(0xff);
		}
	}
}


//void SH1115_Init(void)
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
//	SH1115_Clear();
//	OLED_send_1Cmd(0xAF);
//}


void SH1115_Init(void)
{
	
	SH1115_Display_OFF() ;//AEh 关闭显示 默认
			
	SH1115_Set_Lower_Column_Address(0);
	SH1115_Set_Higher_Column_Address(0);
	
	SH1115_Set_Display_Start_Line(0);//40h~7Fh 显示起始位置 [0:15]默认0
	SH1115_The_Contrast_Control_Mode_Set(0x88);//81h 对比度 [0:255]默认127
	
	SH1115_IREF_Resistor_Set_and_Adjust_ISEG_by_PAD(0x00);//82h 配置参考电流 默认0x00 详情看手册
	
	
	SH1115_Set_SEG_pads_hardware_configuration_0();//A2h 设置点阵排布顺序0 默认
	//SH1115_Set_SEG_pads_hardware_configuration_1();//A3h 设置点阵排布顺序1
	
	//-------------切换方向相关设置----------------
	//SH1115_Set_Segment_Remap_dir0();//A0h 设置映射配置0 默认
	SH1115_Set_Segment_Remap_dir1();//A1h 设置映射配置1
	
	//SH1115_Set_Common_Output_Scan_Dir0();//C0h COM输出扫描方向0 默认
	SH1115_Set_Common_Output_Scan_Dir1();//C8h COM输出扫描方向1
	//-------------切换方向相关设置----------------
	
	
	SH1115_Entire_Display_Off(); 	//A4全亮测试关(默认)
	//SH1115_Entire_Display_On(); 	  //A5全亮测试开
	
	SH1115_Set_Multiplex_Ration(0x3F);//A8 设置频率[0:63]默认63
	

	
	SH1115_Set_Display_Offset(0x00);//D3h y显示偏移 [0:63]默认0
	
	//D5h osc_ofset晶振偏移[0:15]0对应-17.1% 5对应0%(默认) 15对应+25.1%    dir分频0=8分(默认) 1=16分 2=3分 3=4分
	SH1115_Set_Display_Clock_Divide_Ratio_Oscillator_Frequency(0XA,0x0); 
	
	SH1115_Set_Discharge_Pre_charge_Period(0x2,0x2);//D9h 放电[0:15]默认2 充电[0:15] 默认2
	
	SH1115_VCOM_Deselect_Level_Mode_Set(0x40);//DBh 设置VCOM [0h:FFh]默认35h
	
	SH1115_Set_Pump_voltage_value(1);//30h 31h 32h 33h 设置电源电荷泵 b0[0:3]默认2
	
	//SH1115_Set_DCDC_OFF();	//ADh 8Ah 关闭DC升压
	SH1115_Set_DCDC_ON() ;//ADh 8Bh 打开DC升压 默认
	
	SH1115_Set_Reverse_Display_Off();//A6正常显示 默认
	//SH1115_Set_Reverse_Display_On();//A7反色显示
	
	

//	//非必要参数
//	SH1115_Set_Breathing_Display_Effect(0,0);//23h 灰度呼吸设置 en:[0:1]默认0 br:[0:32]默认0
//	SH1115_Additional_Horizontal_Scroll_Setup_Mode_Set(0,0);//24h 垂直滚动设置 Start_Column:[0:127]默认0 End_Column:[0:127]默认0
//	SH1115_Horizontal_Scroll_Setup_Mode_Set(0,0,0,0);//26h/27h 垂直滚动设置 en:[0:1]默认0 Start_Page:[0:7]默认0 Time[0:7]默认0 默认0 End_Page:[0:7]默认7
//	//Continuous_horizontalo_or_vertical_scroll//(default)
//	//Single_Screen_scroll
//	//Column_scroll_mode
//	SH1115_Set_Scroll_Mode(Continuous_horizontalo_or_vertical_scroll);//28h 滚动模式

//	SH1115_Set_Deactivate_Horizontal_Scroll();//2Eh 默认
//	//SH1115_Set_Activate_Horizontal_Scroll();//2Fh
//	
//	SH1115_Set_row_non_overlap_SEG_Hiz_Period(0x01); //DCh 驱动消影?[0h:FFh]默认0x01


		OLED_delay_ms(200);
	SH1115_Display_ON();//AFh 打开显示
}
