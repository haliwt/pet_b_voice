#include "bsp.h"

HARD_TIMER_T  gtimer_t;


uint8_t voice_inputBuf[1];



/*
**********************************************************************************************************
											函数声明
**********************************************************************************************************
*/
static void vTaskVoice(void *pvParameters);
static void vTaskLED(void *pvParameters);
static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);
static void AppObjCreate (void);

#if 0

//static QueueSetHandle_t xQueueSet;          /* 定义队列集 */
//QueueHandle_t           xQueue1;            /* 定义队列1 */
//QueueHandle_t           xQueue2;            /* 定义队列2 */
//QueueHandle_t           xQueue3;            /* 定义队列3 */

//SemaphoreHandle_t       xSemaphore;         /* 定义二值信号量 */

#define QUEUE_LENGTH          					  1                   /* 队列支持的消息个数 */
#define QUEUE_ITEM_SIZE       					  sizeof(uint8_t)    /* 队列中每条消息的大小 */
#define SEMAPHORE_BINARY_LENGTH 					1                   /* 二值信号量的有效长度 */
#define QUEUESET_LENGTH       					  ((3 * QUEUE_LENGTH) + SEMAPHORE_BINARY_LENGTH)  /* 队列集支持的消息个数 */
#endif 

QueueHandle_t           xQueue;             /* 定义队列 */
#define QUEUE_LENGTH    3                   /* 队列支持的消息个数 */
#define QUEUE_ITEM_SIZE sizeof(uint8_t)     /* 队列中每条消息的大小 */


/*
**********************************************************************************************************
											变量声明
**********************************************************************************************************
*/
static TaskHandle_t xHandleTaskVoice = NULL;
static TaskHandle_t xHandleTaskLED = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;

static QueueHandle_t 	xQueue1 = NULL;
static QueueHandle_t 	xQueue2 = NULL;
static QueueHandle_t 	xQueue3 = NULL;


static void Voice_Run_Cmd(uint8_t cmd);

static uint8_t  voice_decoder_temp_value(uint8_t temp);



