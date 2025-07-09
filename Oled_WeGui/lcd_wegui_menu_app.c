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
#include "lcd_wegui_menu_app.h"

#include "lcd_wegui_driver.h"
#include "user_wegui_menu.h"



//------------------------------------------串口显示器功能菜单--------------------------------------------
const Wegui_string_t welcom =
{
 .str_zh_CN=(uint8_t*)"等待上位机操作..",
 .str_en_US=(uint8_t*)"Wait data...",
};
void Uart_Screen_App_Begin()//进入APP执行一次
{
	OLED_Clear_GRAM();
	OLED_Draw_UTF8_String(0,0,(uint8_t*)Wegui_get_string(welcom,Wegui.setting.langauge));
}
void Uart_Screen_App_Loop()//主循环执行
{
	
}
void Uart_Screen_App_Quit()//退出菜单执行一次
{
	
}

void Uart_Screen_Refresh()//刷新屏幕时执行,放绘图函数
{

}




//------------------------------------------控件演示Demo--------------------------------------------
extern uint16_t ResADC;
void m_wDemo_wMessage_ADC_func()//菜单实时更新ADC值
{
	static uint8_t string[7];
	
	itoa(ResADC,string,10);
	m_wDemo_wMessage_ADC.menuPar.wMessage_Par.Value_string = string;
}
void m_wDemo_wMessage_Pres_func()//菜单按下弹窗
{
	static uint8_t string[7];
	
	itoa(ResADC,string,10);
	m_wDemo_wMessage_Pres.menuPar.wMessage_Par.Value_string = string;
}
void m_wDemo_wMessage_Pres2_func()//菜单按下更换文字
{
	static uint8_t num=0;
	Wegui_string_t i[]=
	{
		{
			.str_zh_CN=(uint8_t*)"CA",
			.str_en_US=(uint8_t*)"EA",
		},
		{
			.str_zh_CN=(uint8_t*)"CB",
			.str_en_US=(uint8_t*)"EB",
		},
		{
			.str_zh_CN=(uint8_t*)"CC",
			.str_en_US=(uint8_t*)"EC",
		},
		{
			.str_zh_CN=(uint8_t*)"CD",
			.str_en_US=(uint8_t*)"ED",
		},
	};
	
	
	if(num < (sizeof(i)/sizeof(Wegui_string_t)-1))
	{
		num++;
	}
	else
	{
		num=0;
	}
	
	m_wDemo_wMessage_Pres2.menuPar.wMessage_Par.Value_string = Wegui_get_string(i[num],Wegui.setting.langauge);;
}


//------------------------------------------设置亮度言--------------------------------------------
void update_Wegui_screen_brightness()
{
	LCD_Set_Bright(Wegui.setting.brightness);
}


//------------------------------------------设置语言--------------------------------------------
void Set_langauge_Chinese()
{
	Wegui.setting.langauge=zh_CN;
}
void Set_langauge_English()
{
	Wegui.setting.langauge=en_US;
}

