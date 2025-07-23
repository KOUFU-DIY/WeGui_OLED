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

#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "lcd_driver.h"
#include "lcd_Wegui_driver.h"

void delay_ms(uint32_t ms);




#define ResADC_GPIOx                 GPIOA
#define ResADC_GPIO_Pin_x            GPIO_Pin_1
#define ResADC_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOA
#define ResADC_IO_Init()                                        \
do                                                                  \
{                                                                   \
    GPIO_InitTypeDef GPIO_InitStruct;                               \
    GPIO_InitStruct.GPIO_Pin   = ResADC_GPIO_Pin_x;             \
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;                   \
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AIN;                     \
	  RCC_APB2PeriphClockCmd(ResADC_RCC_APB2Periph_GPIOx,ENABLE); \
    GPIO_Init(ResADC_GPIOx, &GPIO_InitStruct);                  \
}while(0)
#endif