typedef struct Msg
{
	uint8_t  	ucMessageID_setTempValue;
    uint8_t     message_set_temp_flag ;
    
    uint8_t     ucMessgelongkey;
    uint8_t     ucMessageExitSetTemp;

    uint8_t     confirm_key_counter;
    uint8_t     confirm_short_key;
    uint8_t     confirm_key_flag;
	int8_t 	    dsip_temp_number;
	uint8_t 	select_led_flag;
    
    uint8_t     ulData_cofirm[6];
   
    //voice ref
    uint8_t     voice_data[3];
    uint8_t     voice_decoder[1];
 
    uint8_t     voice_temp_data;

    uint16_t    ucMessageID;
    
    
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
static void vTaskVoice(void *pvParameters)
{
	BaseType_t xResult;
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(300); /* ÉèÖÃ×î´óµÈ´ýÊ±¼äÎª300ms */
	uint8_t temp_value;
	
    while(1)
    {
		xResult = xQueueReceive(xQueue3,                   /* ÏûÏ¢¶ÓÁÐ¾ä±ú */
		                         &g_tMsg.voice_decoder[0],  /* ´æ´¢½ÓÊÕµ½µÄÊý¾Ýµ½±äÁ¿ucQueueMsgValueÖÐ */
		                         portMAX_DELAY);/* ÉèÖÃ×èÈûÊ±¼ä */
		
		if(xResult == pdPASS)
		{
			
            if(g_tMsg.voice_decoder[0] > 0x21 && g_tMsg.voice_decoder[0] < 0x2E){
              
                Voice_Run_Cmd(g_tMsg.voice_decoder[0]);

            }
            else{
             
                g_tMsg.message_set_temp_flag = 1;
               
               
                
                g_tMsg.voice_temp_data =  voice_decoder_temp_value(g_tMsg.voice_data[0]);

                 g_tMsg.ucMessageID_setTempValue =  g_tMsg.voice_temp_data;
                
                Smg_Display_Temp_Degree_Handler(g_tMsg.ucMessageID_setTempValue,0);

                 temp_value  =  Read_NTC_Temperature_Degree();
               
                if( g_tMsg.ucMessageID_setTempValue >= temp_value){
                               
			       KEEP_HEAT_LED_ON();
	               RELAY_KEEP_TEMP_SetHigh();
                     
            	}
                else{
                           
			      KEEP_HEAT_LED_OFF();
	              RELAY_KEEP_TEMP_SetLow();
            				 
               }


            	 }
                

            }
			
		}
		
  }

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
		                         &g_tMsg.ucMessageID,  		   /* 这里获取的是结构体的地址 */
		                         portMAX_DELAY);//portMAX_DELAY);/* 设置阻塞时间 */

       
		if(xResult == pdPASS && KEY_CONFIRM_FUN() ==0)
		{
			/* 成功接收，并通过串口将数据打印出来 */
			
             if(g_tMsg.ucMessageID > 0x80){
             g_tMsg.ucMessageID = 0; 
             g_tMsg.confirm_short_key =1;
             gtimer_t.gTimer_confirm_short_key=0;
             TAPE_LED_OFF();
             FAN_LED_OFF();

             }
		
		    if(g_tMsg.ucMessageID< 80 ){  //long key be pressed
                
                if(g_tMsg.confirm_short_key ==1)
                  g_tMsg.confirm_key_counter=0;
                else{
                   g_tMsg.confirm_key_counter=1;

                 }
           
    	   }
              
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
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(200); /* 设置最大等待时间为300ms */
	uint8_t ucQueueMsgValue,temp_value;
    while(1)
    {

	    xResult = xQueueReceive(xQueue1,                   /* 消息队列句柄 */
		                        (void *)&ucQueueMsgValue,  /* 存储接收到的数据到变量ucQueueMsgValue中 */
		                        xMaxBlockTime);//portMAX_DELAY);/* 设置阻塞时间 */
		
		if(xResult == pdPASS && g_tMsg.ucMessageID==1)
		{
			/* 成功接收，并通过串口将数据打印出来 */
			//printf("接收到消息队列数据ucQueueMsgValue = %d\r\n", ucQueueMsgValue);
			g_tMsg.select_led_flag ++ ;
            g_tMsg.confirm_key_flag=0;
            
			//FAN_LED_ON();
            //TAPE_LED_OFF(); // g_tMsg.select_led_flag = 1, TAPE_LED_OFF()
            ////FAN_LED_ON(); // g_tMsg.select_led_flag = 2, FAN_LED_OFF()
		}
       else{

         if( g_tMsg.confirm_short_key ==1 && gtimer_t.gTimer_confirm_short_key > 0){
            gtimer_t.gTimer_confirm_short_key=0;
             g_tMsg.confirm_short_key =0;
             g_tMsg.confirm_key_counter=0;
             TAPE_LED_OFF();
             FAN_LED_OFF();
               

         }
         else if(KEY_CONFIRM_FUN() ==1 &&  g_tMsg.confirm_key_counter==1){

          g_tMsg.confirm_key_counter=0;
          g_tMsg.ucMessageID = 0; 
          g_tMsg.confirm_key_flag = 1;

          // TAPE_LED_ON();
          // FAN_LED_OFF();


        }
         
        Led_Display_Content_Fun(g_tMsg.select_led_flag, g_tMsg.confirm_key_flag=1);
        
         
        if(g_tMsg.message_set_temp_flag ==1 && gtimer_t.gTimer_disp_set_temp   < 3 ){

           Smg_Display_Temp_Degree_Handler(g_tMsg.ucMessageID_setTempValue,0);
        }
        else{
            gtimer_t.gTimer_disp_set_temp =4;
           
           Read_NTC_Temperature_Value_Handler();

           if(g_tMsg.message_set_temp_flag ==1){

               temp_value  =  Read_NTC_Temperature_Degree();
               
                if( g_tMsg.ucMessageID_setTempValue >= temp_value){
                               
			       KEEP_HEAT_LED_ON();
	               RELAY_KEEP_TEMP_SetHigh();
                     
            	}
                else{
                           
			      KEEP_HEAT_LED_OFF();
	              RELAY_KEEP_TEMP_SetLow();
            				 
               }
           }

         }

       
       }
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
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(20); /* 设置最大等待时间为300ms */
   

     if(init_gpio ==0 && gtimer_t.gTimer_init_gpio > 1){
           init_gpio++ ;
          SWDIO_GPIO_Init();

     }


    while(1)
    {
		/* 按键扫描 */

        
		//bsp_KeyScan();
		if(KEY_SELECT_FUN() ==0){

                g_tMsg.ucMessageID =1;
				
					/* 向消息队列发数据，如果消息队列满了，等待10个时钟节拍 */
				xQueueSend(xQueue1,&g_tMsg.ucMessageID,0);
						/* 发送失败，即使等待了10个时钟节拍 */
						//printf("K2键按下，向xQueue1发送数据失败，即使等待了10个时钟节拍\r\n");
					




        }
        if(KEY_CONFIRM_FUN() ==0){

                  
    					g_tMsg.ucMessageID++;
    					
    					/* 使用消息队列实现指针变量的传递 */
    					xQueueSend(xQueue2,                  /* 消息队列句柄 */
    								  &g_tMsg.ucMessageID,           /* 发送结构体指针变量ptMsg的地址 */
    								0);


                        
                       

                   
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
    xTaskCreate(vTaskVoice,       /* 任务函数  */
                 "vTaskVoice",     	/* 任务名    */
                 128,               	/* 任务栈大小，单位word，也就是4字节 */
                 NULL,              	/* 任务参数  */
                 1,                 	/* 任务优先级 数值越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskVoice);  /* 任务句柄  */
	
	
	xTaskCreate( vTaskLED,    		/* 任务函数  */
                 "vTaskLED",  		/* 任务名    */
                 128,         		/* stack大小，单位word，也就是4字节 */
                 NULL,        		/* 任务参数  */
                 2,           		/* 任务优先级 数值越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskLED ); /* 任务句柄  */
	
	xTaskCreate( vTaskMsgPro,     		/* 任务函数  */
                 "vTaskMsgPro",   		/* 任务名    */
                 128,             		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 3,               		/* 任务优先级 数值越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskMsgPro );  /* 任务句柄  */
	
	
	xTaskCreate( vTaskStart,     		/* 任务函数  */
                 "vTaskStart",   		/* 任务名    */
                 128,            		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 4,              		/* 任务优先级 数值越小优先级越低，这个跟uCOS相反 */
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
   #if 0
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

      /* 创建队列 */
   
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

    xQueue1 = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
    xQueue2 = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
    xQueue3 = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
}


/********************************************************************************
	**
	*Function Name:void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	*Function :UART callback function  for UART interrupt for receive data
	*Input Ref: structure UART_HandleTypeDef pointer
	*Return Ref:NO
	*
*******************************************************************************/
static void Voice_Run_Cmd(uint8_t cmd)
{
    uint8_t data1,data2,data3;
    switch(cmd){

    case open_tape:

         
         data2 = cmd - 0x22;

         data1 = data2 >> 1;

         data1 ++;

         data3 = cmd - data1;
         voice_send_function_cmd(data1,data3);
         
         g_tMsg.ulData_cofirm[0] = open_tape_item;
         TAPE_LED_ON(); 
		 RELAY_TAPE_SetHigh();
         

   break;


    case close_tape:

        data2 = cmd - 0x22;

         data1 = data2 >> 1;

         data1 ++;

         data3 = cmd - data1;
         voice_send_function_cmd(data1,data3);

         g_tMsg.ulData_cofirm[1] = close_tape_item;
         TAPE_LED_OFF(); 
		 RELAY_TAPE_SetLow();

         

      


    break;

    case   open_fan:

         data2 = cmd - 0x22;

         data1 = data2 >> 1;

         data1 ++;

         data3 = cmd - data1;
         voice_send_function_cmd(data1,data3);

          g_tMsg.ulData_cofirm[2] = open_fan_item;
         FAN_LED_ON(); 
		 RELAY_FAN_SetHigh();

     

    break;


    case close_fan:

         data2 = cmd - 0x22;

         data1 = data2 >> 1;

         data1 ++;

         data3 = cmd - data1;
         voice_send_function_cmd(data1,data3);

         g_tMsg.ulData_cofirm[3] = close_fan_item;
         FAN_LED_OFF(); 
		 RELAY_FAN_SetLow();

     


    break;

      


    case open_kill:

       data2 = cmd - 0x22;

         data1 = data2 >> 1;

         data1 ++;

         data3 = cmd - data1;
         voice_send_function_cmd(data1,data3);

         
         g_tMsg.ulData_cofirm[4] = open_kill_item;
         KILL_LED_ON(); 
         RELAY_KILL_SetHigh();

         

    break;

    case close_kill:

        data2 = cmd - 0x22;

         data1 = data2 >> 1;

         data1 ++;

         data3 = cmd - data1;
         voice_send_function_cmd(data1,data3);

         g_tMsg.ulData_cofirm[5] = close_kill_item;
         KILL_LED_OFF(); 
         RELAY_KILL_SetLow();

  

    break;



 }
 }

/***********************************************************************************
     *
     *Function Name:static uint8_t voice_decoder_temp_value(uint8_t temp)
     *Function:
     *
     *
     *
 ***********************************************************************************/
static uint8_t voice_decoder_temp_value(uint8_t cmd)
{
    uint8_t data1,data2,data3;
    switch(cmd){

    case temp_degree_16 : // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);

            
    
            return 16;

      


    break;

    case temp_degree_17 : 

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return 17;

      


    break;

    case temp_degree_18 : // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return 18;

      


    break;


    case temp_degree_19 : // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return 19;

      


    break;

    case temp_degree_20: // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return 20;

      


    break;

    case temp_degree_21 : // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return 21;

      


    break;

    case temp_degree_22: // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return 22;

      


    break;

    case temp_degree_23 : // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return 23;

      


    break;

    case temp_degree_24: // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return 24;

      


    break;

    case temp_degree_25 : // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return 25;

      


    break;

    case temp_degree_26: // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return 26;

      


    break;

    case temp_degree_27 : // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return 27;

      


    break;

    case temp_degree_28: // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return 28;

      


    break;

    case temp_degree_29 : // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return 29;

      


    break;

    case temp_degree_30: // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return 30;

      


    break;

    
    }
    

}


/********************************************************************************
	**
	*Function Name:void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	*Function :UART callback function  for UART interrupt for receive data
	*Input Ref: structure UART_HandleTypeDef pointer
	*Return Ref:NO
	*
*******************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    static uint8_t state_stp;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
     if(huart->Instance==USART2){

		switch(state_stp)
		{
		case 0:  //#0
			if(voice_inputBuf[0]==0xA5){  //hex :4D - "M" -fixed mainboard
				state_stp=1; //=1
              
			}
			else{
				state_stp=0; //=1


			}
			break;
		case 1: //#1
			if(voice_inputBuf[0]==0xFA) //hex : 41 -'A'  -fixed master
			{
				state_stp=2; 
			}
			else
				state_stp=0; 
			break;

	   case 2:
	      if(voice_inputBuf[0]==0) //hex : 41 -'A'	-fixed master
		   {
			   state_stp=3; 
		   }
		   else{
			  state_stp=0; 
		   }


	   break;

	   case 3:
	      if(voice_inputBuf[0]==0x81) //hex : 41 -'A'	-fixed master
		   {
			  
			   state_stp=4; 
		   }
		   else{
			  state_stp=0; 
			 }


	   break;

	   case 4:

	    
		 	 g_tMsg.voice_data[0]= voice_inputBuf[0];
		  state_stp=5; 
		

	  break;

	   case 5:
	    
	   if(voice_inputBuf[0]==0x00) //hex : 41 -'A' -fixed master
		{
		  state_stp=6; 
		}
		else
			state_stp=0; 
	   

	   break;

	   case 6:
     

		      g_tMsg.voice_data[1]=voice_inputBuf[0];

              g_tMsg.voice_data[2] = g_tMsg.voice_data[0]+g_tMsg.voice_data[1];
       
               {
               /* ÏòÏûÏ¢¶ÓÁÐ·¢Êý¾Ý */
	            xQueueSendFromISR(xQueue3,
				       &g_tMsg.voice_data[2],
				       &xHigherPriorityTaskWoken);

	                /* Èç¹ûxHigherPriorityTaskWoken = pdTRUE£¬ÄÇÃ´ÍË³öÖÐ¶ÏºóÇÐµ½µ±Ç°×î¸ßÓÅÏÈ¼¶ÈÎÎñÖ´ÐÐ */
	            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);






              }
			
	
  
			 state_stp=0; 
			 
        break;

	

	 
	  }

    __HAL_UART_CLEAR_OREFLAG(&huart2);

	HAL_UART_Receive_IT(&huart2,voice_inputBuf,1);//UART receive data interrupt 1 byte

	}
	
}

  
 

//	__HAL_UART_CLEAR_NEFLAG(&huart1);
//	__HAL_UART_CLEAR_FEFLAG(&huart1);
//	__HAL_UART_CLEAR_OREFLAG(&huart1);
//	__HAL_UART_CLEAR_TXFECF(&huart1);



