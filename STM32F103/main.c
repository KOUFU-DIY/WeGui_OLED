
#include "main.h"


uint16_t ResADC=0;
uint8_t adc_en=1;

void startup_init()
{
	//--系统滴答1ms定时--
	sys1ms_stick = 0;
	SysTick_Config(SystemCoreClock / 1000);
	
	
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
}

void delay_ms(uint32_t ms)
{
	sys1ms_delay = ms;
	while(sys1ms_delay);
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

/*--------------------------------------------------------------
	* 暂不支持使用ARMV6编译,请使用ARMV5编译器
  * 修改oled_wegui_Config.h即可快速上手点屏
----------------------------------------------------------------*/
int main(void)
{
	startup_init();
	
	//本框架"Driver"部分为高效率点阵OLED驱动,类与U8G2,但速度比U8G2快8倍,可单独移植
	OLED_Driver_Init();
	
	//本框架Wegui部分为图形动画ui,处理多级菜单,过度动画等
	OLED_Wegui_Init();

	sys1ms_stick = 0;
	
	while (1)
	{
		wegui_loop_func();//wegui循环驱动
		
		if(sys1ms_stick)//1ms动作
		{
			sys1ms_stick--;
			LED_Func();//闪灯 若程序阻塞,灯会闪变慢
			if(adc_en)
			{
				ResADC = ADC_GetConversionValue(ADC1);//检测外部可调电阻,取其值用于控件延时
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);
			}
		}
	}
}


