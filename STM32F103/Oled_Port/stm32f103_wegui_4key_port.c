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

#include "lcd_wegui_Config.h"

#if defined(WEGUI_USE_4KEY_PORT)

#include "stm32f103_wegui_4key_port.h"
#include "user_wegui_menu.h"
#include "lcd_wegui_menu_mlist.h"
#include "lcd_wegui_tip.h"


//-------------------------------------按键结构体-------------------------------------
typedef enum Key_return//返回值
{
	key_return_none = 0 ,
	start_short_press,           //开始短按
	start_long_press,            //开始长按
	start_long_long_press,       //开始超长按
	long_press_trig,             //连续长按(机关枪)
	long_long_press_trig,        //连续超长按(机关枪)
	end_short_press,             //短按结束
	end_long_press,              //长按结束
	end_long_long_press,         //超长按结束
	
}Key_return_t;

typedef enum Key_state//按键状态
{
	key_state_none = 0,
	short_press_and_hold,         //短按中
	long_press_and_hold,          //长按中
	long_long_press_and_hold,     //超长按中
}Key_state_t;

typedef struct mykey//变量结构体
{
	Key_state_t keysw_state;
	uint16_t keysw_det_count;//时间计数值1
	uint16_t keysw_det_count2;//时间计数值2
}mykey_t;


mykey_t key_left;
mykey_t key_right;
mykey_t key_up;
mykey_t key_down;


//----------------------------短按长按超长按+连续长按超长按------------------------------------
#define key_delay_count 10          //按下消抖次数
#define key_long_count 500          //"短按"到"长按"的计数时间
#define key_long_trig_count 80     //"连续长按"的机关枪间隔触发时间

#define key_long_long_count 2000    //"长按"到"超长按"的计数时间
#define key_long_long_trig_count 12 //"连续超长按"的机关枪间隔触发时间

Key_return_t Keysw_det(mykey_t *p,uint8_t pin_state,uint16_t ms_stick)
{
	if(pin_state)
	{
		p->keysw_det_count += ms_stick;
		switch(p->keysw_state)
		{
			case key_state_none:{p->keysw_det_count2=0;if(p->keysw_det_count>=key_delay_count){p->keysw_state=short_press_and_hold;p->keysw_det_count=0;return start_short_press;}}break;
			case short_press_and_hold:{p->keysw_det_count2=0;if(p->keysw_det_count>=key_long_count){p->keysw_state=long_press_and_hold;p->keysw_det_count=0;return start_long_press;};}break;
			case long_press_and_hold:{p->keysw_det_count2+=ms_stick;if((p->keysw_det_count>=key_long_long_count)){p->keysw_state=long_long_press_and_hold;p->keysw_det_count=0;return start_long_long_press;}if(p->keysw_det_count2>=key_long_trig_count){p->keysw_det_count2-=key_long_trig_count;return long_press_trig;}}break;
			case long_long_press_and_hold:{if(p->keysw_det_count>=key_long_long_trig_count){p->keysw_det_count=0;return long_long_press_trig;}}break;
		}
	}
	else
	{
		p->keysw_det_count2=0;
		switch(p->keysw_state)
		{	
			case key_state_none:{p->keysw_det_count=0;}break;
			case short_press_and_hold:{p->keysw_det_count=0;p->keysw_state=key_state_none;return end_short_press;}//break;
			case long_press_and_hold:{p->keysw_det_count=0;p->keysw_state=key_state_none;return end_long_press;}//break;
			case long_long_press_and_hold:{p->keysw_det_count=0;p->keysw_state=key_state_none;return end_long_press;}//break;
		}
	}
	return key_return_none;
}

void Key_par_Init(mykey_t *p)
{
	p->keysw_state = key_state_none;
	p->keysw_det_count = 0;
	p->keysw_det_count2 = 0;
}


void Wegui_4key_port_Init()//4按键接口初始化
{
	Wegui_KeyLeft_IO_Init();
	Wegui_KeyUp_IO_Init();
	Wegui_KeyDown_IO_Init();
	Wegui_KeyRight_IO_Init();
	
	Key_par_Init(&key_left);
	Key_par_Init(&key_right);
	Key_par_Init(&key_up);
	Key_par_Init(&key_down);
}



static void Wegui_Key_Up(uint16_t ms_stick)
{
	Key_return_t i = Keysw_det(&key_up ,Bool_WKeyUp_is_Pressed(),ms_stick);
	switch (Wegui.tip.state)
	{
		case FREE:break;//弹窗已退出
		case EXITING:break;//弹窗已退出
		case ENTERING:
		case DISPLAYING:
		{
				switch (Wegui.tip.type)
				{
					case message:
					{
						switch(i)
						{
							case start_short_press:       //开始短按
								Wegui_Tip_Quit();
								break;
							default:break;
						}
					}
					case slider:
					{
						switch(i)
						{
							case start_short_press:       //开始短按
								Wegui_Tip_Save_andQuit();
								break;
							default:break;
						}
					}break;
				}
				return;//优先处理弹窗,不处理菜单
		}
	}
	switch(Wegui.menu->menuType)
	{
		case mList:     //列表菜单
		{
			switch(i)
			{
				case start_short_press:       //开始短按
				case start_long_press:        //开始长按
				case long_press_trig:				  //连续长按
				case long_long_press_trig:    //连续超长按
					Wegui_mlist_cursor_Prev();
					break;
				default:break;
			}
		}break;
		case mPorgram:  //自定义功能APP
			if(Wegui.menu == &m_App_UartScreen)
			{
				switch(i)
				{
					case start_short_press:       //开始短按
						Wegui_mlist_Back_menu();;
						break;
					default:break;
				}
			}break;
		case wCheckBox: //控件:复选框
			break;
		case wSlider:   //控件:滑条
			break;
		case wMessage:
			break;
	}
}





