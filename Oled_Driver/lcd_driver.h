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

#ifndef _LCD_DRIVER_H_
#define _LCD_DRIVER_H_

#include "stdint.h"
#include "lcd_wegui_Config.h"
#include "lcd_res.h"






typedef union unicode_par
{
	uint16_t u16;
	uint8_t u8[2];
}unicode_t;

typedef enum circle_part
{
	C_RU = 0x01,//右上八分之一圆
	C_UR = 0x02,//上右八分之一圆
	C_UL = 0x04,//上左八分之一圆
	C_LU = 0x08,//左上八分之一圆
	C_LD = 0x10,//左下八分之一圆
	C_DL = 0x20,//下左八分之一圆
	C_DR = 0x40,//下右八分之一圆
	C_RD = 0x80,//右下八分之一圆
	
	C_HL = C_UL | C_LU | C_LD | C_DL ,//左半圆
	C_HR = C_UR | C_RU | C_RD | C_DR ,//右半圆
	C_HU = C_RU | C_UR | C_UL | C_LU ,//上半圆
	C_HD = C_LD | C_DL | C_DR | C_RD ,//下半圆
	
	C_QLU = C_UL | C_LU,//左上角四分圆
	C_QLD = C_LD | C_DL,//左下角四分圆
	C_QRU = C_UR | C_RU,//右上角四分圆
	C_QRD = C_DR | C_RD,//右下角四分圆
	
	C_ALL = 0xFF,//完整的园

}circle_part_t;

typedef enum lcd_driver_mode//驱动模式
{
	write_0,				    //全屏写0显示
	write_1,				    //全屏写1显示
	write_inverse,	    //全屏反转写入
	write_0_inBox ,			//限制区域内写0(高级)
	write_1_inBox ,			//限制区域内写1(高级)
	write_inverse_inBox,//限制区域内反转(高级)
}lcd_driver_mode_t;

typedef struct oled_boxDriver//高级驱动参数
{
	uint16_t x_min;   //限制矩形x最小值
	uint16_t x_max;   //限制矩形x最大值
	uint16_t ypage_min;//限制矩形ypage最小值
	uint16_t ypage_max;//限制矩形ypage最大值
	uint16_t ypage_min_temp;//最小ypage允许写入的像素点映射(储存计算结果,用于快速运行)
	uint16_t ypage_max_temp;//最大ypage允许写入的像素点映射(储存计算结果,用于快速运行)
}OledBoxDriver_t;

typedef struct lcd_driver
{
	//----------显存----------
	#if ((LCD_MODE == _FULL_BUFF_FULL_UPDATE) || ((LCD_MODE == _FULL_BUFF_DYNA_UPDATE)))//全屏缓存
	uint8_t LCD_GRAM[GRAM_YPAGE_NUM][SCREEN_WIDTH];
	#elif ((LCD_MODE == _PAGE_BUFF_FULL_UPDATE) || (LCD_MODE == _PAGE_BUFF_DYNA_UPDATE))//页缓存
	uint8_t LCD_GRAM[GRAM_YPAGE_NUM][SCREEN_WIDTH];
	uint8_t lcd_refresh_ypage;//记录当前刷屏的是哪一页
	#endif
	//--------绘画驱动--------
	void (*Write_GRAM)(uint16_t x,uint16_t ypage,uint8_t u8_value);//普通写,显示驱动函数
	void (*Clear_GRAM)(uint16_t x,uint16_t ypage,uint8_t u8_value);//普通清,显示驱动函数
	OledBoxDriver_t Box;//高级驱动辅助,限制写入区域
	//----------字体----------
	const fonts_t *fonts_ASCII;   //ASCII字体
	const fonts_t *fonts_UTF8_cut;//UTF8裁剪字体
	uint8_t newline_high;//换行距离
}lcd_driver_t;



/*--------------------------------------------------------------
  * 名称: OLED_Set_Driver_Mode(lcd_driver_mode_t mode)
  * 传入: mode 驱动模式
  * 功能: 设置驱动方式
----------------------------------------------------------------*/
void OLED_Set_Driver_Mode(lcd_driver_mode_t mode);

