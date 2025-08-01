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

#include "lcd_wegui_tip.h"





/*--------------------------------------------------------------
  * 名称: Wegui_Push_Message_tip(int16_t y, uint8_t* string, uint16_t time)
  * 传入1: y显示y位置
  * 传入2: string推送的字符串
  * 传入3: time推送显示时间
  * 功能: 向Wegui屏幕推送一条消息
----------------------------------------------------------------*/
void Wegui_Push_Message_tip(int16_t y, uint8_t* string, uint16_t time)//(推送y位置,推送字符串,推送显示时间)
{
	uint16_t string_xlen;
	uint16_t string_yline;
	if(string[0] != 0x00)
	{
		Wegui.tip.fonts_high = 16;
		//--文字高度--
		switch(Wegui.setting.langauge)
		{
			case zh_CN://中文
				if(lcd_driver.fonts_UTF8_cut != 0x00)
				{
					Wegui.tip.fonts_high = lcd_driver.fonts_UTF8_cut->high;
					break;
				}
			case en_US://英语
			default:
				if(lcd_driver.fonts_ASCII != 0x00)
				{
					Wegui.tip.fonts_high = lcd_driver.fonts_ASCII->high;
				}
				break;
		}
		string_xlen = OLED_Get_UTF8_XLen(string);
		string_yline = OLED_Get_UTF8_YLine(Wegui.tip.string);//字符串分了多少行
		
		Wegui.tip.state = ENTERING;
		Wegui.tip.type=message;
		Wegui.tip.pos_y = y;																							//动画目标位置y
		Wegui.tip.pos_x = -(int16_t)string_xlen/2 - TIP_LR_Scape + ((SCREEN_WIDTH/2)-1);	//动画目标位置x
		
		//初始位置隐藏在上方
		//Wegui.tip.cur_y = SCREEN_HIGH -(-TIP_TB_Scape-TIP_TB_Scape - Wegui.tip.fonts_high);	//开始位置Y
		Wegui.tip.cur_y = (-TIP_TB_Scape-TIP_TB_Scape - Wegui.tip.fonts_high*string_yline);	//开始位置Y
		Wegui.tip.cur_x = Wegui.tip.pos_x;												            //开始位置x
		
		Wegui.tip.time	=	time;//推送显示时间ms
		Wegui.tip.string = string;//推送字符内容
	}
}




/*--------------------------------------------------------------
  * 名称: Wegui_Push_Slider_tip(int16_t y, uint8_t* string, int16_t *p_value,int16_t value_min ,uint16_t value_max,value_change_t change_way,void(*Change_func)(),void(*Finish_func)())
  * 传入1: y:推送显示y位置
  * 传入2: string推送的字符串
  * 传入3: *p_value 待修改的数据指针
  * 传入4: value_min 待修改的数据的最小值
  * 传入5: value_max 待修改的数据的最大值
  * 传入6: change_way 改值方式
  * 传入7: *Change_func 滑条数据改变执行一次的函数指针
  * 传入8: *Finish_func 滑条数据确认后执行一次的函数指针
  * 功能: 向Wegui屏幕推送一条滑条控制窗
----------------------------------------------------------------*/
void Wegui_Push_Slider_tip(int16_t y, uint8_t* string, int16_t *p_value,int16_t value_min ,uint16_t value_max,value_change_t change_way,void(*Change_func)(),void(*Finish_func)())
{
	uint16_t string_yline = OLED_Get_UTF8_YLine(Wegui.tip.string);//字符串分了多少行
	//--更新文字高度--
	switch(Wegui.setting.langauge)
	{
		case zh_CN://中文
			if(lcd_driver.fonts_UTF8_cut != 0x00)
			{
				Wegui.tip.fonts_high = lcd_driver.fonts_UTF8_cut->high;
				break;
			}
		case en_US://英语
		default:
			if(lcd_driver.fonts_ASCII != 0x00)
			{
				Wegui.tip.fonts_high = lcd_driver.fonts_ASCII->high;
			}
			break;
	}
	
	Wegui.tip.state = ENTERING;
	Wegui.tip.type = slider;
	Wegui.tip.pos_x = (SCREEN_WIDTH - BAR_TIP_WIDTH)/2;//弹窗目标位置x(默认居中)
	Wegui.tip.pos_y = y;//弹窗目标位置y
	Wegui.tip.cur_x = (SCREEN_WIDTH - BAR_TIP_WIDTH)/2;//起始位置x
	Wegui.tip.cur_y = -BAR_TIP_HIGHT-TIP_BOX_THICHNESS;//起始位置y
	Wegui.tip.time  = 0;
	if(string!=0x00)
		Wegui.tip.string=string;
	else
		Wegui.tip.string = (uint8_t*)" ";
	Wegui.tip.time = 0;//当前动画时间
	Wegui.tip.Change_Value = Change_func;
	Wegui.tip.Finish_Value = Finish_func;
	Wegui.tip.change_way = change_way;
	
	
	if(p_value==0x00)
	{
		//tip.string=Wegui_get_string(p_ValueError_String,Wegui.setting.langauge);
		Wegui.tip.string=(uint8_t*)"pErr";
		Wegui.tip.pvalue = 0x00;
		Wegui.tip.show_Value=0;
		Wegui.tip.pvalue_min = 0;
		Wegui.tip.pvalue_max = 0;
	}
	else
	{
		Wegui.tip.pvalue = p_value;
		Wegui.tip.show_Value=*p_value;
		Wegui.tip.pvalue_min = value_min;
		Wegui.tip.pvalue_max = value_max;
	}
}



