#include "oled_wegui_tip.h"





/*--------------------------------------------------------------
  * 名称: wegui_Push_Message_tip(int16_t y, uint8_t* string, uint16_t time)
  * 传入1: y显示y位置
  * 传入2: string推送的字符串
  * 传入3: time推送显示时间
  * 功能: 向wegui屏幕推送一条消息
----------------------------------------------------------------*/
void wegui_Push_Message_tip(int16_t y, uint8_t* string, uint16_t time)//(推送y位置,推送字符串,推送显示时间)
{
	uint16_t string_xlen;
	uint16_t string_yline;
	if(string[0] != 0x00)
	{
		wegui.tip.fonts_high = 16;
		//--文字高度--
		switch(wegui.setting.langauge)
		{
			case zh_CN://中文
				if(oled_driver.fonts_UTF8_cut != 0x00)
				{
					wegui.tip.fonts_high = oled_driver.fonts_UTF8_cut->high;
					break;
				}
			case en_US://英语
			default:
				if(oled_driver.fonts_ASCII != 0x00)
				{
					wegui.tip.fonts_high = oled_driver.fonts_ASCII->high;
				}
				break;
		}
		string_xlen = OLED_Get_UTF8_XLen(string);
		string_yline = OLED_Get_UTF8_YLine(wegui.tip.string);//字符串分了多少行
		
		wegui.tip.state = ENTERING;
		wegui.tip.type=message;
		wegui.tip.pos_y = y;																							//动画目标位置y
		wegui.tip.pos_x = -(int16_t)string_xlen/2 - TIP_LR_Scape + ((SCREEN_WIDTH/2)-1);	//动画目标位置x
		
		//初始位置隐藏在上方
		//wegui.tip.cur_y = SCREEN_HIGH -(-TIP_TB_Scape-TIP_TB_Scape - wegui.tip.fonts_high);	//开始位置Y
		wegui.tip.cur_y = (-TIP_TB_Scape-TIP_TB_Scape - wegui.tip.fonts_high*string_yline);	//开始位置Y
		wegui.tip.cur_x = wegui.tip.pos_x;												            //开始位置x
		
		wegui.tip.time	=	time;//推送显示时间ms
		wegui.tip.string = string;//推送字符内容
	}
}




/*--------------------------------------------------------------
  * 名称: wegui_Push_Slider_tip(int16_t y, uint8_t* string, int16_t *p_value,int16_t value_min ,uint16_t value_max,value_change_t change_way,void(*Change_func)(),void(*Finish_func)())
  * 传入1: y:推送显示y位置
  * 传入2: string推送的字符串
  * 传入3: *p_value 待修改的数据指针
  * 传入4: value_min 待修改的数据的最小值
  * 传入5: value_max 待修改的数据的最大值
  * 传入6: change_way 改值方式
  * 传入7: *Change_func 滑条数据改变执行一次的函数指针
  * 传入8: *Finish_func 滑条数据确认后执行一次的函数指针
  * 功能: 向wegui屏幕推送一条滑条控制窗
----------------------------------------------------------------*/
void wegui_Push_Slider_tip(int16_t y, uint8_t* string, int16_t *p_value,int16_t value_min ,uint16_t value_max,value_change_t change_way,void(*Change_func)(),void(*Finish_func)())
{
	uint16_t string_yline = OLED_Get_UTF8_YLine(wegui.tip.string);//字符串分了多少行
	//--更新文字高度--
	switch(wegui.setting.langauge)
	{
		case zh_CN://中文
			if(oled_driver.fonts_UTF8_cut != 0x00)
			{
				wegui.tip.fonts_high = oled_driver.fonts_UTF8_cut->high;
				break;
			}
		case en_US://英语
		default:
			if(oled_driver.fonts_ASCII != 0x00)
			{
				wegui.tip.fonts_high = oled_driver.fonts_ASCII->high;
			}
			break;
	}
	
	wegui.tip.state = ENTERING;
	wegui.tip.type = slider;
	wegui.tip.pos_x = (SCREEN_WIDTH - BAR_TIP_WIDTH)/2;//弹窗目标位置x(默认居中)
	wegui.tip.pos_y = y;//弹窗目标位置y
	wegui.tip.cur_x = (SCREEN_WIDTH - BAR_TIP_WIDTH)/2;//起始位置x
	wegui.tip.cur_y = -BAR_TIP_HIGHT-TIP_BOX_THICHNESS;//起始位置y
	wegui.tip.time  = 0;
	if(string!=0x00)
		wegui.tip.string=string;
	else
		wegui.tip.string = (uint8_t*)" ";
	wegui.tip.time = 0;//当前动画时间
	wegui.tip.Change_Value = Change_func;
	wegui.tip.Finish_Value = Finish_func;
	wegui.tip.change_way = change_way;
	
	
	if(p_value==0x00)
	{
		//tip.string=wegui_get_string(p_ValueError_String,wegui.setting.langauge);
		wegui.tip.string=(uint8_t*)"pErr";
		wegui.tip.pvalue = 0x00;
		wegui.tip.show_Value=0;
		wegui.tip.pvalue_min = 0;
		wegui.tip.pvalue_max = 0;
	}
	else
	{
		wegui.tip.pvalue = p_value;
		wegui.tip.show_Value=*p_value;
		wegui.tip.pvalue_min = value_min;
		wegui.tip.pvalue_max = value_max;
	}
}



