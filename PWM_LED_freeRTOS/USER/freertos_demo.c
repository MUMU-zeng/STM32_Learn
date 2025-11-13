/**
******************************************************************************
*@file main.c
*@author正点原子团队(ALIENTEK)
*@version V1.4
*@date 2022-01-04
*@brief FreeRTOS移植实验
*@license Copyright(c)2020-2032,广州市星翼电子科技有限公司
******************************************************************************
*@attention
*
*实验平台:正点原子战舰F103开发板
*在线视频:www.yuanzige.com
*技术论坛:www.openedv.com
*公司网址:www.alientek.com
*购买地址:openedv.taobao.com
*
******************************************************************************
*/
#include "freertos_demo.h"
#include "usart.h"
#include "key.h"
/*FreeRTOS********************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "PWM.h"
/*****************************************************************************/
/*FreeRTOS配置*/
/*START_TASK任务配置
*包括:任务句柄任务优先级堆栈大小创建任务
*/
#define START_TASK_PRIO	1//优先级
#define START_TASK_SIZE	64//堆栈大小
TaskHandle_t StartTask_Handler;/*任务句柄*/
void start_task(void* pvParameters);	//任务函数

/*TASK1任务配置
*包括:任务句柄任务优先级堆栈大小创建任务
*/
#define TASK1_PRIO	1//优先级
#define TASK1_SIZE	32//堆栈大小
TaskHandle_t Task1_Handler;/*任务句柄*/
void task1(void* pvParameters);	//任务函数

/*TASK2任务配置
*包括:任务句柄任务优先级堆栈大小创建任务
*/
#define TASK2_PRIO	1//优先级
#define TASK2_SIZE	32//堆栈大小
TaskHandle_t Task2_Handler;/*任务句柄*/
void task2(void* pvParameters);	//任务函数

/*TASK3任务配置
*包括:任务句柄任务优先级堆栈大小创建任务
*/
#define TASK3_PRIO	1//优先级
#define TASK3_SIZE	32//堆栈大小
TaskHandle_t Task3_Handler;/*任务句柄*/
void task3(void* pvParameters);	//任务函数

uint16_t test111[6];
/*****************************************************************************/
/*LCD刷屏时使用的颜色*/
//uint16_t lcd_discolor[11]={ WHITE, BLACK, BLUE, RED,
//MAGENTA, GREEN, CYAN, YELLOW,
//BROWN, BRRED, GRAY};
/**
*@brief FreeRTOS例程入口函数
*@param无
*@retval无
*/



void freertos_demo(void)
{
	xTaskCreate(
		(TaskFunction_t     	)  start_task,/*任务函数*/
		(char*         				)  "start_task",/*任务名字*/
		(uint16_t      				)  START_TASK_SIZE,/*任务堆栈大小*/
		(void *        		 		)  NULL,/*任务参数*/
														START_TASK_PRIO,
														&StartTask_Handler/*任务句柄*/
	);
	vTaskStartScheduler();
}


void start_task(void* pvParameters)
{
	taskENTER_CRITICAL();			/*进入临界区*/
	
	xTaskCreate(
		(TaskFunction_t     	)  task1,/*任务函数*/
		(char*         				)  "task1",/*任务名字*/
		(uint16_t      				)  TASK1_SIZE,/*任务堆栈大小*/
		(void *        		 		)  NULL,/*任务参数*/
														TASK1_PRIO,
														&Task1_Handler/*任务句柄*/
	);
	
	xTaskCreate(
		(TaskFunction_t     	)  task2,/*任务函数*/
		(char*         				)  "task2",/*任务名字*/
		(uint16_t      				)  TASK2_SIZE,/*任务堆栈大小*/
		(void *        		 		)  NULL,/*任务参数*/
														TASK2_PRIO,
														&Task2_Handler/*任务句柄*/
	);
		
	xTaskCreate(
		(TaskFunction_t     	)  task3,/*任务函数*/
		(char*         				)  "task3",/*任务名字*/
		(uint16_t      				)  TASK3_SIZE,/*任务堆栈大小*/
		(void *        		 		)  NULL,/*任务参数*/
														TASK3_PRIO,
														&Task3_Handler/*任务句柄*/
	);
	
	taskEXIT_CRITICAL();			/*退出临界区*/
	vTaskDelete(NULL);	//删除当前任务
}


void task1(void* pvParameters)
{
	uint8_t pwm_flag = 0;
	while(1)
	{
		
		if(test111[1] >= 100)
		{
			pwm_flag = 1;
		}
		else if (test111[1] <= 0)
		{
			pwm_flag = 0;
		}
		pwm_flag ? test111[1]-- : test111[1]++;
//		LED0 ? LED0_OFF : LED0_ON;
		
		PWM_SetCompare1(test111[1]);
		
		printf("led is light\n");
		vTaskDelay(1000);
	}
}

void task2(void* pvParameters)
{
	while(1)
	{
		test111[2]++;
		if(test111[2] > 1000)	test111[2] = 0;
		
//		LED1 ? LED1_OFF : LED1_ON;
		vTaskDelay(500);
	}
}

void task3(void* pvParameters)
{
	while(1)
	{
		test111[0] = KEY0;
		test111[3]++;
		if(test111[3] > 1000)	test111[3] = 0;
		if(KEY0)
		{
			if(Task1_Handler != NULL)
			{
				vTaskDelete(Task1_Handler);
				Task1_Handler = NULL;
			}
		}
		vTaskDelay(10);
	}
}




