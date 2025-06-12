#ifndef __SSD1327_H__
#define __SSD1327_H__

	
#define SSD1327_Set_Column_Address(start,end) do{OLED_send_1Cmd(0x15);OLED_send_1Cmd(start);OLED_send_1Cmd(end);}while(0)//15h start[0:127]默认0,end[0:127]默认127

#define SSD1327_Set_Row_Address(start,end) do{OLED_send_1Cmd(0x75);OLED_send_1Cmd(start);OLED_send_1Cmd(end);}while(0)//75h start[0:7F]默认0,end[0:7F]默认7F

#define SSD1327_Set_Contrast_Control(x) do{OLED_send_1Cmd(0x81);OLED_send_1Cmd(x);}while(0)//81h 设置对比度[0:255]默认127

#define SSD1327_Set_Remap(x) do{OLED_send_1Cmd(0xA0);OLED_send_1Cmd(x);}while(0)			//A0h 设置屏幕映射位置 默认0x00

#define SSD1327_Set_Display_Start_Line(x) do{OLED_send_1Cmd(0xA1);OLED_send_1Cmd(x);}while(0)			//A1h [0:127]默认0

#define SSD1327_Set_Display_Offset(x) do{OLED_send_1Cmd(0xA2);OLED_send_1Cmd(x);}while(0)			//A2h [0:127]默认0


#define SSD1327_Set_Display_Mode_A4() do{OLED_send_1Cmd(0xA4);}while(0)			//A4h Normal display (RESET)
#define SSD1327_Set_Display_Mode_A5() do{OLED_send_1Cmd(0xA5);}while(0)			//A5h All ON (All pixels have gray scale of 15, GS15)
#define SSD1327_Set_Display_Mode_A6() do{OLED_send_1Cmd(0xA6);}while(0)			//A6h All OFF (All pixels have gray scale of 0, GS0)
#define SSD1327_Set_Display_Mode_A7() do{OLED_send_1Cmd(0xA7);}while(0)			//A7h Inverse Display (GS0 -> GS15, GS1 -> GS14, GS2 -> GS13, ...)

#define SSD1327_Set_MUX_Ratio(x) do{OLED_send_1Cmd(0xA8);OLED_send_1Cmd(x);}while(0)	//A8h [15:127] 15=16MUX;127=128MUX(默认)


#define SSD1327_Func_A_Select_external_VDD() do{OLED_send_1Cmd(0xAB);OLED_send_1Cmd(0);}while(0)	//ABh 0x00
#define SSD1327_Func_A_Select_internal_VDD() do{OLED_send_1Cmd(0xAB);OLED_send_1Cmd(1);}while(0)	//ABh 0x01 默认

#define SSD1327_Display_OFF()	do{OLED_send_1Cmd(0xAE);}while(0)									//AEh 屏幕关,休眠(默认)
#define SSD1327_Display_ON()	do{OLED_send_1Cmd(0xAF);}while(0)						      //AFh 屏幕开

#define SSD1327_Set_Phase_Length(Phase_1,Phase_2) do{OLED_send_1Cmd(0xB1);OLED_send_1Cmd((Phase_2<<4)|Phase_1);}while(0)		//B1h 充放电周期(周期1[0:15],周期2[0:15]), 默认(7,8)

#define SSD1327_NOP1() do{OLED_send_1Cmd(0xB2);}while(0)		//B2h

#define Set_Front_Clock_Frequency(x) do{OLED_send_1Cmd(0xB3);OLED_send_1Cmd(x);}while(0)		//B3h [0x00:0xFF] 默认0x00 b7~b4设置晶振 b3~b0设置分频

#define GPIO_Hiz_input_dis()    do{OLED_send_1Cmd(0xB5);OLED_send_1Cmd(0x00);}while(0)//B5h 0x00
#define GPIO_Hiz_input_en()     do{OLED_send_1Cmd(0xB5);OLED_send_1Cmd(0x01);}while(0)//B5h 0x01 
#define GPIO_Hiz_output_Low()   do{OLED_send_1Cmd(0xB5);OLED_send_1Cmd(0x02);}while(0)//B5h 0x02 默认
#define GPIO_Hiz_output_High()  do{OLED_send_1Cmd(0xB5);OLED_send_1Cmd(0x03);}while(0)//B5h 0x03

#define Set_Gray_Scale_Table(y0,y1,y2,y3,y4,y5,y6,y7,y8,y9,y10,y11,y12,y13,y14,y15) do{OLED_send_1Cmd(0xB8);OLED_send_1Cmd(y0);OLED_send_1Cmd(y1);OLED_send_1Cmd(y2);OLED_send_1Cmd(y3);OLED_send_1Cmd(y4);OLED_send_1Cmd(y5);OLED_send_1Cmd(y6);OLED_send_1Cmd(y7);OLED_send_1Cmd(y8);OLED_send_1Cmd(y9);OLED_send_1Cmd(y10);OLED_send_1Cmd(y11);OLED_send_1Cmd(y12);OLED_send_1Cmd(y13);OLED_send_1Cmd(y14);OLED_send_1Cmd(y15);}while(0)//B8h 灰度设置

//B9
	
#define SSD1327_NOP2() do{OLED_send_1Cmd(0xBB);}while(0)		//BBh

#define SSD1327_Set_Pre_charge_voltage(x) do{OLED_send_1Cmd(0xBC);OLED_send_1Cmd(x);}while(0)		//BCh [0x00,0x0F] 默认0x05
	
#define SSD1327_Set_VCOMH(x) do{OLED_send_1Cmd(0xBE);OLED_send_1Cmd(x);}while(0)		//BEh [0x00,0x0F] 默认0x05


#define dis_2_precharge  0 //默认
#define en_2_precharge   1
#define Internal_VSL   0 //默认
#define external_VSL   1
#define SSD1327_Func_Selection_B(sec_pre,VSL) do{OLED_send_1Cmd(0xD5);OLED_send_1Cmd(0x60|(sec_pre<<1)|VSL);}while(0)		//D5h 默认(0x0,0x0)

#define SSD1327_Set_Command_Lock()   do{OLED_send_1Cmd(0xFD);OLED_send_1Cmd(0x12);}while(0)		//FDh 0x16
#define SSD1327_Set_Command_unLock() do{OLED_send_1Cmd(0xFD);OLED_send_1Cmd(0x12);}while(0)		//FDh 0x12 (默认)


	
#endif

