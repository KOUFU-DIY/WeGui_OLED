#ifndef OLED_WEGUI_CONFIG_H
#define OLED_WEGUI_CONFIG_H


/*--------------------------------------------------------------
  * WeGUI : V0.1beta
  * Author: KOUFU
	* https://space.bilibili.com/526926544
----------------------------------------------------------------*/



/*--------------------------------------------------------------
	* 暂不支持使用ARMV6编译,请使用ARMV5编译器(默认)
	* 若keil版本过高,请自行安装v5版本编译器
	* 本程序使用了大量的"UTF8"支持多国语言的编码
	* 需要进行两步设置
	* 1.Edit->Configuration->Encoding->"Encod in UTF8"
	* 2.Project -> Oprions for Target-> C/C++ -> 
	* Misc Contiols -> 填入"--locale=english"
----------------------------------------------------------------*/
//提示: 
//IIC相关功能暂不支持使用ARMV6编译,请使用ARMV5编译器!!
//该芯片IIC存在"缺陷",其怪点暂未解决,暂未适配其DMA驱动方式, 推荐使用软件IIC方式!!
//该工程支持"全屏刷新"和"动态刷新"两种刷屏方式(DMA方式强制使用全屏刷新)
//"动态刷新"以牺牲一些全屏刷新速度换取普通刷新的速度, 但同时在屏幕静止时, cpu占用极低
//刷新方式可搜索OLED_Refresh()函数自行调整切换
//默认开启右下角调试状态显示,若要关闭,查找注释掉调用的wegui_update_info(fps_time_count);
//IIC硬件在一次通讯失败后,将拖慢系统运行,暂未解决, 推荐使用软件IIC方式!!
//SPI默认使用8分频,需要更快的速度到指定驱动port文件里修改,查找SPI_BaudRatePrescaler并修改
//软件IIC默认使用适中的延迟速率,需要更快的刷新速度,需要到对应port文件里修改, 查找I2C_SCL_Rise_Delay等并进行修改延迟值
//使用模拟IIC可精确控制上升和下降时间,调整合适的延迟时间,刷新率可以比硬件IIC更快
//测试1:软件IIC刷"中景园128X160",刷128x64区域,150Hz刷新率!
//测试2:硬件IIC刷"中景园128X160",刷128x64区域,仅40Hz刷新率!本版本因此更推荐软件IIC!
//字库在oled_res,可自行使用配套工具修改裁剪多国语言字库,随后会更新视频教程
//按键接口在stm32f103_wegui_port.h里
/*------------------------------------------------------------------------------------
	* ----默认驱动接口----        ---默认按键接口---          外接ADC电位器接口 A1
	* |--SPI--|  |--IIC--|       |OK   | A0  |确定|         (用于DEMO外部数据演示)
	* |CS   A6|  |SDA B11|       |BACK | C15 |返回|    
	* |DC  B11|  |SCL B10|       |UP   | B13 | 上 |    
	* |RES B10|  |3V3 3V3|       |DOWN | B14 | 下 |    
	* |SDA  A7|  |GND GND|       |LEFT | B15 | 左 |    
	* |SCL  A5|                  |RIGHT| B12 | 右 |    
	* |3V3 3V3|                                       
	* |GND GND|               
-------------------------------------------------------------------------------------*/






//-------------------------1.选择一个屏幕通讯接口-----------------------------

//#define OLED_USE_SOFT_3SPI //软件三线SPI驱动   对应文件stm32f103_oled_soft_3spi_port.c
//#define OLED_USE_SOFT_4SPI //软件四线SPI驱动   对应文件stm32f103_oled_soft_4spi_port.c
//#define OLED_USE_HARD_4SPI //硬件四线SPI驱动   对应文件stm32f103_oled_hard_4spi_port.c
//#define OLED_USE_DMA_4SPI  //硬件四线SPI驱动   对应文件stm32f103_oled_dma_4spi_port.c
#define OLED_USE_SOFT_IIC  //软件IIC驱动(推荐) 对应文件stm32f103_oled_hard_iic_port.c 
//#define OLED_USE_HARD_IIC  //硬件IIC驱动       对应文件stm32f103_oled_hard_iic_port.c
//#define OLED_USE_DMA_IIC  //DMA_IIC驱动        存在公认死锁问题,暂未适配


//---------------------------1.1设定屏幕IIC地址--------------------------------

#if defined(OLED_USE_HARD_IIC) || defined(OLED_USE_SOFT_IIC) || defined(OLED_USE_DMA_IIC)
	//一般选择:0x3D/0x3C 
	//7位0x3C => 8位0x78 (大部分默认)
	//7位0x3D => 8位0x7A
	#define OLED_IIC_7ADDR 0x3C 
#endif 


//----------------------------2.设定屏幕分辨率--------------------------------
#define SCREEN_WIDTH 128
#define SCREEN_HIGH  64


//-----------------------3.设定屏幕区域与驱动IC的偏移--------------------------
#define SCREEN_X_OFFSET     0 //x左右方向有偏移时候修改 (优先修改驱动初始化)
#define SCREEN_Y_OFFSET     0 //一般不修改 (值需能被8整除)



//----------------------------4.选择屏幕驱动IC--------------------------------
#define _SH1106  (0)
#define _SH1108  (1)
#define _SH1115  (2)
#define _SSD1306 (3) 
#define _SSD1315 (4)
//#define _SSD1327 //暂不支持灰度OLED芯片
//#define _ST7789  //暂不支持彩屏TFT芯片

