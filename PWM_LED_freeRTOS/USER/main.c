#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "timer.h"
#include "freertos_demo.h"
#include "PWM.h"
#include "myI2C.h"
#include "dht20.h"
//ALIENTEK Mini STM32开发板范例代码27
//内存管理实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 

u16 key, status;
uint8_t data[6];
int main(void)
{ 
		 
	u8 i=0;	    
	u8 *p=0;
	u8 *tp=0;
	u8 paddr[18];			//存放P Addr:+p地址的ASCII值 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
//	LED_Init();		  		//初始化与LED连接的硬件接口
	PWM_Init();
	KEY_Init();				//按键初始化   
	//TIM3_Int_Init(4999,7199);//10Khz的计数频率，计数到5000为500ms  
	//mem_init();				//初始化内存池
	SendString(USART1, "PowerOn!");
	
	IIC_init();
	printf("系统启动...\n");
  delay_ms(1000); // 等待系统稳定
    
	// 初始化DHT20
//	if(DHT20_Init())
//	{
//			printf("DHT20初始化成功\n");
//	}
//	else
//	{
//			printf("DHT20初始化失败\n");
//			while(1);
//	}
	
	while(1)
	{
		DHT20_W_Reg(0xAC, 0x33);
		delay_ms(100);
		// 读取数据
		DHT20_S_Reg(0x71, data);
		
		
		delay_ms(2000); // 2秒测量一次
		
	}
	
//	freertos_demo();
	
	 
}











