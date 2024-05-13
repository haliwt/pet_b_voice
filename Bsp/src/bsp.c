#include "bsp.h"

HARD_TIMER_T  gtimer_t;

/*
**********************************************************************************************************
											函数声明
**********************************************************************************************************
*/
//static void vTaskTaskUserIF(void *pvParameters);
static void vTaskLED(void *pvParameters);
static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);
static void AppObjCreate (void);

//static QueueSetHandle_t xQueueSet;          /* 定义队列集 */
//QueueHandle_t           xQueue1;            /* 定义队列1 */
//QueueHandle_t           xQueue2;            /* 定义队列2 */
//QueueHandle_t           xQueue3;            /* 定义队列3 */

//SemaphoreHandle_t       xSemaphore;         /* 定义二值信号量 */

#define QUEUE_LENGTH          					  1                   /* 队列支持的消息个数 */
#define QUEUE_ITEM_SIZE       					  sizeof(uint8_t)    /* 队列中每条消息的大小 */
#define SEMAPHORE_BINARY_LENGTH 					1                   /* 二值信号量的有效长度 */
#define QUEUESET_LENGTH       					  ((3 * QUEUE_LENGTH) + SEMAPHORE_BINARY_LENGTH)  /* 队列集支持的消息个数 */


/*
**********************************************************************************************************
											变量声明
**********************************************************************************************************
*/
//static TaskHandle_t xHandleTaskUserIF = NULL;
static TaskHandle_t xHandleTaskLED = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;

static QueueHandle_t 	xQueue1 = NULL;
static QueueHandle_t 	xQueue2 = NULL;
//static QueueHandle_t 	xQueue3 = NULL;


typedef struct Msg
{
	uint8_t  	ucMessageID_setTempValue;
    uint8_t     ucMessageID;
    uint8_t     ucMessgelongkey;
    uint8_t     ucMessageExitSetTemp;
    uint8_t     select_key_pressd_flag;
    uint8_t     confirm_key_counter;
	int8_t 	    dsip_temp_number;
	uint8_t 	ulData[4];
    uint8_t     usData[2];
}MSG_T;

MSG_T   g_tMsg; /* 定义一个结构体用于消息队列 */

uint8_t confirm_number[4];

/**********************************************************************************************************
*	函 数 名:  void freeRTOS_Handler(void)
*	功能说明: 
*	形    参: 
*	返 回 值: 
*   优 先 级: 
*********************************************************************************************************/
 void freeRTOS_Handler(void)
 {

   	/* 创建任务 */
	AppTaskCreate();

	/* 创建任务通信机制 */
	AppObjCreate();
	
    /* 启动调度，开始执行任务 */
    vTaskStartScheduler();



 }


/*
*********************************************************************************************************
*	函 数 名: vTaskTaskUserIF
*	功能说明: 接口消息处理。
*	形    参: pvParameters 是在创建该任务时传递的形参
*	返 回 值: 无
*   优 先 级: 1  (数值越小优先级越低，这个跟uCOS相反)
*********************************************************************************************************
*/
#if 0
static void vTaskTaskUserIF(void *pvParameters)
{
	

	MSG_T   *ptMsg;
	uint8_t ucCount = 0;
	uint8_t ucKeyCode;
	uint8_t pcWriteBuffer[500];
	
	/* 初始化结构体指针 */
	ptMsg = &g_tMsg;
	
	/* 初始化数组 */
	ptMsg->ucMessageID = 0;
	ptMsg->ulData[0] = 0;
	ptMsg->usData[0] = 0;

    while(1)
    {
		ucKeyCode = bsp_GetKey();
		
		if (ucKeyCode != KEY_NONE)
		{
			switch (ucKeyCode)
			{
				/* K1键按下 打印任务执行情况 */
			
				
				/* K2键按下，向xQueue1发送数据 */
				case KEY_DOWN_K1:
					ucCount++;
				
					/* 向消息队列发数据，如果消息队列满了，等待10个时钟节拍 */
					if(xQueueSend(xQueue1,(void *) &ucCount,(TickType_t)10) != pdPASS ){
						/* 发送失败，即使等待了10个时钟节拍 */
						//printf("K2键按下，向xQueue1发送数据失败，即使等待了10个时钟节拍\r\n");
					}
					else
					{
						/* 发送成功 */
						//printf("K2键按下，向xQueue1发送数据成功\r\n");						
					}
					break;
				
				/* K3键按下，向xQueue2发送数据 */
				case KEY_DOWN_K2:
					ptMsg->ucMessageID++;
					ptMsg->ulData[0]++;;
					ptMsg->usData[0]++;
					
					/* 使用消息队列实现指针变量的传递 */
					if(xQueueSend(xQueue2,                  /* 消息队列句柄 */
								 (void *) &ptMsg,           /* 发送结构体指针变量ptMsg的地址 */
								 (TickType_t)10) != pdPASS )
					{
						/* 发送失败，即使等待了10个时钟节拍 */
						//printf("K3键按下，向xQueue2发送数据失败，即使等待了10个时钟节拍\r\n");
					}
					else
					{
						/* 发送成功 */
						///printf("K3键按下，向xQueue2发送数据成功\r\n");						
					}
				
				/* 其他的键值不处理 */
				default:                     
					break;
			}
		}
		
		vTaskDelay(20);
	}
}
	
