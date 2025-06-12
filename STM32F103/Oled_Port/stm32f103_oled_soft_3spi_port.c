#include "oled_wegui_Config.h"

#ifdef OLED_USE_SOFT_3SPI


#include "stm32f103_oled_soft_3spi_port.h"
#include "stdint.h"





/*--------------------------------------------------------------
  * 名称: OLED_delay_ms(volatile uint32_t ms)
  * 传入1: ms
  * 返回: 无
  * 功能: 软件延时
  * 说明: 非精准
----------------------------------------------------------------*/
void OLED_delay_ms(volatile uint32_t ms)
{
	//delay_ms(ms);
	
		volatile uint16_t i;
		while (ms--) 
		{
			i = 10000; //根据实际情况调整
			while (i--);
		}
}

/*--------------------------------------------------------------
  * 名称: SPI_send_8bitByte(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: SPI发送1个字节数据
  * 说明: 
----------------------------------------------------------------*/
static void SPI_send_8bitByte(uint8_t dat)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{			  
		OLED_SCL_Clr();
		if(dat&0x80)
		   OLED_SDA_Set();
		else 
		   OLED_SDA_Clr();
		dat<<=1; 
		OLED_SCL_Set();
	}		  
}

/*--------------------------------------------------------------
  * 名称: OLED_send_1Cmd(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: 向屏幕发送1个命令(DC=0时发1字节spi)
  * 说明: 
----------------------------------------------------------------*/
void OLED_send_1Cmd(uint8_t dat)
{
	OLED_CS_Clr();
	OLED_SCL_Clr();
	OLED_SDA_Clr();
	OLED_SCL_Set();
	SPI_send_8bitByte(dat);
	OLED_CS_Set();
}
/*--------------------------------------------------------------
  * 名称: OLED_send_1Data(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: 向屏幕发送1个数据(DC=1时发1字节spi)
  * 说明: 
----------------------------------------------------------------*/
void OLED_send_1Data(uint8_t dat)
{
	OLED_CS_Clr();
	OLED_SCL_Clr();
	OLED_SDA_Set();
	OLED_SCL_Set();
	SPI_send_8bitByte(dat);
	OLED_CS_Set();
}

/*--------------------------------------------------------------
  * 名称: OLED_send_numData(uint8_t dat)
  * 传入1: *p数组指针
  * 传入2: num发送数量
  * 返回: 无
  * 功能: 向屏幕发送num个数据
  * 说明: 
----------------------------------------------------------------*/
void OLED_send_numData(uint8_t *p,uint8_t num)
{
	uint8_t i=0;
	OLED_CS_Clr();

	while(num>i)
	{
		OLED_SCL_Clr();
		OLED_SDA_Set();
		OLED_SCL_Set();
		SPI_send_8bitByte(p[i++]);	  
	}
	OLED_CS_Set();
}

/*--------------------------------------------------------------
  * 名称: OLED_send_numCmd(uint8_t dat)
  * 传入1: *p数组指针
  * 传入2: num发送数量
  * 返回: 无
  * 功能: 向屏幕发送num个命令
  * 说明: 
----------------------------------------------------------------*/
void OLED_send_numCmd(uint8_t *p,uint8_t num)
{
	uint8_t i=0;
	OLED_CS_Clr();
	while(num>i)
	{
		OLED_SCL_Clr();
		OLED_SDA_Clr();
		OLED_SCL_Set();
		SPI_send_8bitByte(p[i++]);	  
	}
	OLED_CS_Set();
}


/*--------------------------------------------------------------
  * 名称: OLED_port_Init()
  * 传入: 无
  * 返回: 无
  * 功能: 屏幕接口初始化
  * 说明: 
----------------------------------------------------------------*/
void OLED_port_Init(void)
{
	OLED_SCL_IO_Init();
	OLED_SDA_IO_Init();
	OLED_RES_IO_Init();
	OLED_CS_IO_Init();
	//OLED_DC_IO_Init();//3SPI无需DC接口
	
	OLED_RES_Clr();
	{
		volatile unsigned int i=10000;
		while(i--);
	}
	OLED_RES_Set();

}

#endif