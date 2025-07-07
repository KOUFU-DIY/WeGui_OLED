#include "lcd_Wegui_Config.h"

#if(LCD_PORT == _DMA_4SPI)


#include "stm32f103_lcd_dma_4spi_port.h"
#include "lcd_driver.h"
#include "stdint.h"


#define OLED_SPIx                   SPI1
#define OLED_DMAx                   DMA1
#define OLED_DMA_CHANNELx           DMA1_Channel3 //OLED_SPIx_TX
#define OLED_DMA_COMPLETE_FLAG      DMA1_FLAG_TC3
#define OLED_DMA_PeripheralBaseAddr (&SPI1->DR)
#define RCC_APB2Periph_SPIx          RCC_APB2Periph_SPI1


volatile lcd_dma_step_t  DMA_State = DMA_FREE;
uint8_t DMA_reflash_step=0;




///*--------------------------------------------------------------
//  * 名称: LCD_is_Busy()
//  * 返回: 0:DMA空闲 1:DMA忙碌
//  * 功能: 
//  * 说明: 
//----------------------------------------------------------------*/
//uint8_t LCD_is_Busy()
//{
//	return DMA_State;
//}



#if defined (LCD_USE_NORMAL_OLED) || defined (LCD_USE_GRAY_OLED)
//-------------------------------------------以下是OLED屏幕专用驱动接口----------------------------------------------


/*--------------------------------------------------------------
  * 名称: LCD_Port_Init()
  * 传入: 无
  * 返回: 无
  * 功能: 屏幕接口初始化
  * 说明: 
----------------------------------------------------------------*/
void LCD_Port_Init(void)
{
	//OELD SPI SCL默认常高,第二个跳变数据沿有效
	SPI_InitTypeDef SPI_InitStructure;
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_x;//分频(最快:SPI_BaudRatePrescaler_2)
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPIx, ENABLE);
	RCC_PCLK2Config(RCC_HCLK_Divx);//分频RCC_HCLK_Div1 RCC_HCLK_Div2 RCC_HCLK_Div4...
	
	SPI_Init(OLED_SPIx, &SPI_InitStructure);
	
	
	DMA_InitTypeDef DMA_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)OLED_DMA_PeripheralBaseAddr;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)lcd_driver.LCD_GRAM;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_DeInit(DMA1_Channel6);
  DMA_Init(OLED_DMA_CHANNELx, &DMA_InitStructure);
	


	SPI_I2S_DMACmd(OLED_SPIx,SPI_I2S_DMAReq_Tx,ENABLE);
	
	SPI_Cmd(OLED_SPIx, ENABLE);
	
	DMA_ITConfig(OLED_DMA_CHANNELx, DMA_IT_TC, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
	
	#if (LCD_MODE == _FULL_BUFF_DYNA_UPDATE)
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);//DMA暂不支持动态刷新 无需CRC
	#endif
	
	LCD_SCL_IO_Init();
	LCD_SDA_IO_Init();
	LCD_RES_IO_Init();
	LCD_DC_IO_Init();
	LCD_CS_IO_Init();
	
	DMA_State=DMA_FREE;
	
	LCD_RES_Clr();
	{
		volatile unsigned int i=10000;
		while(i--);
	}
	LCD_RES_Set();
}


