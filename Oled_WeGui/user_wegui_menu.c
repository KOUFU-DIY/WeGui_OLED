
#include "user_wegui_menu.h"


/*************************************************
* 1.需要多国语言显示必须使用UTF8编码
* Edit->Configuration->Encoding->"Encod in UTF8"
* 
* 2.为放置中文字符串出现编译问题,
* 在V5编译器下,需要调整编译规则
* Project -> Oprions for Target-> C/C++ -> 
* Misc Contiols -> 填入"--locale=english"
*************************************************/


//-------------------m主菜单------------------------
menu_t m_main =
{
	.fatherMenu=0x00,//父菜单
	.subMenu=&m_App_Game,//(首个)子菜单
	.nextMenu=0x00,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"主菜单",//中文标题
	  .str_en_US=(uint8_t *)"MAIN",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"",//中文描述
	  .str_en_US=(uint8_t *)"",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};

menu_t m_App_Game =
{
	.fatherMenu=&m_main,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_App_ThemeClock,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"游戏",//中文标题
	  .str_en_US=(uint8_t *)"GAME",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"1.游戏",//中文描述
	  .str_en_US=(uint8_t *)"1.Game",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};

menu_t m_App_ThemeClock =
{
	.fatherMenu=&m_main,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_App_UartScreen,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"主题时钟",//中文标题
	  .str_en_US=(uint8_t *)"CLOCK",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"2.主题时钟",//中文描述
	  .str_en_US=(uint8_t *)"2.Theme Clock",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};

menu_t m_App_UartScreen =
{
	.fatherMenu=&m_main,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_App_Uart_Debuger,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t*)"Uart显示器",//中文标题
	  .str_en_US=(uint8_t*)"UART SCREEN",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"3.Uart显示器",//中文描述
	  .str_en_US=(uint8_t *)"3.Uart screen",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};

menu_t m_App_Uart_Debuger =
{
	.fatherMenu=&m_main,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_App_Files,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"Uart调试器",//中文标题
	  .str_en_US=(uint8_t *)"UART DEBUGER",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"4.Uart调试器",//中文描述
	  .str_en_US=(uint8_t *)"4.Uart Debuger",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};
menu_t m_App_Files =
{
	.fatherMenu=&m_main,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_App_Setting,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"文件管理器",//中文标题
	  .str_en_US=(uint8_t *)"FILES",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"5.文件管理器",//中文描述
	  .str_en_US=(uint8_t *)"5.File manager",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};

menu_t m_App_Setting =
{
	.fatherMenu=&m_main,//父菜单
	.subMenu=&m_Setting_Display,//(首个)子菜单
	.nextMenu=&m_wDemo,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"设置",//中文标题
	  .str_en_US=(uint8_t *)"SETTING",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"6.设置",//中文描述
	  .str_en_US=(uint8_t *)"6.Setting",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};
menu_t m_wDemo =
{
	.fatherMenu=&m_main,//父菜单
	.subMenu=&m_wDemo_wMessage_Tip,//(首个)子菜单
	.nextMenu=&m_App_8,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"控件Demo",//中文标题
	  .str_en_US=(uint8_t *)"wDemo",//英文标题
	},                      
	.discribe=              
	{                       
		.str_zh_CN=(uint8_t *)"7.控件Demo",//中文描述
	  .str_en_US=(uint8_t *)"7.Widget demo",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};

menu_t m_App_8 =
{
	.fatherMenu=&m_main,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_App_9,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"应用8",//中文标题
	  .str_en_US=(uint8_t *)"APP 8",//英文标题
	},                      
	.discribe=              
	{                       
		.str_zh_CN=(uint8_t *)"8.应用8",//中文描述
	  .str_en_US=(uint8_t *)"8.App 8",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};
menu_t m_App_9 =
{
	.fatherMenu=&m_main,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_App_10,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"应用9",//中文标题
	  .str_en_US=(uint8_t *)"APP 9",//英文标题
	},                      
	.discribe=              
	{                       
		.str_zh_CN=(uint8_t *)"9.应用9",//中文描述
	  .str_en_US=(uint8_t *)"9.App 9",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};
menu_t m_App_10 =
{
	.fatherMenu=&m_main,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_App_11,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"应用10",//中文标题
	  .str_en_US=(uint8_t *)"APP 10",//英文标题
	},                      
	.discribe=              
	{                       
		.str_zh_CN=(uint8_t *)"10.应用10",//中文描述
	  .str_en_US=(uint8_t *)"10.App 10",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};
menu_t m_App_11 =
{
	.fatherMenu=&m_main,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_App_12,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"应用11",//中文标题
	  .str_en_US=(uint8_t *)"APP 11",//英文标题
	},                      
	.discribe=              
	{                       
		.str_zh_CN=(uint8_t *)"11.应用11",//中文描述
	  .str_en_US=(uint8_t *)"11.App 11",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};
