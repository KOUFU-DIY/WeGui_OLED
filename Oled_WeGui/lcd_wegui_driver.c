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

#include "lcd_wegui_driver.h"
#include "user_wegui_menu.h"
#include "lcd_wegui_menu_mlist.h"
#include "lcd_wegui_tip.h"

uint16_t Wegui_stick=0;
Wegui_t Wegui;

/*--------------------------------------------------------------
  * 名称: *itoa(int16_t num,uint8_t *str,uint8_t radix)
  * 传入1: num 数字
  * 传入2: *str (空)字符串指针
	* 传入3: radix 进制数
  * 功能: 数字转字符串,保存到*str里
  * 说明:iota = integer to alphanumeric 把整型数转换成字符串
----------------------------------------------------------------*/
uint8_t *itoa(int16_t num,uint8_t *str,uint8_t radix)
{
    const uint8_t index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";//索引表
    uint32_t unum;//存放要转换的整数的绝对值,转换的整数可能是负数
    uint32_t i=0,j,k;//i用来指示设置字符串相应位，转换之后i其实就是字符串的长度；转换后顺序是逆序的，有正负的情况，k用来指示调整顺序的开始位置;j用来指示调整顺序时的交换。
 
    //获取要转换的整数的绝对值
    if(radix==10&&num<0)//要转换成十进制数并且是负数
    {
        unum=(unsigned)-num;//将num的绝对值赋给unum
        str[i++]='-';//在字符串最前面设置为'-'号，并且索引加1
    }
    else unum=/*(unsigned)*/num;//若是num为正，直接赋值给unum
    //转换部分，注意转换后是逆序的
    do
    {
        str[i++]=index[unum%(unsigned)radix];//取unum的最后一位，并设置为str对应位，指示索引加1
        unum/=radix;//unum去掉最后一位
 
    }while(unum);//直至unum为0退出循环
 
    str[i]='\0';//在字符串最后添加'\0'字符，c语言字符串以'\0'结束。
 
    //将顺序调整过来
    if(str[0]=='-') k=1;//如果是负数，符号不用调整，从符号后面开始调整
    else k=0;//不是负数，全部都要调整
 
    uint8_t temp;//临时变量，交换两个值时用到
    for(j=k;j<=(i-1)/2;j++)//头尾一一对称交换，i其实就是字符串的长度，索引最大值比长度少1
    {
        temp=str[j];//头部赋值给临时变量
        str[j]=str[i-1+k-j];//尾部赋值给头部
        str[i-1+k-j]=temp;//将临时变量的值(其实就是之前的头部值)赋给尾部
    }
    return str;//返回转换后的字符串
}


/*--------------------------------------------------------------
  * 名称: uint8_t* Wegui_get_string(Wegui_string_t object,langage_t langauge)
  * 传入1: object 语言包
  * 传入2: langauge 语言
  * 功能: 返回"语言包"里对应的"langauge语言"字符串指针,
----------------------------------------------------------------*/
uint8_t* Wegui_get_string(Wegui_string_t object,langage_t langauge)
{
	switch(langauge)
	{
		case zh_CN:return (uint8_t*)object.str_zh_CN;
		
		default:
		case en_US:return (uint8_t*)object.str_en_US;
	}
}

/*--------------------------------------------------------------
  * 名称: Get_submenu_sum(menu_t* m)
  * 传入: m:查询的菜单
  * 功能: 获取菜单中子菜单的总数
----------------------------------------------------------------*/
uint8_t Get_submenu_sum(menu_t* m)//获取菜单中子菜单的总数
{
	uint8_t num=0;
	if(m!=0x00)
	{
		if(m->subMenu != 0x00)
		{
			m = m->subMenu;
			num++;
			while(m->nextMenu != 0x00)
			{
				m = m->nextMenu;
				num++;
			}
		}
	}
	return num;
}


