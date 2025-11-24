#include "dht20.h"
#include "usart.h"
#include "Delay.h"

#define DHT20_ADDRESS		0x38

/*写寄存器，
*函数参数：
	RegAddress：寄存器地址
	Data：要写的数据
*/
void DHT20_W_Reg(uint8_t RegAddress, uint8_t Data)
{
	I2C_GenerateSTART(I2C1, ENABLE);	//起始位
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)	//等待主机模式选择完成EV5事件
	{
//		printf("W等待主机模式选择完成EV5事件……");
	}
//	I2C_Send7bitAddress(I2C1, DHT20_ADDRESS, I2C_Direction_Transmitter);	//发送地址
	I2C_SendData(I2C1, (DHT20_ADDRESS << 1));//发送地址
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS)	
	{//等待从机回应ACK，EV6事件
//		printf("W等待从机回应ACK1，EV6事件……");
	}
	I2C_SendData(I2C1, RegAddress);	//发送从设备寄存器地址
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS)	
	{//字节正在发送，EV8事件
//		printf("W从设备寄存器地址正在发送，EV8事件……");
	}
	I2C_SendData(I2C1, Data);	//发送要写入从设备寄存器地址的数据	注：每写/读一位，从设备指针自动后移一位
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS)	
	{//等待移位完成，EV8_2事件
//		printf("W数据正在发送，等待EV8_2事件……");
	}
//	
	I2C_SendData(I2C1, 0x00);	//发送要写入从设备寄存器地址的数据	注：每写/读一位，从设备指针自动后移一位
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)	
	{//等待移位完成，EV8_2事件
//		printf("W数据正在发送，等待EV8_2事件……");
	}
	
	I2C_GenerateSTOP(I2C1, ENABLE);
	delay_ms(100);
}

/*读寄存器，
*函数参数：
	RegAddress：寄存器地址
*/
uint8_t DHT20_R_Reg(uint8_t RegAddress)
{
	uint8_t Data = 0;
	I2C_GenerateSTART(I2C1, ENABLE);	//起始位
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)	//等待主机模式选择完成EV5事件
	{
		printf("R等待主机模式选择完成EV5事件……");
	}
	I2C_Send7bitAddress(I2C1, DHT20_ADDRESS, I2C_Direction_Transmitter);	
//	I2C_SendData(I2C1, (DHT20_ADDRESS << 1));	//发送从设备寄存器地址//发送地址
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS)	
	{//等待从机回应ACK，EV6事件
		printf("等待从机回应ACK，EV6事件……");
	}
	I2C_SendData(I2C1, RegAddress);	//发送从设备寄存器地址
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)	
	{//等待数据发送完毕，EV8_2事件
		printf("R等待数据发送完毕，EV8_2事件……");
	}
	
	I2C_GenerateSTART(I2C1, ENABLE);	//重复起始位
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)	//等待主机模式选择完成EV5事件
	{
		printf("R等待主机模式选择完成EV5事件……");
	}
	
	I2C_Send7bitAddress(I2C1, DHT20_ADDRESS, I2C_Direction_Receiver);	//接收模式
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS)	
	{//等待主机接收，EV6事件
		printf("等待从机回应ACK，EV6事件……");
	}
	
	I2C_AcknowledgeConfig(I2C1, DISABLE);	//先给非应答
	I2C_GenerateSTOP(I2C1, ENABLE);	//停止标志位
	
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS)	
	{//接收一个字节，EV7事件
		printf("R接收一个字节，EV7事件……");
	}
	
	Data = I2C_ReceiveData(I2C1);	//读取DR
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);	//回应ACK
	
	return Data;
}

/*读取DHT20状态字，
*函数参数：
	RegAddress：寄存器地址
*/
void DHT20_S_Reg(uint8_t RegAddress, uint8_t Data[])
{
	I2C_GenerateSTART(I2C1, ENABLE);	//起始位
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)	//等待主机模式选择完成EV5事件
	{
//		printf("等待主机模式选择完成EV5事件……");
	}
	
	I2C_SendData(I2C1, RegAddress);	//接收模式
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS)	//等待主机模式选择完成EV5事件
	{
//		printf("等待建立通信完成EV6事件……");
	}
	
	for(int i = 0; i < 5; i++)
	{
		I2C_AcknowledgeConfig(I2C1, DISABLE);	//先给非应答
		Data[i] = I2C_ReceiveData(I2C1);	//读取DR
		I2C_AcknowledgeConfig(I2C1, ENABLE);	//回应ACK
		while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
	}
	
	I2C_AcknowledgeConfig(I2C1, DISABLE);	//先给非应答
	Data[5] = I2C_ReceiveData(I2C1);	//读取DR
	
	I2C_GenerateSTOP(I2C1, ENABLE);	//停止标志位
}


/* DHT20初始化 */
uint8_t DHT20_Init(void)
{
    uint8_t status;
    uint8_t data[6];
    
    delay_ms(100); // 上电延时
    
    // 读取初始状态
    DHT20_S_Reg(0x71, data);
		status = data[0];
    printf("初始状态: 0x%02X\n", status);
    
    // 如果传感器需要初始化，发送初始化命令
    if((status & 0x18) != 0x18) // 检查校准状态位
    {
        printf("传感器需要初始化...\n");
        
        // 发送初始化命令
        I2C_GenerateSTART(I2C1, ENABLE);
        while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
        
        I2C_SendData(I2C1, (DHT20_ADDRESS << 1) | 0x00);
        while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
        
        I2C_SendData(I2C1, 0xBE); // 初始化命令
        while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
        
        I2C_SendData(I2C1, 0x08); // 参数
        while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
        
        I2C_SendData(I2C1, 0x00); // 参数
        while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
        
        I2C_GenerateSTOP(I2C1, ENABLE);
        
        delay_ms(10);
    }
    
    return 1;
}