menu_t m_App_12 =
{
	.fatherMenu=&m_main,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_App_13,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"应用12",//中文标题
	  .str_en_US=(uint8_t *)"APP 12",//英文标题
	},                      
	.discribe=              
	{                       
		.str_zh_CN=(uint8_t *)"12.应用12",//中文描述
	  .str_en_US=(uint8_t *)"12.App 12",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};


menu_t m_App_13 =
{
	.fatherMenu=&m_main,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=0x00,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"应用13",//中文标题
	  .str_en_US=(uint8_t *)"APP13",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"13.应用13",//中文描述
	  .str_en_US=(uint8_t *)"13.App 13",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};


//-------------------m.m_Widget_Demo------------------------
menu_t m_wDemo_wMessage_Tip=
{
	.fatherMenu=&m_wDemo,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_wDemo_wMessage_ADC,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)" ",//中文标题 wMessage可不设置
	  .str_en_US=(uint8_t *)" ",//英文标题 wMessage可不设置
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"wMessage Tip",//中文描述
	  .str_en_US=(uint8_t *)"wMessage Tip",//英文描述
	},
	.menuType=wMessage,//菜单类型
	.menuPar.wMessage_Par.Tip_string=
	{
		.str_zh_CN=(uint8_t *)"wMessage\n支持换行\n222",//中文标题
	  .str_en_US=(uint8_t *)"wMessage\nnewline A\nnewline B",//英文标题
	},
};


//-------------------m.m_wDemo_wMessage------------------------
menu_t m_wDemo_wMessage_ADC=
{
	.fatherMenu=&m_wDemo,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_wDemo_wMessage_Pres,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"",//中文标题  wMessage可不设置
	  .str_en_US=(uint8_t *)"",//英文标题  wMessage可不设置
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"wMess ADC",//中文描述 
	  .str_en_US=(uint8_t *)"wMess ADC",//英文描述
	},
	.menuType=wMessage,//菜单类型
	.menuPar.wMessage_Par=
	{
		.Press_func=0x00,
		.Value_string=(uint8_t *)"-",
		.Tip_string=
		{
			.str_zh_CN=(uint8_t *)"可调电阻ADC\nIO: A1",//中文提示框
			.str_en_US=(uint8_t *)"ResADC\nIO: A1",//英文提示框
		},
	},
};

void m_wDemo_wMessage_Pres_func();
menu_t m_wDemo_wMessage_Pres=
{
	.fatherMenu=&m_wDemo,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_wDemo_wMessage_Pres2,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)" ",//中文标题 wMessage可不设置
	  .str_en_US=(uint8_t *)" ",//英文标题 wMessage可不设置
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"wMes 按下",//中文描述
	  .str_en_US=(uint8_t *)"wMes pres",//英文描述
	},
	.menuType=wMessage,//菜单类型
	.menuPar.wMessage_Par=
	{
		.Press_func=m_wDemo_wMessage_Pres_func,
		.Value_string=(uint8_t *)"-",
		.Tip_string=
		{
			.str_zh_CN=(uint8_t *)"",//中文提示框
			.str_en_US=(uint8_t *)"",//英文提示框
		},
	},
};

void m_wDemo_wMessage_Pres2_func();
menu_t m_wDemo_wMessage_Pres2=
{
	.fatherMenu=&m_wDemo,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_wDemo_wCheckbox,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)" ",//中文标题 wMessage可不设置
	  .str_en_US=(uint8_t *)" ",//英文标题 wMessage可不设置
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"wMes 按下",//中文描述
	  .str_en_US=(uint8_t *)"wMes pres",//英文描述
	},
	.menuType=wMessage,//菜单类型
	.menuPar.wMessage_Par=
	{
		.Press_func=m_wDemo_wMessage_Pres2_func,
		.Value_string=(uint8_t *)"-",
		.Tip_string=
		{
			.str_zh_CN=(uint8_t *)"",//中文提示框
			.str_en_US=(uint8_t *)"",//英文提示框
		},
	},
};


extern uint8_t adc_en;
menu_t m_wDemo_wCheckbox=
{
	.fatherMenu=&m_wDemo,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_wDemo_wSlider1,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)" ",//中文标题 wMessage可不设置
	  .str_en_US=(uint8_t *)" ",//英文标题 wMessage可不设置
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"wCheckBox",//中文描述
	  .str_en_US=(uint8_t *)"wCheckBox",//英文描述
	},
	.menuType=wCheckBox,//菜单类型
	.menuPar.wCheckBox_Par =
	{
		.pstr=&adc_en,         //复选框控制的数据指针
		.Change_Value=0x00,//值被修改 执行一次
	},
};

