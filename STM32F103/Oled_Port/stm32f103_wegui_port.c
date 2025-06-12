#include "stm32f103_wegui_port.h"


mykey_t key_left;
mykey_t key_right;
mykey_t key_up;
mykey_t key_down;
mykey_t key_ok;
mykey_t key_back;



//----------------------------短按长按超长按+连续长按超长按------------------------------------
#define key_delay_count 10          //按下消抖次数
#define key_long_count 500          //"短按"到"长按"的计数时间
#define key_long_trig_count 80     //"连续长按"的机关枪间隔触发时间

#define key_long_long_count 2000    //"长按"到"超长按"的计数时间
#define key_long_long_trig_count 12 //"连续超长按"的机关枪间隔触发时间

Key_return_t Keysw_det(mykey_t *p,uint8_t pin_state,uint16_t ms_stick)
{
	if(pin_state)
	{
		p->keysw_det_count += ms_stick;
		switch(p->keysw_state)
		{
			case key_state_none:{p->keysw_det_count2=0;if(p->keysw_det_count>=key_delay_count){p->keysw_state=short_press_and_hold;p->keysw_det_count=0;return start_short_press;}}break;
			case short_press_and_hold:{p->keysw_det_count2=0;if(p->keysw_det_count>=key_long_count){p->keysw_state=long_press_and_hold;p->keysw_det_count=0;return start_long_press;};}break;
			case long_press_and_hold:{p->keysw_det_count2+=ms_stick;if((p->keysw_det_count>=key_long_long_count)){p->keysw_state=long_long_press_and_hold;p->keysw_det_count=0;return start_long_long_press;}if(p->keysw_det_count2>=key_long_trig_count){p->keysw_det_count2-=key_long_trig_count;return long_press_trig;}}break;
			case long_long_press_and_hold:{if(p->keysw_det_count>=key_long_long_trig_count){p->keysw_det_count=0;return long_long_press_trig;}}break;
		}
	}
	else
	{
		p->keysw_det_count2=0;
		switch(p->keysw_state)
		{	
			case key_state_none:{p->keysw_det_count=0;}break;
			case short_press_and_hold:{p->keysw_det_count=0;p->keysw_state=key_state_none;return end_short_press;}break;
			case long_press_and_hold:{p->keysw_det_count=0;p->keysw_state=key_state_none;return end_long_press;}break;
			case long_long_press_and_hold:{p->keysw_det_count=0;p->keysw_state=key_state_none;return end_long_press;}break;
		}
	}
	return key_return_none;
}

void Key_par_Init(mykey_t *p)
{
	p->keysw_state = key_state_none;
	p->keysw_det_count = 0;
	p->keysw_det_count2 = 0;
}




/*

void Wkey_Back_func(uint16_t ms_stick)
{
	switch(Keysw_det(&key_back ,Bool_Wkey1_is_Pressed(),ms_stick))
	{
		case start_short_press:       //开始短按
			break;
		case start_long_press:        //开始长按
			break;
		case end_short_press:					//结束短按
			break;
		case end_long_press:					//结束长按
			break;
		case end_long_long_press:			//结束超长按
			break;
		case long_press_trig:				  //连续长按
			break;
		case long_long_press_trig:    //连续超长按
			break;
		default:break;
	}
}
void Wkey_Ok_func(uint16_t ms_stick)
{
	switch(Keysw_det(&key_ok ,Bool_Wkey2_is_Pressed(),ms_stick))
	{
		case start_short_press:       //开始短按
			break;
		case start_long_press:        //开始长按
			break;
		case end_short_press:					//结束短按
			break;
		case end_long_press:					//结束长按
			break;
		case end_long_long_press:			//结束超长按
			break;
		case long_press_trig:				  //连续长按
			break;
		case long_long_press_trig:    //连续超长按
			break;
		default:break;
	}
}

void Wkey_Right_func(uint16_t ms_stick)
{
	switch(Keysw_det(&key_right ,Bool_Wkey3_is_Pressed(),ms_stick))
	{
		case start_short_press:       //开始短按
			break;
		case start_long_press:        //开始长按
			break;
		case end_short_press:					//结束短按
			break;
		case end_long_press:					//结束长按
			break;
		case end_long_long_press:			//结束超长按
			break;
		case long_press_trig:				  //连续长按
			break;
		case long_long_press_trig:    //连续超长按
			break;
		default:break;
	}
}

void Wkey_Up_func(uint16_t ms_stick)
{
	switch(Keysw_det(&key_up ,Bool_Wkey4_is_Pressed(),ms_stick))
	{
		case start_short_press:       //开始短按
		case start_long_press:        //开始长按
		case long_press_trig:				  //连续长按
			wegui_Key_Up();
			break;
		case end_short_press:					//结束短按
			break;
		case end_long_press:					//结束长按
			break;
		case end_long_long_press:			//结束超长按
			break;
		case long_long_press_trig:    //连续超长按
			break;
		default:break;
	}
}

void Wkey_Down_func(uint16_t ms_stick)
{
	switch(Keysw_det(&key_down ,Bool_Wkey5_is_Pressed(),ms_stick))
	{
		case start_short_press:       //开始短按
		case long_press_trig:				  //连续长按
		case start_long_press:        //开始长按
			wegui_Key_Down();
			break;
		case end_short_press:					//结束短按
			break;
		case end_long_press:					//结束长按
			break;
		case end_long_long_press:			//结束超长按
			break;
		
		case long_long_press_trig:    //连续超长按
			break;
		default:break;
	}
}

void Wkey_Left_func(uint16_t ms_stick)
{
	switch(Keysw_det(&key_left ,Bool_Wkey6_is_Pressed(),ms_stick))
	{
		case start_short_press:       //开始短按
			break;
		case start_long_press:        //开始长按
			break;
		case end_short_press:					//结束短按
			break;
		case end_long_press:					//结束长按
			break;
		case end_long_long_press:			//结束超长按
			break;
		case long_press_trig:				  //连续长按
			break;
		case long_long_press_trig:    //连续超长按
			break;
		default:break;
	}
}
*/


void wegui_1ms_Stick()
{
	if(wegui_1ms_stick < 65535)
		wegui_1ms_stick++;
}

void wegui_port_Init()
{
	WEGUI_Key1_IO_Init();
	WEGUI_Key2_IO_Init();
	WEGUI_Key3_IO_Init();
	WEGUI_Key4_IO_Init();
	WEGUI_Key5_IO_Init();
	WEGUI_Key6_IO_Init();
	
	Key_par_Init(&key_left);
	Key_par_Init(&key_right);
	Key_par_Init(&key_up);
	Key_par_Init(&key_down);
	Key_par_Init(&key_ok);
	Key_par_Init(&key_back);
	
	wegui_1ms_stick = 0;
}