#endif 
/*
*********************************************************************************************************
*	函 数 名: vTaskLED
*	功能说明: 使用函数xQueueReceive接收任务vTaskTaskUserIF发送的消息队列数据(xQueue2)	
*	形    参: pvParameters 是在创建该任务时传递的形参
*	返 回 值: 无
*   优 先 级: 2  
*********************************************************************************************************
*/
static void vTaskLED(void *pvParameters)
{
	MSG_T *ptMsg;
	BaseType_t xResult;
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(200); /* 设置最大等待时间为200ms */
	
    while(1)
    {
		xResult = xQueueReceive(xQueue2,                   /* 消息队列句柄 */
		                        (void *)&ptMsg,  		   /* 这里获取的是结构体的地址 */
		                        portMAX_DELAY);/* 设置阻塞时间 */
		
		
		if(xResult == pdPASS)
		{
			/* 成功接收，并通过串口将数据打印出来 */
			//printf("接收到消息队列数据ptMsg->ucMessageID = %d\r\n", ptMsg->ucMessageID);
			//printf("接收到消息队列数据ptMsg->ulData[0] = %d\r\n", ptMsg->ulData[0]);
			///printf("接收到消息队列数据ptMsg->usData[0] = %d\r\n", ptMsg->usData[0]);
			TAPE_LED_ON();
            KILL_LED_OFF();
		}
		else
		{
			/* 超时 */
			//bsp_LedToggle(2);
			///bsp_LedToggle(3);
		}
    }
}


/*********************************************************************************************************
*	函 数 名: vTaskMsgPro
*	功能说明: 消息处理，使用函数comGetChar获取串口命令，使用函数comSendBuf发送串口消息
*	形    参: pvParameters 是在创建该任务时传递的形参
*	返 回 值: 无
*   优 先 级: 3  (数值越小优先级越低，这个跟uCOS相反)
*********************************************************************************************************/
static void vTaskMsgPro(void *pvParameters)
{

	BaseType_t xResult;
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(300); /* 设置最大等待时间为300ms */
	uint8_t ucQueueMsgValue;
    while(1)
    {

	    xResult = xQueueReceive(xQueue1,                   /* 消息队列句柄 */
		                        (void *)&ucQueueMsgValue,  /* 存储接收到的数据到变量ucQueueMsgValue中 */
		                         portMAX_DELAY);/* 设置阻塞时间 */
		
		if(xResult == pdPASS)
		{
			/* 成功接收，并通过串口将数据打印出来 */
			//printf("接收到消息队列数据ucQueueMsgValue = %d\r\n", ucQueueMsgValue);
			KILL_LED_ON();
            TAPE_LED_OFF();
		}
       else{

         KEEP_HEAT_LED_OFF()	;
         

       }
     
		
  	//vTaskDelay(20);
    }
}

