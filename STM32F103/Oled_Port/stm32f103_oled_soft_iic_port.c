#include "oled_wegui_Config.h"


#ifdef OLED_USE_SOFT_IIC


#include "stm32f103_oled_soft_iic_port.h"
#include "stdint.h"



/*--------------------------------------------------------------
	* 暂不支持使用ARMV6编译,请使用ARMV5编译器
----------------------------------------------------------------*/


//I2C延迟信号 设置
//速度最快(屏幕点不亮选择慢速)
//#define I2C_SCL_Rise_Delay() {volatile uint8_t t=0;while(t--);}
//#define I2C_SCL_Fall_Delay() {volatile uint8_t t=0;while(t--);}
//#define I2C_SDA_Rise_Delay() {volatile uint8_t t=5;while(t--);}
//#define I2C_SDA_Fall_Delay() {volatile uint8_t t=0;while(t--);}

//速度较快
//#define I2C_SCL_Rise_Delay() {volatile uint8_t t=1;while(t--);}
//#define I2C_SCL_Fall_Delay() {volatile uint8_t t=1;while(t--);}
//#define I2C_SDA_Rise_Delay() {volatile uint8_t t=1;while(t--);}
//#define I2C_SDA_Fall_Delay() {volatile uint8_t t=1;while(t--);}

//速度稍快2
//#define I2C_SCL_Rise_Delay() {volatile uint8_t t=2;while(t--);}
//#define I2C_SCL_Fall_Delay() {volatile uint8_t t=2;while(t--);}
//#define I2C_SDA_Rise_Delay() {volatile uint8_t t=2;while(t--);}
//#define I2C_SDA_Fall_Delay() {volatile uint8_t t=2;while(t--);}

//速度适中
#define I2C_SCL_Rise_Delay() {volatile uint8_t t=5;while(t--);}
#define I2C_SCL_Fall_Delay() {volatile uint8_t t=5;while(t--);}
#define I2C_SDA_Rise_Delay() {volatile uint8_t t=5;while(t--);}
#define I2C_SDA_Fall_Delay() {volatile uint8_t t=5;while(t--);}

//速度最慢
//#define I2C_SCL_Rise_Delay() {volatile uint8_t t=10;while(t--);}
//#define I2C_SCL_Fall_Delay() {volatile uint8_t t=10;while(t--);}
//#define I2C_SDA_Rise_Delay() {volatile uint8_t t=10;while(t--);}
//#define I2C_SDA_Fall_Delay() {volatile uint8_t t=10;while(t--);}


//I2C起始信号
static void OLED_I2C_Start(void)
{
	OLED_SDA_Clr();I2C_SDA_Fall_Delay();
	OLED_SCL_Clr();
}

//I2C结束信号
static void OLED_I2C_Stop(void)
{
	//OLED_SCL_Clr();//初始化确保状态正确
	
	OLED_SDA_Clr();I2C_SDA_Fall_Delay();
	OLED_SCL_Set();I2C_SCL_Rise_Delay();
	OLED_SDA_Set();I2C_SDA_Rise_Delay();
}

//I2C等待信号响应
static void OLED_I2C_WaitAck(void)
{
	OLED_SDA_Set();I2C_SDA_Rise_Delay();
	OLED_SCL_Set();I2C_SCL_Rise_Delay();
	OLED_SCL_Clr();I2C_SCL_Fall_Delay();
}
//I2C发送1字节数据
static void I2C_send_1Byte(uint8_t dat)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		if(dat&0x80)//将dat的8位从最高位依次写入
		{
			__NOP();
			OLED_SCL_Clr();I2C_SCL_Fall_Delay();
			OLED_SDA_Set();I2C_SDA_Rise_Delay();
    }
		else
		{
			OLED_SCL_Clr();I2C_SCL_Fall_Delay();
			OLED_SDA_Clr();I2C_SDA_Fall_Delay();
    }
		
		dat<<=1;
		OLED_SCL_Set();I2C_SCL_Rise_Delay();
		
  }
	__NOP();__NOP();__NOP();
	OLED_SCL_Clr();I2C_SCL_Fall_Delay();
}


/*--------------------------------------------------------------
  * 名称: OLED_send_1Cmd(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: 向屏幕发送1个命令
  * 说明: 
----------------------------------------------------------------*/
void OLED_send_1Cmd(uint8_t dat) __attribute__((optimize("O0")))
{
	OLED_I2C_Start();
	I2C_send_1Byte(OLED_IIC_7ADDR<<1);
	OLED_I2C_WaitAck();
  I2C_send_1Byte(0x00);
	OLED_I2C_WaitAck();
	I2C_send_1Byte(dat);
	OLED_I2C_WaitAck();
	OLED_I2C_Stop();
}

/*--------------------------------------------------------------
  * 名称: OLED_send_1Data(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: 向屏幕发送1个数据
  * 说明: 
----------------------------------------------------------------*/
void OLED_send_1Data(uint8_t dat) __attribute__((optimize("O0")))
{
	OLED_I2C_Start();
	I2C_send_1Byte(OLED_IIC_7ADDR<<1);
	OLED_I2C_WaitAck();
	I2C_send_1Byte(0x40);
	OLED_I2C_WaitAck();
	I2C_send_1Byte(dat);
	OLED_I2C_WaitAck();
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
	OLED_I2C_Start();
	I2C_send_1Byte(OLED_IIC_7ADDR<<1);
	OLED_I2C_WaitAck();
	I2C_send_1Byte(0x40);
	OLED_I2C_WaitAck();
	uint8_t i=0;
	while(num>i)
	{
		I2C_send_1Byte(p[i]);
		OLED_I2C_WaitAck();
		i++;
	}
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
	OLED_I2C_Start();
	I2C_send_1Byte(OLED_IIC_7ADDR<<1);
	OLED_I2C_WaitAck();
	I2C_send_1Byte(0x00);
	OLED_I2C_WaitAck();
	uint8_t i=0;
	while(num>i)
	{
		I2C_send_1Byte(p[i]);
		OLED_I2C_WaitAck();
		i++;
	}
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
	
	OLED_RES_Clr();
	{
		volatile unsigned int i=10000;
		while(i--);
	}
	OLED_RES_Set();

}

#endif