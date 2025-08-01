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

#include "lcd_wegui_menu_mlist.h"

mList_par_t mList_par;

void Wegui_mList_Init()
{
	uint8_t max=0;
	if(lcd_driver.fonts_ASCII != 0x00)
	{
		if(max<lcd_driver.fonts_ASCII->high)
		{
			max = lcd_driver.fonts_ASCII->high;
		}
	}
	if(lcd_driver.fonts_UTF8_cut != 0x00)
	{
		if(max<lcd_driver.fonts_UTF8_cut->high)
		{
			max = lcd_driver.fonts_UTF8_cut->high;
		}
	}
	if(max == 0){max=12;}
	
	mList_par.list_font_high = max;      //菜单文字高度
	mList_par.list_y_scape = max + max/2;    //菜单换行距离 //可自定义
	
	
	mList_par.list_y_offset_target = 0; //菜单下移位置目标值
	mList_par.list_y_offset_cur = 0;    //菜单下移位置当前值
	mList_par.list_animation_temp_y = 0;//动画运行变量
	                           
	mList_par.cursor_id=0;              //光标指向第几个列表id
	//mList_par.cursor_box_x0=5;          //光标矩形目标位置x
	mList_par.cursor_box_y0=0;          //光标矩形目标位置y
	//mList_par.cursor_box_x0=0;          //光标矩形目标位置x
	//mList_par.cursor_box_y0=0;          //光标矩形目标位置y
	
	mList_par.scroll_bar_len=SCREEN_HIGH;//滚动条长度
	mList_par.scrool_timer = 0;
	mList_par.scroll_y_offset_save = 0;
}
void Wegui_show_mList(uint16_t farmes)
{
	#define LINE0_START_X_SCAPE 3  //标题位置
	#define LINE1_START_X_SCAPE 10 //菜单位置
	int16_t temp_y=0;
	uint8_t* string;
	uint8_t id;//序号
	menu_t* p;

	
	
	//---------------------------------------1.菜单-------------------------------------------------
	
	if(farmes != 0)
	{
		//使用P(PID)的方式,使当前值接近目标值 
		//(cur_value:当前变量, target_value目标值, P:[0快:16慢], count:连续处理count次)
		//Value_Change_PID_P(cur_value,target_value,P,count)
		Value_Change_PID_P( mList_par.list_animation_temp_y,
												(SCREEN_HIGH-1+SCREEN_HIGH/8),
												(3),
		                    //(13 - SCREEN_HIGH/36+1),//控制菜单下拉速度[1最快:16最慢]
												farmes);
		
		
		
		Value_Change_PID_P( mList_par.list_y_offset_cur,
												mList_par.list_y_offset_target,
												2,
												farmes);
	}

	
	uint8_t id_min=(mList_par.list_y_offset_cur + mList_par.list_y_scape-mList_par.list_font_high)/mList_par.list_y_scape;
	
	p = Wegui.menu->subMenu;
	//-----显示首行标题-----
	if(id_min==0)
	{
		if(mList_par.list_animation_temp_y < (-mList_par.list_y_offset_cur))
		{
			temp_y = mList_par.list_animation_temp_y;
		}
		else
		{
			temp_y = (-mList_par.list_y_offset_cur);
		}
		string=Wegui_get_string(Wegui.menu->titel,Wegui.setting.langauge);
		OLED_Draw_UTF8_String(LINE0_START_X_SCAPE,temp_y,(uint8_t*)string);
		

		uint8_t str[6];
		itoa(SystemCoreClock/1000000,str,10);//数值转10进制字符串, 传递回给字符串指针			
		str[2]='M';str[3]='H';str[4]='z';str[5]='\0';
		OLED_Draw_UTF8_String	(SCREEN_WIDTH - 1 - OLED_Get_UTF8_XLen(str) - 2,
															temp_y,
															str);

		/*
		OLED_Draw_UTF8_String	(SCREEN_WIDTH - 1 - OLED_Get_UTF8_XLen((uint8_t*)"Wegui") - 2,
															temp_y,
															(uint8_t*)"Wegui");//LOGO
		*/
	}
	uint16_t temp_show_id_max = 1+(mList_par.list_y_offset_cur + 
	(mList_par.list_y_scape-mList_par.list_font_high) + SCREEN_HIGH)/mList_par.list_y_scape;
		
	//-----显示余下菜单-----
	if(p!=0x00)
	{
		for(id=0;(id+1)<id_min;id++){p=p->nextMenu;if(p==0x00){return ;}};
		while((p!=0x00)&&(temp_y<SCREEN_HIGH)&&(id<temp_show_id_max))
		{
			temp_y=mList_par.list_y_scape*(id+1)-mList_par.list_y_offset_cur;
			//temp_y+=list_y_scape;
			if(temp_y>mList_par.list_animation_temp_y)
				temp_y=mList_par.list_animation_temp_y;
			OLED_Draw_Ascii(LINE1_START_X_SCAPE-lcd_driver.fonts_ASCII->width-lcd_driver.fonts_ASCII->scape - 4,temp_y,'-');
			string=Wegui_get_string(p->discribe,Wegui.setting.langauge);
			OLED_Draw_UTF8_String(LINE1_START_X_SCAPE,temp_y,(uint8_t*)string);
			
			//---若菜单是带参数设置的, 末尾显示各自参数---
			switch (p->menuType)
			{
				case wMessage:
				{
					if(p->menuPar.wMessage_Par.Value_string != 0x00)
					{		
						OLED_Draw_UTF8_String	(SCREEN_WIDTH - 1 - OLED_Get_UTF8_XLen(p->menuPar.wMessage_Par.Value_string) -2,
														temp_y,
														p->menuPar.wMessage_Par.Value_string);
					}
				}break;
				case wSlider:
				{
						if(p->menuPar.wSliderTip_Par.pstr != 0x00)
						{
							uint8_t str[7];
							itoa(*p->menuPar.wSliderTip_Par.pstr,str,10);//数值转10进制字符串, 传递回给字符串指针			
							OLED_Draw_UTF8_String	(SCREEN_WIDTH - 1 - OLED_Get_UTF8_XLen(str) -2,
															temp_y,
															str);
						}
				}break;
				case wCheckBox:
				{
					
					OLED_Draw_RBox(SCREEN_WIDTH - 1 -1 +1 - mList_par.list_font_high -2 ,
																temp_y + 1 ,
																SCREEN_WIDTH - 1 -1 -2 ,
																temp_y + mList_par.list_font_high -1,
																2);
					if(p->menuPar.wCheckBox_Par.pstr != 0x00)
					{
						if(*p->menuPar.wCheckBox_Par.pstr != 0x00)
						{
							OLED_Fill_Box			(SCREEN_WIDTH - 1 -1 + 1 +2 - mList_par.list_font_high-2,
																temp_y +1 +2 ,
																SCREEN_WIDTH - 1 -1 -1 -2 - 1,
																temp_y + mList_par.list_font_high -1 -2);
						}
					}
					else//没有控制对象
					{
						OLED_Draw_Line(SCREEN_WIDTH - 1 -1 + 1 +2 - mList_par.list_font_high-2,
														temp_y +1 +2 ,
														SCREEN_WIDTH - 1 -1 -1 -2 - 1,
														temp_y + mList_par.list_font_high -1 -2);
						
						OLED_Draw_Line(SCREEN_WIDTH - 1 -1 -1 -2 - 1,
														temp_y +1 +2 ,
														SCREEN_WIDTH - 1 -1 + 1 +2 - mList_par.list_font_high-2,
														temp_y + mList_par.list_font_high -1 -2);
					}
				}break;
				default: break;
			}
			
			p=p->nextMenu;
			id++;
		}
	}

	//---------------------------------------2.光标-------------------------------------------------
	#define CURSOR_X_LOW_LEN 3 //光标矩形左方向延长
	#define CURSOR_X_HIGH_LEN 3 //光标矩形右方向延长
	#define CURSOR_R 4 //光标矩形圆角
	
	int16_t curr_target_x0;//光标左上角目标位置x
	int16_t curr_target_y0;//光标左上角目标位置y
	
	p = Wegui.menu->subMenu;
	if(p==0x00){mList_par.cursor_box_x0=0;mList_par.cursor_box_y0=0;mList_par.cursor_box_x1=0;mList_par.cursor_box_y1=0;return;}
	
	//调整菜单位置使得光标完全显示
	
	curr_target_y0 = (mList_par.list_y_scape)*mList_par.cursor_id-mList_par.list_y_offset_target;
	if(curr_target_y0<0)
		mList_par.list_y_offset_target = mList_par.list_y_offset_target + curr_target_y0;
	else if(curr_target_y0>SCREEN_HIGH-1-mList_par.list_font_high)
		mList_par.list_y_offset_target = mList_par.list_y_offset_target + curr_target_y0 - (SCREEN_HIGH-1 - mList_par.list_font_high);
	

	//标题光标位置
	if(mList_par.cursor_id==0)
	{
		curr_target_x0 = LINE0_START_X_SCAPE;
		curr_target_y0 = mList_par.list_y_offset_target;
		string=Wegui_get_string(Wegui.menu->titel,Wegui.setting.langauge);
	}
	//子菜单项光标位置
	else
	{	
		for(id=0;(id+1)<mList_par.cursor_id;id++){p=p->nextMenu;if(p==0x00){mList_par.cursor_id=id+1;break;}};
		curr_target_x0=LINE1_START_X_SCAPE;
		//curr_target_y0=mList_par.list_y_scape*mList_par.cursor_id - mList_par.list_y_offset_target;
		curr_target_y0=mList_par.list_y_scape*mList_par.cursor_id - mList_par.list_y_offset_cur;
		string=Wegui_get_string(p->discribe,Wegui.setting.langauge);
	}
	
	
	if(farmes != 0)
	{
		//----------------光标矩形两点移动----------------
		//使用P(PID)的方式,使当前值接近目标值 
		//(cur_value:当前变量, target_value目标值, P:[0快:16慢], count:连续处理count次)
		//Value_Change_PID_P(cur_value,target_value,P,count)
		Value_Change_PID_P( (mList_par.cursor_box_x0),
												(curr_target_x0),
												(3),
												(farmes));
	
												
		Value_Change_PID_P( mList_par.cursor_box_y0,
												(curr_target_y0),
												(2),
												//(SCREEN_HIGH/64+1),
												(farmes));
		if(mList_par.cursor_box_y0 > mList_par.list_animation_temp_y)//防止光标比菜单下滑还要快
		{
			mList_par.cursor_box_y0 = mList_par.list_animation_temp_y;
		}
												
		Value_Change_PID_P( (mList_par.cursor_box_x1),
												(curr_target_x0+(OLED_Get_UTF8_XLen((uint8_t*)string))),
												(1),
												(farmes));
												
//		Value_Change_PID_P( mList_par.cursor_box_y1,
//		                    curr_target_y0+mList_par.list_font_high,
//		                    2,
//		                    farmes);
	}
	
	OLED_Set_Driver_Mode(write_inverse);
	OLED_Fill_RBox( mList_par.cursor_box_x0-CURSOR_X_LOW_LEN,
	                mList_par.cursor_box_y0, 
	                mList_par.cursor_box_x1+CURSOR_X_HIGH_LEN, 
	                mList_par.cursor_box_y0+mList_par.list_font_high,//mList_par.cursor_box_y1,
	                CURSOR_R);//画方框, 输入x起点 Y起点, x终点, y终点, r倒圆角
									
	OLED_Set_Driver_Mode(write_1);
	
	
	//---------------------------------------3.滚动条-------------------------------------------------
	//#define close_scroll_time (2500/Wegui.setting.ui_fps_ms)//静止隐藏滚动条,单位ui帧
	#define close_scroll_time (2500/16)//静止隐藏滚动条,单位ui帧
	
	if(Wegui.menu->subMenu==0x00)
	{
		mList_par.scroll_bar_len = SCREEN_HIGH;
		//scroll_bar_pos=0;
	}
	uint8_t id_max=0;
	uint16_t scroll_bar_len_y0;
	uint32_t temp;//菜单下拉总行程
	
	
	if(mList_par.scroll_y_offset_save != mList_par.list_y_offset_cur)//界面移动激活显示滚动条
	{
		mList_par.scroll_y_offset_save = mList_par.list_y_offset_cur;
		
		if(mList_par.scrool_timer < (close_scroll_time+2))
		{
			mList_par.scrool_timer=2;
		}
		else
		{
			mList_par.scrool_timer=0;
		}
	}
	
		
		uint16_t width = 0;
		if(mList_par.scrool_timer <= (close_scroll_time+5))//自动隐藏滚动条
		{
			mList_par.scrool_timer+=farmes;
			if(mList_par.scrool_timer < 2)
			{
				width = 1;
			}
			else if(mList_par.scrool_timer <= (close_scroll_time))
			{
				width = 2;
			}
			else if(mList_par.scrool_timer <= (close_scroll_time+2))
			{
				width = 3;
			}
			else if(mList_par.scrool_timer <= (close_scroll_time+4))
			{
				width = 2;
			}
			else if(mList_par.scrool_timer <= (close_scroll_time+6))
			{
				width = 1;
			}
			else
			{
				width = 0;
			}
		}
		
		
		if(width>0)
		{
			p = Wegui.menu->subMenu;
			for(id_max=0;p!=0x00;id_max++){p=p->nextMenu;}
			temp=((id_max)*mList_par.list_y_scape+mList_par.list_font_high+1);//菜单下拉总行程
			if(temp < SCREEN_HIGH)
			{
				//无需滚动条
			}
			else if(temp > SCREEN_HIGH)
			{
				temp -= SCREEN_HIGH;
				
				mList_par.scroll_bar_len = SCREEN_HIGH - ((id_max+1)- SCREEN_HIGH / mList_par.list_y_scape)*SCREEN_HIGH/id_max;
				if(mList_par.scroll_bar_len < 10){mList_par.scroll_bar_len = 10;}
				scroll_bar_len_y0 = SCREEN_HIGH - mList_par.scroll_bar_len - ((uint32_t)SCREEN_HIGH-mList_par.scroll_bar_len)*(temp - mList_par.list_y_offset_cur)/temp;
				OLED_Fill_Box( SCREEN_WIDTH-width,
									scroll_bar_len_y0,
									SCREEN_WIDTH,
									scroll_bar_len_y0+mList_par.scroll_bar_len);
			}
			
		}
}



