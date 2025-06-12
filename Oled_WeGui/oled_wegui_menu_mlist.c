#include "oled_wegui_menu_mlist.h"



mList_par_t mList_par;


void wegui_mList_Init()
{
	uint8_t max=0;
	if(oled_driver.fonts_ASCII != 0x00)
	{
		if(max<oled_driver.fonts_ASCII->high)
		{
			max = oled_driver.fonts_ASCII->high;
		}
	}
	if(oled_driver.fonts_UTF8_cut != 0x00)
	{
		if(max<oled_driver.fonts_UTF8_cut->high)
		{
			max = oled_driver.fonts_UTF8_cut->high;
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
void wegui_show_mList(uint16_t farmes)
{
	#define LINE0_START_X_SCAPE 3  //标题位置
	#define LINE1_START_X_SCAPE 10 //菜单位置
	int16_t temp_y=0;
	uint8_t* string;
	uint8_t id;//序号
	menu_t* p;

	
	//---------------------------------------1.菜单-------------------------------------------------
	
	//使用P(PID)的方式,使当前值接近目标值 
	//(cur_value:当前变量, target_value目标值, P:[0快:16慢], count:连续处理count次)
	//Value_Change_PID_P(cur_value,target_value,P,count)
	Value_Change_PID_P( mList_par.list_animation_temp_y,
	                    (SCREEN_HIGH-1+SCREEN_HIGH/8),
	                    3 ,
	                    farmes);
	
	
	
	Value_Change_PID_P( mList_par.list_y_offset_cur,
	                    mList_par.list_y_offset_target,
	                    2,
	                    farmes);
	
	uint8_t id_min=(mList_par.list_y_offset_cur + mList_par.list_y_scape-mList_par.list_font_high)/mList_par.list_y_scape;
	
	p = wegui.menu->subMenu;
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
		string=wegui_get_string(wegui.menu->titel,wegui.setting.langauge);
		OLED_Draw_UTF8_String(LINE0_START_X_SCAPE,temp_y,(uint8_t*)string);
		

		uint8_t str[6];
		itoa(SystemCoreClock/1000000,str,10);//数值转10进制字符串, 传递回给字符串指针			
		str[2]='M';str[3]='H';str[4]='z';str[5]='\0';
		OLED_Draw_UTF8_String	(SCREEN_WIDTH - 1 - OLED_Get_UTF8_XLen(str) - 2,
															temp_y,
															str);

		/*
		OLED_Draw_UTF8_String	(SCREEN_WIDTH - 1 - OLED_Get_UTF8_XLen((uint8_t*)"WeGui") - 2,
															temp_y,
															(uint8_t*)"WeGui");//LOGO
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
			OLED_Draw_Ascii(LINE1_START_X_SCAPE-oled_driver.fonts_ASCII->width-oled_driver.fonts_ASCII->scape - 4,temp_y,'-');
			string=wegui_get_string(p->discribe,wegui.setting.langauge);
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
							uint8_t str[5];
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
	
	p = wegui.menu->subMenu;
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
		string=wegui_get_string(wegui.menu->titel,wegui.setting.langauge);
	}
	//子菜单项光标位置
	else
	{	
		for(id=0;(id+1)<mList_par.cursor_id;id++){p=p->nextMenu;if(p==0x00){mList_par.cursor_id=id+1;break;}};
		curr_target_x0=LINE1_START_X_SCAPE;
		//curr_target_y0=mList_par.list_y_scape*mList_par.cursor_id - mList_par.list_y_offset_target;
		curr_target_y0=mList_par.list_y_scape*mList_par.cursor_id - mList_par.list_y_offset_cur;
		string=wegui_get_string(p->discribe,wegui.setting.langauge);
	}
	
	
	
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
											(farmes));
											
	Value_Change_PID_P( (mList_par.cursor_box_x1),
	                    (curr_target_x0+(OLED_Get_UTF8_XLen((uint8_t*)string))),
	                    (1),
	                    (farmes));
											
//	Value_Change_PID_P( mList_par.cursor_box_y1,
//	                    curr_target_y0+mList_par.list_font_high,
//	                    2,
//	                    farmes);
	
	OLED_Set_Driver_Mode(write_inverse);
	OLED_Fill_RBox( mList_par.cursor_box_x0-CURSOR_X_LOW_LEN,
	                mList_par.cursor_box_y0, 
	                mList_par.cursor_box_x1+CURSOR_X_HIGH_LEN, 
	                mList_par.cursor_box_y0+mList_par.list_font_high,//mList_par.cursor_box_y1,
	                CURSOR_R);//画方框, 输入x起点 Y起点, x终点, y终点, r倒圆角
									
	OLED_Set_Driver_Mode(write_1);
	
	
	//---------------------------------------3.滚动条-------------------------------------------------
	//#define close_scroll_time (2500/wegui.setting.ui_fps_ms)//静止隐藏滚动条,单位ui帧
	#define close_scroll_time (2500/16)//静止隐藏滚动条,单位ui帧
	
	if(wegui.menu->subMenu==0x00)
	{
		mList_par.scroll_bar_len = SCREEN_HIGH;
		//scroll_bar_pos=0;
	}
	uint8_t id_max=0;
	uint8_t scroll_bar_len_y0;
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
			p = wegui.menu->subMenu;
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




void wegui_mlist_keyUp(Key_return_t i)
{
	switch(i)
	{
		case start_short_press:       //开始短按
		case long_press_trig:				  //连续长按
		case long_long_press_trig:    //连续超长按
		{
			if(mList_par.cursor_id > 0)
			{
				//菜单光标减1
				mList_par.cursor_id--;
				//Send_Buzzer(BUZZER_1_SHORT);
			}
		}break;
		case start_long_press:        //开始长按
			break;
		case end_short_press:					//结束短按
			break;
		case end_long_press:					//结束长按
			break;
		case end_long_long_press:			//结束超长按
			break;
		default:break;
	}
}

void wegui_mlist_keyDown(Key_return_t i)
{
	switch(i)
	{
		case start_short_press:       //开始短按
		case long_press_trig:				  //连续长按
		case long_long_press_trig:    //连续超长按
		{
			//当前光标位置 < 子菜单总数量
			if(mList_par.cursor_id < Get_submenu_sum(wegui.menu))
			{
				//菜单光标加1
				mList_par.cursor_id++;
				//Send_Buzzer(BUZZER_1_SHORT);
			}
		}break;
		case start_long_press:        //开始长按
			break;
		case end_short_press:					//结束短按
			break;
		case end_long_press:					//结束长按
			break;
		case end_long_long_press:			//结束超长按
			break;
		default:break;
	}
}

void wegui_mlist_keyOk(Key_return_t i)
{
	switch(i)
	{
		case start_short_press:       //开始短按
		{
			menu_t *p;
			//--------------光标在标题处返回父菜单----------------
			if(mList_par.cursor_id==0)
			{
				//检测是否存在该父菜单
				p=wegui.menu->fatherMenu;
				if(p==0x00){mList_par.cursor_id=0;mList_par.list_y_offset_target=0;return;}//没有菜单
				//进入菜单
				wegui_enter_menu(p);
				//光标
				mList_par.cursor_id = wegui.menu->history_cursor_id;//光标历史记录
				mList_par.list_y_offset_target = wegui.menu->history_pos;//位置历史记录
			}
			//--------------光标在菜单处,进入菜单----------------
			else
			{
				uint8_t id;
				//检测是否存在子菜单
				p=wegui.menu->subMenu;
				if(p==0x00){return;}
				//检测是否存在光标所处的菜单
				for(id=0;(id+1)<mList_par.cursor_id;id++){p=p->nextMenu;if(p==0x00){return;}};
				switch(p->menuType)
				{
					case wMessage:
					case wSlider:
					{
						wegui_enter_menu(p);
					}break;
					case mList:
					case mPorgram:
					{
						wegui_enter_menu(p);
						if(wegui.menu->subMenu!=0x00){mList_par.cursor_id=1;}
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
		}break;
		case start_long_press:        //开始长按
			break;
		case end_short_press:					//结束短按
			break;
		case end_long_press:					//结束长按
			break;
		case end_long_long_press:			//结束超长按
			break;
		case long_press_trig:				  //连续长按
			break;
		case long_long_press_trig:    //连续超长按
			break;
		default:break;
	}
}



void wegui_mlist_keyBack(Key_return_t i)
{
	switch(i)
	{
		case start_short_press:       //开始短按
		{
			menu_t *p;
			//--------------返回父菜单----------------
			//检测是否存在该父菜单
			p=wegui.menu->fatherMenu;
			if(p==0x00)//没有父菜单
			{
				if(mList_par.cursor_id != 0)
				{
					mList_par.cursor_id=0;
				}
				else
				{
					mList_par.list_y_offset_target=0;
					//wegui_Push_Message_tip(0, (uint8_t*)"No menu!", 800);//(推送y位置,推送字符串,推送显示时间)
				}
				return;
			}
			//进入父菜单
			wegui_enter_menu(p);
			//光标
			mList_par.cursor_id = wegui.menu->history_cursor_id;//光标历史记录
			mList_par.list_y_offset_target = wegui.menu->history_pos;//位置历史记录
		}break;
		case start_long_press:        //开始长按
			break;
		case end_short_press:					//结束短按
			break;
		case end_long_press:					//结束长按
			break;
		case end_long_long_press:			//结束超长按
			break;
		case long_press_trig:				  //连续长按
			break;
		case long_long_press_trig:    //连续超长按
			break;
		default:break;
	}
}


void wegui_mlist_keyRight(Key_return_t i)
{
	switch(i)
	{
		case start_short_press:       //开始短按
		{
			menu_t *p;
			//--------------光标在标题处返回父菜单----------------
			if(mList_par.cursor_id==0)
			{
				//检测是否存在该父菜单
				p=wegui.menu->fatherMenu;
				if(p==0x00){mList_par.cursor_id=0;mList_par.list_y_offset_target=0;return;}//没有菜单
				//进入菜单
				wegui_enter_menu(p);
				//光标
				//if(wegui.menu->subMenu!=0x00){mList_par.cursor_id=1;}
				mList_par.cursor_id = wegui.menu->history_cursor_id;//光标历史记录
				mList_par.list_y_offset_target = wegui.menu->history_pos;//位置历史记录
			}
			//--------------光标在菜单处,进入菜单----------------
			else
			{
				uint8_t id;
				//检测是否存在子菜单
				p=wegui.menu->subMenu;
				if(p==0x00){return;}
				//检测是否存在光标所处的菜单
				for(id=0;(id+1)<mList_par.cursor_id;id++){p=p->nextMenu;if(p==0x00){return;}};
				switch(p->menuType)
				{
					case wMessage:
					case wSlider:
					{
						wegui_enter_menu(p);
					}break;
					case mList:
					case mPorgram:
					{
						wegui_enter_menu(p);
						if(wegui.menu->subMenu!=0x00){mList_par.cursor_id=1;}
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
		}break;
		case start_long_press:        //开始长按
			break;
		case end_short_press:					//结束短按
			break;
		case end_long_press:					//结束长按
			break;
		case end_long_long_press:			//结束超长按
			break;
		case long_press_trig:				  //连续长按
			break;
		case long_long_press_trig:    //连续超长按
			break;
		default:break;
	}
}

void wegui_mlist_keyLeft(Key_return_t i)
{
	switch(i)
	{
		case start_short_press:       //开始短按
		{
			menu_t *p;
			//--------------返回父菜单----------------
			//检测是否存在该父菜单
			p=wegui.menu->fatherMenu;
			if(p==0x00){mList_par.cursor_id=0;mList_par.list_y_offset_target=0;return;}//没有父菜单
			//进入父菜单
			wegui_enter_menu(p);
			//光标
			
			mList_par.cursor_id = wegui.menu->history_cursor_id;//光标历史记录
			mList_par.list_y_offset_target = wegui.menu->history_pos;//位置历史记录

		}break;
		case start_long_press:        //开始长按
			break;
		case end_short_press:					//结束短按
			break;
		case end_long_press:					//结束长按
			break;
		case end_long_long_press:			//结束超长按
			break;
		case long_press_trig:				  //连续长按
			break;
		case long_long_press_trig:    //连续超长按
			break;
		default:break;
	}
}