/*--------------------------------------------------------------
  * 名称: OLED_Set_Driver_Box(uint16_t x_min ,uint16_t y_min ,uint16_t x_max,uint16_t y_max)
  * 传入: (x_min,y_min)起始点 (x_max,y_max)终点
  * 功能: 设置高级驱动的限制区域(Box)
----------------------------------------------------------------*/
void OLED_Set_Driver_Box(uint16_t x_min ,uint16_t y_min ,uint16_t x_max,uint16_t y_max);

/*--------------------------------------------------------------
  * 名称: OLED_Draw_Pixl(int16_t x,uint16_t y)
  * 传入: x,y 坐标点
  * 功能: 绘制一个像素点
  * 说明: 坐标点支持负数
----------------------------------------------------------------*/
void OLED_Draw_Pixl(int16_t x,int16_t y);

/*--------------------------------------------------------------
  * 名称: OLED_Draw_Line(int16_t x1,int16_t y1,int16_t x2,int16_t y2)
  * 传入: (x1,y1)起点 (x0,y0)终点
  * 功能: 两点绘制一条直线
  * 说明: 布雷森汉姆直线算法
----------------------------------------------------------------*/
void OLED_Draw_Line(int16_t x1,int16_t y1,int16_t x2,int16_t y2);

/*--------------------------------------------------------------
  * OLED_Draw_Circel_part(int16_t x0,int16_t y0,uint8_t r,circle_part_t cPart)
  * 传入: (x0,y0):起点  r:半径 cPart:圆的部分
  * 功能: 绘制圆形部分
----------------------------------------------------------------*/
void OLED_Draw_Circel_part(int16_t x0,int16_t y0,uint8_t r,circle_part_t cPart);

/*--------------------------------------------------------------
  * OLED_Fill_Circel_part(int16_t x0,int16_t y0,uint8_t r,circle_part_t cPart)
  * 传入: (x0,y0):起点  r:半径 cPart:圆的部分
  * 功能: 填充圆形部分
----------------------------------------------------------------*/
void OLED_Fill_Circel_part(int16_t x0,int16_t y0,uint8_t r,circle_part_t cPart);

/*--------------------------------------------------------------
  * 名称: OLED_Clear_Box(int x_min,int y_min, int x_max, int y_max)
  * 传入: 4点坐标
  * 返回: 无
  * 功能: 长方形区域挖空
  * 说明: 坐标点支持负数
----------------------------------------------------------------*/
void OLED_Clear_Box(int16_t x_min,int16_t y_min, int16_t x_max, int16_t y_max);

/*--------------------------------------------------------------
  * 名称: OLED_Draw_Box(int16_t x_min,int16_t y_min, int16_t x_max, int16_t y_max)
  * 传入: (x_min,y_min)起点 (x_max,y_max)终点
  * 功能: 绘制矩形
----------------------------------------------------------------*/
void OLED_Draw_Box(int16_t x_min,int16_t y_min, int16_t x_max, int16_t y_max);

/*--------------------------------------------------------------
  * 名称: OLED_Fill_Box(int16_t x_min,int16_t y_min, int16_t x_max, int16_t y_max)
  * 传入: 4点坐标
  * 功能: 填充矩形
  * 说明: 坐标点支持负数
----------------------------------------------------------------*/
void OLED_Fill_Box(int16_t x_min,int16_t y_min, int16_t x_max, int16_t y_max);

/*--------------------------------------------------------------
  * 名称: OLED_Draw_Bitmap(int16_t x0,int16_t y0,uint8_t sizex,uint8_t sizey,uint8_t BMP[])
  * 传入1: x0 坐标左上角横坐标点
	* 传入2: y0 坐标左上角纵坐标点
  * 传入3: sizex 点阵图形x宽度
  * 传入4: sizey 点阵图形y高度
  * 传入5: BMP[] 点阵图形数组地址
  * 功能: 将点阵图形摆放到任意坐标点上
  * 说明: 坐标点支持负数
----------------------------------------------------------------*/
void OLED_Draw_Bitmap(int16_t x0,int16_t y0,uint8_t sizex,uint8_t sizey,uint8_t BMP[]);

