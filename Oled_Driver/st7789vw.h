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

#ifndef __ST7735_H__
#define __ST7735_H__


#include "main.h"

//-------------------IC最大支持的分辨率-------------------
//#define TFT_IC_WIDTH_PIXEL (320)
//#define TFT_IC_HIGH_PIXEL  (240)
//#define TFT_IC_PIXEL  (TFT_IC_WIDTH_PIXEL*TFT_IC_HIGH_PIXEL)

void ST7789VW_Set_Addr(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);

void ST7789VW_Set_RGB444_Mode(void);
void ST7789VW_Set_RGB565_Mode(void);
void ST7789VW_Set_RGB666_Mode(void);

void ST7789VW_Init(void);


#endif