#define LCD_IC _SSD1306












  
 

//------------编译-----------
#include "stm32f103_wegui_port.h"


#if defined OLED_USE_SOFT_3SPI    //软件三线SPI 
	#include "stm32f103_oled_soft_3spi_port.h"
#elif defined OLED_USE_SOFT_4SPI //软件四线SPI 
	#include "stm32f103_oled_soft_4spi_port.h"
#elif defined OLED_USE_HARD_4SPI //硬件四线SPI 
	#include "stm32f103_oled_hard_4spi_port.h"
#elif defined OLED_USE_DMA_4SPI //DMA四线SPI 
	#include "stm32f103_oled_dma_4spi_port.h"
#elif defined OLED_USE_SOFT_IIC  //软件IIC   
	#include "stm32f103_oled_soft_iic_port.h"
#elif defined OLED_USE_HARD_IIC  //硬件IIC    
	#include "stm32f103_oled_hard_iic_port.h"
#elif defined OLED_USE_DMA_IIC  //DMA_IIC驱动
	//#include "stm32f103_oled_dma_iic_port.h"
	#error ("stm32f103 dma iic driver is not supported!")
#endif


#if (LCD_IC == _SH1106)
	#include "sh1106.h"
	#define OLED_IC_Init() do{SH1106_Init();}while(0)
	#define IC_Set_Address_x(x) do{SH1106_Set_Address_x(x+SCREEN_X_OFFSET);}while(0)
	#define IC_Set_Address_ypage(page) do{SH1106_Set_Address_ypage(page+SCREEN_Y_OFFSET/8);}while(0)
	#define IC_Set_Address_x_ypage(x,page) do{SH1106_Set_Address_x_ypage((x+SCREEN_X_OFFSET),(page+SCREEN_Y_OFFSET/8));}while(0)
	#define IC_Set_Bright(x) do{SH1106_Set_Contrast(x);}while(0)
#elif (LCD_IC == _SH1108)
	#include "sh1108.h"
	#define OLED_IC_Init() do{SH1108_Init();}while(0)
	#define IC_Set_Address_x(x) do{SH1108_Set_Address_x(x+SCREEN_X_OFFSET);}while(0)
	#define IC_Set_Address_ypage(page) do{SH1108_Set_Address_ypage(page+SCREEN_Y_OFFSET/8);}while(0)
	#define IC_Set_Address_x_ypage(x,page) do{SH1108_Set_Address_x_ypage((x+SCREEN_X_OFFSET),(page+SCREEN_Y_OFFSET/8));}while(0)
	#define IC_Set_Bright(x) do{SH1108_Set_Contrast(x);}while(0)
#elif (LCD_IC == _SSD1306)
	#include "ssd1306.h"
	#define OLED_IC_Init() do{SSD1306_Init();}while(0)
	#define IC_Set_Address_x(x) do{SSD1306_Set_Address_x(x+SCREEN_X_OFFSET);}while(0)
	#define IC_Set_Address_ypage(page) do{SSD1306_Set_Address_ypage(page+SCREEN_Y_OFFSET/8);}while(0)
	#define IC_Set_Address_x_ypage(x,page) do{SSD1306_Set_Address_x_ypage((x+SCREEN_X_OFFSET),(page+SCREEN_Y_OFFSET/8));}while(0)
	#define IC_Set_Bright(x) do{OLED_send_1Cmd(0x81);OLED_send_1Cmd(x);}while(0)
#elif (LCD_IC == _SSD1315)
	#include "ssd1315.h"
	#define OLED_IC_Init() do{SSD1315_Init();}while(0)
	#define IC_Set_Address_x(x) do{SSD1315_Set_Address_x(x+SCREEN_X_OFFSET);}while(0)
	#define IC_Set_Address_ypage(page) do{SSD1315_Set_Address_ypage(page+SCREEN_Y_OFFSET/8);}while(0)
	#define IC_Set_Address_x_ypage(x,page) do{SSD1315_Set_Address_x_ypage((x+SCREEN_X_OFFSET),(page+SCREEN_Y_OFFSET/8));}while(0)
	#define IC_Set_Bright(x) do{SSD1315_Set_Contrast_Control(x);}while(0)
#elif (LCD_IC == _SH1115)
	#include "sh1115.h"
	#define OLED_IC_Init() do{SH1115_Init();}while(0)
	#define IC_Set_Address_x(x) do{SH1115_Set_Address_x(x+SCREEN_X_OFFSET);}while(0)
	#define IC_Set_Address_ypage(page) do{SH1115_Set_Address_ypage(page+SCREEN_Y_OFFSET/8);}while(0)
	#define IC_Set_Address_x_ypage(x,page) do{SH1115_Set_Address_x_ypage((x+SCREEN_X_OFFSET),(page+SCREEN_Y_OFFSET/8));}while(0)
	#define IC_Set_Bright(x) do{SH1115_The_Contrast_Control_Mode_Set(x);}while(0)
#elif (LCD_IC == _SSD1327)
	//该芯片为多阶灰度芯片,不同于单色点阵OLED,绘制点阵ui更占用资源,wegui暂不支持
	#error("do not support this ic!")
#else
	#warning("No screen ic init!")
#endif



	
#endif
