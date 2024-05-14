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
#include "bsp_led.h"
#include "bsp_ntc.h"
#include "bsp_adc.h"
#include "bsp_tm1650.h"
#include "bsp_relay.h"
#include "bsp_delay.h"
#include "interrupt_manager.h"





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

typedef struct hard_timer{

    uint8_t gTimer_key_long_exit_timer;
    uint8_t gTimer_read_adc_value_timer;
    uint8_t gTimer_smg_dis_temp_value;
    uint8_t gTimer_display_relay_led;
    uint8_t gTimer_pro_disp_temp;
    uint8_t gTimer_select_fun_key_timer;
    uint8_t gTimer_init_gpio;
    uint8_t gTimer_led_blink;
    uint8_t gTimer_confirm_short_key;
    

}HARD_TIMER_T;

extern HARD_TIMER_T  gtimer_t;




//void bsp_Init(void); 


void freeRTOS_Handler(void);




#endif 