/*--------------------------------------------------------------
  * 名称: LCD_delay_ms(volatile uint32_t ms)
  * 传入1: ms
  * 返回: 无
  * 功能: 软件延时
  * 说明: 非精准
----------------------------------------------------------------*/
void LCD_delay_ms(volatile uint32_t ms)
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
  * 名称: LCD_Send_1Cmd(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: 向屏幕发送1个命令(DC=0时发1字节spi)
  * 说明: 
----------------------------------------------------------------*/
void LCD_Send_1Cmd(uint8_t dat)
{
	while(DMA_State!=DMA_FREE){;}
	while(1)
	{
		if((OLED_SPIx->SR & SPI_I2S_FLAG_BSY) == (uint16_t)RESET)
		{
			break;
		}
	};
		
	LCD_DC_Clr();
	LCD_CS_Clr();
	{
		//方式1,调库发送
		//while((OLED_SPIx->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
		//SPI_I2S_SendData(OLED_SPIx, dat);
		
		//方式2,寄存器操作发送
		while((OLED_SPIx->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
		OLED_SPIx->DR = dat;
	}
	while((OLED_SPIx->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
	while((OLED_SPIx->SR & SPI_I2S_FLAG_BSY) != (uint16_t)RESET);
	LCD_CS_Set();
}

/*--------------------------------------------------------------
  * 名称: LCD_Send_1Dat(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: 向屏幕发送1个数据(DC=1时发1字节spi)
  * 说明: 
----------------------------------------------------------------*/
void LCD_Send_1Dat(uint8_t dat)
{
	while(DMA_State!=DMA_FREE){;}
	while((OLED_SPIx->SR & SPI_I2S_FLAG_BSY) != (uint16_t)RESET);
	LCD_DC_Set();
	LCD_CS_Clr();
	{
		//方式1,调库发送
		//SPI_I2S_SendData(OLED_SPIx, dat);
		
		//方式2,寄存器操作发送
		OLED_SPIx->DR = dat;
	}
	while((OLED_SPIx->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
	while((OLED_SPIx->SR & SPI_I2S_FLAG_BSY) != (uint16_t)RESET);
	LCD_CS_Set();
}

/*--------------------------------------------------------------
  * 名称: LCD_Send_nDat(uint8_t *p,uint16_t num)
  * 传入1: *p数组指针
  * 传入2: num发送数量
  * 返回: 无
  * 功能: 向屏幕发送num个数据
  * 说明: 
----------------------------------------------------------------*/
void LCD_Send_nDat(uint8_t *p,uint16_t num)
{
	while((OLED_SPIx->SR & SPI_I2S_FLAG_BSY) != (uint16_t)RESET);
	LCD_DC_Set();
	LCD_CS_Clr();
	
	OLED_DMA_CHANNELx->CMAR = (uint32_t)p;
	OLED_DMA_CHANNELx->CNDTR = (uint32_t)num; 
	DMA_Cmd(OLED_DMA_CHANNELx, ENABLE);
}

/*--------------------------------------------------------------
  * 名称: LCD_Send_nCmd(uint8_t *p,uint16_t num)
  * 传入1: *p数组指针
  * 传入2: num发送数量
  * 返回: 无
  * 功能: 向屏幕发送num个命令
  * 说明: 
----------------------------------------------------------------*/
void LCD_Send_nCmd(uint8_t *p,uint16_t num)
{
	static uint8_t DMA_INT_Buff[4];//最多设置4个命令
	uint8_t i=0;
	while(i<num)
	{
		DMA_INT_Buff[i] = p[i];
		i++;
	}
	while((OLED_SPIx->SR & SPI_I2S_FLAG_BSY) != (uint16_t)RESET);
	LCD_DC_Clr();
	LCD_CS_Clr();

	OLED_DMA_CHANNELx->CMAR = (uint32_t)DMA_INT_Buff;
	OLED_DMA_CHANNELx->CNDTR = (uint32_t)num; 
	DMA_Cmd(OLED_DMA_CHANNELx, ENABLE);
}
#endif












/*--------------------------------------------------------------
  * 名称: LCD_Refresh(void)
  * 功能: 驱动接口,将显存LCD_GRAM全部内容发送至屏幕
----------------------------------------------------------------*/
/*--------------------------------------------------------------
  * 名称: DMA1_Channel3_IRQHandler(void)
  * 功能: DMA中断接口
----------------------------------------------------------------*/

//----------------------------普通OLED屏幕刷屏接口-------------------------------------
#if defined (LCD_USE_NORMAL_OLED)

#if (LCD_MODE == _FULL_BUFF_FULL_UPDATE)
//---------方式1:全屏刷新----------
//--优点:全屏刷新
//--缺点:内容不变的区域也参与了刷新
uint8_t LCD_Refresh(void)
{
	while(DMA_State != DMA_FREE){;}
	DMA_reflash_step = 0;
	DMA_State = DMA_REFLASH_DAT;
	LCD_Set_Addr(0,0);//发送DMA 激活DMA
	//DMA中断里执行余下指令
	return 0;
}
void DMA1_Channel3_IRQHandler()
{
		DMA_Cmd(OLED_DMA_CHANNELx, DISABLE);
		DMA_ClearFlag(OLED_DMA_COMPLETE_FLAG);
	
		//等待SPI发完(DMA完毕不代表SPI完毕)
		while((OLED_SPIx->SR & SPI_I2S_FLAG_BSY) != (uint16_t)RESET){;}
		LCD_CS_Set();
	
		switch(DMA_State)
		{
			case DMA_FREE:break;
			case DMA_NORMAL_CMD:
			{
				DMA_State = DMA_FREE;
				LCD_CS_Set();
			}break;
			case DMA_REFLASH_CMD:
			{
				LCD_Set_Addr(0,DMA_reflash_step);
				DMA_State = DMA_REFLASH_DAT;
			}break;
			case DMA_REFLASH_DAT:
			{
				LCD_Send_nDat(&lcd_driver.LCD_GRAM[DMA_reflash_step++][0],SCREEN_WIDTH);
				DMA_State = DMA_REFLASH_CMD;
				if(DMA_reflash_step >= GRAM_YPAGE_NUM)
				{
					DMA_reflash_step = 0;
					DMA_State = DMA_DONE;
				}
			}break;
			case DMA_DONE:
			{
				LCD_CS_Set();
				DMA_reflash_step = 0;
				DMA_State = DMA_FREE;
			}
		}
}

#elif (LCD_MODE == _FULL_BUFF_DYNA_UPDATE)
	//动态刷新不支持dma方式
	#error("DYNA_UPDATE mode not support dma4spi driver yet!")
#elif (LCD_MODE == _PAGE_BUFF_FULL_UPDATE)
	//页刷新不支持dma方式
	#error("PAGE_BUFF mode not support dma4spi driver yet!")
#elif (LCD_MODE == _PAGE_BUFF_DYNA_UPDATE)
	//页刷新不支持dma方式
	#error("PAGE_BUFF mode not support dma4spi driver yet!")
#endif

//----------------------------灰度OLED屏幕刷屏接口-------------------------------------
#elif defined (LCD_USE_GRAY_OLED)//灰度OLED
	//灰度OLED屏不支持dma4spi方式驱动 请更改屏幕驱动方式
	#error ("Gray OLED not support dma4spi driver yet!Use 4spi_driver please!")

//----------------------------RGB565屏幕刷屏接口-------------------------------------
#elif defined (LCD_USE_RGB565)
	//彩屏TFT屏不支持dma4spi方式驱动 请更改屏幕驱动方式
	#error ("TFT not support dma4spi driver yet!");
#else
	#error ("Not support LCD!");
#endif



#endif