//保存值并且退出
void Wegui_Tip_Save_andQuit()
{
	switch(Wegui.tip.type)
	{
		case message:
		{
			Wegui.tip.state = EXITING;
		}break;
		case slider:
		{
			Wegui.tip.state = EXITING;
			if(Wegui.tip.change_way == VALUE_DONE_AND_UPDATE)
			{
				if(Wegui.tip.pvalue != 0x00)
				{
					*Wegui.tip.pvalue = Wegui.tip.show_Value;
				}
			}
			if(Wegui.tip.Finish_Value!=0x00)
			Wegui.tip.Finish_Value();
		}break;
	}
}


//直接退出
void Wegui_Tip_Quit()
{
	switch(Wegui.tip.type)
	{
		case message:
		{
			Wegui.tip.state = EXITING;
		}break;
		case slider:
		{
			Wegui.tip.state = EXITING;
		}break;
	}
}

//加值
void Wegui_Tip_Value_Add()
{
	switch(Wegui.tip.type)
	{
		case message:break;
		case slider:
		{
			if(Wegui.tip.show_Value<Wegui.tip.pvalue_max)
			{
				Wegui.tip.show_Value += 1;
				if(Wegui.tip.change_way == VALUE_CHANGE_AND_UPDATE)//实时更新值
				{
					*Wegui.tip.pvalue = Wegui.tip.show_Value;
				}
				if(Wegui.tip.Change_Value!=0x00)
					Wegui.tip.Change_Value();
			}
		}break;
	}
}

//减值
void Wegui_Tip_Value_Dec()
{
	switch(Wegui.tip.type)
	{
		case message:break;
		case slider:
		{
			if(Wegui.tip.show_Value>Wegui.tip.pvalue_min)
			{
				Wegui.tip.show_Value -= 1;
				if(Wegui.tip.change_way == VALUE_CHANGE_AND_UPDATE)//实时更新值
				{
					*Wegui.tip.pvalue = Wegui.tip.show_Value;
				}
				if(Wegui.tip.Change_Value!=0x00)
					Wegui.tip.Change_Value();
			}
		}break;
	}
}



