#ifndef _STM32F103_WEGUI_PORT_H_
#define _STM32F103_WEGUI_PORT_H_

#include "stm32f10x.h"
#include "oled_wegui_driver.h"



//-------------------------------------结构体-------------------------------------
typedef enum Key_return
{
	key_return_none = 0 ,
	start_short_press,           //开始短按
	start_long_press,            //开始长按
	start_long_long_press,       //开始超长按
	long_press_trig,             //连续长按(机关枪)
	long_long_press_trig,        //连续超长按(机关枪)
	end_short_press,             //短按结束
	end_long_press,              //长按结束
	end_long_long_press,         //超长按结束
	
}Key_return_t;

typedef enum Key_state
{
	key_state_none = 0,
	short_press_and_hold,         //短按中
	long_press_and_hold,          //长按中
	long_long_press_and_hold,     //超长按中
}Key_state_t;

typedef struct mykey
{
	Key_state_t keysw_state;
	uint16_t keysw_det_count;
	uint16_t keysw_det_count2;
}mykey_t;













//-------------------------------------按键配置-------------------------------------


#define Wegui_Key1_GPIOx                 GPIOC
#define Wegui_Key1_GPIO_Pin_x            GPIO_Pin_15
#define Wegui_Key1_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOC
#define WEGUI_Key1_IO_Init()                                        \
do                                                                  \
{                                                                   \
    GPIO_InitTypeDef GPIO_InitStruct;                               \
    GPIO_InitStruct.GPIO_Pin   = Wegui_Key1_GPIO_Pin_x;             \
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
	  RCC_APB2PeriphClockCmd(Wegui_Key1_RCC_APB2Periph_GPIOx,ENABLE); \
    GPIO_Init(Wegui_Key1_GPIOx, &GPIO_InitStruct);                  \
}while(0)

#define Wegui_Key2_GPIOx                 GPIOA
#define Wegui_Key2_GPIO_Pin_x            GPIO_Pin_0
#define Wegui_Key2_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOA
#define WEGUI_Key2_IO_Init()                                        \
do                                                                  \
{                                                                   \
    GPIO_InitTypeDef GPIO_InitStruct;                               \
    GPIO_InitStruct.GPIO_Pin   = Wegui_Key2_GPIO_Pin_x;             \
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
	  RCC_APB2PeriphClockCmd(Wegui_Key2_RCC_APB2Periph_GPIOx,ENABLE); \
    GPIO_Init(Wegui_Key2_GPIOx, &GPIO_InitStruct);                  \
}while(0)

#define Wegui_Key3_GPIOx                 GPIOB
#define Wegui_Key3_GPIO_Pin_x            GPIO_Pin_12
#define Wegui_Key3_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOB
#define WEGUI_Key3_IO_Init()                                        \
do                                                                  \
{                                                                   \
    GPIO_InitTypeDef GPIO_InitStruct;                               \
    GPIO_InitStruct.GPIO_Pin   = Wegui_Key3_GPIO_Pin_x;             \
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
	  RCC_APB2PeriphClockCmd(Wegui_Key3_RCC_APB2Periph_GPIOx,ENABLE); \
    GPIO_Init(Wegui_Key3_GPIOx, &GPIO_InitStruct);                  \
}while(0)

#define Wegui_Key4_GPIOx                 GPIOB
#define Wegui_Key4_GPIO_Pin_x            GPIO_Pin_13
#define Wegui_Key4_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOB
#define WEGUI_Key4_IO_Init()                                        \
do                                                                  \
{                                                                   \
    GPIO_InitTypeDef GPIO_InitStruct;                               \
    GPIO_InitStruct.GPIO_Pin   = Wegui_Key4_GPIO_Pin_x;             \
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
	  RCC_APB2PeriphClockCmd(Wegui_Key4_RCC_APB2Periph_GPIOx,ENABLE); \
    GPIO_Init(Wegui_Key4_GPIOx, &GPIO_InitStruct);                  \
}while(0)

