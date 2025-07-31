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


#include "main.h"


uint16_t ResADC=0;
uint8_t adc_en=1;


void delay_ms(uint32_t ms)
{
	sys1ms_delay = ms;
	while(sys1ms_delay);
}

void startup_init()
{
	
	//--释放JTAG 接口作为GPIO--
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	
	//--板载指示灯--
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	
	//--电位器--
	ResADC_IO_Init();
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	ADC_InitTypeDef  ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_1Cycles5);
	ADC_Cmd(ADC1, ENABLE);
	 /* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));
  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
	/* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	
	//--系统滴答1ms定时--
	sys1ms_stick = 0;
	SysTick_Config(SystemCoreClock / 1000);
}



//--板载指示灯--
void LED_Func()
{
	if(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)!=0)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	}
	else
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
	}
}

void gui_demo()//刷图demo
{
	#define DEMO_DELAY_MS 500
	
	
	//--------------文字显示字体1-----------------
	do
	{
		//0.---等待发送完毕---
		while(LCD_is_Busy()!=0);//DMA方式专用,其他模式可省略
		//1.---清空缓存---
		OLED_Clear_GRAM();
		//2.-----绘图-----
		lcd_driver.fonts_ASCII = &ascii_SongTi_8X16;//ASCII字体
		lcd_driver.fonts_UTF8_cut = &SongTi_UTF8_16X16;//UTF8字体(裁切)
		lcd_driver.newline_high = lcd_driver.fonts_UTF8_cut->high;//更新\n换行间距
		OLED_Draw_UTF8_String(0,0,(uint8_t*)"Fonts 中文\n8x16\n16x16");
	}while(LCD_Refresh());//直到每行都刷完
	delay_ms(DEMO_DELAY_MS);

	//--------------文字显示字体2-----------------
	do
	{
		//0.---等待发送完毕---
		while(LCD_is_Busy()!=0);//DMA方式专用,其他模式可省略
		//1.---清空缓存---
		OLED_Clear_GRAM();
		//2.-----绘图-----
		lcd_driver.fonts_ASCII = &ascii_SongTi_6X12;//ASCII字体
		lcd_driver.fonts_UTF8_cut = &SongTi_UTF8_12X12;//UTF8字体(裁切)
		lcd_driver.newline_high = lcd_driver.fonts_UTF8_cut->high;//更新\n换行间距
		OLED_Draw_UTF8_String(0,0,(uint8_t*)"Fonts 中文\n6x12\12x12");
	}while(LCD_Refresh());//直到每行都刷完
	delay_ms(DEMO_DELAY_MS);
	

	

	//--------------------画线-----------------------
	{
		uint16_t x=0;
		while(x <= SCREEN_WIDTH-1)
		{
			do
			{
				//0.---等待发送完毕---
				while(LCD_is_Busy()!=0);//DMA方式专用,其他模式可省略
				//1.---清空缓存---
				OLED_Clear_GRAM();
				//2.-----绘图-----
				OLED_Draw_Line(0,0,x,SCREEN_HIGH-1);
				OLED_Draw_Line(SCREEN_WIDTH-1,0,SCREEN_WIDTH-1-x,SCREEN_HIGH-1);
				
			}while(LCD_Refresh());//直到每行都刷完
			x++;
		}
	}
	
	{
		uint16_t y=0;
		while(y <= SCREEN_HIGH-1)
		{
			do
			{
				//0.---等待发送完毕---
				while(LCD_is_Busy()!=0);//DMA方式专用,其他模式可省略
				//1.---清空缓存---
				OLED_Clear_GRAM();
				//2.-----绘图-----
				OLED_Draw_Line(0,0,SCREEN_WIDTH-1,SCREEN_HIGH-y);
				OLED_Draw_Line(SCREEN_WIDTH-1,0,0,SCREEN_HIGH-y);
				
			}while(LCD_Refresh());//直到每行都刷完
			y++;
		}
	}
	//--------------------画圆-----------------------
	{
		uint8_t i=0;
		uint8_t C[]=
		{
			C_RU,//右上八分之一圆
			C_UR,//上右八分之一圆
			C_UL,//上左八分之一圆
			C_LU,//左上八分之一圆
			C_LD,//左下八分之一圆
			C_DL,//下左八分之一圆
			C_DR,//下右八分之一圆
			C_RD,//右下八分之一圆
			
			C_QRU,//右上角四分圆
			C_QLU,//左上角四分圆
			C_QLD,//左下角四分圆
			C_QRD,//右下角四分圆
			
			C_HR,//右半圆
			C_HU,//上半圆
			C_HL,//左半圆
			C_HD,//下半圆
			
			C_HR|C_UL,//右半圆+上左 (任意组合)
			C_HU|C_LD,//上半圆+左下
			C_HL|C_DR,//左半圆+下右
			C_HD|C_RU,//下半圆+右上

			C_ALL,//完整的园
		};
		while(i<=(sizeof(C)/sizeof(uint8_t)-1))
		{
			do
			{
				while(LCD_is_Busy()!=0);//DMA方式专用,其他模式可省略
				OLED_Clear_GRAM();
				OLED_Draw_Circel_part(32,20,16,(circle_part_t)C[i]);
				OLED_Fill_Circel_part(SCREEN_WIDTH-32,16,16,(circle_part_t)C[i]);
			}while(LCD_Refresh());//直到每行都刷完
			delay_ms(50);
			i++;
		}
	}
	delay_ms(DEMO_DELAY_MS);
	
	//--------------------矩形-----------------------
	{
		uint16_t i=0;
		while((i<SCREEN_HIGH) || (i<SCREEN_WIDTH))
		{
			uint8_t x,y;
			if(i < SCREEN_WIDTH){x=i;}else{x=SCREEN_WIDTH-1;}
			if(i < SCREEN_HIGH){y=i;}else{y=SCREEN_HIGH-1;}
			do
			{
				while(LCD_is_Busy()!=0);//DMA方式专用,其他模式可省略
				OLED_Clear_GRAM();
				OLED_Draw_Box(0,0, x, y);
			}while(LCD_Refresh());
			i++;
		}
	}
	delay_ms(DEMO_DELAY_MS);
	{
		uint16_t i=0;
		while((i<SCREEN_HIGH) || (i<SCREEN_WIDTH))
		{
			uint8_t x,y;
			if(i < SCREEN_WIDTH){x=i;}else{x=SCREEN_WIDTH-1;}
			if(i < SCREEN_HIGH){y=i;}else{y=SCREEN_HIGH-1;}
			do
			{
				while(LCD_is_Busy()!=0);//DMA方式专用,其他模式可省略
				OLED_Clear_GRAM();
				OLED_Fill_Box(0,0, x, y);
			}while(LCD_Refresh());
			i++;
		}
	}
	delay_ms(DEMO_DELAY_MS);
	
	//--------------------圆角矩形-----------------------
	{
		uint16_t r=0;
		while(r<SCREEN_HIGH)
		{
			do
			{
				while(LCD_is_Busy()!=0);//DMA方式专用,其他模式可省略
				OLED_Clear_GRAM();
				OLED_Draw_RBox(0,0,SCREEN_WIDTH-1, SCREEN_HIGH-1,r);
			}while(LCD_Refresh());
			r++;
		}
	}
	delay_ms(DEMO_DELAY_MS);
	{
		uint16_t r=0;
		while(r<SCREEN_HIGH)
		{
			do
			{
				while(LCD_is_Busy()!=0);//DMA方式专用,其他模式可省略
				OLED_Clear_GRAM();
				OLED_Fill_RBox(0,0,SCREEN_WIDTH-1, SCREEN_HIGH-1,r);
			}while(LCD_Refresh());
			r++;
		}
	}
	delay_ms(DEMO_DELAY_MS);
	//--------------------十进制数字-----------------------
	{
		int16_t r=-500;
		while(r<1200)
		{
			do
			{
				while(LCD_is_Busy()!=0);//DMA方式专用,其他模式可省略
				OLED_Clear_GRAM();
				OLED_Draw_int32(0,0,r);//十进制带符号
			}while(LCD_Refresh());
			//delay_ms(5);
			r++;
		}
	}
	delay_ms(DEMO_DELAY_MS);
	
	//--------------------刷点驱动切换-----------------------
	do
	{
		while(LCD_is_Busy()!=0);//DMA方式专用,其他模式可省略
		
		OLED_Set_Driver_Mode(write_1);//写1模式(普通) 白点模式
		OLED_Clear_GRAM();
		
		//填充
		OLED_Fill_RBox(0,0, SCREEN_WIDTH-1, SCREEN_HIGH-1,8);//倒圆方框

		//挖空
	  OLED_Set_Driver_Mode(write_0);//写0模式(普通) 黑点模式
		OLED_Fill_RBox(10,2, 50, 30,2);//倒圆方框
		
		//反写文字
	  OLED_Set_Driver_Mode(write_inverse);//反写模式(普通)
		OLED_Draw_UTF8_String(10,1,(uint8_t*)"Fill_RBox_ABCDEFGHIJK");

	}while(LCD_Refresh());//直到每行都刷完
	delay_ms(800);
	
	//恢复正常的刷点模式
	OLED_Set_Driver_Mode(write_1);//写1模式(普通) 白点模式


	//--------------------图片demo----------------------
	do
	{
		//0.---等待发送完毕---
		while(LCD_is_Busy()!=0);//DMA方式专用,其他模式可省略
		
		//1.---清空缓存---
		OLED_Clear_GRAM();
		//2.-----绘图-----
		
		OLED_Draw_Bitmap(
											0,    //x位置
											0,    //y位置
											128,  //图片宽
											64,   //图片高
		                  (uint8_t*)demo_bitmap_128x64 //图片数组
		                 );
		
	}while(LCD_Refresh());//直到每行都刷完
	delay_ms(DEMO_DELAY_MS);


}

/*--------------------------------------------------------------
	* 暂不支持使用ARMV6编译,请使用ARMV5编译器
  * 修改oled_Wegui_Config.h即可快速上手点屏
----------------------------------------------------------------*/
int main(void)
{
	startup_init();
	
	//本框架"Driver"部分为高效率点阵OLED驱动,类与U8G2,但速度比U8G2快,可单独移植使用移植,demo程序 gui_demo();
	lcd_driver_Init();
	
	//本框架Wegui部分为多级菜单图形动画ui,处理多级菜单,过度动画等
	OLED_Wegui_Init();
	
	sys1ms_stick = 0;
	while (1)
	{
		//--------------刷图DEMO---------------
		//gui_demo();//刷图demo
		
		//------------多级菜单DEMO-------------
		Wegui_loop_func();//Wegui循环驱动
		
		//--------------主循环-----------------
		if(sys1ms_stick)//1ms动作
		{
			
			sys1ms_stick--;
			LED_Func();//闪灯 若程序阻塞,灯会闪变慢
			if(adc_en)
			{
				ResADC = ADC_GetConversionValue(ADC1);//检测外部可调电阻ADC,取其值用于控件菜单演示
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);
			}
		}
	}
}


