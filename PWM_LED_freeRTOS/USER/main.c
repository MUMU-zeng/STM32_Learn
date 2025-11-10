#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "timer.h"
#include "freertos_demo.h"
#include "PWM.h"
//ALIENTEK Mini STM32开发板范例代码27
//内存管理实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 

u16 key;
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
 
	freertos_demo();
	
	 
}











