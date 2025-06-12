#include "oled_wegui_Config.h"
#ifdef OLED_USE_HARD_IIC

#include "stdint.h"
#include "stm32f103_oled_hard_iic_port.h"




/*--------------------------------------------------------------
	* 暂不支持使用ARMV6编译,请使用ARMV5编译器
----------------------------------------------------------------*/



/*--------------------------------------------------------------
  * IIC基础接口驱动
----------------------------------------------------------------*/
#define OLED_HARD_IIC_TIMEOUT_UINT8 80 //硬件IIC超时退出时间


//I2C起始信号
#define OLED_I2C_Start()  do                                    \
{	                                                              \
	Timeout = OLED_HARD_IIC_TIMEOUT_UINT8;                        \
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY))                 \
	{                                                             \
		if((Timeout--) == 0) break;                                 \
	}                                                             \
	I2C_GenerateSTART(I2C2, ENABLE);                              \
	Timeout = OLED_HARD_IIC_TIMEOUT_UINT8;                        \
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))    \
	{                                                             \
		if((Timeout--) == 0) break;                                 \
	}                                                             \
}while(0)

//I2C结束信号
#define OLED_I2C_Stop() do                                         \
{                                                                  \
	Timeout = OLED_HARD_IIC_TIMEOUT_UINT8;                  \
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))  \
	{                                                                \
		if((Timeout--) == 0) break;                                    \
	}                                                                \
	I2C_GenerateSTOP(I2C2, ENABLE);                                  \
}while(0)



//I2C发送地址
#define OLED_I2C_SendAddr(addr) do                                          \
{                                                                           \
	Timeout = OLED_HARD_IIC_TIMEOUT_UINT8;                                    \
	I2C_Send7bitAddress(I2C2, addr, I2C_Direction_Transmitter);               \
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))  \
	{                                                                         \
		if((Timeout--) == 0) break;                                             \
	}                                                                         \
}while(0)


//I2C发送1字节数据
#define OLED_I2C_send_1Byte(dat)  do                                       \
{                                                                          \
	Timeout = OLED_HARD_IIC_TIMEOUT_UINT8;                                   \
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING)) \
	{                                                                        \
		if((Timeout--) == 0) break;                                            \
	}                                                                        \
	I2C_SendData(I2C2, dat);                                                 \
}while(0)



/*--------------------------------------------------------------
  * 名称: OLED_send_1Cmd(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: 向屏幕发送1个命令
  * 说明: 
----------------------------------------------------------------*/
void OLED_send_1Cmd(uint8_t dat)
{
	uint16_t Timeout;
	//------------起始信号------------
	OLED_I2C_Start();
	//------------发送地址------------	
	OLED_I2C_SendAddr(OLED_IIC_7ADDR<<1);
	//------------发送数据------------
	OLED_I2C_send_1Byte(0x00);              
	OLED_I2C_send_1Byte(dat);
	//------------结束信号------------                                                           
	OLED_I2C_Stop();  
}

/*--------------------------------------------------------------
  * 名称: OLED_send_1Data(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: 向屏幕发送1个数据
  * 说明: 
----------------------------------------------------------------*/
void OLED_send_1Data(uint8_t dat)
{
	volatile uint16_t Timeout;
	//------------起始信号------------
	OLED_I2C_Start();
	//------------发送地址------------	
	OLED_I2C_SendAddr(OLED_IIC_7ADDR<<1);
	//------------发送数据------------
	OLED_I2C_send_1Byte(0x40);              
	OLED_I2C_send_1Byte(dat);
	//------------结束信号------------                                                           
	OLED_I2C_Stop();  
}

/*--------------------------------------------------------------
  * 名称: OLED_send_numData(uint8_t *p,uint16_t num)
  * 传入1: *p数组指针
  * 传入2: num发送数量
  * 返回: 无
  * 功能: 向屏幕发送num个数据
  * 说明: 
----------------------------------------------------------------*/
void OLED_send_numData(uint8_t *p,uint16_t num)
{
	uint16_t Timeout;
	uint16_t i;
	
	//------------起始信号------------
	OLED_I2C_Start();
	//------------发送地址------------	
	OLED_I2C_SendAddr(OLED_IIC_7ADDR<<1);
	//------------发送1+n个数据------------
	I2C_SendData(I2C2, 0x40);
	i=0;
	while(num>i)
	{
		Timeout = OLED_HARD_IIC_TIMEOUT_UINT8;
		while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING))
		{
			if((Timeout--) == 0) break;
		}
		I2C_SendData(I2C2, p[i]);
		i++;
	}                
	//------------结束信号------------                                                            
	OLED_I2C_Stop();                                 
}

/*--------------------------------------------------------------
  * 名称: OLED_send_numCmd(uint8_t *p,uint16_t num)
  * 传入1: *p数组指针
  * 传入2: num发送数量
  * 返回: 无
  * 功能: 向屏幕发送num个命令
  * 说明: 
----------------------------------------------------------------*/
void OLED_send_numCmd(uint8_t *p,uint16_t num)
{
	uint16_t Timeout;
	uint16_t i;
	
	//------------起始信号------------
	OLED_I2C_Start();
	//------------发送地址------------	
	OLED_I2C_SendAddr(OLED_IIC_7ADDR<<1);
	//------------发送1+n个指令------------
	I2C_SendData(I2C2, 0x00);
	i=0;
	while(num>i)
	{
		Timeout = OLED_HARD_IIC_TIMEOUT_UINT8;
		while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING))
		{
			if((Timeout--) == 0) break;
		}
		I2C_SendData(I2C2, p[i]);
		i++;
	}              
	//------------结束信号------------                                                           
	OLED_I2C_Stop();                               
}



/*--------------------------------------------------------------
  * 名称: OLED_delay_ms(volatile uint32_t ms)
  * 传入1: ms
  * 返回: 无
  * 功能: 软件延时
  * 说明: 非精准
----------------------------------------------------------------*/
void OLED_delay_ms(volatile uint32_t ms)
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
  * 名称: OLED_port_Init()
  * 传入: 无
  * 返回: 无
  * 功能: 屏幕接口初始化
  * 说明: 
----------------------------------------------------------------*/
void OLED_port_Init(void)
{
	OLED_SCL_IO_Init();
	OLED_SDA_IO_Init();
	OLED_RES_IO_Init();
	
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
	
	
	OLED_RES_Clr();
	{
		volatile unsigned int i=10000;
		while(i--);
	}
	OLED_RES_Set();
	
}

#endif