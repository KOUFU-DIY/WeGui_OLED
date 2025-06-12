#include "SSD1327.h"
#include "oled_wegui_driver.h"


#error("wegui do not suppout this ic!")


/*--------------------------------------------------------------
  * 名称: SSD1327_Set_Address_x(unsigned char x)
  * 传入: unsigned char x
  * 返回: 无
  * 功能: 向屏幕设置x方向的"光标"
----------------------------------------------------------------*/
void SSD1327_Set_Address_x(unsigned char x)
{
		OLED_send_1Cmd(0x15);//CMD
	OLED_send_1Cmd(0);//START
	OLED_send_1Cmd(63);//END
	//SSD1327_Set_Column_Address(0,127);//15h start[0:127]默认0,end[0:127]默认127
}

/*--------------------------------------------------------------
  * 名称: SSD1327_Set_Address_ypage(unsigned char page)
  * 传入: page
  * 返回: 无
  * 功能: 向屏幕设置y方向的"页page"
  * 说明: 页1page = 8个像素点
----------------------------------------------------------------*/
void SSD1327_Set_Address_ypage(unsigned char page)
{
		OLED_send_1Cmd(0x75);//CMD
	OLED_send_1Cmd(page*8);//START
	OLED_send_1Cmd(63);//END
}



void Column_Address(u8 a, u8 b)
{
	OLED_send_1Cmd(0x15);			    // Set Column Address
	OLED_send_1Cmd(a);				//   Default => 0x00
	OLED_send_1Cmd(b);				//   Default => 0x77
}

//******************************************************************************
//    函数说明：OLED显示行的起始终止地址
//    入口数据：a  行的起始地址
//              b  行的终止地址
//    返回值：  无
//******************************************************************************
void Row_Address(u8 a, u8 b)
{
	OLED_send_1Cmd(0x75);			// Set Row Address
	OLED_send_1Cmd(a);				//   Default => 0x00
	OLED_send_1Cmd(b);				//   Default => 0x3F
}
//******************************************************************************
//    函数说明：OLED清屏显示
//    入口数据：无
//    返回值：  无
//******************************************************************************
void OLED_Clear(u8 x1,u8 y1,u8 x2,u8 y2,u8 color)
{
	u8 i,m=0;
	x1/=2;x2/=2;
	Column_Address(x1,x2-1);
	Row_Address(y1,y2-1);
	for (m=0;m<y2-y1;m++) 
	{ 
		for (i=0;i<x2-x1;i++)
		{
			 OLED_send_1Data(color);
		}
	}
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
//	unsigned char page,x;
//	for(page=0;page<8;page++)
//	{
//		SSD1327_Set_Address_ypage(page);
//		SSD1327_Set_Address_x(0);
//		for(x=0;x<128;x++)
//		{
//			//OLED_send_1Data(0x00);
//			OLED_send_1Data(0xff);
//		}
//	}
}



//void SSD1327_Init(void)
//{
//	OLED_send_1Cmd(0xae);//Set display off
//	OLED_send_1Cmd(0xa0);//Set re-map
//	
//	OLED_send_1Cmd(0x66);//USE_HORIZONTAL1
//	//OLED_send_1Cmd(0x55);//USE_HORIZONTAL2
//	
//	OLED_send_1Cmd(0xa1);//Set display start line
//	OLED_send_1Cmd(0x00);
//	OLED_send_1Cmd(0xa2);//Set display offset
//	OLED_send_1Cmd(0x00);
//	OLED_send_1Cmd(0xa4);//Normal Display
//	OLED_send_1Cmd(0xa8);//Set multiplex ratio
//	OLED_send_1Cmd(0x7f);
//	OLED_send_1Cmd(0xab);//Function Selection A
//	OLED_send_1Cmd(0x01);//Enable internal VDD regulator
//	OLED_send_1Cmd(0x81);//Set contrast
//	OLED_send_1Cmd(0x77);
//	OLED_send_1Cmd(0xb1);//Set Phase Length
//	OLED_send_1Cmd(0x31);
//	OLED_send_1Cmd(0xb3);//Set Front Clock Divider /Oscillator Frequency
//	OLED_send_1Cmd(0xb1);
//  OLED_send_1Cmd(0xb5);//
//  OLED_send_1Cmd(0x03);//0X03 enable
//	OLED_send_1Cmd(0xb6);//Set Second pre-charge Period
//	OLED_send_1Cmd(0x0d);
//	
//	OLED_send_1Cmd(0xbc);//Set Pre-charge voltage
//	OLED_send_1Cmd(0x07);
//	OLED_send_1Cmd(0xbe);//Set VCOMH
//	OLED_send_1Cmd(0x07);
//	OLED_send_1Cmd(0xd5);//Function Selection B
//	OLED_send_1Cmd(0x02);//Enable second pre-charge
//	SSD1327_Clear();
//	OLED_send_1Cmd(0xaf);//Display on
//	
//	OLED_Clear(0,0,16,16,0XFF);
//	OLED_Clear(16,16,32,32,0XAA);
//	while(1);
//	
//	
//}