/*
*********************************************************************************************************
*	函 数 名: vTaskStart
*	功能说明: 启动任务，也就是最高优先级任务，这里用作按键扫描。
*	形    参: pvParameters 是在创建该任务时传递的形参
*	返 回 值: 无
*   优 先 级: 4  (数值越小优先级越低，这个跟uCOS相反)
*********************************************************************************************************
*/
static void vTaskStart(void *pvParameters)
{
    static uint8_t init_gpio;
    
	MSG_T   *ptMsg;
	uint8_t ucCount = 0;
	


    while(1)
    {
		/* 按键扫描 */
//       if(init_gpio ==0 && gtimer_t.gTimer_init_gpio > 1){
//           init_gpio++ ;
//           SWDIO_GPIO_Init();
//
//        }
        
		//bsp_KeyScan();
		if(KEY_SELECT_FUN() ==0){

          ucCount++;
				
					/* 向消息队列发数据，如果消息队列满了，等待10个时钟节拍 */
				xQueueSend(xQueue1,(void *) &ucCount,portMAX_DELAY);
						/* 发送失败，即使等待了10个时钟节拍 */
						//printf("K2键按下，向xQueue1发送数据失败，即使等待了10个时钟节拍\r\n");
					




        }
        else if(KEY_CONFIRM_FUN() ==0){

                     ptMsg->ucMessageID++;
					ptMsg->ulData[0]++;;
					ptMsg->usData[0]++;
					
					/* 使用消息队列实现指针变量的传递 */
					xQueueSend(xQueue2,                  /* 消息队列句柄 */
								 (void *) &ptMsg,           /* 发送结构体指针变量ptMsg的地址 */
								 portMAX_DELAY);
					


        }
       
        vTaskDelay(10);
    }
}
				
/*
*********************************************************************************************************
*	函 数 名: AppTaskCreate
*	功能说明: 创建应用任务
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void AppTaskCreate (void)
{
//    xTaskCreate( vTaskTaskUserIF,   	/* 任务函数  */
//                 "vTaskUserIF",     	/* 任务名    */
//                 128,               	/* 任务栈大小，单位word，也就是4字节 */
//                 NULL,              	/* 任务参数  */
//                 1,                 	/* 任务优先级 数值越小优先级越低，这个跟uCOS相反 */
//                 &xHandleTaskUserIF );  /* 任务句柄  */
	
	
	xTaskCreate( vTaskLED,    		/* 任务函数  */
                 "vTaskLED",  		/* 任务名    */
                 128,         		/* stack大小，单位word，也就是4字节 */
                 NULL,        		/* 任务参数  */
                 1,           		/* 任务优先级 数值越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskLED ); /* 任务句柄  */
	
	xTaskCreate( vTaskMsgPro,     		/* 任务函数  */
                 "vTaskMsgPro",   		/* 任务名    */
                 128,             		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 2,               		/* 任务优先级 数值越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskMsgPro );  /* 任务句柄  */
	
	
	xTaskCreate( vTaskStart,     		/* 任务函数  */
                 "vTaskStart",   		/* 任务名    */
                 128,            		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 3,              		/* 任务优先级 数值越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskStart );   /* 任务句柄  */
}



/*
*********************************************************************************************************
*	函 数 名: AppObjCreate
*	功能说明: 创建任务通信机制
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void AppObjCreate (void)
{
   #if 1
   /* 创建10个uint8_t型消息队列 */
	xQueue1 = xQueueCreate(10, sizeof(uint8_t));
    if( xQueue1 == 0 )
    {
        /* 没有创建成功，用户可以在这里加入创建失败的处理机制 */
    }
	
	/* 创建10个存储指针变量的消息队列，由于CM3/CM4内核是32位机，一个指针变量占用4个字节 */
	xQueue2 = xQueueCreate(10, sizeof(struct Msg *));
    if( xQueue2 == 0 )
    {
        /* 没有创建成功，用户可以在这里加入创建失败的处理机制 */
    }
	#endif 

    #if 0

	/* 创建队列集 */
    xQueueSet = xQueueCreateSet(QUEUESET_LENGTH);
    /* 创建队列 */
    xQueue1 = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
    xQueue2 = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
	xQueue3 = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
    /* 创建二值信号量 */
   // xSemaphore = xSemaphoreCreateBinary();
    /* 将队列和二值信号量添加到队列集 */
    xQueueAddToSet(xQueue1, xQueueSet);
    xQueueAddToSet(xQueue2, xQueueSet);
	xQueueAddToSet(xQueue3, xQueueSet);
	
    //xQueueAddToSet(xSemaphore, xQueueSet);
    #endif 
}





