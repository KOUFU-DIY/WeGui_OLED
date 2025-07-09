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

#ifndef _STM32F103_WEGUI_4KEY_PORT_H_
#define _STM32F103_WEGUI_4KEY_PORT_H_

#include "stm32f10x.h"
#include "lcd_Wegui_driver.h"










//-------------------------------------按键配置-------------------------------------


//#define Wegui_KeyBack_GPIOx                 GPIOC
//#define Wegui_KeyBack_GPIO_Pin_x            GPIO_Pin_15
//#define Wegui_KeyBack_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOC
//#define Wegui_KeyBack_IO_Init()                                        \
//do                                                                  \
//{                                                                   \
//    GPIO_InitTypeDef GPIO_InitStruct;                               \
//    GPIO_InitStruct.GPIO_Pin   = Wegui_KeyBack_GPIO_Pin_x;             \
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
//    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
//	  RCC_APB2PeriphClockCmd(Wegui_KeyBack_RCC_APB2Periph_GPIOx,ENABLE); \
//    GPIO_Init(Wegui_KeyBack_GPIOx, &GPIO_InitStruct);                  \
//}while(0)

//#define Wegui_KeyOk_GPIOx                 GPIOA
//#define Wegui_KeyOk_GPIO_Pin_x            GPIO_Pin_0
//#define Wegui_KeyOk_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOA
//#define Wegui_KeyOk_IO_Init()                                        \
//do                                                                  \
//{                                                                   \
//    GPIO_InitTypeDef GPIO_InitStruct;                               \
//    GPIO_InitStruct.GPIO_Pin   = Wegui_KeyOk_GPIO_Pin_x;             \
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
//    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
//	  RCC_APB2PeriphClockCmd(Wegui_KeyOk_RCC_APB2Periph_GPIOx,ENABLE); \
//    GPIO_Init(Wegui_KeyOk_GPIOx, &GPIO_InitStruct);                  \
//}while(0)

#define Wegui_KeyRight_GPIOx                 GPIOB
#define Wegui_KeyRight_GPIO_Pin_x            GPIO_Pin_12
#define Wegui_KeyRight_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOB
#define Wegui_KeyRight_IO_Init()                                        \
do                                                                  \
{                                                                   \
    GPIO_InitTypeDef GPIO_InitStruct;                               \
    GPIO_InitStruct.GPIO_Pin   = Wegui_KeyRight_GPIO_Pin_x;             \
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
	  RCC_APB2PeriphClockCmd(Wegui_KeyRight_RCC_APB2Periph_GPIOx,ENABLE); \
    GPIO_Init(Wegui_KeyRight_GPIOx, &GPIO_InitStruct);                  \
}while(0)

#define Wegui_KeyUp_GPIOx                 GPIOB
#define Wegui_KeyUp_GPIO_Pin_x            GPIO_Pin_13
#define Wegui_KeyUp_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOB
#define Wegui_KeyUp_IO_Init()                                        \
do                                                                  \
{                                                                   \
    GPIO_InitTypeDef GPIO_InitStruct;                               \
    GPIO_InitStruct.GPIO_Pin   = Wegui_KeyUp_GPIO_Pin_x;             \
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
	  RCC_APB2PeriphClockCmd(Wegui_KeyUp_RCC_APB2Periph_GPIOx,ENABLE); \
    GPIO_Init(Wegui_KeyUp_GPIOx, &GPIO_InitStruct);                  \
}while(0)

#define Wegui_KeyDown_GPIOx                 GPIOB
#define Wegui_KeyDown_GPIO_Pin_x            GPIO_Pin_14
#define Wegui_KeyDown_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOB
#define Wegui_KeyDown_IO_Init()                                        \
do                                                                  \
{                                                                   \
    GPIO_InitTypeDef GPIO_InitStruct;                               \
    GPIO_InitStruct.GPIO_Pin   = Wegui_KeyDown_GPIO_Pin_x;             \
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
	  RCC_APB2PeriphClockCmd(Wegui_KeyDown_RCC_APB2Periph_GPIOx,ENABLE); \
    GPIO_Init(Wegui_KeyDown_GPIOx, &GPIO_InitStruct);                  \
}while(0)

#define Wegui_KeyLeft_GPIOx                 GPIOB
#define Wegui_KeyLeft_GPIO_Pin_x            GPIO_Pin_15
#define Wegui_KeyLeft_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOB
#define Wegui_KeyLeft_IO_Init()                                        \
do                                                                  \
{                                                                   \
    GPIO_InitTypeDef GPIO_InitStruct;                               \
    GPIO_InitStruct.GPIO_Pin   = Wegui_KeyLeft_GPIO_Pin_x;             \
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
	  RCC_APB2PeriphClockCmd(Wegui_KeyLeft_RCC_APB2Periph_GPIOx,ENABLE); \
    GPIO_Init(Wegui_KeyLeft_GPIOx, &GPIO_InitStruct);                  \
}while(0)





//开发板正向按键
/*---------------------------
	*  ---默认按键接口---
	*  |OK   | A0  |确定|
	*  |BACK | C15 |返回|
	*  |UP   | B13 | 上 |
	*  |DOWN | B14 | 下 |
	*  |LEFT | B15 | 左 |
	*  |RIGHT| B12 | 右 |
----------------------------*/
//#define Bool_WKeyBack_is_Pressed()  (GPIO_ReadInputDataBit(Wegui_KeyBack_GPIOx, Wegui_KeyBack_GPIO_Pin_x) == RESET)
//#define Bool_WKeyOk_is_Pressed()    (GPIO_ReadInputDataBit(Wegui_KeyOk_GPIOx, Wegui_KeyOk_GPIO_Pin_x) == RESET)
#define Bool_WkeyRight_is_Pressed() (GPIO_ReadInputDataBit(Wegui_KeyRight_GPIOx, Wegui_KeyRight_GPIO_Pin_x) == RESET)
#define Bool_WKeyUp_is_Pressed()    (GPIO_ReadInputDataBit(Wegui_KeyUp_GPIOx, Wegui_KeyUp_GPIO_Pin_x) == RESET)
#define Bool_WKeyDown_is_Pressed()  (GPIO_ReadInputDataBit(Wegui_KeyDown_GPIOx, Wegui_KeyDown_GPIO_Pin_x) == RESET)
#define Bool_WkeyLeft_is_Pressed()  (GPIO_ReadInputDataBit(Wegui_KeyLeft_GPIOx, Wegui_KeyLeft_GPIO_Pin_x) == RESET)





//-------------------------------------声明-------------------------------------
void Wegui_4key_port_Init(void);
void Wegui_Interface_stick(uint16_t ms);


#endif
