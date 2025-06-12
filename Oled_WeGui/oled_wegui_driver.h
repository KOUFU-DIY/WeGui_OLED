#ifndef _OLED_WEGUI_DRIVER_H_
#define _OLED_WEGUI_DRIVER_H_

#include "oled_driver.h"
#include "oled_res.h"



#define fps_2_ms(x) ((uint16_t)1000/x) //输入FPS返回毫秒,不能是0


//-----非线性动画1-----
/*--------------------------------------------------------------
  * 名称: #define Value_Change_PID_P(cur_value,target_value,P,count)
  * 传入1: cur_value 当前值
  * 传入2: target_value目标值
	* 传入3: P:[0:15] 0:变化最慢 16变化最慢
	* 传入4: count:连续处理count次
  * 功能: 使用P(PID)的方式,使当前值逼近目标值
----------------------------------------------------------------*/
#define Value_Change_PID_P(cur_value,target_value,P,count) \
do                                                   \
{                                                    \
	uint8_t f=count;                                   \
	while(f>0)                                         \
	{                                                  \
		f--;                                             \
		if(cur_value > target_value)                     \
		{                                                \
			uint16_t i = cur_value - target_value;         \
			i = i>>P;                                      \
			if(i==0){i=1;}                                 \
			cur_value-=i;                                  \
		}                                                \
		else if (cur_value < target_value)               \
		{                                                \
			uint16_t i = target_value - cur_value;         \
			i = i>>P;                                      \
			if(i==0){i=1;}                                 \
			cur_value+=i;                                  \
		}                                                \
	}                                                  \
}while(0)





//--------------------语言--------------------
//-------语言类型--------
typedef enum langauge
{
	en_US=0,//英语
	zh_CN,//简体中文
	
}langage_t;
//-----多语言字符串------
typedef struct langauge_string_t
{
	/*const*/ uint8_t * str_zh_CN;
	/*const*/ uint8_t * str_en_US;
}wegui_string_t;
//--------------------设置--------------------
typedef struct wegui_t_setting
{
	langage_t langauge;    //系统语言
	int16_t brightness;   //系统亮度
	int16_t ui_fps_ms;    //ui绘制时间(建议与刷屏同步)
	int16_t screen_fps_ms;//屏幕刷新时间(建议与刷屏同步)
	
	//const fonts_t *fonts_ASCII;   //ASCII字体
	//const fonts_t *fonts_UTF8_cut;//UTF8裁剪字体
	
}setting_t;
//-----------------系统信息------------------
typedef struct wegui_sysInfo
{
	uint16_t info_fps;//CPU负载
	uint16_t cpu_load;//实时刷新率
	uint16_t cpu_time;//刷屏函数总占用时间
	uint16_t fps_time;//屏幕刷新时间
	
}sysInfo_t;
//------------------菜单&控件------------------

//----菜单&控件类型----
typedef enum menuType
{
	mList,     //列表菜单
  mPorgram,  //自定义功能APP
	wCheckBox, //控件:复选框
	wSlider,   //控件:滑条
	wMessage,  //控件:消息
}menuType_t;

//------mList参数------
typedef struct mList_Propertys
{
	void (*begin_fun)();//菜单进入 执行一次
	void (*loop_fun)(); //菜单功能 持续执行
	void (*quit_fun)(); //菜单退出 执行一次
	void (*pstr_control_func)(uint16_t value);
	uint8_t display_y_offset;//保存显示所处位置
	uint8_t cursor_id;       //保存当前选中的项
}mList_Par_t;

//-----mPorgram参数-----
typedef struct mPorgram_Propertys
{
	void (*begin_fun)();//菜单进入 执行一次
	void (*loop_fun)(); //菜单功能 持续执行
	void (*quit_fun)(); //菜单退出 执行一次
}mPorgram_Par_t;

//----wCheckBox参数-----
typedef struct wCheckBox_Propertys
{
	uint8_t *pstr;         //复选框控制的数据指针
	void (*Change_Value)();//值被修改 执行一次
}wCheckBox_Par_t;

//------wSlider参数------
typedef struct wSliderTip_Propertys
{
	int16_t *pstr;               //滑条控制的数据指针
	int16_t min;                 //滑条最小值
	int16_t max;                 //滑条最大值
	void (*Push_tip_func)();    //控件进入 执行一次
	void (*Change_Value_func)();//值被修改 执行一次
	void (*End_tip_func)();     //控件退出 执行一次
}wSliderTip_Par_t;	

typedef struct wMessage_Propertys
{
	void (*Press_func)();              //按下执行一次
	uint8_t* Value_string;             //末尾显示的值 0x00不显示
	wegui_string_t Tip_string;         //提示框字符串
}wMessage_Par_t;	



//-------参数共同体-------
typedef union menuType_Propertys
{
  mList_Par_t      mList_Par;
	mPorgram_Par_t   mPorgram_Par;
  wCheckBox_Par_t	 wCheckBox_Par;
	wSliderTip_Par_t wSliderTip_Par;
	wMessage_Par_t wMessage_Par;
}menuType_Par_t;