int16_t slider_demo_value=-5;
menu_t m_wDemo_wSlider1 =
{
	.fatherMenu=&m_wDemo,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_wDemo_wSlider2,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"demo1",//中文标题 弹窗里显示的名称
	  .str_en_US=(uint8_t *)"demo1",//英文标题 弹窗里显示的名称
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"wSlider",//中文描述 列表里显示的名称
	  .str_en_US=(uint8_t *)"wSlider",//英文描述 列表里显示的名称
	},
	.menuType=wSlider,//菜单类型
	.menuPar.wSliderTip_Par =
	{
		.Push_tip_func=0x00,      //控件进入 执行一次
		.Change_Value_func=0x00,  //值被修改 执行一次
		.End_tip_func=0x00,       //控件退出 执行一次
		
		.pstr = &slider_demo_value,
		.min = -100,
		.max = 100,
	},
};

menu_t m_wDemo_wSlider2 =
{
	.fatherMenu=&m_wDemo,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=0x00,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"---demo2----\nnewline\nnewline\nnewline",//中文标题 弹窗里显示的名称
	  .str_en_US=(uint8_t *)"---demo2----\nnewline\nnewline\nnewline",//英文标题 弹窗里显示的名称
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"wSlider",//中文描述 列表里显示的名称
	  .str_en_US=(uint8_t *)"wSlider",//英文描述 列表里显示的名称
	},
	.menuType=wSlider,//菜单类型
	.menuPar.wSliderTip_Par =
	{
		.Push_tip_func=0x00,    //控件进入 执行一次
		.Change_Value_func=0x00,//值被修改 执行一次
		.End_tip_func=0x00,     //控件退出 执行一次
		
		.pstr = &slider_demo_value,
		.min = -100,
		.max = 100,
	},
};










//-------------------m.m_App_Setting------------------------
menu_t m_Setting_Display =
{
	.fatherMenu=&m_App_Setting,//父菜单
	.subMenu=&m_Setting_Display_Brightness,//(首个)子菜单
	.nextMenu=&m_Setting_Time,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"显示",//中文标题
	  .str_en_US=(uint8_t *)"DISPLAY",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"1.显示",//中文描述
	  .str_en_US=(uint8_t *)"1.Display",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};

menu_t m_Setting_Time =
{
	.fatherMenu=&m_App_Setting,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_Setting_Speaker,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"时间&闹钟",//中文标题
	  .str_en_US=(uint8_t *)"Time&Clock",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"2.时间&闹钟",//中文描述
	  .str_en_US=(uint8_t *)"2.Time&Clock",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};

menu_t m_Setting_Speaker =
{
	.fatherMenu=&m_App_Setting,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_Setting_UI,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"音频",//中文标题
	  .str_en_US=(uint8_t *)"SPEAKER",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"3.音频",//中文描述
	  .str_en_US=(uint8_t *)"3.Speaker",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};


menu_t m_Setting_UI =
{
	.fatherMenu=&m_App_Setting,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_Setting_Langauge,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"UI&主题",//中文标题
	  .str_en_US=(uint8_t *)"UI THEME",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"5.UI&主题",//中文描述
	  .str_en_US=(uint8_t *)"5.UI Theme",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};

menu_t m_Setting_Langauge =
{
	.fatherMenu=&m_App_Setting,//父菜单
	.subMenu=&m_Setting_Langauge_English,//(首个)子菜单
	.nextMenu=&m_Setting_Developer,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"系统:简体中文 ",//中文标题
	  .str_en_US=(uint8_t *)"SYS:English",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"6.语言",//中文描述
	  .str_en_US=(uint8_t *)"6.Langauge",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};

menu_t m_Setting_Developer =
{
	.fatherMenu=&m_App_Setting,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_Setting_About,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"开发者选项",//中文标题
	  .str_en_US=(uint8_t *)"DEVELOPER",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"7.开发者选项",//中文描述
	  .str_en_US=(uint8_t *)"7.Developer",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};



menu_t m_Setting_About=
{
	.fatherMenu=&m_App_Setting,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=0x00,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"关于",//中文标题
	  .str_en_US=(uint8_t *)"ABOUT",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"8.关于",//中文描述
	  .str_en_US=(uint8_t *)"8.About",//英文描述
	},
	.menuType=mList,//菜单类型
	.menuPar.mList_Par =
	{
		.begin_fun=0x00,//菜单进入 执行一次
		.loop_fun=0x00, //菜单功能 持续执行
		.quit_fun=0x00, //菜单退出 执行一次
	},
};


