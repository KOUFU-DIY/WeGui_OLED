#ifndef __SH1115_H__
#define __SH1115_H__



#define SH1115_Set_Lower_Column_Address(x)  do{OLED_send_1Cmd(x);}while(0)//[0:15]默认0
#define SH1115_Set_Higher_Column_Address(x) do{OLED_send_1Cmd(0x10|x);}while(0)//[0:7]默认0

#define SH1115_Set_Breathing_Display_Effect(en,br) do{OLED_send_1Cmd(0x23);OLED_send_1Cmd((en<<7)|br);}while(0)//23h 灰度呼吸设置 en:[0:1]默认0 br:[0:32]默认0

#define SH1115_Additional_Horizontal_Scroll_Setup_Mode_Set(Start_Column,End_Column) do{OLED_send_1Cmd(0x24);OLED_send_1Cmd(Start_Column);OLED_send_1Cmd(End_Column);}while(0)//24h 垂直滚动设置 Start_Column:[0:127]默认0 End_Column:[0:127]默认0


#define SH1115_Horizontal_Scroll_Setup_Mode_Set(en,Start_Page,Time,End_Page) do{OLED_send_1Cmd(0x26|en);OLED_send_1Cmd(Start_Page);OLED_send_1Cmd(Time);OLED_send_1Cmd(End_Page);}while(0)//26h/27h 垂直滚动设置 Start_Page:[0:7]默认0 End_Page:[0:7]默认0

#define Continuous_horizontalo_or_vertical_scroll 0//(default)
#define Single_Screen_scroll 1
#define Column_scroll_mode 2
#define SH1115_Set_Scroll_Mode(mode) do{OLED_send_1Cmd(0x28|mode);}while(0)//28h 


#define SH1115_Set_Deactivate_Horizontal_Scroll() do{OLED_send_1Cmd(0x2E);}while(0)//2E 默认
#define SH1115_Set_Activate_Horizontal_Scroll() do{OLED_send_1Cmd(0x2F);}while(0)//2F

#define SH1115_Set_Pump_voltage_value(x) do{OLED_send_1Cmd(0x30|x);}while(0)//30h 设置电源电荷泵 [0:3]默认2

#define SH1115_Set_Display_Start_Line(x) do{OLED_send_1Cmd(0x40|x);}while(0)//40h~7Fh 显示起始位置 [0:15]默认0


#define SH1115_The_Contrast_Control_Mode_Set(x) do{OLED_send_1Cmd(0x81);OLED_send_1Cmd(x);}while(0)//81h 对比度 [0:255]默认127

#define SH1115_IREF_Resistor_Set_and_Adjust_ISEG_by_PAD(x)	do{OLED_send_1Cmd(0x82);OLED_send_1Cmd(x);}while(0)//82h 配置参考电流 默认0x00 详情看手册

#define SH1115_Set_Segment_Remap_dir0() do{OLED_send_1Cmd(0xA0);}while(0)//A0h 设置映射配置0 默认
#define SH1115_Set_Segment_Remap_dir1() do{OLED_send_1Cmd(0xA1);}while(0)//A1h 设置映射配置1

#define SH1115_Set_SEG_pads_hardware_configuration_0() do{OLED_send_1Cmd(0xA2);}while(0)//A2h 设置点阵排布顺序0 默认
#define SH1115_Set_SEG_pads_hardware_configuration_1() do{OLED_send_1Cmd(0xA3);}while(0)//A3h 设置点阵排布顺序1

#define SH1115_Entire_Display_Off() 										do{OLED_send_1Cmd(0xA4);}while(0)			//A4全亮测试关(默认)
#define SH1115_Entire_Display_On() 											do{OLED_send_1Cmd(0xA5);}while(0)		  //A5全亮测试开
		                                                  
#define SH1115_Set_Reverse_Display_Off() 								do{OLED_send_1Cmd(0xA6);}while(0)		//A6正常显示 默认
#define SH1115_Set_Reverse_Display_On() 								do{OLED_send_1Cmd(0xA7);}while(0)		//A7反色显示

#define SH1115_Set_Multiplex_Ration(x) do{OLED_send_1Cmd(0xA8);OLED_send_1Cmd(x);}while(0)//A8 设置频率[0:63]默认63

#define SH1115_Set_DCDC_OFF() do{OLED_send_1Cmd(0xAD);OLED_send_1Cmd(0x8A);}while(0)		//ADh 8Ah 关闭DC升压
#define SH1115_Set_DCDC_ON() do{OLED_send_1Cmd(0xAD);OLED_send_1Cmd(0x8B);}while(0)		//ADh 8Bh 打开DC升压 默认


#define SH1115_Display_OFF()  do{OLED_send_1Cmd(0xAE);OLED_send_1Cmd(0x8B);}while(0)		//AEh 关闭显示 默认
#define SH1115_Display_ON() do{OLED_send_1Cmd(0xAF);OLED_send_1Cmd(0x8B);}while(0)		//AFh 打开显示

#define SH1115_Set_Common_Output_Scan_Dir0() do{OLED_send_1Cmd(0xC0);}while(0)		//C0h COM输出扫描方向0 默认
#define SH1115_Set_Common_Output_Scan_Dir1() do{OLED_send_1Cmd(0xC8);}while(0)		//C8h COM输出扫描方向1


#define SH1115_Set_Display_Offset(x) do{OLED_send_1Cmd(0xD3);OLED_send_1Cmd(x);}while(0)		//D3h y显示偏移 [0:63]默认0

#define SH1115_Set_Display_Clock_Divide_Ratio_Oscillator_Frequency(osc_ofset,osc_div) do{OLED_send_1Cmd(0xD5);OLED_send_1Cmd((osc_ofset<<4)|osc_div);}while(0)//D5h osc_ofset晶振偏移[0:15]0对应-17.1% 5对应0%(默认) 15对应+25.1%    dir分频0=8分(默认) 1=16分 2=3分 3=4分 

#define SH1115_Set_Adaptive_Power_Save_ON() do{OLED_send_1Cmd(0xD6);}while(0)		//D7h省电模式开(默认)
#define SH1115_Set_Adaptive_Power_Save_OFF() do{OLED_send_1Cmd(0xD7);}while(0)	//D6h省电模式关


#define SH1115_Set_Discharge_Pre_charge_Period(Discharge,charge) do{OLED_send_1Cmd(0xD9);OLED_send_1Cmd((Discharge<<4)|charge);}while(0)	//D9h 放电[0:15]默认2 充电[0:15]默认2

#define SH1115_VCOM_Deselect_Level_Mode_Set(x) do{OLED_send_1Cmd(0xDB);OLED_send_1Cmd(x);}while(0)	//DBh 设置VCOM [0h:FFh]默认35h


#define SH1115_Set_row_non_overlap_SEG_Hiz_Period(x) do{OLED_send_1Cmd(0xDC);OLED_send_1Cmd(x);}while(0)	//DCh 驱动消影?[0h:FFh]默认0x01

#define SH1115_NOP() do{OLED_send_1Cmd(0xE3);}while(0)	//E3h NOP



void SH1115_Set_Address_x(unsigned char x);
void SH1115_Set_Address_ypage(unsigned char page);
void SH1115_Set_Address_x_ypage(unsigned char x,unsigned char page);
void SH1115_Init(void);




	
	
#endif