static void Wegui_Key_Down(uint16_t ms_stick)
{
	Key_return_t i = Keysw_det(&key_down ,Bool_WKeyDown_is_Pressed(),ms_stick);
	switch (Wegui.tip.state)
	{
		case FREE:break;//弹窗已退出
		case EXITING:break;//弹窗已退出
		case ENTERING:
		case DISPLAYING:
		{
				switch (Wegui.tip.type)
				{
					case message:
					{
						switch(i)
						{
							case start_short_press:       //开始短按
								Wegui_Tip_Quit();
								break;
							default:break;
						}
					}
					case slider:break;
				}
		}
		return;//优先处理弹窗,不处理菜单
	}
	switch(Wegui.menu->menuType)
	{
		case mList:     //列表菜单
		{
			switch(i)
			{
				case start_short_press:       //开始短按
				case start_long_press:        //开始长按
				case long_press_trig:				  //连续长按
				case long_long_press_trig:    //连续超长按
					Wegui_mlist_cursor_Next();
					break;
				default:break;
			}
		}break;
		case mPorgram:  //自定义功能APP
			if(Wegui.menu == &m_App_UartScreen)
			{
				switch(i)
				{
					case start_short_press:       //开始短按
						Wegui_mlist_Back_menu();;
						break;
					default:break;
				}
			}break;
		case wCheckBox: //控件:复选框
			break;
		case wSlider:   //控件:滑条
			break;
		case wMessage:
			break;
	}
}







static void Wegui_Key_Left(uint16_t ms_stick)
{
	Key_return_t i = Keysw_det(&key_left ,Bool_WkeyLeft_is_Pressed(),ms_stick);
	switch (Wegui.tip.state)
	{
		case FREE:break;//弹窗已退出
		case EXITING:break;//弹窗已退出
		case ENTERING:
		case DISPLAYING:
		{
				switch (Wegui.tip.type)
				{
					case message:
					{
						switch(i)
						{
							case start_short_press:       //开始短按
								Wegui_Tip_Quit();
								break;
							default:break;
						}
					}
					case slider:
					{
						switch(i)
						{
							case start_short_press:       //开始短按
							case start_long_press:        //开始长按
							case long_press_trig:				  //连续长按
							case long_long_press_trig:    //连续超长按
								Wegui_Tip_Value_Dec();
								break;
							default:break;
						}
					}break;
				}
			return;//优先处理弹窗,不处理菜单
		}
	}
	switch(Wegui.menu->menuType)
	{
		case mList:     //列表菜单
		{
			switch(i)
			{
				case start_short_press:       //开始短按
					Wegui_mlist_Back_menu();
					break;
				default:break;
			}
		}break;
		case mPorgram:  //自定义功能APP
			if(Wegui.menu == &m_App_UartScreen)
			{
				switch(i)
				{
					case start_short_press:       //开始短按
						Wegui_mlist_Back_menu();;
						break;
					default:break;
				}
			}break;
		case wCheckBox: //控件:复选框
			break;
		case wSlider:   //控件:滑条
			break;
		case wMessage:
			break;
	}
}







static void Wegui_Key_Right(uint16_t ms_stick)
{
	Key_return_t i = Keysw_det(&key_right ,Bool_WkeyRight_is_Pressed(),ms_stick);
	//-----------------------优先处理弹窗---------------------
	switch (Wegui.tip.state)
	{
		case FREE:break;//弹窗已退出
		case EXITING:break;//弹窗已退出
		case ENTERING:
		case DISPLAYING:
		{
				switch (Wegui.tip.type)
				{
					case message:
					{
						switch(i)
						{
							case start_short_press:       //开始短按
								Wegui_Tip_Quit();
								break;
							default:break;
						}
					}
					case slider:
					{
						switch(i)
						{
							case start_short_press:       //开始短按
							case start_long_press:        //开始长按
							case long_press_trig:				  //连续长按
							case long_long_press_trig:    //连续超长按
								Wegui_Tip_Value_Add();
								break;
							default:break;
						}
					}break;
				}
			return;//优先处理弹窗,不处理菜单
		}
	}
	
	
	//-----------------------再处理菜单---------------------
	switch(Wegui.menu->menuType)
	{
		case mList:     //列表菜单
		{
			switch(i)
			{
				case start_short_press:       //开始短按
					Wegui_mlist_Enter_cursor();
					break;
				default:break;
			}
		}break;
		case mPorgram:  //自定义功能APP
			if(Wegui.menu == &m_App_UartScreen)
			{
				switch(i)
				{
					case start_short_press:       //开始短按
						Wegui_mlist_Back_menu();;
						break;
					default:break;
				}
			}break;
		case wCheckBox: //控件:复选框
			break;
		case wSlider:   //控件:滑条
			break;
		case wMessage:
			break;
	}
}


void Wegui_Interface_stick(uint16_t ms)
{
	if(ms)
	{
		Wegui_Key_Up(ms)   ;
		Wegui_Key_Down(ms) ;
		Wegui_Key_Left(ms) ;
		Wegui_Key_Right(ms);
	}
}




#endif
