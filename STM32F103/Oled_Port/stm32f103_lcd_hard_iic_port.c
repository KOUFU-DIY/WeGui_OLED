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

#include "lcd_wegui_Config.h"

#if (LCD_PORT == _HARD_IIC)

#include "stdint.h"
#include "stm32f103_lcd_hard_iic_port.h"
#include "lcd_driver.h"





/*--------------------------------------------------------------
  * IIC基础接口驱动
----------------------------------------------------------------*/
#define LCD_HARD_IIC_TIMEOUT_UINT8 255 //硬件IIC超时退出时间


//I2C起始信号
#define LCD_I2C_Start()  do                                    \
{	                                                              \
	Timeout = LCD_HARD_IIC_TIMEOUT_UINT8;                        \
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY))                 \
	{                                                             \
		if((Timeout--) == 0) break;                                 \
	}                                                             \
	I2C_GenerateSTART(I2C2, ENABLE);                              \
	Timeout = LCD_HARD_IIC_TIMEOUT_UINT8;                        \
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))    \
	{                                                             \
		if((Timeout--) == 0) break;                                 \
	}                                                             \
}while(0)

//I2C结束信号
#define LCD_I2C_Stop() do                                         \
{                                                                  \
	Timeout = LCD_HARD_IIC_TIMEOUT_UINT8;                  \
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))  \
	{                                                                \
		if((Timeout--) == 0) break;                                    \
	}                                                                \
	I2C_GenerateSTOP(I2C2, ENABLE);                                  \
}while(0)



//I2C发送地址
#define LCD_I2C_SendAddr(addr) do                                          \
{                                                                           \
	Timeout = LCD_HARD_IIC_TIMEOUT_UINT8;                                    \
	I2C_Send7bitAddress(I2C2, addr, I2C_Direction_Transmitter);               \
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))  \
	{                                                                         \
		if((Timeout--) == 0) break;                                             \
	}                                                                         \
}while(0)


//I2C发送1字节数据
#define LCD_I2C_send_1Byte(dat)  do                                       \
{                                                                          \
	Timeout = LCD_HARD_IIC_TIMEOUT_UINT8;                                   \
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING)) \
	{                                                                        \
		if((Timeout--) == 0) break;                                            \
	}                                                                        \
	I2C_SendData(I2C2, dat);                                                 \
}while(0)



/*--------------------------------------------------------------
  * 名称: LCD_Send_1Cmd(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: 向屏幕发送1个命令
  * 说明: 
----------------------------------------------------------------*/
void LCD_Send_1Cmd(uint8_t dat)
{
	uint16_t Timeout;
	//------------起始信号------------
	LCD_I2C_Start();
	//------------发送地址------------	
	LCD_I2C_SendAddr(OLED_IIC_7ADDR<<1);
	//------------发送数据------------
	LCD_I2C_send_1Byte(0x00);              
	LCD_I2C_send_1Byte(dat);
	//------------结束信号------------                                                           
	LCD_I2C_Stop();  
}

/*--------------------------------------------------------------
  * 名称: LCD_Send_1Dat(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: 向屏幕发送1个数据
  * 说明: 
----------------------------------------------------------------*/
void LCD_Send_1Dat(uint8_t dat)
{
	volatile uint16_t Timeout;
	//------------起始信号------------
	LCD_I2C_Start();
	//------------发送地址------------	
	LCD_I2C_SendAddr(OLED_IIC_7ADDR<<1);
	//------------发送数据------------
	LCD_I2C_send_1Byte(0x40);              
	LCD_I2C_send_1Byte(dat);
	//------------结束信号------------                                                           
	LCD_I2C_Stop();  
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
	uint16_t Timeout;
	uint16_t i;
	
	//------------起始信号------------
	LCD_I2C_Start();
	//------------发送地址------------	
	LCD_I2C_SendAddr(OLED_IIC_7ADDR<<1);
	//------------发送1+n个数据------------
	I2C_SendData(I2C2, 0x40);
	i=0;
	while(num>i)
	{
		Timeout = LCD_HARD_IIC_TIMEOUT_UINT8;
		while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING))
		{
			if((Timeout--) == 0) break;
		}
		I2C_SendData(I2C2, p[i]);
		i++;
	}                
	//------------结束信号------------                                                            
	LCD_I2C_Stop();                                 
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
	uint16_t Timeout;
	uint16_t i;
	
	//------------起始信号------------
	LCD_I2C_Start();
	//------------发送地址------------	
	LCD_I2C_SendAddr(OLED_IIC_7ADDR<<1);
	//------------发送1+n个指令------------
	I2C_SendData(I2C2, 0x00);
	i=0;
	while(num>i)
	{
		Timeout = LCD_HARD_IIC_TIMEOUT_UINT8;
		while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING))
		{
			if((Timeout--) == 0) break;
		}
		I2C_SendData(I2C2, p[i]);
		i++;
	}              
	//------------结束信号------------                                                           
	LCD_I2C_Stop();                               
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
  * 名称: LCD_Port_Init()
  * 传入: 无
  * 返回: 无
  * 功能: 屏幕接口初始化
  * 说明: 