/*--------------------------------------------------------------
  * 名称: Wegui_enter_menu(menu_t* p)
  * 传入1: p:菜单结构体
  * 功能: 进入p菜单
----------------------------------------------------------------*/
void Wegui_enter_menu(menu_t* p)
{
		switch(p->menuType)
		{
			case mList:
			{
				if(p==0x00){mList_par.cursor_id=0;mList_par.list_y_offset_target=0;return;}//没有菜单
				
				
				//保存当前菜单位置
				switch(Wegui.menu->menuType)
				{
					case mList:
					{
						Wegui.menu->history_cursor_id = mList_par.cursor_id ;//光标历史记录
						Wegui.menu->history_pos = mList_par.list_y_offset_target;//位置历史记录
					}break;
					default:break;
				}
				
				if(Wegui.menu->menuPar.mList_Par.quit_fun!=0x00)
					Wegui.menu->menuPar.mList_Par.quit_fun();//执行函数
				
				Wegui.menu = p;//进入新的菜单
				Wegui_mList_Init();
				
				if(Wegui.menu->menuPar.mList_Par.begin_fun!=0x00)
					Wegui.menu->menuPar.mList_Par.begin_fun();//执行函数
				
			}break;
			case mPorgram:
			{
				//保存当前菜单位置
				switch(Wegui.menu->menuType)
				{
					case mList:
					{
						Wegui.menu->history_cursor_id = mList_par.cursor_id ;//光标历史记录
						Wegui.menu->history_pos = mList_par.list_y_offset_target;//位置历史记录
					}break;
					default:break;
				}
				
				if(Wegui.menu->menuPar.mList_Par.quit_fun!=0x00)
					Wegui.menu->menuPar.mList_Par.quit_fun();//执行函数
				
				Wegui.menu = p;//进入新的APP
				
				if(Wegui.menu->menuPar.mList_Par.begin_fun!=0x00)
					Wegui.menu->menuPar.mList_Par.begin_fun();//执行函数
			}break;
			case wMessage:
			{
				if(p->menuPar.wMessage_Par.Press_func != 0x00)
				{
					p->menuPar.wMessage_Par.Press_func();
				}
				Wegui_Push_Message_tip(8, Wegui_get_string(p->menuPar.wMessage_Par.Tip_string,Wegui.setting.langauge), 3000);//推送提示信息, (推送y位置, 提示内容字符串, 展示时间ms)
			}break;
			case wSlider:
			{
				Wegui_Push_Slider_tip		(8, //Y位置
																Wegui_get_string(p->titel,Wegui.setting.langauge), //标题
																p->menuPar.wSliderTip_Par.pstr, //参数指针
																p->menuPar.wSliderTip_Par.min ,//最小值
																p->menuPar.wSliderTip_Par.max,//最大值
																VALUE_CHANGE_AND_UPDATE,//实时更新值
																p->menuPar.wSliderTip_Par.Change_Value_func,//改变数值执行的函数的指针
																p->menuPar.wSliderTip_Par.End_tip_func);//确定数值执行的函数的指针
			}break;
			default:break;
		}
}

//刷新屏幕帧率
static void Reflash_fps(uint16_t stick)
{
	static uint16_t display_count = 0;//更新数据计时
	static uint8_t  sum_count=0;//次数
	static uint16_t sum=1;//总数 
	display_count += stick;
	sum += Wegui.sysInfo.fps_time;
	sum_count++;
	
	if(display_count > 100)//更新时间ms
	{
		//帧率 = 1000/(总时间/次数)
		Wegui.sysInfo.info_fps = (uint32_t)1000 * sum_count / sum;
		//Wegui.sysInfo.info_fps = 1000 / (sum / sum_count);
		
		//if(Wegui.sysInfo.info_fps > 99){Wegui.sysInfo.info_fps = 99;}
		display_count = 0;
		sum_count = 0;
		sum = 1;
	}
}


//刷新CPU负载百分比
static void Reflash_CpuLoad(uint16_t stick)
{
	static uint16_t display_count = 0;
	static uint8_t  sum_count=0;//次数
	static uint16_t sum=0;//总数 
	display_count += stick;
	sum += Wegui.sysInfo.cpu_time;
	
	sum_count++;
	if(display_count > 151)//更新时间ms
	{
		//占用cpu_load = 100% / (刷屏占用时间/设置帧率时间)
		if(Wegui.setting.screen_fps_ms != 0)
		{
			Wegui.sysInfo.cpu_load = ((uint16_t)100*sum / sum_count)/Wegui.setting.screen_fps_ms;
		}
		else
		{
			Wegui.sysInfo.cpu_load=100;
		}
		if(Wegui.sysInfo.cpu_load>100){Wegui.sysInfo.cpu_load = 100;}
		
		display_count = 0;
		sum_count = 0;
		sum = 0;
	}
}


