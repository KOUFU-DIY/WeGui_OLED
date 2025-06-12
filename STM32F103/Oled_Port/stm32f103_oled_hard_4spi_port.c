#include "oled_wegui_Config.h"

#ifdef OLED_USE_HARD_4SPI


#include "stm32f103_oled_hard_4spi_port.h"
#include "stdint.h"





/*--------------------------------------------------------------
  * 名称: OLED_delay_ms(uint32_t ms)
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
  * 名称: OLED_send_1Cmd(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: 向屏幕发送1个命令(DC=0时发1字节spi)
  * 说明: 
----------------------------------------------------------------*/
void OLED_send_1Cmd(uint8_t dat)
{
	while((SPI1->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
	OLED_DC_Clr();
	OLED_CS_Clr();
	{
		//方式1,调库发送
		//while((SPI1->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
		//SPI_I2S_SendData(SPI1, dat);
		
		//方式2,寄存器操作发送
		while((SPI1->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
		SPI1->DR = dat;
	}
	while((SPI1->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
	while((SPI1->SR & SPI_I2S_FLAG_BSY) != (uint16_t)RESET);
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
	while((SPI1->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
	OLED_DC_Set();
	OLED_CS_Clr();
	{
		//方式1,调库发送
		//SPI_I2S_SendData(SPI1, dat);
		
		//方式2,寄存器操作发送
		SPI1->DR = dat;
	}
	while((SPI1->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
	while((SPI1->SR & SPI_I2S_FLAG_BSY) != (uint16_t)RESET);
	OLED_CS_Set();
}

/*--------------------------------------------------------------
  * 名称: OLED_send_numData(uint8_t *p,uint16_t num)
  * 传入1: *p数组指针
  * 传入2: num发送数量
  * 返回: 无
  * 功能: 向屏幕发送num个数据
  * 说明: 
----------------------------------------------------------------*/
void OLED_send_numData(uint8_t *p,uint16_t num)
{
	uint8_t i=0;
	while((SPI1->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
	OLED_DC_Set();
	OLED_CS_Clr();
	while(num>i)	  
	{
		//方式1,调库发送
		//SPI_I2S_SendData(SPI1, p[i++]);
		//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == SET);
		
		//方式2,寄存器操作发送
		while((SPI1->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
		SPI1->DR = p[i++];
		
	}
	while((SPI1->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
	while((SPI1->SR & SPI_I2S_FLAG_BSY) != (uint16_t)RESET);
	OLED_CS_Set();
}

/*--------------------------------------------------------------
  * 名称: OLED_send_numCmd(uint8_t *p,uint16_t num)
  * 传入1: *p数组指针
  * 传入2: num发送数量
  * 返回: 无
  * 功能: 向屏幕发送num个命令
  * 说明: 
----------------------------------------------------------------*/
void OLED_send_numCmd(uint8_t *p,uint16_t num)
{
	uint8_t i=0;
	OLED_DC_Clr();
	OLED_CS_Clr();
	while(num>i)	  
	{
		//方式1,调库发送
		//SPI_I2S_SendData(SPI1, p[i++]);
		//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == SET);
		
		//方式2,寄存器操作发送
		while((SPI1->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
		SPI1->DR = p[i++];
		
	}
	while((SPI1->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
	while((SPI1->SR & SPI_I2S_FLAG_BSY) != (uint16_t)RESET);
	OLED_CS_Set();
}

/*--------------------------------------------------------------
  * 名称: OLED_Set_Address_x_ypage(uint8_t page)
  * 传入: x,page
  * 返回: 无
  * 功能: 向屏幕设置x和ypage的光标位置
  * 说明: 
----------------------------------------------------------------*/
void OLED_Set_Address_x_ypage(uint8_t x,uint8_t page)
{
	IC_Set_Address_x_ypage(x , page + SCREEN_Y_OFFSET/8);
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
	SPI_InitTypeDef SPI_InitStructure;
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;//分频(最快:SPI_BaudRatePrescaler_2)
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_PCLK2Config(RCC_HCLK_Div2);//分频RCC_HCLK_Div1 RCC_HCLK_Div2 RCC_HCLK_Div4...
	
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
	
	
	
	OLED_SCL_IO_Init();
	OLED_SDA_IO_Init();
	OLED_RES_IO_Init();
	OLED_DC_IO_Init();
	OLED_CS_IO_Init();
	

	
	OLED_RES_Clr();
	{
		volatile unsigned int i=10000;
		while(i--);
	}
	OLED_RES_Set();

}

#endif