----------------------------------------------------------------*/
void LCD_Port_Init(void)
{
	LCD_SCL_IO_Init();
	LCD_SDA_IO_Init();
	LCD_RES_IO_Init();
	
	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.I2C_Ack=I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_ClockSpeed=400000;//默认400000 (某屏幕测试最高可使用600000)
	I2C_InitStruct.I2C_DutyCycle=I2C_DutyCycle_2;//I2C_DutyCycle_16_9   I2C_DutyCycle_2
	I2C_InitStruct.I2C_Mode=I2C_Mode_I2C;
	I2C_InitStruct.I2C_OwnAddress1 = OLED_IIC_7ADDR;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	I2C_DeInit(I2C2);
	I2C_Init(I2C2, &I2C_InitStruct);
	I2C_Cmd(I2C2, ENABLE);
	
	#if ((LCD_MODE == _FULL_BUFF_DYNA_UPDATE) || (LCD_MODE ==_PAGE_BUFF_DYNA_UPDATE))
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
	#endif
	
	LCD_RES_Clr();
	{
		volatile unsigned int i=10000;
		while(i--);
	}
	LCD_RES_Set();
	
}




/*--------------------------------------------------------------
  * 名称: LCD_Refresh(void)
  * 功能: 驱动接口,将显存LCD_GRAM全部内容发送至屏幕
----------------------------------------------------------------*/

//----------------------------普通OLED屏幕刷屏接口-------------------------------------
#if defined (LCD_USE_NORMAL_OLED)

#if (LCD_MODE == _FULL_BUFF_FULL_UPDATE)
//---------方式1:全缓存全屏刷新----------
//--优点:全屏刷新
//--缺点:内容不变的区域也参与了刷新
uint8_t LCD_Refresh(void)
{
	unsigned char ypage;
	for(ypage=0;ypage<(SCREEN_HIGH/8);ypage++)
	{
		LCD_Set_Addr(0,ypage);
		LCD_Send_nDat(&lcd_driver.LCD_GRAM[ypage][0],SCREEN_WIDTH);
	}
	return 0;
}

#elif (LCD_MODE == _FULL_BUFF_DYNA_UPDATE)
//---------方式2:全缓存动态刷新----------
uint8_t LCD_Refresh(void)
{
	//每page做"sum+mini_crc组合"校验,若校验码没变,则不刷新该page
	static uint32_t sum1[GRAM_YPAGE_NUM];
	unsigned char ypage,x;
	for(ypage=0;ypage<GRAM_YPAGE_NUM;ypage++)
	{
		uint32_t i_sum1;
		
		//-----方式1:CRC算法校验-----
		CRC->CR = CRC_CR_RESET;//CRC_ResetDR();
		for(x=0;x<SCREEN_WIDTH;x++)
		{
			CRC->DR = lcd_driver.LCD_GRAM[ypage][x];//CRC_CalcCRC(lcd_driver.LCD_GRAM[ypage][x]);
		}
		i_sum1 = CRC->DR;//i_sum1 = CRC_GetCRC();
		//---------------------------
		
		//-----方式2:累加乘积校验-----
		//i_sum1 = 0;
		//for(x=0;x<SCREEN_WIDTH;x++)
		//{
		//	i_sum1 = i_sum1 + (uint32_t)lcd_driver.LCD_GRAM[ypage][x]*x;
		//}
		//---------------------------
		
		if(sum1[ypage] != i_sum1)
		{
			LCD_Set_Addr(0,ypage);
			LCD_Send_nDat(&lcd_driver.LCD_GRAM[ypage][0],SCREEN_WIDTH);
		}
		sum1[ypage] = i_sum1;
	}
	return 0;
}
//---------方式3:页缓存全局刷新----------
#elif (LCD_MODE == _PAGE_BUFF_FULL_UPDATE)

