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

#if defined WEGUI_UART_ON

#include "stm32f103_wegui_uart_port.h"
#include "lcd_wegui_menu_mlist.h"
#include "user_wegui_menu.h"
#include "lcd_wegui_tip.h"


#include "lcd_driver.h"



rx_state_t irq_rx_state;//接收中断状态
uint8_t uart_rx_time_out;//超时计时
uint8_t uart_rx_wait_deal_task;//数据包接收完成一次+1
Ring_t rxRing;//创建一个rxRing的缓冲区



//-----------------------------UART接收使用环形缓冲区---------------------------------------


/*--------------------------------------------------------------
  * 名称: USART2_IRQHandler(void)
  * 传入: 
  * 返回: 
  * 功能: UART接收中断处理
  * 说明: 
----------------------------------------------------------------*/
void USART2_IRQHandler(void)                                          
{
	if ( USART_GetITStatus( USART2, USART_IT_RXNE ) != RESET )     
	{
		static uint16_t len = 0x00;//数据长度
		static uint16_t get_len = 0x00;//已经获取的长度
		
		
		switch(irq_rx_state)
		{
			//--------------1.头码接收------------
			case UART_RX_WAIT_HEAD:
			{
				if(USART_ReceiveData(USART2) == 0x78)
				{
					irq_rx_state = UART_RX_WAIT_GET_LENGTH_H;
					get_len = 0;
				}
				if(Get_rxRing_len())//缓存内没有任何数据
				{
					//uart_rx_time_out = 0;//接收超时清零
				}
			}break;
			//--------------1.长度接收------------
			case UART_RX_WAIT_GET_LENGTH_H:
			{
				uint8_t i = USART_ReceiveData(USART2);
				len = i<<8;
				irq_rx_state = UART_RX_WAIT_GET_LENGTH_L;
				//uart_rx_time_out = 0;//接收超时清零
			}break;
			case UART_RX_WAIT_GET_LENGTH_L:
			{
				uint8_t i = USART_ReceiveData(USART2);
				len |= i;
				irq_rx_state = UART_RX_WAIT_DAT;
				//uart_rx_time_out = 0;//接收超时清零
			}break;
			//--------------1.数据接收------------
			case UART_RX_WAIT_DAT:
			{
				uint8_t i = USART_ReceiveData(USART2);
				Write_rxRing(USART_ReceiveData(USART2));//存到缓冲区里
				if(++get_len >= len)
				{
					irq_rx_state = UART_RX_WAIT_HEAD;//接收完毕
					uart_rx_wait_deal_task++;//数据包接收完成一次+1
				}
				uart_rx_time_out = 0;//接收超时清零
			}break;
			default:
			{
				
			}
		}
		
	}
}

/*--------------------------------------------------------------
  * 名称: Write_rxRing(uint8_t data)
  * 传入: data当前接收到的数据
  * 返回: 0写入失败 1写入成功
  * 功能: 往rxRing的Buff写入一个数据
  * 说明: 
----------------------------------------------------------------*/
uint8_t Write_rxRing(uint8_t data)
{
   if(rxRing.Lenght >= RXRING_LEN) //判断缓冲区是否已满
   {
     return 0;//缓冲溢出
   }
   rxRing.Buff[rxRing.Tail]=data;
   rxRing.Tail = (rxRing.Tail+1)%RXRING_LEN;//防止越界非法访问
   rxRing.Lenght++;
   return 1;//没问题
}

/*--------------------------------------------------------------
  * 名称: Get_rxRing_len(void)
  * 传入: data当前接收到的数据
  * 返回: 已经接收到并且未处理的数据的数量
  * 功能: 
  * 说明: 0无数据
----------------------------------------------------------------*/
uint8_t Get_rxRing_len(void)
{
	//获取已经储存数据的数量
	return rxRing.Lenght;
}