//更新显示系统信息,调试信息,帧率,cpu
static void Wegui_update_info()
{
	//右上角实时显示帧数
		uint8_t str[10];
		uint8_t y=0;
	
	const fonts_t *i  = lcd_driver.fonts_ASCII;
	lcd_driver.fonts_ASCII = &ascii_SongTi_6X12;
	OLED_Draw_Box( SCREEN_WIDTH - 1 - ((lcd_driver.fonts_ASCII->width + lcd_driver.fonts_ASCII->scape)* 7-lcd_driver.fonts_ASCII->scape )-1,
	                SCREEN_HIGH - 1 - lcd_driver.fonts_ASCII->high * 2-1,
	                SCREEN_WIDTH - 1,
	                SCREEN_HIGH - 1);
	OLED_Clear_Box( SCREEN_WIDTH - 1 - ((lcd_driver.fonts_ASCII->width + lcd_driver.fonts_ASCII->scape)* 7-lcd_driver.fonts_ASCII->scape),
	                SCREEN_HIGH - 1 - lcd_driver.fonts_ASCII->high * 2,
	                SCREEN_WIDTH - 1,
	                SCREEN_HIGH - 1);
	OLED_Set_Driver_Mode(write_inverse);
	//--------显示主频---------
		
//		str[0]='F';str[1]='R';str[2]=':';itoa(SystemCoreClock/1000000,&str[3],10);str[6]='M';str[7]='\0';
//		OLED_Draw_UTF8_String	( SCREEN_WIDTH - 1 - OLED_Get_UTF8_XLen(str),//x
//														y++*lcd_driver.fonts_ASCII->high,//y
//														str);
		//--------显示CPU---------								
		str[0]='C';str[1]='P';str[2]='U';str[3]=':';
		itoa(Wegui.sysInfo.cpu_load,&str[4],10);	
		//itoa(Wegui.sysInfo.cpu_time,&str[4],10);	
		OLED_Draw_UTF8_String(  SCREEN_WIDTH - 1 - OLED_Get_UTF8_XLen(str),//x
														SCREEN_HIGH - 1 - lcd_driver.fonts_ASCII->high - y++*lcd_driver.fonts_ASCII->high,//y
														str);
	
	
	
	//--------显示PFS---------								
		str[0]='F';str[1]='P';str[2]='S';str[3]=':';
		itoa(Wegui.sysInfo.info_fps,&str[4],10);	
		OLED_Draw_UTF8_String(  SCREEN_WIDTH - 1 - OLED_Get_UTF8_XLen(str),//x
														SCREEN_HIGH - 1 - lcd_driver.fonts_ASCII->high - y++*lcd_driver.fonts_ASCII->high,//y
														str);
	lcd_driver.fonts_ASCII = i;
	OLED_Set_Driver_Mode(write_1);
}



