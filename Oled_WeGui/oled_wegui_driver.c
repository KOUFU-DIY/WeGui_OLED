#include "oled_wegui_driver.h"


#include "user_wegui_menu.h"
#include "oled_wegui_menu_mlist.h"
#include "oled_wegui_tip.h"



	
uint16_t wegui_1ms_stick=0;
wegui_t wegui;



extern uint16_t ResADC;
void m_wDemo_wMessage_ADC_func()
{
	static uint8_t string[7];
	
	itoa(ResADC,string,10);
	m_wDemo_wMessage_ADC.menuPar.wMessage_Par.Value_string = string;
}
void m_wDemo_wMessage_Pres_func()
{
	static uint8_t string[7];
	
	itoa(ResADC,string,10);
	m_wDemo_wMessage_Pres.menuPar.wMessage_Par.Value_string = string;
}
void m_wDemo_wMessage_Pres2_func()
{
	static uint8_t num=0;
	wegui_string_t i[]=
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
	
	
	if(num < (sizeof(i)/sizeof(wegui_string_t)-1))
	{
		num++;
	}
	else
	{
		num=0;
	}
	
	m_wDemo_wMessage_Pres2.menuPar.wMessage_Par.Value_string = wegui_get_string(i[num],wegui.setting.langauge);;
}

void update_wegui_screen_brightness()
{
	IC_Set_Bright(wegui.setting.brightness);
}

void Set_langauge_Chinese()
{
	wegui.setting.langauge=zh_CN;
}
void Set_langauge_English()
{
	wegui.setting.langauge=en_US;
}



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
  * 名称: uint8_t* wegui_get_string(wegui_string_t object,langage_t langauge)
  * 传入1: object 语言包
  * 传入2: langauge 语言
  * 功能: 返回"语言包"里对应的"langauge语言"字符串指针,
----------------------------------------------------------------*/
uint8_t* wegui_get_string(wegui_string_t object,langage_t langauge)
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
  * 名称: wegui_enter_menu(menu_t* p)
  * 传入1: p:菜单结构体
  * 功能: 进入p菜单
----------------------------------------------------------------*/
void wegui_enter_menu(menu_t* p)
{
		switch(p->menuType)
		{
			case wSlider:
			{
				wegui_Push_Slider_tip		(8, //Y位置
																wegui_get_string(p->titel,wegui.setting.langauge), //标题
																p->menuPar.wSliderTip_Par.pstr, //参数指针
																p->menuPar.wSliderTip_Par.min ,//最小值
																p->menuPar.wSliderTip_Par.max,//最大值
																VALUE_CHANGE_AND_UPDATE,//实时更新值
																p->menuPar.wSliderTip_Par.Change_Value_func,//改变数值执行的函数的指针
																p->menuPar.wSliderTip_Par.End_tip_func);//确定数值执行的函数的指针
			}break;
			
			case mList:
			{
				if(p==0x00){mList_par.cursor_id=0;mList_par.list_y_offset_target=0;return;}//没有菜单
				
				
				//保存当前菜单位置
				switch(wegui.menu->menuType)
				{
					case mList:
					{
						wegui.menu->history_cursor_id = mList_par.cursor_id ;//光标历史记录
						wegui.menu->history_pos = mList_par.list_y_offset_target;//位置历史记录
					}break;
					default:break;
				}

				
				wegui.menu = p;
				wegui_mList_Init();
				if(wegui.menu->menuPar.mList_Par.quit_fun!=0x00)
				wegui.menu->menuPar.mList_Par.quit_fun();//执行函数
				
				if(wegui.menu->menuPar.mList_Par.begin_fun!=0x00)
				wegui.menu->menuPar.mList_Par.begin_fun();//执行函数
				
			}break;
			case mPorgram:break;
			case wMessage:
			{
				if(p->menuPar.wMessage_Par.Press_func != 0x00)
				{
					p->menuPar.wMessage_Par.Press_func();
				}
				wegui_Push_Message_tip(8, wegui_get_string(p->menuPar.wMessage_Par.Tip_string,wegui.setting.langauge), 3000);//推送提示信息, (推送y位置, 提示内容字符串, 展示时间ms)
			}break;
			default:break;
		}
}


//刷新屏幕帧率
static void Reflash_fps(uint16_t stick)
{
	static uint16_t display_count = 0;//更新数据计时
	static uint8_t  sum_count=0;//次数
	static uint16_t sum=0;//总数 
	display_count += stick;
	sum += wegui.sysInfo.fps_time;
	sum_count++;
	
	if(display_count > 100)//更新时间ms
	{
		//帧率 = 1000/(总时间/次数)
		wegui.sysInfo.info_fps = (uint32_t)1000 * sum_count / sum;
		//wegui.sysInfo.info_fps = 1000 / (sum / sum_count);
		
		//if(wegui.sysInfo.info_fps > 99){wegui.sysInfo.info_fps = 99;}
		display_count = 0;
		sum_count = 0;
		sum = 0;
	}
}