//-------------------m.Setting.Langauge语言------------------------
void Set_langauge_English();
menu_t m_Setting_Langauge_English =
{
	.fatherMenu=&m_Setting_Langauge,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_Setting_Langauge_Chinese,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"ENGLISH",//中文标题
	  .str_en_US=(uint8_t *)"ENGLISH",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"1.English",//中文描述
	  .str_en_US=(uint8_t *)"1.English",//英文描述
	},

	.menuType=wMessage,//菜单类型
	.menuPar.wMessage_Par =
	{
		.Press_func=Set_langauge_English,//按下执行一次
		.Value_string=0x00,              //末尾显示的值 0x00不显示
		.Tip_string=
		{
			.str_zh_CN=(uint8_t *)"error",//中文提示框
			.str_en_US=(uint8_t *)"English now!",//英文提示框
		}, 
	},
};

void Set_langauge_Chinese();
menu_t m_Setting_Langauge_Chinese =
{
	.fatherMenu=&m_Setting_Langauge,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=0x00,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"简体中文",//中文标题
	  .str_en_US=(uint8_t *)"简体中文",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"2.简体中文",//中文描述
	  .str_en_US=(uint8_t *)"2.简体中文",//英文描述
	},
	.menuType=wMessage,//菜单类型
	.menuPar.wMessage_Par =
	{
		.Press_func=Set_langauge_Chinese, //按下执行一次
		.Value_string=0x00,               //末尾显示的值 0x00不显示
		.Tip_string=
		{
			.str_zh_CN=(uint8_t *)"已设置简体中文",//中文提示框
			.str_en_US=(uint8_t *)"error",//英文提示框
		}, 
	},
	
	
};
//-------------------m.Setting.Display显示------------------------
void update_wegui_screen_brightness();
menu_t m_Setting_Display_Brightness =
{
	.fatherMenu=&m_Setting_Display,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_Setting_Display_ScreenFPS,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"对比度",//中文标题
	  .str_en_US=(uint8_t *)"Bright",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"1.对比度",//中文描述
	  .str_en_US=(uint8_t *)"1.Bright",//英文描述
	},
	.menuType=wSlider,//菜单类型
	.menuPar.wSliderTip_Par =
	{
		.Push_tip_func=0x00,                                //控件进入 执行一次
		.Change_Value_func=update_wegui_screen_brightness,  //值被修改 执行一次
		.End_tip_func=0x00,                                 //控件退出 执行一次
		.pstr = &wegui.setting.brightness,
		.min = 0,
		.max = 255,
	},
};


menu_t m_Setting_Display_ScreenFPS =
{
	.fatherMenu=&m_Setting_Display,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_Setting_UI_Speed,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"屏幕刷新时间\nms",//中文标题
	  .str_en_US=(uint8_t *)"Screen ms",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"2.屏幕帧率",//中文描述
	  .str_en_US=(uint8_t *)"2.Screen FPS",//英文描述
	},
	.menuType=wSlider,//菜单类型
	.menuPar.wSliderTip_Par =
	{
		.Push_tip_func=0x00,      //控件进入 执行一次
		.Change_Value_func=0x00,  //值被修改 执行一次
		.End_tip_func=0x00,       //控件退出 执行一次
		.pstr = &wegui.setting.screen_fps_ms,
		.min = 1,
		.max = 100,
	},
};


menu_t m_Setting_UI_Speed =
{
	.fatherMenu=&m_Setting_UI,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=&m_Setting_Display_InvertColors,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"UI刷新时间\nms",//中文标题
	  .str_en_US=(uint8_t *)"UI ms",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"3.动画帧率 ",//中文描述
	  .str_en_US=(uint8_t *)"3.UI FPS ",//英文描述
	},
	.menuType=wSlider,//菜单类型
	.menuPar.wSliderTip_Par =
	{
		.Push_tip_func=0x00,      //控件进入 执行一次
		.Change_Value_func=0x00,  //值被修改 执行一次
		.End_tip_func=0x00,       //控件退出 执行一次
		.pstr = &wegui.setting.ui_fps_ms,
		.min = 1,
		.max = 100,
	},
};


menu_t m_Setting_Display_InvertColors =
{
	.fatherMenu=&m_Setting_Display,//父菜单
	.subMenu=0x00,//(首个)子菜单
	.nextMenu=0x00,//同级下一个菜单
	.titel=
	{
		.str_zh_CN=(uint8_t *)"屏幕反色",//中文标题
	  .str_en_US=(uint8_t *)"InvertPixel",//英文标题
	},
	.discribe=
	{
		.str_zh_CN=(uint8_t *)"4.屏幕反色",//中文描述
	  .str_en_US=(uint8_t *)"4.Inv Pixel",//英文描述
	},
	.menuType = wCheckBox,//菜单类型
	.menuPar.wCheckBox_Par =
	{
		.pstr=0x00,        //复选框控制的数据指针
		.Change_Value=0x00,//值被修改 执行一次
	},
};


//-------------------m.Setting.UI显示------------------------