//光标前一个
void Wegui_mlist_cursor_Prev()
{
	if(mList_par.cursor_id > 0)
	{
		//菜单光标减1
		mList_par.cursor_id--;
		//Send_Buzzer(BUZZER_1_SHORT);
	}
}
//光标下一个
void Wegui_mlist_cursor_Next()
{
		//当前光标位置 < 子菜单总数量
	if(mList_par.cursor_id < Get_submenu_sum(Wegui.menu))
	{
		//菜单光标加1
		mList_par.cursor_id++;
		//Send_Buzzer(BUZZER_1_SHORT);
	}
}

//进入光标位置菜单
void Wegui_mlist_Enter_cursor()
{
	menu_t *p;
	//--------------光标在标题处返回父菜单----------------
	if(mList_par.cursor_id==0)
	{
		//检测是否存在该父菜单
		p=Wegui.menu->fatherMenu;
		if(p==0x00){mList_par.cursor_id=0;mList_par.list_y_offset_target=0;return;}//没有菜单
		//进入菜单
		Wegui_enter_menu(p);
		//光标
		//if(Wegui.menu->subMenu!=0x00){mList_par.cursor_id=1;}
		mList_par.cursor_id = Wegui.menu->history_cursor_id;//光标历史记录
		mList_par.list_y_offset_target = Wegui.menu->history_pos;//位置历史记录
	}
	//--------------光标在菜单处,进入菜单----------------
	else
	{
		uint8_t id;
		//检测是否存在子菜单
		p=Wegui.menu->subMenu;
		if(p==0x00){return;}
		//检测是否存在光标所处的菜单
		for(id=0;(id+1)<mList_par.cursor_id;id++){p=p->nextMenu;if(p==0x00){return;}};
		switch(p->menuType)
		{
			case wMessage:
			case wSlider:
			{
				Wegui_enter_menu(p);
			}break;
			case mList:
			{
				Wegui_enter_menu(p);
				if(Wegui.menu->subMenu!=0x00){mList_par.cursor_id=1;}
			}break;
			case mPorgram:
			{
				Wegui_enter_menu(p);
			}break;
			case wCheckBox:
			{
				if(p->menuPar.wCheckBox_Par.pstr!=0x00)
				{
					if(*p->menuPar.wCheckBox_Par.pstr==0x00)
					{
						*p->menuPar.wCheckBox_Par.pstr = 1;
					}
					else
					{
						*p->menuPar.wCheckBox_Par.pstr = 0;
					}
					if(p->menuPar.wCheckBox_Par.Change_Value != 0x00)
					{
						p->menuPar.wCheckBox_Par.Change_Value();
					}
				}
			}
			default:break;
		}
	}
}

//返回上一级菜单
void Wegui_mlist_Back_menu()
{
	menu_t *p;
	//--------------返回父菜单----------------
	//检测是否存在该父菜单
	p=Wegui.menu->fatherMenu;
	if(p==0x00){mList_par.cursor_id=0;mList_par.list_y_offset_target=0;return;}//没有父菜单
	//进入父菜单
	Wegui_enter_menu(p);
	//光标
	
	mList_par.cursor_id = Wegui.menu->history_cursor_id;//光标历史记录
	mList_par.list_y_offset_target = Wegui.menu->history_pos;//位置历史记录
}