uint8_t LCD_Refresh(void)
{
	uint8_t i=0;
	
	for(i=0;i<GRAM_YPAGE_NUM;i++)
	{
		LCD_Set_Addr(0,lcd_driver.lcd_refresh_ypage);
		LCD_Send_nDat(&lcd_driver.LCD_GRAM[i][0],SCREEN_WIDTH);
		lcd_driver.lcd_refresh_ypage++;
		if(lcd_driver.lcd_refresh_ypage >= ((SCREEN_HIGH+7)/8))
		{
			lcd_driver.lcd_refresh_ypage = 0;
			break;
		}
	}
	return lcd_driver.lcd_refresh_ypage;
}
//---------方式4:页缓存动态刷新----------
#elif (LCD_MODE == _PAGE_BUFF_DYNA_UPDATE)
uint8_t LCD_Refresh(void)
{
	//每page做校验,若校验码没变,则不刷新该page
	static uint32_t crc[((SCREEN_HIGH+7)/8)];
	unsigned char ypage,x;

	for(ypage=0;ypage<GRAM_YPAGE_NUM;ypage++)
	{
		uint32_t i_crc;

		//判断屏幕是否已刷完
		if(lcd_driver.lcd_refresh_ypage + ypage > ((SCREEN_HIGH+7)/8)-1)
		{
			break;
		}
		//-----方式1:CRC算法校验-----
		CRC->CR = CRC_CR_RESET;//CRC_ResetDR();
		for(x=0;x<SCREEN_WIDTH;x++)
		{
			CRC->DR = lcd_driver.LCD_GRAM[ypage][x];//CRC_CalcCRC(lcd_driver.LCD_GRAM[ypage][x]);
		}
		i_crc = CRC->DR;//i_sum1 = CRC_GetCRC();
		//---------------------------
		if(crc[lcd_driver.lcd_refresh_ypage + ypage] != i_crc)
		{
			LCD_Set_Addr(0,lcd_driver.lcd_refresh_ypage + ypage);
			LCD_Send_nDat(&lcd_driver.LCD_GRAM[ypage][0],SCREEN_WIDTH);
			crc[lcd_driver.lcd_refresh_ypage + ypage] = i_crc;
		}
	}
	
	lcd_driver.lcd_refresh_ypage += GRAM_YPAGE_NUM;
	if(lcd_driver.lcd_refresh_ypage >= ((SCREEN_HIGH+7)/8))
	{
		lcd_driver.lcd_refresh_ypage = 0;
	}
	return lcd_driver.lcd_refresh_ypage;
}
#endif




//----------------------------灰度OLED屏幕刷屏接口-------------------------------------
#elif defined (LCD_USE_GRAY_OLED)//灰度OLED
	//灰度OLED暂不支持硬件IIC 请使用软件IIC(存在硬件问题暂未解决)
	#error("Gray OLED not support hard_iic driver yet! Use soft_iic please!")
	
//#if (LCD_MODE == _FULL_BUFF_FULL_UPDATE)
////---------方式1:全屏刷新----------
////--优点:全屏刷新
////--缺点:内容不变的区域也参与了刷新
//void LCD_Refresh(void)
//{
//	unsigned char x,y,i,Timeout;
//	#if defined(GRAY_DRIVER_0DEG)
//	//---扫描方向1(不旋转)----
//	LCD_Set_Addr(0,0,(SCREEN_WIDTH/2-1),(SCREEN_HIGH-1));
//	LCD_I2C_Start();
//	LCD_I2C_SendAddr(OLED_IIC_7ADDR<<1);
//	LCD_I2C_send_1Byte(0x40);
//	for(y=0;y<SCREEN_HIGH;y++)
//	{
//		uint8_t page,mask;
//		page=y/8;
//		mask=(0x01<<y%8);
//		for(x=0;x<SCREEN_WIDTH;)
//		{
//			i = 0x00;
//			//第一个点
//			if(lcd_driver.LCD_GRAM[page][x]&mask)
//			{
//				i = GRAY_COLOUR<<4;
//			}
//			x++;
//			//第二个点
//			if(x<SCREEN_WIDTH)
//			{
//				if(lcd_driver.LCD_GRAM[page][x]&mask)
//				{
//					i |= GRAY_COLOUR;
//				}
//			}
//			x++;
//			LCD_I2C_send_1Byte(i);
//		}
//	}

