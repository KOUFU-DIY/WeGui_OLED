#include "oled_wegui_Config.h"

#ifdef OLED_USE_DMA_4SPI


#include "stm32f103_oled_dma_4spi_port.h"
#include "stdint.h"


#define OLED_SPIx                   SPI1
#define OLED_DMAx                   DMA1
#define OLED_DMA_CHANNELx           DMA1_Channel3 //OLED_SPIx_TX
#define OLED_DMA_COMPLETE_FLAG      DMA1_FLAG_TC3
#define OLED_DMA_PeripheralBaseAddr (&SPI1->DR)
#define RCC_Periph                  RCC_APB2Periph_SPI1


oled_dma_step_t  DMA_State = DMA_FREE;
uint8_t DMA_reflash_step=0;


///*--------------------------------------------------------------
//  * 名称: OLED_is_Busy()
//  * 返回: 0:DMA空闲 1:DMA忙碌
//  * 功能: 
//  * 说明: 
//----------------------------------------------------------------*/
//uint8_t OLED_is_Busy()
//{
//	return DMA_State;
//}
/*--------------------------------------------------------------
  * 名称: DMA1_Channel3_IRQHandler()
  * 返回: 无
  * 功能: DMA中断函数
  * 说明: 
----------------------------------------------------------------*/
void DMA1_Channel3_IRQHandler()
{
		DMA_Cmd(OLED_DMA_CHANNELx, DISABLE);
		DMA_ClearFlag(OLED_DMA_COMPLETE_FLAG);
	
		//等待SPI发完(DMA完毕不代表SPI完毕)
		while((OLED_SPIx->SR & SPI_I2S_FLAG_BSY) != (uint16_t)RESET){;}
		OLED_CS_Set();
	
		switch(DMA_State)
		{
			case DMA_FREE:break;
			case DMA_NORMAL_CMD:
			{
				DMA_State = DMA_FREE;
				OLED_CS_Set();
			}break;
			case DMA_REFLASH_CMD:
			{
				IC_Set_Address_x_ypage(0,DMA_reflash_step);
				DMA_State = DMA_REFLASH_DAT;
			}break;
			case DMA_REFLASH_DAT:
			{
				OLED_send_numData(&oled_driver.OLED_GRAM[DMA_reflash_step++][0],SCREEN_WIDTH);
				DMA_State = DMA_REFLASH_CMD;
				if(DMA_reflash_step >= SCREEN_HIGH/8)
				{
					DMA_reflash_step = 0;
					DMA_State = DMA_DONE;
					
				}
			}break;
			case DMA_DONE:
			{
				OLED_CS_Set();
				DMA_reflash_step = 0;
				DMA_State = DMA_FREE;
			}
		}
}




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
  * 名称: OLED_send_1Cmd(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: 向屏幕发送1个命令(DC=0时发1字节spi)
  * 说明: 
----------------------------------------------------------------*/
void OLED_send_1Cmd(uint8_t dat)
{
	while(DMA_State!=DMA_FREE){;}
	while(1)
	{
		if((OLED_SPIx->SR & SPI_I2S_FLAG_BSY) == (uint16_t)RESET)
		{
			break;
		}
	};
		
	OLED_DC_Clr();
	OLED_CS_Clr();
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
	while(DMA_State!=DMA_FREE){;}
	while((OLED_SPIx->SR & SPI_I2S_FLAG_BSY) != (uint16_t)RESET);
	OLED_DC_Set();
	OLED_CS_Clr();
	{
		//方式1,调库发送
		//SPI_I2S_SendData(OLED_SPIx, dat);
		
		//方式2,寄存器操作发送
		OLED_SPIx->DR = dat;
	}
	while((OLED_SPIx->SR & SPI_I2S_FLAG_TXE) == (uint16_t)RESET);
	while((OLED_SPIx->SR & SPI_I2S_FLAG_BSY) != (uint16_t)RESET);
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
	while((OLED_SPIx->SR & SPI_I2S_FLAG_BSY) != (uint16_t)RESET);
	OLED_DC_Set();
	OLED_CS_Clr();
	
	OLED_DMA_CHANNELx->CMAR = (uint32_t)p;
	OLED_DMA_CHANNELx->CNDTR = (uint32_t)num; 
	DMA_Cmd(OLED_DMA_CHANNELx, ENABLE);
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
	static uint8_t DMA_INT_Buff[4];//最多设置4个命令
	uint8_t i=0;
	while(i<num)
	{
		DMA_INT_Buff[i] = p[i];
		i++;
	}
	while((OLED_SPIx->SR & SPI_I2S_FLAG_BSY) != (uint16_t)RESET);
	OLED_DC_Clr();
	OLED_CS_Clr();

	OLED_DMA_CHANNELx->CMAR = (uint32_t)DMA_INT_Buff;
	OLED_DMA_CHANNELx->CNDTR = (uint32_t)num; 
	DMA_Cmd(OLED_DMA_CHANNELx, ENABLE);
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

	RCC_APB2PeriphClockCmd(RCC_Periph, ENABLE);
	RCC_PCLK2Config(RCC_HCLK_Div2);//分频RCC_HCLK_Div1 RCC_HCLK_Div2 RCC_HCLK_Div4...
	
	SPI_Init(OLED_SPIx, &SPI_InitStructure);
	
	
	DMA_InitTypeDef DMA_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)OLED_DMA_PeripheralBaseAddr;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)oled_driver.OLED_GRAM;
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
	
	OLED_SCL_IO_Init();
	OLED_SDA_IO_Init();
	OLED_RES_IO_Init();
	OLED_DC_IO_Init();
	OLED_CS_IO_Init();
	

	DMA_State=DMA_FREE;
	
	OLED_RES_Clr();
	{
		volatile unsigned int i=10000;
		while(i--);
	}
	OLED_RES_Set();
		
	
}

#endif