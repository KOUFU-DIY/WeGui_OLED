#ifndef _OLED_DRIVER_H_
#define _OLED_DRIVER_H_

#include "stdint.h"
#include "oled_wegui_Config.h"
#include "oled_res.h"






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

typedef enum oled_driver_mode//驱动模式
{
	write_0,				    //全屏写0显示
	write_1,				    //全屏写1显示
	write_inverse,	    //全屏反转写入
	write_0_inBox ,			//限制区域内写0(高级)
	write_1_inBox ,			//限制区域内写1(高级)
	write_inverse_inBox,//限制区域内反转(高级)
}oled_driver_mode_t;

typedef struct oled_boxDriver//高级驱动参数
{
	uint8_t x_min;   //限制矩形x最小值
	uint8_t x_max;   //限制矩形x最大值
	uint8_t ypage_min;//限制矩形ypage最小值
	uint8_t ypage_max;//限制矩形ypage最大值
	uint8_t ypage_min_temp;//最小ypage允许写入的像素点映射(储存计算结果,用于快速运行)
	uint8_t ypage_max_temp;//最大ypage允许写入的像素点映射(储存计算结果,用于快速运行)
}OledBoxDriver_t;

typedef struct oled_driver
{
	//----------显存----------
	uint8_t OLED_GRAM[SCREEN_HIGH/8][SCREEN_WIDTH];
	//--------绘画驱动--------
	void (*Write_GRAM)(uint16_t x,uint16_t ypage,uint8_t u8_value);//普通写,显示驱动函数
	void (*Clear_GRAM)(uint16_t x,uint16_t ypage,uint8_t u8_value);//普通清,显示驱动函数
	OledBoxDriver_t Box;//高级驱动辅助,限制写入区域
	//----------字体----------
	const fonts_t *fonts_ASCII;   //ASCII字体
	const fonts_t *fonts_UTF8_cut;//UTF8裁剪字体
	uint8_t newline_high;//换行距离
}oled_driver_t;






/*--------------------------------------------------------------
  * 名称: OLED_Refresh(void)
  * 功能: 驱动接口,将显存OLED_GRAM全部内容发送至屏幕
----------------------------------------------------------------*/
void OLED_Refresh(void);

/*--------------------------------------------------------------
  * 名称: OLED_Driver_Write_0(uint16_t x,uint16_t ypage,uint8_t u8_value)
  * 功能: 普通快速驱动函数,将值以清0的方式写入显存
----------------------------------------------------------------*/
void OLED_Driver_Write_0(uint16_t x,uint16_t ypage,uint8_t u8_value);

/*--------------------------------------------------------------
  * 名称: OLED_Driver_Write_1(uint16_t x,uint16_t ypage,uint8_t u8_value)
  * 功能: 普通快速驱动函数,将值以写1的方式写入显存
----------------------------------------------------------------*/
void OLED_Driver_Write_1(uint16_t x,uint16_t ypage,uint8_t u8_value);

/*--------------------------------------------------------------
  * 名称: OLED_Driver_Write_inv(uint16_t x,uint16_t ypage,uint8_t u8_value)
  * 功能: 普通快速驱动函数,将值以"反色"的方式写入显存
----------------------------------------------------------------*/
void OLED_Driver_Write_inv(uint16_t x,uint16_t ypage,uint8_t u8_value);

/*--------------------------------------------------------------
  * 名称: OLED_Driver_Write_0_inBox(uint16_t x,uint16_t ypage,uint8_t u8_value)
  * 功能: 高级驱动函数,在限制区域(Box)内,将值以清0的方式写入到显存
----------------------------------------------------------------*/
void OLED_Driver_Write_0_inBox(uint16_t x,uint16_t ypage,uint8_t u8_value);

/*--------------------------------------------------------------
  * 名称: OLED_Driver_Write_1_inBox(uint16_t x,uint16_t ypage,uint8_t u8_value)
  * 功能: 高级驱动函数,在限制区域(Box)内,将值以写1的方式写入到显存
----------------------------------------------------------------*/
void OLED_Driver_Write_1_inBox(uint16_t x,uint16_t ypage,uint8_t u8_value);

/*--------------------------------------------------------------
  * 名称: OLED_Driver_Write_inv_inBox(uint16_t x,uint16_t ypage,uint8_t u8_value)
  * 功能: 高级驱动函数,在限制区域(Box)内,将值以反写的方式写入到显存
----------------------------------------------------------------*/
void OLED_Driver_Write_inv_inBox(uint16_t x,uint16_t ypage,uint8_t u8_value);

/*--------------------------------------------------------------
  * 名称: OLED_Set_Driver_Mode(oled_driver_mode_t mode)
  * 传入: mode 驱动模式
  * 功能: 设置驱动方式
----------------------------------------------------------------*/
void OLED_Set_Driver_Mode(oled_driver_mode_t mode);

/*--------------------------------------------------------------
  * 名称: OLED_Set_Driver_Box(uint8_t x_min ,uint8_t y_min ,uint8_t x_max,uint8_t y_max)
  * 传入: (x_min,y_min)起始点 (x_max,y_max)终点
  * 功能: 设置高级驱动的限制区域(Box)
----------------------------------------------------------------*/
void OLED_Set_Driver_Box(uint8_t x_min ,uint8_t y_min ,uint8_t x_max,uint8_t y_max);

/*--------------------------------------------------------------
  * 名称: OLED_Draw_One_Byte(int16_t x,int16_t y,uint8_t u8_value)
  * 传入1: (x,y)坐标
  * 传入2: u8_page 一字节点阵数据
  * 功能: 将u8_page值以对其坐标的方式写到显存
  * 说明: 坐标点x,y支持负数
----------------------------------------------------------------*/
void OLED_Draw_One_Byte(int16_t x,int16_t y,uint8_t u8_page);

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
  * 功能: 将value值依次完整填充到显存OLED_GRAM
----------------------------------------------------------------*/
void OLED_Fill_value_GRAM(uint8_t value);

/*--------------------------------------------------------------
  * 名称: OLED_Clear_GRAM()
  * 功能: 清屏
----------------------------------------------------------------*/
void OLED_Clear_GRAM(void);

/*--------------------------------------------------------------
  * 名称: OLED_Driver_Init()
  * 功能: 驱动初始化
----------------------------------------------------------------*/
void OLED_Driver_Init(void);



//---------驱动结构体---------
extern oled_driver_t oled_driver;


#endif

