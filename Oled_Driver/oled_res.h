#ifndef _OLED_WEGUI_RES_H_
#define _OLED_WEGUI_RES_H_


#include "stdint.h"



/*
	UTF8多国语言裁剪字符取模方式:
	1.---------下载取模软件---------
	取模软件FontLab-v1.0.13.2309
	下载地址https://download.csdn.net/download/qq_37749995/90930109
	软件弊端:需要注册登录,但免费
	
	2.------获取unicode_index-------
	(1)选择菜单栏的"字符编码"
	(2)选择输入"文字"
	(3)填写入需要取模的文字,例如"主页游戏时间帧率屏幕刷新"
	(4)取模方式选择"连续",字符编码选择Unicode,点击"查询"
	(5)生成的数组,即为unicode_index的数组
	
	3.---------获取font字库----------
	(1)选择菜单栏的"字库生成器"
	(2)字体样式栏中,选择需要的字体,字号
	(2)字符集栏中,选择"自定义字符",打开"编辑码表"
	(3)输入需要取模的文字,顺序需要与2.相同,例如"主页游戏时间帧率屏幕刷新新",确认
	注意:该取模软件有BUG,最后一个字会遗漏,在此处文字最后补上一个字,如"新"
	(4)排值方式栏中,选择"字节竖置"
	(5)字节方式栏中,选择"低位在前"
	(6)导出字库栏中,选择C文件
	(7)点阵样式栏中,设置取模宽高,和取模位置偏移相关设置
	(8)点击"生成
	(9)生成的数组,即为font字库的数组
	(10)可在生成的字库末尾,找到广告字节并删除
	
	//广告字节:
	0xB1,0xBE,0xCE,0xC4,0xBC,0xFE,0xD3,0xC9,    0x46,0x6F,0x6E,0x74,0x4C,0x61,0x62,0x81,
	0x30,0x85,0x33,0xC9,0xFA,0xB3,0xC9,0xA3,    0xAC,0xBD,0xF6,0xD3,0xC3,0xD3,0xDA,0xBC,
	0xBC,0xCA,0xF5,0xCA,0xB5,0xD1,0xE9,0xA3,    0xAC,0xBD,0xFB,0xD6,0xB9,0xC9,0xCC,0xD2,
	0xB5,0xCA,0xB9,0xD3,0xC3,0xA1,0xA3,
*/

/*
	单字大小byte_size计算方式:
	if(high%8==0){byte_size = width * (high / 8);}
	else         {byte_size = width * (high/8+1);}
*/



typedef struct fonts
{
	const unsigned char width;    //宽
	const unsigned char high;     //高
	const unsigned char byte_size;//单字大小
	const unsigned char scape;    //间隔(默认0)
	const unsigned char *unicode_index;   //目录(UTF8查表用)
	const unsigned char *font;    //字库
		
}fonts_t;

extern const fonts_t ascii_SongTi_6X12;
extern const fonts_t ascii_SongTi_8X16;
extern const fonts_t SongTi_UTF8_12X12;
extern const fonts_t SongTi_UTF8_16X16;

#endif