/*--------------------------------------------------------------
  * 名称: OLED_Fill_RBox(int16_t x_min,int16_t y_min, int16_t x_max, int16_t y_max, int8_t r)
  * 传入: (x_min,y_min)起点 (x_max,y_max)终点 r:半径
  * 功能: 填充倒圆角矩形
----------------------------------------------------------------*/
void OLED_Fill_RBox(int16_t x_min,int16_t y_min, int16_t x_max, int16_t y_max, int8_t r);

/*--------------------------------------------------------------
  * 名称: OLED_Draw_RBox(int16_t x_min,int16_t y_min, int16_t x_max, int16_t y_max)
  * 传入: (x_min,y_min)起点 (x_max,y_max)终点
  * 功能: 绘制镂空矩形
----------------------------------------------------------------*/
void OLED_Draw_RBox(int16_t x_min,int16_t y_min, int16_t x_max, int16_t y_max, uint8_t r);

/*--------------------------------------------------------------
  * 名称: OLED_Draw_Ascii(int16_t x,int16_t y,uint8_t chr)
  * 传入: (x,y)左上角坐标 char:字符
  * 功能: 绘制一个Ascii字符
----------------------------------------------------------------*/
void OLED_Draw_Ascii(int16_t x,int16_t y,uint8_t chr);

/*--------------------------------------------------------------
  * 名称: void OLED_Draw_int32(int16_t x,int16_t y,int16_t num)//写数字,自动长度,32位带符号
  * 传入: (x,y)左上角坐标 num带符号16位数字
  * 功能: 根据输入的num数字用对应的"ASCII字库"绘制到屏幕对应坐标上
----------------------------------------------------------------*/
void OLED_Draw_int32(int16_t x,int16_t y,int16_t num);

/*--------------------------------------------------------------
  * 名称: void OLED_Draw_Unicode(int16_t x,int16_t y,unicode_t unicode_id)
  * 传入: (x,y)左上角坐标 unicode_id
  * 功能: 根据输入的unicode_id寻找对应的"裁剪字库"绘制到屏幕坐标上
----------------------------------------------------------------*/
void OLED_Draw_Unicode(int16_t x,int16_t y,unicode_t unicode_id);

/*--------------------------------------------------------------
  * 名称: OLED_Draw_UTF8_String(int16_t x,int16_t y,uint8_t *p)
  * 传入: (x,y)左上角坐标 *p字符串指针
  * 功能: 在指定坐标上按照系统设定字体格式绘制字符串
----------------------------------------------------------------*/
void OLED_Draw_UTF8_String(int16_t x,int16_t y,uint8_t *p);
	
/*--------------------------------------------------------------
  * 名称: uint16_t OLED_Get_UTF8_XLen(uint8_t *p)
  * 传入: *p字符串指针
  * 功能: 返回字符串在系统字体上x方向的总像素长度
----------------------------------------------------------------*/
uint16_t OLED_Get_UTF8_XLen(uint8_t *p);

/*--------------------------------------------------------------
  * 名称: OLED_Get_UTF8_YLine(int16_t x,int16_t y,uint8_t chr)
  * 传入: *p字符串指针
  * 功能: 返回UTF8字符串换行的次数
----------------------------------------------------------------*/
uint16_t OLED_Get_UTF8_YLine(uint8_t *p);

/*--------------------------------------------------------------
  * 名称: OLED_Fill_value_GRAM(uint8_t value)
  * 功能: 将value值依次完整填充到显存LCD_GRAM
----------------------------------------------------------------*/
void OLED_Fill_value_GRAM(uint8_t value);

/*--------------------------------------------------------------
  * 名称: OLED_Clear_GRAM()
  * 功能: 清屏
----------------------------------------------------------------*/
void OLED_Clear_GRAM(void);

/*--------------------------------------------------------------
  * 名称: lcd_driver_Init()
  * 功能: 驱动初始化
----------------------------------------------------------------*/
void lcd_driver_Init(void);



//---------驱动结构体---------
extern lcd_driver_t lcd_driver;


#endif