//	#elif defined(GRAY_DRIVER_90DEG)
//	//---扫描方向2(90度旋转)---
//	LCD_Set_Addr(0,0,(SCREEN_HIGH/2-1),(SCREEN_WIDTH-1));
//	LCD_I2C_Start();
//	LCD_I2C_SendAddr(OLED_IIC_7ADDR<<1);
//	LCD_I2C_send_1Byte(0x40);
//	for(y=0;y<SCREEN_HIGH;y+=2)
//	{
//		uint8_t page1,page2,mask1,mask2;
//		page1=y/8;
//		page2=(y+1)/8;
//		mask1=(0x01<<y%8);
//		mask2=(0x01<<(y+1)%8);
//		for(x=0;x<SCREEN_WIDTH;x++)
//		{
//			i = 0x00;
//			//第一个点
//			if(lcd_driver.LCD_GRAM[page1][x]&mask1)
//			{
//				i = GRAY_COLOUR<<4;
//			}
//			//第二个点
//			if((y+1)<SCREEN_HIGH)
//			{
//				if(lcd_driver.LCD_GRAM[page2][x]&mask2)
//				{
//					i |= GRAY_COLOUR;
//				}
//			}
//			LCD_I2C_send_1Byte(i);
//		}
//	}
//	#endif
//	LCD_I2C_Stop();
//}
//#elif (LCD_MODE == _FULL_BUFF_DYNA_UPDATE)
////---------方式2:动态刷新----------
////--优点:性能好,按需区域刷新,节省MCU资源
////--缺点:全屏刷新相对变慢
//void LCD_Refresh(void)
//{
//	//每page做"sum+mini_crc组合"校验,若校验码没变,则不刷新该page
//	static uint32_t sum1[GRAM_YPAGE_NUM];
//	unsigned char ypage,x,y,i,ycount,Timeout;
//	for(ypage=0;ypage<GRAM_YPAGE_NUM;ypage++)
//	{
//		uint32_t i_sum1;
//		
//		//-----方式1:CRC算法校验-----
//		CRC->CR = CRC_CR_RESET;//CRC_ResetDR();
//		for(x=0;x<SCREEN_WIDTH;x++)
//		{
//			CRC->DR = lcd_driver.LCD_GRAM[ypage][x];//CRC_CalcCRC(lcd_driver.LCD_GRAM[ypage][x]);
//		}
//		i_sum1 = CRC->DR;//i_sum1 = CRC_GetCRC();
//		//---------------------------

//		if(sum1[ypage] != i_sum1)
//		{
//			ycount = 8* ypage;
//#if defined(GRAY_DRIVER_0DEG)
//			//----扫描方向1(不旋转)---
//			LCD_Set_Addr(0,ycount,(SCREEN_WIDTH/2-1),(SCREEN_HIGH-1));
//			LCD_I2C_Start();
//			LCD_I2C_SendAddr(OLED_IIC_7ADDR<<1);
//			LCD_I2C_send_1Byte(0x40);
//			
//			for(y=0;y<8;y++)
//			{
//				uint8_t mask;
//				if(++ycount >= SCREEN_HIGH){break;}
//				mask=0x01<<(y%8);
//				for(x=0;x<SCREEN_WIDTH;)
//				{
//					//----第一个点----
//					i = 0x00;
//					if(lcd_driver.LCD_GRAM[ypage][x]&mask)
//					{
//						i = GRAY_COLOUR<<4;
//					}
//					//----第二个点----
//					x++;
//					if((lcd_driver.LCD_GRAM[ypage][x]&mask)&&(x<SCREEN_WIDTH))
//					{
//						i |= GRAY_COLOUR;
//					}
//					x++;
//					I2C_send_1Byte(i);
//				}
//			}

//#elif defined(GRAY_DRIVER_90DEG)
//			//---扫描方向2(90度旋转)----
//			LCD_Set_Addr(ycount/2,0,(SCREEN_HIGH/2-1),(SCREEN_WIDTH-1));
//			LCD_I2C_Start();
//			LCD_I2C_SendAddr(OLED_IIC_7ADDR<<1);
//			LCD_I2C_send_1Byte(0x40);
//			for(y=0;y<8;y+=2)
//			{
//				if(++ycount >= SCREEN_HIGH){break;}
//				for(x=0;x<SCREEN_WIDTH;x++)
//				{
//					//(4位一个点)
//					//----第一个点----
//					i = 0x00;
//					if(lcd_driver.LCD_GRAM[ypage][x]&(0x01<<y))
//					{
//						i = GRAY_COLOUR<<4;
//					}
//					//----第二个点----
//					if((y+1)<SCREEN_HIGH)
//					{
//						if(lcd_driver.LCD_GRAM[ypage][x]&(0x01<<(y+1)))
//						{
//							i |= GRAY_COLOUR;
//						}
//					}
//					LCD_I2C_send_1Byte(i);
//				}
//			}
//#endif
//			LCD_I2C_Stop();
//		}
//		sum1[ypage] = i_sum1;
//	}
//}
//#endif



//----------------------------RGB565屏幕刷屏接口-------------------------------------
#elif defined (LCD_USE_RGB565)
	//彩屏TFT屏不支持I2C方式驱动 请更改屏幕驱动IC型号
	#error ("TFT not support I2C Driver!");
#endif





#endif
