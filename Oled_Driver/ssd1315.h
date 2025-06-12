#ifndef __SSD1315_H__
#define __SSD1315_H__


#define SSD1315_Set_Lower_ColumnStart_Address_for_Page_Addressing_Mode(x)  do{OLED_send_1Cmd(x);}while(0)//[0:15]默认0
#define SSD1315_Set_Higher_ColumnStart_Address_for_Page_Addressing_Mode(x) do{OLED_send_1Cmd(0x10|x);}while(0)//[0:7]默认0


//工作模式
#define Horizontal_Addressing_Mode 0				
#define Vertical_Addressing_Mode	 1		
#define Page_Addressing_Mode       2 //默认 
#define SSD1315_Set_Memory_addressing_mode(x)	do{OLED_send_1Cmd(0x20);OLED_send_1Cmd(x);}while(0)


#define SSD1315_Set_Column_Address(start,end) do{OLED_send_1Cmd(0x21);OLED_send_1Cmd(start);OLED_send_1Cmd(end);}while(0)//21 start[0:127]默认0,end[0:127]默认127

#define SSD1315_Set_Page_Address(start,end) do{OLED_send_1Cmd(0x22);OLED_send_1Cmd(start);OLED_send_1Cmd(end);}while(0)//22 start[0:7]默认0,end[0:7]默认7

#define SSD1315_Set_Display_Start_Line(x) do{OLED_send_1Cmd(0x40|x);}while(0)//[0:63]默认0


//对比度
#define SSD1315_Set_Contrast_Control(x) do{OLED_send_1Cmd(0x81);OLED_send_1Cmd(x);}while(0)//81 设置对比度[0:255]默认127


//映射方向
#define SSD1315_Set_Segment_Remap_dir0() 										do{OLED_send_1Cmd(0xA0);}while(0)			//A0设置屏幕X扫描方向0
#define SSD1315_Set_Segment_Remap_dir1() 										do{OLED_send_1Cmd(0xA1);}while(0)	    //A1设置屏幕X扫描方向1


		
//全亮测试			
#define SSD1315_Entire_Display_Off() 												do{OLED_send_1Cmd(0xA4);}while(0)			//A4全亮测试关
#define SSD1315_Entire_Display_On() 												do{OLED_send_1Cmd(0xA5);}while(0)		  //A5全亮测试开

//反色显示			                                                  
#define SSD1315_Set_Reverse_Display_Off() 										do{OLED_send_1Cmd(0xA6);}while(0)		//A6正常显示
#define SSD1315_Set_Reverse_Display_On() 										do{OLED_send_1Cmd(0xA7);}while(0)			//A7反色显示

//设置频率
#define SSD1315_Set_Multiplex_Ratio(x) do{OLED_send_1Cmd(0xA8);OLED_send_1Cmd(x);}while(0)//A8 设置频率[0:63]默认63  0~14无效 15对应16MUX 63对应64MUX


//配置参考电流		
#define external_IREF      0x00
#define internal_19uA_IREF_ISEG_150uA 0x10
#define internal_30uA_IREF_ISEG_240uAF 0x30
#define SSD1315_Set_Internal_IREF(x)													do{OLED_send_1Cmd(0xAD);OLED_send_1Cmd(x);}while(0)//AD 配置参考电流

//开关屏幕			
#define SSD1315_Display_Off()																 do{OLED_send_1Cmd(0xAE);}while(0)									//AE 屏幕关,休眠(默认)
#define SSD1315_Display_On()																	do{OLED_send_1Cmd(0xAF);}while(0)						      //AF 屏幕开
//COM扫描方向			
#define SSD1315_Set_COM_Scan_Dir0() 													do{OLED_send_1Cmd(0xC0);}while(0)//C0 设置屏幕Y扫描方向,COM0到COMn-1(默认)
#define SSD1315_Set_COM_Scan_Dir1() 													do{OLED_send_1Cmd(0xC8);}while(0)//C8 设置屏幕Y扫描方向,COMn-1到COM0

//屏幕偏移显示
#define SSD1315_Set_Display_Offset(x) do{OLED_send_1Cmd(0xD3);OLED_send_1Cmd(x);}while(0)//D3 屏幕偏移显示[0:63]默认0



//分频和时钟
#define SSD1315_Set_Frequency(F_OSC,Divide_ratio)						do{OLED_send_1Cmd(0xD5);OLED_send_1Cmd((F_OSC<<4)|Divide_ratio);}while(0)			//D5 分频和时钟 F_OSC[0:15]默认8, Divide_ratio分频[0:15]默认0对应1分频 
//充放电
#define SSD1315_Set_Pre_charge_Period(Phase_1,Phase_2)	   do{OLED_send_1Cmd(0xD9);OLED_send_1Cmd((Phase_2<<4)|Phase_1);}while(0)			//D9 设置预充电(第一阶段时间,第二阶段时间), 默认(2,2)

//硬件连接方式(根据屏幕开发商走线配置)
//0x02,0x12,0x32,0x42
#define SSD1315_Set_COM_Pins_Hardware_Cfg(x)	   do{OLED_send_1Cmd(0xDA);OLED_send_1Cmd(x);}while(0)//DA 硬件连接方式(根据屏幕开发商走线配置) 0x02,0x12,0x32,0x42



//设定VCOM [0:63] 默认0x20
#define SSD1315_Set_VCOMH(x)																	do{OLED_send_1Cmd(0xDB);OLED_send_1Cmd(x);}while(0)//DB 0x00=0.65VCC 0x10=0.71VCC 0x20=0.77VCC(默认) 0x30=0.83VCC
#define SSD1315_NOP()                                  do{OLED_send_1Cmd(0xE3);}while(0)


//设定电荷泵
//0x14=7.5V(默认)
//0x94=8.5V
//0x95=9.0V
#define SSD1315_Charge_Pump_Setting(x)                                  do{OLED_send_1Cmd(0x8D);OLED_send_1Cmd(x);}while(0)//8D 设定电荷泵0x14=7.5V(默认) 0x94=8.5V 0x95=9.0V


//消影用?
#define Disable_Fade_Out_Blinking_mode 0
#define Enable_Fade_Out_mode 2
#define Enable_Blinking_mode 3
#define SSD1315_Set_Fade_Out_and_Blinking(mode,frames_set) do{OLED_send_1Cmd(0x23);OLED_send_1Cmd(mode<<4|frames_set);}while(0)//23 frames_set[0:15] 0对应8帧 1对应16帧 2对应24帧 15对应128帧

//放大模式
#define SSD1315_Set_Zoom_In(En) do{OLED_send_1Cmd(0xD6);OLED_send_1Cmd(En);}while(0)//D6 放大模式 0关闭 1使能



void SSD1315_Set_Address_x(unsigned char x);
void SSD1315_Set_Address_ypage(unsigned char page);
void SSD1315_Set_Address_x_ypage(unsigned char x,unsigned char page);
void SSD1315_Init(void);




	
	
#endif

