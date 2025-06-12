#ifndef __SH1106_H__
#define __SH1106_H__


#define SH1106_Set_Column_Address(x) do{OLED_send_1Cmd(x&0x0f);OLED_send_1Cmd(0x10|(x>>4));}while(0) //0x00~0x07 0x20~0x27 起始位置[0:255]默认0

#define SH1106_Set_Pump_voltage_value(x) do{OLED_send_1Cmd(0x30|x);}while(0) //30h~33h [0:2]默认2
#define SH1106_Set_Display_Start_Line(x) do{OLED_send_1Cmd(0x40|x);}while(0) //40h~4fh [0:63]默认0
#define SH1106_Set_Contrast(x) do{OLED_send_1Cmd(0x81);OLED_send_1Cmd(x);}while(0) //81h [0H:FFH]默认80H

#define SH1106_Set_Segment_Remap_right() do{OLED_send_1Cmd(0xA0);}while(0) //A0 映射方向右(默认)
#define SH1106_Set_Segment_Remap_left() do{OLED_send_1Cmd(0xA1);}while(0) //A1 映射方向左

#define SH1106_Set_Entire_Display_OFF() do{OLED_send_1Cmd(0xA4);}while(0) //A4 全亮测试关闭
#define SH1106_Set_Entire_Display_ON() do{OLED_send_1Cmd(0xA5);}while(0) //A5 全亮测试开启

#define SH1106_Set_Normal_Display() do{OLED_send_1Cmd(0xA6);}while(0) //A6 正常显示
#define SH1106_Set_Reverse_Display() do{OLED_send_1Cmd(0xA6);}while(0) //A7 反色显示


#define SH1106_Multiplex_Ration_Data_Set(x) do{OLED_send_1Cmd(0xA8);OLED_send_1Cmd(x);}while(0) //A8 [0H:3FH]默认3FH

#define SH1106_DCDC_OFF() do{OLED_send_1Cmd(0xAD);OLED_send_1Cmd(0x8A);}while(0) //AD 8A
#define SH1106_DCDC_ON() do{OLED_send_1Cmd(0xAD);OLED_send_1Cmd(0x8B);}while(0) //AD 8B(默认)

#define SH1106_Display_OFF() do{OLED_send_1Cmd(0xAE);}while(0) //AE(默认)
#define SH1106_Display_ON() do{OLED_send_1Cmd(0xAF);}while(0) //AF

#define SH1106_Set_Common_Output_Scan_Direction_0() do{OLED_send_1Cmd(0xC0);}while(0) //C0 com扫描方向0(默认)
#define SH1106_Set_Common_Output_Scan_Direction_1() do{OLED_send_1Cmd(0xC8);}while(0) //C8 com扫描方向1(默认)

#define SH1106_Set_Display_Offset(x) do{OLED_send_1Cmd(0xD3);OLED_send_1Cmd(0);}while(0) //D3 [0:63]默认0


#define SH1106_Set_Frequency(F_OSC,Divide_ratio)	do{OLED_send_1Cmd(0xD5);OLED_send_1Cmd((F_OSC<<4)|Divide_ratio);}while(0)	//D5 ([0:15],[0:15])设置内部晶振频率,设置时钟分频, 默认(5,0)

#define SH1106_Set_charge_Period(dis_charge,pre_charge)	do{OLED_send_1Cmd(0xD9);OLED_send_1Cmd((dis_charge<<4)|pre_charge);}while(0)//D9 设置预充电(第一阶段时间,第二阶段时间), 默认(2,2)

#define SH1106_Set_Common_Pads_Hardware_Configuration_Mode0() do{OLED_send_1Cmd(0xDA);OLED_send_1Cmd(0x02);}while(0)//da 02
#define SH1106_Set_Common_Pads_Hardware_Configuration_Mode1() do{OLED_send_1Cmd(0xDA);OLED_send_1Cmd(0x12);}while(0)//da 12

#define SH1106_Set_VCOM_Deselect_Level_Mode(x) do{OLED_send_1Cmd(0xDB);OLED_send_1Cmd(x);}while(0)//DB [0:255]默认0x35H

#define SH1106_Read_Modify_Write()	do{OLED_send_1Cmd(0xE0);}while(0)//E0
#define SH1106_End()	do{OLED_send_1Cmd(0xEE);}while(0)//EE
#define SH1106_NOP()	do{OLED_send_1Cmd(0xE3);}while(0)//E3




void SH1106_Set_Address_x(unsigned char x);
void SH1106_Set_Address_ypage(unsigned char page);
void SH1106_Set_Address_x_ypage(unsigned char x,unsigned char page);
void SH1106_Init(void);




	
	
#endif

