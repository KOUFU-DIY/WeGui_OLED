#ifndef _OLED_WEGUI_TIP_H_
#define _OLED_WEGUI_TIP_H_


#include "oled_wegui_driver.h"




void wegui_Tip_keyOk(Key_return_t i);
void wegui_Tip_keyBack(Key_return_t i);
void wegui_Tip_keyRight(Key_return_t i);
void wegui_Tip_keyLeft(Key_return_t i);
void wegui_Tip_keyUp(Key_return_t i);
void wegui_Tip_keyDown(Key_return_t i);
void wegui_show_tip(uint16_t farmes, uint16_t Tms);




/*--------------------------------------------------------------
  * 名称: wegui_Push_Message_tip(int16_t y, uint8_t* string, uint16_t time)
  * 传入1: y显示y位置
  * 传入2: string推送的字符串
  * 传入3: time推送显示时间
  * 功能: 像wegui屏幕推送一条消息
----------------------------------------------------------------*/
void wegui_Push_Message_tip(int16_t y, uint8_t* string, uint16_t time);//(推送y位置,推送字符串,推送显示时间)




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
void wegui_Push_Slider_tip(int16_t y, uint8_t* string, int16_t *p_value,int16_t value_min ,uint16_t value_max,value_change_t change_way,void(*Change_func)(),void(*Finish_func)());

#endif