/*--------------------------------------------------------------
  * 名称: Read_rxRing_buff()
  * 传入: 无
  * 返回: 读取的数据
  * 功能: 往rxRing的Buff里顺序读一个数据
  * 说明: 需要确保已有数据(Get_rxRing_len() > 0),否出读出的是0
----------------------------------------------------------------*/
uint8_t Read_rxRing_buff(void)
{
	uint8_t i=0;
	if(rxRing.Lenght > 0)
	{
		i = rxRing.Buff[rxRing.Head];//从缓冲区头出
		rxRing.Head = (rxRing.Head+1)%RXRING_LEN;//防止越界非法访问
		rxRing.Lenght--;
	}
	return i;
}





//----------------------------------------------------------------------------------


/*--------------------------------------------------------------
  * 名称: void Wegui_UartSend_1Dat(uint8_t dat)
  * 传入: 
  * 返回: 
  * 功能: 向uart发送一个数据
  * 说明: 
----------------------------------------------------------------*/
void Wegui_UartSend_1Dat(uint8_t dat)
{
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2,dat);
}

/*--------------------------------------------------------------
  * 名称: void Wegui_UartSend_1Dat(uint8_t dat)
  * 传入: 
  * 返回: 
  * 功能: 向uart发送一个数据
  * 说明: 
----------------------------------------------------------------*/
void Wegui_UartSend_nDat(uint8_t *p,uint16_t num)
{
	uint16_t i=0;
	while(i < num)	  
	{
		Wegui_UartSend_1Dat(p[i]);
		i++;
	}
}


/*--------------------------------------------------------------
  * 名称: int fputc(int ch, FILE *f)
  * 传入: 
  * 返回: 
  * 功能: 串口发送接口
  * 说明: 
----------------------------------------------------------------*/
int fputc(int ch, FILE *f)
{
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		USART_SendData(USART2,(uint8_t) ch);
	
//  USART_SendData(USART2, (uint8_t) ch);
//  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
//  {}
  return ch;
}


/*--------------------------------------------------------------
  * 名称: rxRing_par_Init()
  * 传入: 
  * 返回: 
  * 功能: 串口接收数据初始化/重置
  * 说明: 
----------------------------------------------------------------*/
void rxRing_par_Init()
{
	  rxRing.Head=0;
    rxRing.Tail=0;
    rxRing.Lenght=0;
}
































static void Uart_keyUp()
{
	switch (Wegui.tip.state)
	{
		case FREE:break;//弹窗已退出
		case EXITING:break;//弹窗已退出
		case ENTERING:
		case DISPLAYING:
		{
				switch (Wegui.tip.type)
				{
					case message:
					{
						Wegui_Tip_Quit();
					}break;
					case slider:
					{
							Wegui_Tip_Save_andQuit();
					}break;
				}
				return;//优先处理弹窗,不处理菜单
		}
	}
	switch(Wegui.menu->menuType)
	{
		case mList:     //列表菜单
		{
				Wegui_mlist_cursor_Prev();
		}break;
		case mPorgram:  //自定义功能APP
		{
			if(Wegui.menu == &m_App_UartScreen)
			{
				Wegui_mlist_Back_menu();
			}
		}break;
		case wCheckBox: //控件:复选框
			break;
		case wSlider:   //控件:滑条
			break;
		case wMessage:
			break;
	}
}




static void Uart_keyDown()
{
	switch (Wegui.tip.state)
	{
		case FREE:break;//弹窗已退出
		case EXITING:break;//弹窗已退出
		case ENTERING:
		case DISPLAYING:
		{
			Wegui_Tip_Quit();
		}
		return;//优先处理弹窗,不处理菜单
	}
	switch(Wegui.menu->menuType)
	{
		case mList:     //列表菜单
		{
			Wegui_mlist_cursor_Next();
		}break;
		case mPorgram:  //自定义功能APP
			if(Wegui.menu == &m_App_UartScreen)
			{
				Wegui_mlist_Back_menu();
			}break;
		case wCheckBox: //控件:复选框
			break;
		case wSlider:   //控件:滑条
			break;
		case wMessage:
			break;
	}
}