void SSD1327_Init(void)
{
	SSD1327_Display_OFF();//AEh 屏幕关,休眠(默认)
	
	//---------------根据屏幕设置--------------
	SSD1327_Set_Remap(0x66);//A0h 设置屏幕映射位置 默认0x00
	//SSD1327_Set_Remap(0x55);//A0h 设置屏幕映射位置 默认0x00
	//---------------根据屏幕设置--------------
	
	SSD1327_Set_Display_Start_Line(0);//A1h [0:127]默认0
	SSD1327_Set_Display_Offset(0);//A2h [0:127]默认0
	
	SSD1327_Set_Display_Mode_A4();//A4h Normal display (默认)
	//SSD1327_Set_Display_Mode_A5();//A5h All ON (All pixels have gray scale of 15, GS15)
	//SSD1327_Set_Display_Mode_A6();//A6h All OFF (All pixels have gray scale of 0, GS0)
	//SSD1327_Set_Display_Mode_A7();//A7h Inverse Display (GS0 -> GS15, GS1 -> GS14, GS2 -> GS13, ...)
	
	SSD1327_Set_MUX_Ratio(127);//A8h [15:127] 15=16MUX;127=128MUX(默认)
	
		//SSD1327_Func_A_Select_external_VDD();//ABh 0x00
	SSD1327_Func_A_Select_internal_VDD();//ABh 0x01 默认
	
	SSD1327_Set_Contrast_Control(0x77);//81h 设置对比度[0:255]默认127
	
	SSD1327_Set_Phase_Length(3,1);//B1h 充放电周期(周期1[0:15],周期2[0:15]), 默认(7,8)
	
	Set_Front_Clock_Frequency(0xb1);//B3h [0x00:0xFF] 默认0x00 b7~b4设置晶振 b3~b0设置分频
	
	//GPIO_Hiz_input_dis()  ;//B5h 0x00
	//GPIO_Hiz_input_en()   ;//B5h 0x01 
	//GPIO_Hiz_output_Low() ;//B5h 0x02 默认
	GPIO_Hiz_output_High();//B5h 0x03
	
	SSD1327_Set_VCOMH(0x07);//BEh [0x00,0x0F] 默认0x05
	
	//#define dis_2_precharge  0 //默认
	//#define en_2_precharge   1
	//#define Internal_VSL   0 //默认
	//#define external_VSL   1
	SSD1327_Func_Selection_B(en_2_precharge,Internal_VSL);//D5h 默认(0x0,0x0)
	
	SSD1327_Set_Pre_charge_voltage(0x07);//BCh [0x00,0x0F] 默认0x05
	
	
	
	//------非必要-----
	//Set_Gray_Scale_Table(y0,y1,y2,y3,y4,y5,y6,y7,y8,y9,y10,y11,y12,y13,y14,y15);//B8h 灰度设置
	//SSD1327_Set_Command_Lock()  ;//FDh 0x16
	//SSD1327_Set_Command_unLock();//FDh 0x12 (默认)
	//------非必要-----




	SSD1327_Display_ON();//AFh 屏幕开
		OLED_Clear(0,0,16,16,0XFF);
	OLED_Clear(16,16,32,32,0XAA);
	while(1);
}