//刷新CPU负载百分比
static void Reflash_CpuLoad(uint16_t stick)
{
	static uint16_t display_count = 0;
	static uint8_t  sum_count=0;//次数
	static uint16_t sum=0;//总数 
	display_count += stick;
	sum += wegui.sysInfo.cpu_time;
	
	sum_count++;
	if(display_count > 151)//更新时间ms
	{
		//占用cpu_load = 100% / (刷屏占用时间/设置帧率时间)
		if(wegui.setting.screen_fps_ms != 0)
		{
			wegui.sysInfo.cpu_load = ((uint16_t)100*sum / sum_count)/wegui.setting.screen_fps_ms;
		}
		else
		{
			wegui.sysInfo.cpu_load=100;
		}
		if(wegui.sysInfo.cpu_load>100){wegui.sysInfo.cpu_load = 100;}
		
		display_count = 0;
		sum_count = 0;
		sum = 0;
	}
}


//更新显示系统信息,调试信息,帧率,cpu
static void wegui_update_info(uint16_t stick)
{
	//右上角实时显示帧数
		uint8_t str[8];
		uint8_t y=0;
	
	const fonts_t *i  = oled_driver.fonts_ASCII;
	oled_driver.fonts_ASCII = &ascii_SongTi_6X12;
	OLED_Draw_Box( SCREEN_WIDTH - 1 - ((oled_driver.fonts_ASCII->width + oled_driver.fonts_ASCII->scape)* 7-oled_driver.fonts_ASCII->scape )-1,
	                SCREEN_HIGH - 1 - oled_driver.fonts_ASCII->high * 2-1,
	                SCREEN_WIDTH - 1,
	                SCREEN_HIGH - 1);
	OLED_Clear_Box( SCREEN_WIDTH - 1 - ((oled_driver.fonts_ASCII->width + oled_driver.fonts_ASCII->scape)* 7-oled_driver.fonts_ASCII->scape),
	                SCREEN_HIGH - 1 - oled_driver.fonts_ASCII->high * 2,
	                SCREEN_WIDTH - 1,
	                SCREEN_HIGH - 1);
	OLED_Set_Driver_Mode(write_inverse);
	//--------显示主频---------
		
//		str[0]='F';str[1]='R';str[2]=':';itoa(SystemCoreClock/1000000,&str[3],10);str[6]='M';str[7]='\0';
//		OLED_Draw_UTF8_String	( SCREEN_WIDTH - 1 - OLED_Get_UTF8_XLen(str),//x
//														y++*oled_driver.fonts_ASCII->high,//y
//														str);
		//--------显示CPU---------								
		str[0]='C';str[1]='P';str[2]='U';str[3]=':';itoa(wegui.sysInfo.cpu_load,&str[4],10);	
		OLED_Draw_UTF8_String(  SCREEN_WIDTH - 1 - OLED_Get_UTF8_XLen(str),//x
														SCREEN_HIGH - 1 - oled_driver.fonts_ASCII->high - y++*oled_driver.fonts_ASCII->high,//y
														str);
	
	//--------显示PFS---------								
		str[0]='F';str[1]='P';str[2]='S';str[3]=':';itoa(wegui.sysInfo.info_fps,&str[4],10);	
		OLED_Draw_UTF8_String(  SCREEN_WIDTH - 1 - OLED_Get_UTF8_XLen(str),//x
														SCREEN_HIGH - 1 - oled_driver.fonts_ASCII->high - y++*oled_driver.fonts_ASCII->high,//y
														str);
	oled_driver.fonts_ASCII = i;
	OLED_Set_Driver_Mode(write_1);
	//更新帧率
	Reflash_fps(stick);
	//更新CPU负载百分比
	Reflash_CpuLoad(stick);
}