void Wegui_loop_func()
{
	//两者帧率参数设为一致,获得最佳的视觉和性能体验
	
	//可变帧率
	#define UI_DRAW_TIME_MS        Wegui.setting.ui_fps_ms     //ui绘制速度   8ms=100hz 5ms=200hz 4=240hz 3=333hz 2=500hz 1=1000hz
	#define SCREEN_REFRESH_TIME_MS Wegui.setting.screen_fps_ms //屏幕刷新速度 8ms=100hz 5ms=200hz 4=240hz 3=333hz 2=500hz 1=1000hz
	
	//固定帧率
	//#define UI_DRAW_TIME_MS        fps_2_ms(100)  //ui绘制速度   100Hz
	//#define SCREEN_REFRESH_TIME_MS fps_2_ms(100) //屏幕刷新速度  100Hz
	
	static uint16_t ui_time_count  = 0; //ui绘图计时器
	static uint16_t fps_time_count = 0; //帧率计时器
	static uint8_t ui_farmes;
	static uint16_t time_count=0;
	uint8_t fps_farmes;
	uint16_t stick = Wegui_stick;
	Wegui_stick = 0;
	


	
	ui_time_count  += stick;
	time_count += stick;
	
	if(UI_DRAW_TIME_MS!=0)
	{
		ui_farmes  += ui_time_count / UI_DRAW_TIME_MS; 
		ui_time_count %= UI_DRAW_TIME_MS;
	}
	else
	{
		ui_farmes  = 255; 
	}
	
	fps_time_count += stick;
	fps_farmes = fps_time_count / SCREEN_REFRESH_TIME_MS;
	
	#if (0) //ui没刷新,禁止屏幕刷新
	if((LCD_is_Busy()==0)&&(fps_farmes > 0)&&(ui_farmes > 0))
	{
	#else  //就算ui没刷新,屏幕也会重新刷一遍(浪费资源)
	if((LCD_is_Busy()==0)&&(fps_farmes > 0))
	{
		//if(ui_farmes > 0)
	#endif
		{
			
			//------------------屏幕刷新前自定义的操作---------------------
			m_wDemo_wMessage_ADC_func();//持续刷新显示的ADC值
			//------------------屏幕刷新前自定义的操作---------------------
			
			
			//------------------------开始刷屏--------------------------
			do
			{
				//--------------------绘制对应菜单------------------------
				switch (Wegui.menu->menuType)
				{
					case mPorgram:  //自定义功能APP菜单
					{
						if(Wegui.menu->menuPar.mPorgram_Par.refresh_fun != 0x00)
						{
							Wegui.menu->menuPar.mPorgram_Par.refresh_fun();
						}
					}break;
					case wCheckBox: //控件:复选框菜单(不会进入)
						break;
					case wSlider:   //控件:滑条菜单(不会进入)
						break;
					default:
					case mList:     //列表菜单菜单
					{
						OLED_Clear_GRAM();
						//--------------------绘制菜单------------------------
						Wegui_show_mList(ui_farmes);
						//--------------------绘制弹窗------------------------
						Wegui_show_tip(ui_farmes,time_count);
						//-------------------绘制调试窗-----------------------
						Wegui_update_info();
					}break;
				}
				ui_farmes = 0;
				time_count = 0;
			}while(LCD_Refresh());
			


			//---刷新调试窗的信息---
			{
				static uint16_t i;
				Wegui.sysInfo.cpu_time = Wegui_stick ;//更新"刷屏一次cpu占用时间"
				Reflash_CpuLoad(fps_time_count-i);//更新CPU负载百分比
				Reflash_fps(fps_time_count);//更新帧率
				Wegui.sysInfo.fps_time = fps_time_count - i; //更新"两次刷屏间隔时间"
				fps_time_count %= SCREEN_REFRESH_TIME_MS;
				i = fps_time_count;
			}
		}
	}

	
	
	//-------------------------菜单的自定义LOOP任务---------------------------
	switch (Wegui.menu->menuType)
	{
		default:
			case 	mList:     //列表菜单
			{
				if(Wegui.menu->menuPar.mList_Par.loop_fun != 0x00)
				{
					Wegui.menu->menuPar.mList_Par.loop_fun();
				}
			}break;
			case mPorgram:  //自定义功能APP
			{
				if(Wegui.menu->menuPar.mPorgram_Par.loop_fun != 0x00)
				{
					Wegui.menu->menuPar.mPorgram_Par.loop_fun();
				}
			}break;
			case wCheckBox: //控件:复选框
			case wSlider:   //控件:滑条
			break;
	}
	//-------------------------菜单的LOOP任务---------------------------
	
	
	if(stick>0)
	{
		Wegui_Interface_stick(stick);//按键处理 stick传递时间用于计时 (隔执行减少占用)
	}
	Wegui_uart_rx_stick(stick);//串口处理 stick传递时间用于计时 (需要持续判断防止漏码)
}

void Wegui_Hello_Word()
{

	#if (LCD_PORT == _SOFT_3SPI)  //软件三线SPI驱动   
	uint8_t* string = (uint8_t*)"Hello WeGui!\nDriver:Soft3SPI";
	#elif (LCD_PORT == _SOFT_4SPI)  //软件四线SPI驱动   
	uint8_t* string = (uint8_t*)"Hello WeGui!\nDriver:Soft4SPI";
	#elif (LCD_PORT == _HARD_4SPI)  //硬件四线SPI驱动   
	uint8_t* string = (uint8_t*)"Hello WeGui!\nDriver:Hard4SPI";
	#elif (LCD_PORT == _DMA_4SPI)   //DMA四线SPI驱动 
	uint8_t* string = (uint8_t*)"Hello WeGui!\nDriver:DMA 4SPI";
	#elif (LCD_PORT == _SOFT_IIC)   //软件IIC驱动
	uint8_t* string = (uint8_t*)"Hello WeGui!\nDriver:SoftI2C";
	#elif (LCD_PORT ==_HARD_IIC)   //硬件IIC驱动
	uint8_t* string = (uint8_t*)"Hello WeGui!\nDriver:HardI2C";
	#endif
	
	Wegui_Push_Message_tip(2, string, 3000);//推送提示信息, (推送y位置, 提示内容字符串, 展示时间ms)
}

void Wegui_1ms_stick()
{
	if(Wegui_stick < 65535)
		Wegui_stick++;
}

void OLED_Wegui_Init()
{
	Wegui_Interface_port_Init();//交互接口初始化(6键/4键/编码器)
	Wegui_Uart_Port_Init();//uart接口初始化,缓冲区初始化
	
	Wegui.menu = &m_main;//开机初始菜单menu
	
	//Wegui.setting.langauge = en_US; //默认语言设置 en_US  zh_CN
	Wegui.setting.langauge = zh_CN; //默认语言设置 en_US  zh_CN
	
	Wegui.setting.brightness=127;//默认亮度设置(对比度)
		
	Wegui.setting.screen_fps_ms = fps_2_ms(1000);//屏幕帧率设置(建议两者一致) 建议60~100
	Wegui.setting.ui_fps_ms = fps_2_ms(60);//UI帧率设置(建议两者一致) 建议60~100
	
	Wegui.sysInfo.info_fps = 0;//CPU负载
	Wegui.sysInfo.cpu_load = 0;//实时刷新率
	Wegui.sysInfo.cpu_time = 0;//刷屏资源占用时间
	Wegui.sysInfo.fps_time = 0;//刷屏间隔时间

	Wegui_mList_Init();
	
	Wegui_Hello_Word();//开机欢迎弹窗

	Wegui_stick = 0;
}
