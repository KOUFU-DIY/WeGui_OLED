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

#ifndef LCD_Wegui_MENU_MLIST_H
#define LCD_Wegui_MENU_MLIST_H


#include "lcd_wegui_driver.h"

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
	
	uint16_t scroll_bar_len;         //滚动条长度
	uint16_t scrool_timer;          //计时用,倒计到隐藏滚动条
	int16_t scroll_y_offset_save;   //用于检测有无滚动页面,储存list_y_offset_cur,
	
}mList_par_t;







//返回上一级菜单
void Wegui_mlist_Back_menu(void);
//进入光标位置菜单
void Wegui_mlist_Enter_cursor(void);
//光标前一个
void Wegui_mlist_cursor_Prev(void);
//光标下一个
void Wegui_mlist_cursor_Next(void);



//初始化
void Wegui_mList_Init(void);
//显示驱动
void Wegui_show_mList(uint16_t farmes);




extern mList_par_t mList_par;

#endif