void wegui_loop_func()
{
	//两者帧率参数设为一致,获得最佳的视觉体验
	
	//可变帧率
	#define UI_DRAW_TIME_MS        wegui.setting.ui_fps_ms     //ui绘制速度   0:关闭动画 8ms=100hz 5ms=200hz 4=240hz 3=333hz 2=500hz 1=1000hz
	#define SCREEN_REFRESH_TIME_MS wegui.setting.screen_fps_ms //屏幕刷新速度 8ms=100hz 5ms=200hz 4=240hz 3=333hz 2=500hz 1=1000hz
	
	//固定帧率
	//#define UI_DRAW_TIME_MS        fps_2_ms(100)  //ui绘制速度   100Hz
	//#define SCREEN_REFRESH_TIME_MS fps_2_ms(100) //屏幕刷新速度  100Hz
	
	
	uint8_t ui_farmes;
	uint8_t fps_farmes;
	uint16_t stick;
	static uint16_t ui_time_count  = 0; 
	static uint16_t fps_time_count = 0; 
	
	stick = wegui_1ms_stick;
	wegui_1ms_stick = 0;
	
	wegui_key_interface_stick(stick);//按键处理
	
	
	if(UI_DRAW_TIME_MS!=0)
	{
		ui_time_count  += stick;
		ui_farmes  = ui_time_count / UI_DRAW_TIME_MS; 
	}
	else
	{
		ui_farmes  = 255; 
	}
	
	fps_time_count += stick;
	fps_farmes = fps_time_count / SCREEN_REFRESH_TIME_MS;
	
	#if (0) //ui没刷新,禁止屏幕刷新
	if((OLED_is_Busy()==0)&&(fps_farmes > 0)&&(ui_farmes > 0))
	{
	#else  //就算ui没刷新,屏幕也会重新刷一遍(浪费资源)
	if((OLED_is_Busy()==0)&&(fps_farmes > 0))
	{
		
		if(ui_farmes > 0)
	#endif
		{
			//------------------屏幕刷新前自定义的操作---------------------
			m_wDemo_wMessage_ADC_func();//持续刷新显示的ADC值
			//------------------屏幕刷新前自定义的操作---------------------
			
			
			//------------------------菜单--------------------------
			switch (wegui.menu->menuType)
			{
				default:
				case mList:     //列表菜单
				case mPorgram:  //自定义功能APP
				case wCheckBox: //控件:复选框
				case wSlider:   //控件:滑条:
				{
						OLED_Clear_GRAM();
					
						if(UI_DRAW_TIME_MS!=0)
						{
							ui_farmes  = ui_time_count / UI_DRAW_TIME_MS; 
							wegui_show_mList(ui_farmes);
						}
						else
						{
							wegui_show_mList(1000);
						}
						
						//wegui_show_type1List_cursor(farmes);
						//wegui_show_type1List_scroll_bar(farmes, fps_time_count);
				}break;
				
			}
			//------------------------弹窗--------------------------
			wegui_show_tip(ui_farmes,ui_time_count);
			
			if(UI_DRAW_TIME_MS!=0)
			{
				ui_time_count =  ui_time_count%UI_DRAW_TIME_MS;
			}
		}
		

	
		//------------------------调试--------------------------
		wegui_update_info(fps_time_count);//在OLED_Refresh()前调用,可显示更新系统信息
		//------------------------刷屏--------------------------
		OLED_Refresh();
		wegui.sysInfo.cpu_time = wegui_1ms_stick ;//更新"刷屏一次cpu占用时间"
		wegui.sysInfo.fps_time = fps_time_count ; //更新"刷屏间隔时间"
		
		
		fps_time_count %= SCREEN_REFRESH_TIME_MS;
	}
	
	
	
//	switch (wegui.menu->menuType)
//	{
//		default:
//			case 	mList:     //列表菜单
//			case mPorgram:  //自定义功能APP
//			case wCheckBox: //控件:复选框
//			case wSlider:   //控件:滑条:
//			break;
//	}
	
	
}


static void wegui_Key_Up(uint16_t ms_stick)
{
	Key_return_t i = Keysw_det(&key_up ,Bool_Wkey4_is_Pressed(),ms_stick);
	switch (wegui.tip.state)
	{
		case FREE:
		case EXITING:break;
		case ENTERING:
		case DISPLAYING:
		{
			switch(wegui.tip.type)
			{
				case message:break;
				case slider:wegui_Tip_keyUp(i);return;
			}
		}
	}
	switch(wegui.menu->menuType)
	{
		case mList:     //列表菜单
			wegui_mlist_keyUp(i);
			break;
		case mPorgram:  //自定义功能APP
			break;
		case wCheckBox: //控件:复选框
			break;
		case wSlider:   //控件:滑条
			break;
		case wMessage:
			break;
	}
}
static void wegui_Key_Down(uint16_t ms_stick)
{
	Key_return_t i = Keysw_det(&key_down ,Bool_Wkey5_is_Pressed(),ms_stick);
	switch (wegui.tip.state)
	{
		case FREE:
		case EXITING:break;
		case ENTERING:
		case DISPLAYING:
		{
			switch(wegui.tip.type)
			{
				case message:break;
				case slider:wegui_Tip_keyDown(i);return;
			}
		}
	}
	switch(wegui.menu->menuType)
	{
		case mList:     //列表菜单
			wegui_mlist_keyDown(i);
		  break;
		case mPorgram:  //自定义功能APP
			break;
		case wCheckBox: //控件:复选框
			break;
		case wSlider:   //控件:滑条
			break;
		case wMessage:
			break;
	}
}
static void wegui_Key_Ok(uint16_t ms_stick)
{
	Key_return_t i = Keysw_det(&key_ok ,Bool_Wkey2_is_Pressed(),ms_stick);
	switch (wegui.tip.state)
	{
		case FREE:
		case EXITING:break;
		case ENTERING:
		case DISPLAYING:
		{
			switch(wegui.tip.type)
			{
				case message:break;
				case slider:wegui_Tip_keyOk(i);return;
			}
		}
	}
	switch(wegui.menu->menuType)
	{
		case mList:     //列表菜单
			wegui_mlist_keyOk(i);
		  break;
		case mPorgram:  //自定义功能APP
			break;
		case wCheckBox: //控件:复选框
			break;
		case wSlider:   //控件:滑条
			break;
		case wMessage:
			break;
	}
}
static void wegui_Key_Back(uint16_t ms_stick)
{
	Key_return_t i = Keysw_det(&key_back ,Bool_Wkey1_is_Pressed(),ms_stick);
	switch (wegui.tip.state)
	{
		case FREE:
		case EXITING:break;
		case ENTERING:
		case DISPLAYING:
		{
			switch(wegui.tip.type)
			{
				case message:break;
				case slider:wegui_Tip_keyBack(i);return;
			}
		}
	}
	switch(wegui.menu->menuType)
	{
		case mList:     //列表菜单
			wegui_mlist_keyBack(i);
		  break;
		case mPorgram:  //自定义功能APP
			break; 
		case wCheckBox: //控件:复选框
			break;
		case wSlider:   //控件:滑条
			break;
		case wMessage:
			break;
	}
}

static void wegui_Key_Left(uint16_t ms_stick)
{
	Key_return_t i = Keysw_det(&key_left ,Bool_Wkey6_is_Pressed(),ms_stick);
	switch (wegui.tip.state)
	{
		case FREE:break;
		case EXITING:break;
		case ENTERING:
		case DISPLAYING:
		{
			wegui_Tip_keyLeft(i);return;
		}
	}
	switch(wegui.menu->menuType)
	{
		case mList:     //列表菜单
			wegui_mlist_keyLeft(i);
		  break;
		case mPorgram:  //自定义功能APP
			break;
		case wCheckBox: //控件:复选框
			break;
		case wSlider:   //控件:滑条
			break;
		case wMessage:
			break;
	}
}

static void wegui_Key_Right(uint16_t ms_stick)
{
	Key_return_t i = Keysw_det(&key_right ,Bool_Wkey3_is_Pressed(),ms_stick);
	switch (wegui.tip.state)
	{
		case FREE:break;
		case EXITING:break;
		case ENTERING:
		case DISPLAYING:
		{
			wegui_Tip_keyRight(i);
			return;
		}
	}
	
	switch(wegui.menu->menuType)
	{
		case mList:     //列表菜单
			wegui_mlist_keyRight(i);
		  break;
		case mPorgram:  //自定义功能APP
			break;
		case wCheckBox: //控件:复选框
			break;
		case wSlider:   //控件:滑条
			break;
		case wMessage:
			break;
	}
}


void wegui_key_interface_stick(uint16_t ms)
{
	if(ms)
	{
		wegui_Key_Right(ms);
		wegui_Key_Up(ms)   ;
		wegui_Key_Down(ms) ;
		wegui_Key_Left(ms) ;
		wegui_Key_Back(ms) ;
		wegui_Key_Ok(ms)   ;
	}
}


void OLED_Wegui_Init()
{
	wegui_port_Init();

	wegui.menu = &m_main;//初始菜单menu
	
	//wegui.setting.langauge = en_US; //默认语言设置 en_US  zh_CN
	wegui.setting.langauge = zh_CN; //默认语言设置 en_US  zh_CN
	
	wegui.setting.brightness=127;//默认亮度设置(对比度)
		
	wegui.setting.screen_fps_ms = fps_2_ms(1000);//屏幕帧率设置(建议两者一致) 建议60~100
	wegui.setting.ui_fps_ms = fps_2_ms(60);//UI帧率设置(建议两者一致) 建议60~100
	
	wegui.sysInfo.info_fps = 0;//CPU负载
	wegui.sysInfo.cpu_load = 0;//实时刷新率
	wegui.sysInfo.cpu_time = 0;//刷屏资源占用时间
	wegui.sysInfo.fps_time = 0;//刷屏间隔时间

	wegui_mList_Init();
	
	
	wegui_1ms_stick = 0;
	wegui_Push_Message_tip(8, (uint8_t*)"Hello WEGUI!", 2000);//推送提示信息, (推送y位置, 提示内容字符串, 展示时间ms)
}