void wegui_Tip_keyOk(Key_return_t i)
{
	switch (wegui.tip.type)
	{
		case message:break;
		case slider:
		{
			switch(i)
			{
				case start_short_press:       //开始短按
				{
					wegui.tip.state = EXITING;
					//结束时更新值
					if(wegui.tip.change_way == VALUE_DONE_AND_UPDATE)
						*wegui.tip.pvalue = wegui.tip.show_Value;
					if(wegui.tip.Finish_Value!=0x00)
						wegui.tip.Finish_Value();
				}break;
				case long_press_trig:				  //连续长按
					break;
				case start_long_press:        //开始长按
					break;
				case long_long_press_trig:    //连续超长按
					break;
				case end_short_press:					//结束短按
					break;
				case end_long_press:					//结束长按
					break;
				case end_long_long_press:			//结束超长按
					break;
				default:break;
			}
		}break;
	}
}
void wegui_Tip_keyBack(Key_return_t i)
{
	switch (wegui.tip.type)
	{
		case message:
		{
			switch(i)
			{
				case start_short_press:       //开始短按
					wegui.tip.state = EXITING;
					break;
				case long_press_trig:				  //连续长按
					break;
				case start_long_press:        //开始长按
					break;
				case long_long_press_trig:    //连续超长按
					break;
				case end_short_press:					//结束短按
					break;
				case end_long_press:					//结束长按
					break;
				case end_long_long_press:			//结束超长按
					break;
				default:break;
			}
		}break;
		case slider:
		{
			switch(i)
			{
				case start_short_press:       //开始短按
					wegui.tip.state = EXITING;
					break;
				case long_press_trig:				  //连续长按
					break;
				case start_long_press:        //开始长按
					break;
				case long_long_press_trig:    //连续超长按
					break;
				case end_short_press:					//结束短按
					break;
				case end_long_press:					//结束长按
					break;
				case end_long_long_press:			//结束超长按
					break;
				default:break;
			}
		}break;
	}
}
void wegui_Tip_keyRight(Key_return_t i)
{
	switch (wegui.tip.type)
	{
		case message:
		{
			switch(i)
			{
				case start_short_press:       //开始短按
					wegui.tip.state = EXITING;
					break;
				case long_press_trig:				  //连续长按
					break;
				case start_long_press:        //开始长按
					break;
				case long_long_press_trig:    //连续超长按
					break;
				case end_short_press:					//结束短按
					break;
				case end_long_press:					//结束长按
					break;
				case end_long_long_press:			//结束超长按
					break;
				default:break;
			}
		}break;
		case slider:
		{
			switch(i)
			{
				case start_short_press:       //开始短按
				case long_press_trig:				  //连续长按
				case long_long_press_trig:    //连续超长按
				{
					if(wegui.tip.show_Value<wegui.tip.pvalue_max)
					{
						wegui.tip.show_Value += 1;
						if(wegui.tip.change_way == VALUE_CHANGE_AND_UPDATE)//实时更新值
						{
							*wegui.tip.pvalue = wegui.tip.show_Value;
						}
						if(wegui.tip.Change_Value!=0x00)
							wegui.tip.Change_Value();
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
		}break;
	}
}

void wegui_Tip_keyLeft(Key_return_t i)
{
	switch (wegui.tip.type)
	{
		case message:
		{
			switch(i)
			{
				case start_short_press:       //开始短按
					wegui.tip.state = EXITING;
					break;
				case long_press_trig:				  //连续长按
					break;
				case start_long_press:        //开始长按
					break;
				case long_long_press_trig:    //连续超长按
					break;
				case end_short_press:					//结束短按
					break;
				case end_long_press:					//结束长按
					break;
				case end_long_long_press:			//结束超长按
					break;
				default:break;
			}
		}break;
		case slider:
		{
			switch(i)
			{
				case start_short_press:       //开始短按
				case long_press_trig:				  //连续长按
				case long_long_press_trig:    //连续超长按
				{
					if(wegui.tip.show_Value>wegui.tip.pvalue_min)
					{
						wegui.tip.show_Value -= 1;
						if(wegui.tip.change_way == VALUE_CHANGE_AND_UPDATE)//实时更新值
						{
							*wegui.tip.pvalue = wegui.tip.show_Value;
						}
						if(wegui.tip.Change_Value!=0x00)
							wegui.tip.Change_Value();
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
		}break;
	}
}

void wegui_Tip_keyUp(Key_return_t i)
{
	switch (wegui.tip.type)
	{
		case message:break;
		case slider:
		{
			switch(i)
			{
				case start_short_press:       //开始短按
				case long_press_trig:				  //连续长按
				case long_long_press_trig:    //连续超长按
				{
					if(wegui.tip.show_Value<wegui.tip.pvalue_max)
					{
						wegui.tip.show_Value += 1;
						if(wegui.tip.change_way == VALUE_CHANGE_AND_UPDATE)//实时更新值
						{
							*wegui.tip.pvalue = wegui.tip.show_Value;
						}
						if(wegui.tip.Change_Value!=0x00)
							wegui.tip.Change_Value();
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
		}break;
	}
}
void wegui_Tip_keyDown(Key_return_t i)
{
	switch (wegui.tip.type)
	{
		case message:break;
		case slider:
		{
			switch(i)
			{
				case start_short_press:       //开始短按
				case long_press_trig:				  //连续长按
				case long_long_press_trig:    //连续超长按
				{
					if(wegui.tip.show_Value>wegui.tip.pvalue_min)
					{
						wegui.tip.show_Value -= 1;
						if(wegui.tip.change_way == VALUE_CHANGE_AND_UPDATE)//实时更新值
						{
							*wegui.tip.pvalue = wegui.tip.show_Value;
						}
						if(wegui.tip.Change_Value!=0x00)
							wegui.tip.Change_Value();
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
		}break;
	}
}

void wegui_show_tip(uint16_t farmes, uint16_t Tms)
{
	if(wegui.tip.state != FREE)
	{
		uint8_t pid_p;
		switch(wegui.tip.state)
		{
			default:
			case ENTERING://弹窗正在进入
				pid_p = 2;//进入动画更快
				break;
			case DISPLAYING://弹窗正在展示
				pid_p = 2;//进入动画更快
				break;
			case EXITING://弹窗正在退出
				pid_p = 3;//退出动画更慢
				break;
		}
		//使用P(PID)的方式,使当前值接近目标值 
		//(cur_value:当前变量, target_value目标值, P:[0快:15慢], count:连续处理count次)
		//Value_Change_PID_P(cur_value,target_value,P,count)
		Value_Change_PID_P( wegui.tip.cur_x,//当前x位置
												wegui.tip.pos_x,//目标x位置
												pid_p,
												farmes);
		
		Value_Change_PID_P( wegui.tip.cur_y,//当前y位置
												wegui.tip.pos_y,//目标y位置
												pid_p,
												farmes);
		
		uint8_t string_yline = OLED_Get_UTF8_YLine(wegui.tip.string);//字符串分了多少行
		switch(wegui.tip.type)
		{
			case message:
			{
				uint8_t string_xlen = OLED_Get_UTF8_XLen(wegui.tip.string);
				
				OLED_Set_Driver_Mode(write_0);//选择0笔刷
				OLED_Fill_RBox		(wegui.tip.cur_x-TIP_BOX_THICHNESS ,
													wegui.tip.cur_y-TIP_BOX_THICHNESS,
													wegui.tip.cur_x+string_xlen+TIP_LR_Scape+TIP_LR_Scape+TIP_BOX_THICHNESS,
													wegui.tip.cur_y+string_yline*wegui.tip.fonts_high+TIP_TB_Scape+TIP_TB_Scape+TIP_BOX_THICHNESS,
													TIP_BOX_R+TIP_BOX_THICHNESS);
													
				OLED_Set_Driver_Mode(write_1);//选择1笔刷
				OLED_Draw_RBox	(wegui.tip.cur_x ,
															wegui.tip.cur_y,
															wegui.tip.cur_x+string_xlen+TIP_LR_Scape+TIP_LR_Scape,
															wegui.tip.cur_y+string_yline*wegui.tip.fonts_high+TIP_TB_Scape+TIP_TB_Scape,
															TIP_BOX_R);
				//居中显示提示文字
				OLED_Draw_UTF8_String	(wegui.tip.cur_x+TIP_LR_Scape,
															wegui.tip.cur_y+TIP_TB_Scape,
															wegui.tip.string);		
												
														
				if(wegui.tip.time > Tms)
				{
					wegui.tip.time -= Tms;
				}		
				else
				{
					wegui.tip.time = 0;
					wegui.tip.state = EXITING;//弹窗正在退出
				}
				
			}break;
			case slider:
			{
				
					OLED_Set_Driver_Mode(write_0);//选择0笔刷
					OLED_Fill_RBox		(wegui.tip.cur_x-TIP_BOX_THICHNESS ,
														wegui.tip.cur_y-TIP_BOX_THICHNESS,
														wegui.tip.cur_x+BAR_TIP_WIDTH+TIP_BOX_THICHNESS,
														wegui.tip.cur_y+BAR_TIP_HIGHT+TIP_BOX_THICHNESS,
														TIP_BOX_R+TIP_BOX_THICHNESS);
					
					OLED_Set_Driver_Mode(write_1);//选择1笔刷
					OLED_Draw_RBox	(wegui.tip.cur_x ,
																wegui.tip.cur_y,
																wegui.tip.cur_x+BAR_TIP_WIDTH,
																wegui.tip.cur_y+BAR_TIP_HIGHT,
																TIP_BOX_R);	
					
					//进度条边框
					OLED_Draw_RBox	(wegui.tip.cur_x + BAR_TIP_SIDE_SCAPE,
																wegui.tip.cur_y + wegui.tip.fonts_high*string_yline + BAR_TIP_TOP_SCAPE + BAR_TO_CHAR_SCAPE,
																wegui.tip.cur_x  + BAR_TIP_SIDE_SCAPE + BAR_WIDTH,
																wegui.tip.cur_y + wegui.tip.fonts_high*string_yline + BAR_TIP_TOP_SCAPE + BAR_TO_CHAR_SCAPE + BAR_HIGHT,
																2);
																
					//进度
					OLED_Fill_RBox				(wegui.tip.cur_x + BAR_TIP_SIDE_SCAPE,
																wegui.tip.cur_y + wegui.tip.fonts_high*string_yline + BAR_TIP_TOP_SCAPE + BAR_TO_CHAR_SCAPE,
																wegui.tip.cur_x  + BAR_TIP_SIDE_SCAPE + (BAR_WIDTH*(wegui.tip.show_Value-wegui.tip.pvalue_min)/(wegui.tip.pvalue_max-wegui.tip.pvalue_min)),
																wegui.tip.cur_y + wegui.tip.fonts_high*string_yline + BAR_TIP_TOP_SCAPE + BAR_TO_CHAR_SCAPE + BAR_HIGHT,
																2);
					uint8_t string[6];
					itoa(wegui.tip.show_Value,string,10);//数值转10进制字符串, 传递回给字符串指针
					
					OLED_Draw_UTF8_String	(wegui.tip.cur_x + BAR_TIP_SIDE_SCAPE,
													wegui.tip.cur_y + BAR_TIP_TOP_SCAPE/* + (string_yline-1)*string_yline*/,
													wegui.tip.string);
													
					OLED_Draw_UTF8_String	(wegui.tip.cur_x + BAR_TIP_SIDE_SCAPE + BAR_WIDTH - OLED_Get_UTF8_XLen(string),
													wegui.tip.cur_y + BAR_TIP_TOP_SCAPE + (string_yline-1)*wegui.tip.fonts_high,
													string);
													
					
			}break;
		}
		switch(wegui.tip.state)
		{
			default:
			case ENTERING://弹窗正在进入
				if((wegui.tip.cur_x == wegui.tip.pos_x)&&(wegui.tip.cur_y == wegui.tip.pos_y))
				{
					wegui.tip.state = DISPLAYING;//位置已到达
				}
				break;
			case DISPLAYING://弹窗正在展示
				break;
			case EXITING://弹窗正在退出
				switch(wegui.tip.type)
				{
					case message:wegui.tip.pos_y = -TIP_TB_Scape-TIP_TB_Scape - wegui.tip.fonts_high*string_yline;break;//退到屏幕外
					case slider:wegui.tip.pos_y = -BAR_TIP_HIGHT - TIP_BOX_THICHNESS - TIP_BOX_THICHNESS;break;//退到屏幕外
				}
				if((wegui.tip.cur_x == wegui.tip.pos_x)&&(wegui.tip.cur_y == wegui.tip.pos_y))
				{
					wegui.tip.state = FREE;//弹窗结束
				}
				break;
		}
	}		
}