void Wegui_show_tip(uint16_t farmes, uint16_t Tms)
{

	if(Wegui.tip.state != FREE)
	{
		if(farmes != 0)
		{
			uint8_t pid_p;
			switch(Wegui.tip.state)
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
			Value_Change_PID_P( Wegui.tip.cur_x,//当前x位置
													Wegui.tip.pos_x,//目标x位置
													pid_p,
													farmes);
			
			Value_Change_PID_P( Wegui.tip.cur_y,//当前y位置
													Wegui.tip.pos_y,//目标y位置
													pid_p,
													farmes);
		}
		
		
		uint8_t string_yline = OLED_Get_UTF8_YLine(Wegui.tip.string);//字符串分了多少行
		switch(Wegui.tip.type)
		{
			case message:
			{
				uint8_t string_xlen = OLED_Get_UTF8_XLen(Wegui.tip.string);
				
				OLED_Set_Driver_Mode(write_0);//选择0笔刷
				OLED_Fill_RBox		(Wegui.tip.cur_x-TIP_BOX_THICHNESS ,
													Wegui.tip.cur_y-TIP_BOX_THICHNESS,
													Wegui.tip.cur_x+string_xlen+TIP_LR_Scape+TIP_LR_Scape+TIP_BOX_THICHNESS,
													Wegui.tip.cur_y+string_yline*Wegui.tip.fonts_high+TIP_TB_Scape+TIP_TB_Scape+TIP_BOX_THICHNESS,
													TIP_BOX_R+TIP_BOX_THICHNESS);
													
				OLED_Set_Driver_Mode(write_1);//选择1笔刷
				OLED_Draw_RBox	(Wegui.tip.cur_x ,
															Wegui.tip.cur_y,
															Wegui.tip.cur_x+string_xlen+TIP_LR_Scape+TIP_LR_Scape,
															Wegui.tip.cur_y+string_yline*Wegui.tip.fonts_high+TIP_TB_Scape+TIP_TB_Scape,
															TIP_BOX_R);
				//居中显示提示文字
				OLED_Draw_UTF8_String	(Wegui.tip.cur_x+TIP_LR_Scape,
															Wegui.tip.cur_y+TIP_TB_Scape,
															Wegui.tip.string);		
												
														
				if(Wegui.tip.time > Tms)
				{
					Wegui.tip.time -= Tms;
				}		
				else
				{
					Wegui.tip.time = 0;
					Wegui.tip.state = EXITING;//弹窗正在退出
				}
				
			}break;
			case slider:
			{
				
					OLED_Set_Driver_Mode(write_0);//选择0笔刷
					OLED_Fill_RBox		(Wegui.tip.cur_x-TIP_BOX_THICHNESS ,
														Wegui.tip.cur_y-TIP_BOX_THICHNESS,
														Wegui.tip.cur_x+BAR_TIP_WIDTH+TIP_BOX_THICHNESS,
														Wegui.tip.cur_y+BAR_TIP_HIGHT+TIP_BOX_THICHNESS,
														TIP_BOX_R+TIP_BOX_THICHNESS);
					
					OLED_Set_Driver_Mode(write_1);//选择1笔刷
					OLED_Draw_RBox	(Wegui.tip.cur_x ,
																Wegui.tip.cur_y,
																Wegui.tip.cur_x+BAR_TIP_WIDTH,
																Wegui.tip.cur_y+BAR_TIP_HIGHT,
																TIP_BOX_R);	
					
					//进度条边框
					OLED_Draw_RBox	(Wegui.tip.cur_x + BAR_TIP_SIDE_SCAPE,
																Wegui.tip.cur_y + Wegui.tip.fonts_high*string_yline + BAR_TIP_TOP_SCAPE + BAR_TO_CHAR_SCAPE,
																Wegui.tip.cur_x  + BAR_TIP_SIDE_SCAPE + BAR_WIDTH,
																Wegui.tip.cur_y + Wegui.tip.fonts_high*string_yline + BAR_TIP_TOP_SCAPE + BAR_TO_CHAR_SCAPE + BAR_HIGHT,
																2);
																
					//进度
					OLED_Fill_RBox				(Wegui.tip.cur_x + BAR_TIP_SIDE_SCAPE,
																Wegui.tip.cur_y + Wegui.tip.fonts_high*string_yline + BAR_TIP_TOP_SCAPE + BAR_TO_CHAR_SCAPE,
																Wegui.tip.cur_x  + BAR_TIP_SIDE_SCAPE + (BAR_WIDTH*(Wegui.tip.show_Value-Wegui.tip.pvalue_min)/(Wegui.tip.pvalue_max-Wegui.tip.pvalue_min)),
																Wegui.tip.cur_y + Wegui.tip.fonts_high*string_yline + BAR_TIP_TOP_SCAPE + BAR_TO_CHAR_SCAPE + BAR_HIGHT,
																2);
					uint8_t string[7];
					itoa(Wegui.tip.show_Value,string,10);//数值转10进制字符串, 传递回给字符串指针
					
					OLED_Draw_UTF8_String	(Wegui.tip.cur_x + BAR_TIP_SIDE_SCAPE,
													Wegui.tip.cur_y + BAR_TIP_TOP_SCAPE/* + (string_yline-1)*string_yline*/,
													Wegui.tip.string);
													
					OLED_Draw_UTF8_String	(Wegui.tip.cur_x + BAR_TIP_SIDE_SCAPE + BAR_WIDTH - OLED_Get_UTF8_XLen(string),
													Wegui.tip.cur_y + BAR_TIP_TOP_SCAPE + (string_yline-1)*Wegui.tip.fonts_high,
													string);
													
					
			}break;
		}
		switch(Wegui.tip.state)
		{
			default:
			case ENTERING://弹窗正在进入
				if((Wegui.tip.cur_x == Wegui.tip.pos_x)&&(Wegui.tip.cur_y == Wegui.tip.pos_y))
				{
					Wegui.tip.state = DISPLAYING;//位置已到达
				}
				break;
			case DISPLAYING://弹窗正在展示
				break;
			case EXITING://弹窗正在退出
				switch(Wegui.tip.type)
				{
					case message:Wegui.tip.pos_y = -TIP_TB_Scape-TIP_TB_Scape - Wegui.tip.fonts_high*string_yline;break;//退到屏幕外
					case slider:Wegui.tip.pos_y = -BAR_TIP_HIGHT - TIP_BOX_THICHNESS - TIP_BOX_THICHNESS;break;//退到屏幕外
				}
				if((Wegui.tip.cur_x == Wegui.tip.pos_x)&&(Wegui.tip.cur_y == Wegui.tip.pos_y))
				{
					Wegui.tip.state = FREE;//弹窗结束
				}
				break;
		}
	}		
}