//-------菜单结构体-------
typedef struct menu_t
{
	struct menu_t * fatherMenu;//父菜单
	struct menu_t * subMenu;//(首个)子菜单
	struct menu_t * nextMenu;//同级下一个菜单
	/*const*/ wegui_string_t titel;//多语言标题
	/*const*/ wegui_string_t discribe;//多语言描述
	menuType_t menuType;//菜单类型
	menuType_Par_t menuPar;//菜单属性
	
	uint8_t history_cursor_id;//光标历史记录
	int16_t history_pos;//位置历史记录
}menu_t;

//------------------弹窗结构体------------------
//----消息弹窗----
#define TIP_BOX_THICHNESS 2   //边框&背景隔离的厚度
#define TIP_BOX_R 3           //倒圆角
#define TIP_LR_Scape 4				//文字和边框左右的间距
#define TIP_TB_Scape 4				//文字和边框上下的间距
//----滑条弹窗----
#define BAR_TIP_TOP_SCAPE 4  //弹窗顶部预留空间(顶部到文字)
#define BAR_TIP_BOT_SCAPE 4  //弹窗底部预留空间(底部到进度条)
#define BAR_TO_CHAR_SCAPE 4  //进度条到文字的空间
#define BAR_TIP_SIDE_SCAPE 4 //弹窗到进度侧边的距离

#define BAR_WIDTH (SCREEN_WIDTH-32) //进度条的宽度
#define BAR_HIGHT 3					//进度条的高度

#define BAR_TIP_HIGHT (wegui.tip.fonts_high*string_yline + BAR_TIP_TOP_SCAPE + BAR_TO_CHAR_SCAPE + BAR_HIGHT + BAR_TIP_BOT_SCAPE)	//弹窗高度
#define BAR_TIP_WIDTH (BAR_WIDTH + BAR_TO_CHAR_SCAPE*2) //弹窗宽度, 双数优先
typedef enum tip_type
{
	message,//消息弹窗
	slider,//滑条弹窗
}tip_type_t;
typedef enum value_change_type
{
	VALUE_CHANGE_AND_UPDATE,//值实时更新
	VALUE_DONE_AND_UPDATE,//值点击"确定"后才更新
}value_change_t;
typedef enum tip_state
{
	FREE = 0x00,//弹窗空闲
	ENTERING,//弹窗正在进入
	DISPLAYING,//弹窗正在展示
	EXITING,//弹窗正在退出
}tip_state_t;
typedef struct wegui_tip
{
	tip_state_t state;//有无弹窗
	tip_type_t type;//当前弹窗的类型
	uint8_t fonts_high;
	
	int16_t   pos_y;//目标位置y
	int16_t   pos_x;//目标位置x
	int16_t   cur_y;//当前位置y
	int16_t   cur_x;//当前位置x
	int16_t   time;//时间
	uint8_t*  string;//字符串
	
	
	int16_t* pvalue;//待修改的参数的指针(调值弹窗有效)
	int16_t show_Value;//弹窗显示值
	int16_t pvalue_min;//待修改的参数的最小值(调值弹窗有效)
	int16_t pvalue_max;//待修改的参数的最大值(调值弹窗有效)
	value_change_t change_way;//改值方式
	
	void (*Change_Value)();
	void (*Finish_Value)();
	
}wegui_tip_t;


//------------------主结构体------------------
typedef struct wegui_t
{
	menu_t *menu;//菜单
	wegui_tip_t tip;//弹窗
	setting_t setting;
	sysInfo_t sysInfo;
}wegui_t;





/*--------------------------------------------------------------
  * 名称: *itoa(int16_t num,uint8_t *str,uint8_t radix)
  * 传入1: num 数字
  * 传入2: *str (空)字符串指针
	* 传入3: radix 进制数
  * 功能: 数字转成字符串,保存到*str里
  * 说明:iota = integer to alphanumeric 把整型数转换成字符串
----------------------------------------------------------------*/
uint8_t *itoa(int16_t num,uint8_t *str,uint8_t radix);
/*--------------------------------------------------------------
  * 名称: Get_submenu_sum(menu_t* m)
  * 传入: m:查询的菜单
  * 功能: 获取菜单中子菜单的总数
----------------------------------------------------------------*/
uint8_t Get_submenu_sum(menu_t* m);//获取菜单中子菜单的总数
/*--------------------------------------------------------------
  * 名称: uint8_t* wegui_get_string(wegui_string_t object,langage_t langauge)
  * 传入1: object 语言包
  * 传入2: langauge 语言
  * 功能: 返回"语言包"里对应的"langauge语言"字符串指针,
----------------------------------------------------------------*/
uint8_t* wegui_get_string(wegui_string_t object,langage_t langauge);




void wegui_enter_menu(menu_t* p);
void wegui_key_interface_stick(uint16_t ms);

void wegui_loop_func();//放到主循环
void OLED_Wegui_Init();


extern wegui_t wegui;
extern uint16_t wegui_1ms_stick;

#endif
