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

#ifndef STM32F103_WEGUI_UART_PORT_H
#define STM32F103_WEGUI_UART_PORT_H

#if defined WEGUI_UART_ON




#include "stdint.h"
#include "stdio.h"
#include "stm32f10x.h"

#define RXRING_LEN 64//接收缓冲区大小


typedef enum 
{
	UART_RX_WAIT_HEAD=0,//等待头码"0x78"
	UART_RX_WAIT_GET_LENGTH_H,//获取数据的长度值高8位
	UART_RX_WAIT_GET_LENGTH_L,//获取数据的长度值低8位
	UART_RX_WAIT_DAT,//获取n个数据
}rx_state_t;


typedef struct
{
    uint16_t Head;
    uint16_t Tail;
    uint16_t Lenght;
    uint8_t Buff[RXRING_LEN];
}Ring_t;





/*--------------------------------------------------------------
  * 名称: Write_rxRing(uint8_t data)
  * 传入: data当前接收到的数据
  * 返回: 0写入失败 1写入成功
  * 功能: 往rxRing的Buff写入一个数据
  * 说明: 
----------------------------------------------------------------*/
uint8_t Write_rxRing(uint8_t data);

/*--------------------------------------------------------------
  * 名称: Get_rxRing_len(void)
  * 传入: data当前接收到的数据
  * 返回: 已经接收到并且未处理的数据的数量
  * 功能: 
  * 说明: 0无数据
----------------------------------------------------------------*/
uint8_t Get_rxRing_len(void);

/*--------------------------------------------------------------
  * 名称: Read_rxRing_buff()
  * 传入: 无
  * 返回: 读取的数据
  * 功能: 往rxRing的Buff里顺序读一个数据
  * 说明: 需要确保已有数据(Get_rxRing_len() > 0),否出读出的是0
----------------------------------------------------------------*/
uint8_t Read_rxRing_buff(void);



/*--------------------------------------------------------------
  * 名称: Wegui_uart_rx_stick(uint16_t stick)
  * 传入: uint16_t stick 时间ms
  * 返回: 
  * 功能: 串口接收数据处理
  * 说明: 
----------------------------------------------------------------*/
void Wegui_uart_rx_stick(uint16_t stick);

void Wegui_Uart_Port_Init(void);




#else

#endif



#endif


