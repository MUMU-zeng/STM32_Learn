#include "myI2C.h"

//硬件iic，引脚PB7->SDA，PB6->SCL
//硬件I2C初始化
void IIC_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	I2C_InitTypeDef I2C_InitStructer;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;				 //PB.6 PB.7端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; 		 //复用开漏
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.8
	
	
	
	I2C_InitStructer.I2C_Mode 								= I2C_Mode_I2C;	//模式
	I2C_InitStructer.I2C_ClockSpeed 					= 100000;	//时钟速度，最大400000
	I2C_InitStructer.I2C_DutyCycle 						= I2C_DutyCycle_2;	//占空比
	I2C_InitStructer.I2C_Ack 									= I2C_Ack_Enable;	//接收字节后给从机Ack应答使能
	I2C_InitStructer.I2C_AcknowledgedAddress 	= I2C_AcknowledgedAddress_7bit;	//作为从机时，地址字节多少位
	I2C_InitStructer.I2C_OwnAddress1 					= 0x66;	//当设备为从模式的地址
	
	I2C_Init(I2C1, &I2C_InitStructer);
	
	I2C_Cmd(I2C1, ENABLE);
}