static void Uart_keyLeft()
{
	switch (Wegui.tip.state)
	{
		case FREE:break;//弹窗已退出
		case EXITING:break;//弹窗已退出
		case ENTERING:
		case DISPLAYING:
		{
				switch (Wegui.tip.type)
				{
					case message:
					{
						Wegui_Tip_Quit();
						break;
					}
					case slider:
					{
						Wegui_Tip_Value_Dec();
					}break;
				}
			return;//优先处理弹窗,不处理菜单
		}
	}
	switch(Wegui.menu->menuType)
	{
		case mList:     //列表菜单
		{
				Wegui_mlist_Back_menu();
		}break;
		case mPorgram:  //自定义功能APP
			if(Wegui.menu == &m_App_UartScreen)
			{
				Wegui_mlist_Back_menu();
			}break;
		case wCheckBox: //控件:复选框
			break;
		case wSlider:   //控件:滑条
			break;
		case wMessage:
			break;
	}
}







static void Uart_keyRight()
{
	//-----------------------优先处理弹窗---------------------
	switch (Wegui.tip.state)
	{
		case FREE:break;//弹窗已退出
		case EXITING:break;//弹窗已退出
		case ENTERING:
		case DISPLAYING:
		{
				switch (Wegui.tip.type)
				{
					case message:
					{
						Wegui_Tip_Quit();
					}break;
					case slider:
					{
						Wegui_Tip_Value_Add();
					}break;
				}
			return;//优先处理弹窗,不处理菜单
		}
	}
	
	
	//-----------------------再处理菜单---------------------
	switch(Wegui.menu->menuType)
	{
		case mList:     //列表菜单
		{
				Wegui_mlist_Enter_cursor();
		}break;
		case mPorgram:  //自定义功能APP
			if(Wegui.menu == &m_App_UartScreen)
			{
				Wegui_mlist_Back_menu();
			}break;
		case wCheckBox: //控件:复选框
			break;
		case wSlider:   //控件:滑条
			break;
		case wMessage:
			break;
	}
}






typedef enum
{
	DEAL_FREE = 0,
	DEAL_CTRL,//上位机操作
	DEAL_REQUEST//上位机获取数据
}deal_code_t;
static deal_code_t deal_code=DEAL_FREE;
static void Wegui_uart_rx_default_func(void);
/*--------------------------------------------------------------
  * 名称: Wegui_uart_rx_stick()
  * 传入: 
  * 返回: 
  * 功能: 串口接收数据处理
  * 说明: 
----------------------------------------------------------------*/
void Wegui_uart_rx_stick(uint16_t stick)
{
	if((irq_rx_state != UART_RX_WAIT_HEAD) || (deal_code != 0) || ((Get_rxRing_len() > 0)&&(uart_rx_wait_deal_task == 0)) || ((Get_rxRing_len() == 0)&&(uart_rx_wait_deal_task != 0)))
	{
		if(uart_rx_time_out<50)
		{
			uart_rx_time_out += stick;	
		}
		else
		{
			irq_rx_state = UART_RX_WAIT_HEAD;//串口接收超时重置
			rxRing_par_Init();//接收缓冲区重置
			deal_code = DEAL_FREE;
			uart_rx_wait_deal_task = 0;
		}
	}
	else
	{
		uart_rx_time_out=0;
	}
	
	
	switch(Wegui.menu->menuType)
	{
		case mPorgram:  //自定义功能APP
		{

		}//break;
		default://默认基础功能
		{	
			Wegui_uart_rx_default_func();
		}break;
	}
}




//[0]0x00 上位机操作请求
//[0]0x00 [1]0x00 [2]0x00 [2]0xFF操作上键模拟按下 [完成后返回: 头信息 0x00 0x01 0x00]
//[0]0x00 [1]0x00 [2]0x01 [2]0xFE操作下键模拟按下 [完成后返回: 头信息 0x00 0x01 0x01]
//[0]0x00 [1]0x00 [2]0x02 [2]0xFD操作左键模拟按下 [完成后返回: 头信息 0x00 0x01 0x02]
//[0]0x00 [1]0x00 [2]0x03 [2]0xFC操作右键模拟按下 [完成后返回: 头信息 0x00 0x01 0x03]

