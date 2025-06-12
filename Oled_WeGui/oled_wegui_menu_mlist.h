#ifndef OLED_WEGUI_MENU_MLIST_H
#define OLED_WEGUI_MENU_MLIST_H


#include "oled_wegui_driver.h"

typedef struct mList_par
{
	
	int16_t list_y_offset_target;   //菜单下移位置目标值
	int16_t list_y_offset_cur;      //菜单下移位置当前值
	uint8_t list_y_scape;           //菜单换行距离
	uint8_t list_font_high;         //菜单文字高度
	uint16_t list_animation_temp_y; //--动画运行变量
	
	uint16_t cursor_id;             //光标指向第几个列表id
	int16_t cursor_box_x0;          //光标矩形目标位置x0
	int16_t cursor_box_y0;          //光标矩形目标位置y0
	int16_t cursor_box_x1;          //光标矩形目标位置x1
	int16_t cursor_box_y1;          //光标矩形目标位置y1
	
	uint8_t scroll_bar_len;         //滚动条长度
	uint16_t scrool_timer;          //计时用,倒计到隐藏滚动条
	int16_t scroll_y_offset_save;   //用于检测有无滚动页面,储存list_y_offset_cur,
	
}mList_par_t;






void wegui_mList_Init();
void wegui_mlist_keyUp(Key_return_t i);
void wegui_mlist_keyDown(Key_return_t i);
void wegui_mlist_keyOk(Key_return_t i);
void wegui_mlist_keyBack(Key_return_t i);
void wegui_mlist_keyLeft(Key_return_t i);
void wegui_mlist_keyRight(Key_return_t i);
void wegui_show_mList(uint16_t farmes);




extern mList_par_t mList_par;

#endif