#define Wegui_Key5_GPIOx                 GPIOB
#define Wegui_Key5_GPIO_Pin_x            GPIO_Pin_14
#define Wegui_Key5_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOB
#define WEGUI_Key5_IO_Init()                                        \
do                                                                  \
{                                                                   \
    GPIO_InitTypeDef GPIO_InitStruct;                               \
    GPIO_InitStruct.GPIO_Pin   = Wegui_Key5_GPIO_Pin_x;             \
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
	  RCC_APB2PeriphClockCmd(Wegui_Key5_RCC_APB2Periph_GPIOx,ENABLE); \
    GPIO_Init(Wegui_Key5_GPIOx, &GPIO_InitStruct);                  \
}while(0)

#define Wegui_Key6_GPIOx                 GPIOB
#define Wegui_Key6_GPIO_Pin_x            GPIO_Pin_15
#define Wegui_Key6_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOB
#define WEGUI_Key6_IO_Init()                                        \
do                                                                  \
{                                                                   \
    GPIO_InitTypeDef GPIO_InitStruct;                               \
    GPIO_InitStruct.GPIO_Pin   = Wegui_Key6_GPIO_Pin_x;             \
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
	  RCC_APB2PeriphClockCmd(Wegui_Key6_RCC_APB2Periph_GPIOx,ENABLE); \
    GPIO_Init(Wegui_Key6_GPIOx, &GPIO_InitStruct);                  \
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
#define Bool_Wkey1_is_Pressed() (GPIO_ReadInputDataBit(Wegui_Key1_GPIOx, Wegui_Key1_GPIO_Pin_x) == RESET)
#define Bool_Wkey2_is_Pressed() (GPIO_ReadInputDataBit(Wegui_Key2_GPIOx, Wegui_Key2_GPIO_Pin_x) == RESET)
#define Bool_Wkey3_is_Pressed() (GPIO_ReadInputDataBit(Wegui_Key3_GPIOx, Wegui_Key3_GPIO_Pin_x) == RESET)
#define Bool_Wkey4_is_Pressed() (GPIO_ReadInputDataBit(Wegui_Key4_GPIOx, Wegui_Key4_GPIO_Pin_x) == RESET)
#define Bool_Wkey5_is_Pressed() (GPIO_ReadInputDataBit(Wegui_Key5_GPIOx, Wegui_Key5_GPIO_Pin_x) == RESET)
#define Bool_Wkey6_is_Pressed() (GPIO_ReadInputDataBit(Wegui_Key6_GPIOx, Wegui_Key6_GPIO_Pin_x) == RESET)





//开发板90度垂直显示按键
//#define Bool_Wkey1_is_Pressed() (GPIO_ReadInputDataBit(Wegui_Key1_GPIOx, Wegui_Key1_GPIO_Pin_x) == RESET)
//#define Bool_Wkey2_is_Pressed() (GPIO_ReadInputDataBit(Wegui_Key2_GPIOx, Wegui_Key2_GPIO_Pin_x) == RESET)
//#define Bool_Wkey3_is_Pressed() (GPIO_ReadInputDataBit(Wegui_Key4_GPIOx, Wegui_Key4_GPIO_Pin_x) == RESET)
//#define Bool_Wkey4_is_Pressed() (GPIO_ReadInputDataBit(Wegui_Key6_GPIOx, Wegui_Key6_GPIO_Pin_x) == RESET)
//#define Bool_Wkey5_is_Pressed() (GPIO_ReadInputDataBit(Wegui_Key3_GPIOx, Wegui_Key3_GPIO_Pin_x) == RESET)
//#define Bool_Wkey6_is_Pressed() (GPIO_ReadInputDataBit(Wegui_Key5_GPIOx, Wegui_Key5_GPIO_Pin_x) == RESET)








//-------------------------------------声明-------------------------------------

extern mykey_t key_left;
extern mykey_t key_right;
extern mykey_t key_up;
extern mykey_t key_down;
extern mykey_t key_ok;
extern mykey_t key_back;

void wegui_port_Init();
void wegui_1ms_Stick();//放到1ms中断
Key_return_t Keysw_det(mykey_t *p ,uint8_t pin_state,uint16_t ms_stick);


#endif