//[0]0x00 [1]0x10 [2]0xEF (uart显示器APP专用)准备操作显存 [接收完成后发送: 头信息 0x01 0x10 0x01]
//[0]0x00 [1]0x20 [2]0xDF 进入uart串口APP [准备好后发送: 头信息 0x01 0x20 0x01]
//[0]0x00 [1]0x30 [2]0xCF [3]0xAA软件复位 [复位前发送: 头信息 0x01 0x30 0x01]



//[0]0x80 上位机获取请求
//[0]0x80 [2]0x00获取屏幕宽  [完成后返回: 头信息 0x81 0x00 屏幕宽高8位 屏幕宽低8位]
//[0]0x80 [2]0x01获取屏幕高  [完成后返回: 头信息 0x81 0x01 屏幕高高8位 屏幕高低8位]
//[0]0x80 [2]0x02获取屏幕驱动型号[完成后返回: 头信息 0x81 0x02 驱动型号字符串]
//[0]0x80 [2]0x03获取屏幕驱动方式[完成后返回: 头信息 0x81 0x03 驱动方式字符串]
//[0]0x80 [2]0x04获取屏幕刷新方式[完成后返回: 头信息 0x81 0x04 刷新方式字符串]
//[0]0x80 [2]0x05获取屏幕软件版本[完成后返回: 头信息 0x81 0x05 版本字符串]
//[0]0x80 [2]0x10获取屏幕显存[完成后返回: 头信息 0x81 0x10 所有显存]
//[0]0x80 [2]0x20获取串口缓冲区的大小[完成后返回: 头信息 0x81 0x20 高8位 低8位]
static void Wegui_uart_rx_default_func()
{
	while((Get_rxRing_len() > 0)&&(uart_rx_wait_deal_task > 0))
	{
		uint8_t dat = Read_rxRing_buff();
		switch (deal_code)
		{
			default:deal_code=DEAL_FREE;//错误
			case DEAL_FREE:
			{
				switch(dat)
				{
					case 0x00:deal_code=DEAL_CTRL;break;//上位机请求操作
					case 0x80:deal_code=DEAL_REQUEST;break;//上位机获取数据
					default:deal_code=DEAL_FREE;break;
				}
			}break;
			case DEAL_CTRL:
			{
				switch(dat)//控制码
				{
					case 0x00:
					{
						//[0]0x00 [1]0x00 [2]0x00 [2]0xFF操作上键模拟按下 [完成后返回: 头信息 0x00 0x01 0x00]
						//[0]0x00 [1]0x00 [2]0x01 [2]0xFE操作下键模拟按下 [完成后返回: 头信息 0x00 0x01 0x01]
						//[0]0x00 [1]0x00 [2]0x02 [2]0xFD操作左键模拟按下 [完成后返回: 头信息 0x00 0x01 0x02]
						//[0]0x00 [1]0x00 [2]0x03 [2]0xFC操作右键模拟按下 [完成后返回: 头信息 0x00 0x01 0x03]
						uint8_t i[]={0x78,0x00,0x03,0x00,0x01,0xFF};
						dat = Read_rxRing_buff();
						//if(dat == 0x00)
						{
							//dat = Read_rxRing_buff();
							switch(dat)
							{
								case 0x00:dat = Read_rxRing_buff(); if(dat==0xFF){i[5]=0x00;Wegui_UartSend_nDat((uint8_t*)i,sizeof(i)/sizeof(uint8_t));Uart_keyUp();}break;
								case 0x01:dat = Read_rxRing_buff(); if(dat==0xFE){i[5]=0x01;Wegui_UartSend_nDat((uint8_t*)i,sizeof(i)/sizeof(uint8_t));Uart_keyDown();}break;
								case 0x02:dat = Read_rxRing_buff(); if(dat==0xFD){i[5]=0x02;Wegui_UartSend_nDat((uint8_t*)i,sizeof(i)/sizeof(uint8_t));Uart_keyLeft();}break;
								case 0x03:dat = Read_rxRing_buff(); if(dat==0xFC){i[5]=0x03;Wegui_UartSend_nDat((uint8_t*)i,sizeof(i)/sizeof(uint8_t));Uart_keyRight();}break;
								default:break;
							}
						}
					}break;
					case 0x10://[0]0x00 [1]0x10 [2]0xEF (uart显示器APP专用)准备操作显存 [接收完成后发送: 头信息 0x01 0x10 0x01]
					{
						if(Wegui.menu != &m_App_UartScreen)
						{
							break;
						}
							uint8_t i[]={0x78,0x00,0x03,0x01,0x10,0x00};
							uint8_t i2[]={0x78,0x00,0x03,0x01,0x10,0x01};
							uint16_t num=0;
							volatile uint8_t* pgram = &lcd_driver.LCD_GRAM[0][0];
							
							dat = Read_rxRing_buff();
							if(dat == 0xEF)
							{
								Wegui_UartSend_nDat((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
								USART_ITConfig(USART2, USART_IT_RXNE, DISABLE); //关闭rx中断
								for(num=0;num<(GRAM_YPAGE_NUM*SCREEN_WIDTH);num++)
								{
									volatile uint16_t timeout=0;
									while(USART_GetFlagStatus( USART2, USART_FLAG_RXNE ) == RESET )///等待数据
									{
										if(timeout++ > 20000)
										{
											//超时
											USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //重新打开rx中断
											return;
										}
									};
									pgram[num]=USART_ReceiveData(USART2);
								}
								Wegui_UartSend_nDat((uint8_t*)i2,sizeof(i2)/sizeof(uint8_t));
								USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //重新打开rx中断
							}

					}break;
					case 0x20://[0]0x00 [1]0x20 [2]0xDF 进入uart串口APP [准备好后发送: 头信息 0x01 0x20 0x01]
					{
						uint8_t i[]={0x78,0x00,0x03,0x01,0x20,0x01};
						dat = Read_rxRing_buff();
						if(dat == 0xDF)
						{
							Wegui_enter_menu(&m_App_UartScreen);
							Wegui_UartSend_nDat((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
						}
					}break;
					case 0x30://[0]0x00 [1]0x30 [2]0xCF [3]0xAA软件复位 [复位前发送: 头信息 0x01 0x30 0x01]
					{
						if(Read_rxRing_buff() != 0xCF){break;}
						if(Read_rxRing_buff() != 0xAA){break;}
						{
							uint8_t i[]={0x78,0x00,0x03,0x01,0x30,0x01};
							Wegui_UartSend_nDat((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
							
							__disable_fault_irq();
							Wegui_enter_menu(&m_App_UartScreen);NVIC_SystemReset();
						}
					}break;
					
					default:break;
				}
				deal_code=DEAL_FREE;//处理完毕
				uart_rx_wait_deal_task--;
				return;
			}//break;
			case DEAL_REQUEST:
			{
				switch(dat)
				{
					case 0x00://[0]0x80 [2]0x00获取屏幕宽  [完成后返回: 头信息 0x81 0x00 屏幕宽高8位 屏幕宽低8位]
					{
						uint8_t i[]={0x78,0x00,0x04,0x81,0x00,(SCREEN_WIDTH>>8),(SCREEN_WIDTH&0xff)};
						Wegui_UartSend_nDat((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
					}break;
					case 0x01://[0]0x80 [2]0x01获取屏幕高  [完成后返回: 头信息 0x81 0x01 屏幕高高8位 屏幕高低8位]
					{
						uint8_t i[]={0x78,0x00,0x04,0x81,0x01,(SCREEN_HIGH>>8),(SCREEN_HIGH&0xff)};
						Wegui_UartSend_nDat((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
					}break;
					case 0x02://[0]0x80 [2]0x02获取屏幕驱动型号[完成后返回: 头信息 0x81 0x02 驱动型号字符串]
					{
						#if   (LCD_IC==_SH1106  )
						uint8_t i[]={0x78,0x00,0x09,0x81,0x02,'S','H','1','1','0','6','\0'};
						#elif (LCD_IC==_SH1108  )
						uint8_t i[]={0x78,0x00,0x09,0x81,0x02,'S','H','1','1','0','8','\0'};
						#elif (LCD_IC==_SH1107  )
						uint8_t i[]={0x78,0x00,0x09,0x81,0x02,'S','H','1','1','0','7','\0'};
						#elif (LCD_IC==_SH1115  )
						uint8_t i[]={0x78,0x00,0x09,0x81,0x02,'S','H','1','1','1','5','\0'};
						#elif (LCD_IC==_SSD1306 )
						uint8_t i[]={0x78,0x00,0x0A,0x81,0x02,'S','S','D','1','3','0','6','\0'};
						#elif (LCD_IC==_SSD1309 )
						uint8_t i[]={0x78,0x00,0x0A,0x81,0x02,'S','S','D','1','3','0','9','\0'};
						#elif (LCD_IC==_SSD1312 )
						uint8_t i[]={0x78,0x00,0x0A,0x81,0x02,'S','S','D','1','3','1','2','\0'};
						#elif (LCD_IC==_SSD1315 )
						uint8_t i[]={0x78,0x00,0x0A,0x81,0x02,'S','S','D','1','3','1','5','\0'};
						#elif (LCD_IC==_SSD1327 )
						uint8_t i[]={0x78,0x00,0x0A,0x81,0x02,'S','S','D','1','3','2','7','\0'};
						#elif (LCD_IC==_ST7735  )
						uint8_t i[]={0x78,0x00,0x09,0x81,0x02,'S','T','7','7','3','5','\0'};
						#elif (LCD_IC==_ST7789VW)
						uint8_t i[]={0x78,0x00,0x0B,0x81,0x02,'S','T','7','7','8','9','V','W','\0'};
						#elif (LCD_IC==_ST7796S )
						uint8_t i[]={0x78,0x00,0x0A,0x81,0x02,'S','T','7','7','9','6','S','\0'};
						#elif (LCD_IC==_GC9A01  )
						uint8_t i[]={0x78,0x00,0x09,0x81,0x02,'G','C','9','A','0','1','\0'};
						#else
						uint8_t i[]={0x78,0x00,0x08,0x81,0x02,'O','t','h','e','r','\0'};
						#endif
						Wegui_UartSend_nDat((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
					}break;
					case 0x03://[0]0x80 [2]0x03获取屏幕驱动方式[完成后返回: 头信息 0x81 0x03 驱动方式字符串]
					{
						#if defined LCD_USE_SOFT_3SPI 
						uint8_t i[]={0x78,0x00,0x0C,0x81,0x03,'s','o','f','t',' ','3','s','p','i','\0'};
						#elif defined LCD_USE_SOFT_4SPI 
						uint8_t i[]={0x78,0x00,0x0C,0x81,0x03,'s','o','f','t',' ','4','s','p','i','\0'};
						#elif defined LCD_USE_HARD_4SPI
						uint8_t i[]={0x78,0x00,0x0C,0x81,0x03,'h','a','r','d',' ','4','s','p','i','\0'};
						#elif defined LCD_USE_DMA_4SPI  
						uint8_t i[]={0x78,0x00,0x0B,0x81,0x03,'d','m','a',' ','4','s','p','i','\0'};
						#elif defined LCD_USE_SOFT_IIC  
						uint8_t i[]={0x78,0x00,0x0B,0x81,0x03,'s','o','f','t',' ','i','2','c','\0'};
						#elif defined LCD_USE_HARD_IIC  
						uint8_t i[]={0x78,0x00,0x0B,0x81,0x03,'h','a','r','d',' ','i','2','c','\0'};
						#else
						uint8_t i[]={0x78,0x00,0x08,0x81,0x03,'O','t','h','e','r','\0'};
						#endif
						Wegui_UartSend_nDat((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
					}break;
					case 0x04://[0]0x80 [2]0x04获取屏幕刷新方式[完成后返回: 头信息 0x81 0x04 刷新方式字符串]
					{
						#if ((LCD_MODE == LCD_USE_FULL_BUFF_FULL_REFRESH) || (LCD_MODE == _PAGE_BUFF_FULL_UPDATE))
						uint8_t i[]={0x78,0x00,0x08,0x81,0x04,'F','u','l','l','\0'};
						#elif ((LCD_MODE == LCD_USE_FULL_BUFF_DYNAMIC_REFRESH) || (LCD_MODE == _PAGE_BUFF_DYNA_UPDATE))
						uint8_t i[]={0x78,0x00,0x0A,0x81,0x04,'D','y','n','a','m','i','c','\0'};
						#else
						uint8_t i[]={0x78,0x00,0x08,0x81,0x04,'O','t','h','e','r','\0'};
						#endif
						Wegui_UartSend_nDat((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
					}break;
					case 0x05://[0]0x80 [2]0x05获取屏幕软件版本[完成后返回: 头信息 0x81 0x05 版本字符串]
					{
						uint8_t i[]={0x78,0x00,0x0B,0x81,0x05,'V','0','.','4','B','e','t','a','\0'};
						Wegui_UartSend_nDat((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
					}break;
					case 0x06://[0]0x80 [2]0x06获取屏幕显存大小[完成后返回: 头信息 0x81 高8位 低8位 版本字符串]
					{
						uint8_t i[]={0x78,0x00,0x04,0x81,0x06,(GRAM_YPAGE_NUM*SCREEN_WIDTH)>>8,(GRAM_YPAGE_NUM*SCREEN_WIDTH)&0xff};
						Wegui_UartSend_nDat((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
					}break;
					
					case 0x10://[0]0x80 [2]0x10获取屏幕显存[完成后返回: 头信息 0x81 0x10 所有显存]
					{
						uint8_t i[]={0x78,((GRAM_YPAGE_NUM*SCREEN_WIDTH+2)>>8),((GRAM_YPAGE_NUM*SCREEN_WIDTH+2)&0xff),0x81,0x10};
						Wegui_UartSend_nDat((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
						Wegui_UartSend_nDat((uint8_t*)lcd_driver.LCD_GRAM,(GRAM_YPAGE_NUM*SCREEN_WIDTH));
					}break;
					case 0x20://[0]0x80 [2]0x20获取串口缓冲区的大小[完成后返回: 头信息 0x81 0x20 高8位 低8位]
					{
						uint8_t i[]={0x78,0x00,0x04,0x81,0x20,RXRING_LEN>>8,RXRING_LEN&0xff};
						Wegui_UartSend_nDat((uint8_t*)i,sizeof(i)/sizeof(uint8_t));
					}break;
				}
				deal_code=DEAL_FREE;
				uart_rx_wait_deal_task--;
				return;
			}//break;
		}
	}
}















/*--------------------------------------------------------------
  * 名称: void Wegui_Uart_Port_Init()
  * 传入: 
  * 返回: 
  * 功能: 初始化
  * 说明: 
----------------------------------------------------------------*/
void Wegui_Uart_Port_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	/* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART Rx as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  /* USART configuration */
	USART_InitStructure.USART_BaudRate = 921600;
	//USART_InitStructure.USART_BaudRate = 2000000;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART2, &USART_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel			= USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 15; /* 抢占优先级3 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 15;       /* 子优先级3 */
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;        /* IRQ通道使能 */
	NVIC_Init( &NVIC_InitStructure );
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 
  /* Enable USART */
  USART_Cmd(USART2, ENABLE);
	
	
	//变量初始化
	irq_rx_state = UART_RX_WAIT_HEAD;//接收状态重置
	rxRing_par_Init();//接收缓冲区数据初始化
	uart_rx_time_out = 0;
}




#endif

