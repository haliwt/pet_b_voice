#ifndef __BSP_H_
#define __BSP_H_
#include "main.h"
#include <stdio.h>
#include <string.h>


#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "gpio_init.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"
#include "semphr.h"
#include "event_groups.h"

//bsp
#include "bsp_key.h"
#include "bsp_smg.h"
#include "bsp_uart_fifo.h"
//#include "bsp_freertos_app.h"


#define  USE_FreeRTOS      1

#if USE_FreeRTOS == 1
	//#include "FreeRTOS.h"
	///#include "task.h"
	#define DISABLE_INT()    taskENTER_CRITICAL()
	#define ENABLE_INT()     taskEXIT_CRITICAL()
#else
	/* ����ȫ���жϵĺ� */
	#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
	#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */
#endif




void bsp_Init(void); 


void freeRTOS_Handler(void);




#endif 
