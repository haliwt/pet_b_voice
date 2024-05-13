#include "bsp.h"

HARD_TIMER_T  gtimer_t;

/*
**********************************************************************************************************
											函数声明
**********************************************************************************************************
*/
static void vTaskTaskUserIF(void *pvParameters);
//static void vTaskLED(void *pvParameters);
static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);
static void AppObjCreate (void);

static QueueSetHandle_t xQueueSet;          /* 定义队列集 */
QueueHandle_t           xQueue1;            /* 定义队列1 */
QueueHandle_t           xQueue2;            /* 定义队列2 */
QueueHandle_t           xQueue3;            /* 定义队列3 */

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
static TaskHandle_t xHandleTaskUserIF = NULL;
//static TaskHandle_t xHandleTaskLED = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;

//static QueueHandle_t 	xQueue1 = NULL;
//static QueueHandle_t 	xQueue2 = NULL;
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
static void vTaskTaskUserIF(void *pvParameters)
{
	uint8_t ucKeyCode;
    uint8_t key_value;

    while(1)
    {
		ucKeyCode = bsp_GetKey();
		
		if (ucKeyCode != KEY_NONE)
		{
			switch (ucKeyCode)
			{
			    case KEY_1_DOWN : //key_select fun 
                    key_value = 1;
				   /* 向消息队列发数据，如果消息队列满了，等待10个时钟节拍 */
                  //  xQueueSend(xQueue1,&key_value,(TickType_t)10);
					if( xQueueSend(xQueue1,(void*) &key_value,(TickType_t)10) != pdPASS ){
						/* 发送失败，即使等待了10个时钟节拍 */
						//printf("K2键按下，向xQueue1发送数据失败，即使等待了10个时钟节拍\r\n");
					}
					else
					{
						/* 发送成功 */
						//printf("K2键按下，向xQueue1发送数据成功\r\n");		
						 gtimer_t.gTimer_select_fun_key_timer=0;
					}


				break;

				case KEY_2_DOWN: //key_confirm fun

                   key_value =4;
				  /* 使用消息队列实现指针变量的传递 */
					if(xQueueSend(xQueue2,                  /* 消息队列句柄 */
								   (void *)&key_value,           /* 发送结构体指针变量ptMsg的地址 */
								  (TickType_t)10) != pdPASS ){
								  
						/* 发送失败，即使等待了10个时钟节拍 */
						//printf("K3键按下，向xQueue2发送数据失败，即使等待了10个时钟节拍\r\n");
					}
					else
					{
						/* 发送成功 */
						//printf("K3键按下，向xQueue2发送数据成功\r\n");						
					}

				break;

				case KEY_2_LONG: //long key_cofirm fun
                    key_value =6;
				  /* 使用消息队列实现指针变量的传递 */
					if(xQueueSend(xQueue3,                  /* 消息队列句柄 */
								 (void *) &key_value,           /* 发送结构体指针变量ptMsg的地址 */
								 (TickType_t)10) != pdPASS )
					{
						/* 发送失败，即使等待了10个时钟节拍 */
						//printf("K3键按下，向xQueue2发送数据失败，即使等待了10个时钟节拍\r\n");
					}
					else
					{
						/* 发送成功 */
						//printf("K3键按下，向xQueue2发送数据成功\r\n");						
					}


				break;

			}
		}
		
		vTaskDelay(20); //当你在任务中调用 vTaskDelay() 函数时，它会将当前任务挂起
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

	MSG_T   *ptMsg;
    const TickType_t xMaxBlockTime = pdMS_TO_TICKS(10); /* 设置最大等待时间为300ms */
    QueueSetMemberHandle_t  activate_member = NULL;
    uint8_t                queue_recv      = 0;
	static uint8_t  select_numbers,key_pressed_flag, key_long_default=0xff;
	
    while(1)
    {

	    activate_member = xQueueSelectFromSet(xQueueSet,  (TickType_t)xMaxBlockTime);/* 等待队列集中的队列接收到消息 */
        
        if (activate_member == xQueue1) //select_key function
        {
            xQueueReceive(activate_member, &queue_recv, (TickType_t)xMaxBlockTime);
			//KEY_SELECT information 
            if(queue_recv == 1){

                if(ptMsg->ucMessgelongkey == 1){ //input temperature value of numbers -> is add numbers

                    ptMsg->dsip_temp_number ++;
                    gtimer_t.gTimer_key_long_exit_timer =0;
                   
                    if(ptMsg ->dsip_temp_number > 30)ptMsg->dsip_temp_number=30; //don't loop key
                    else if(ptMsg ->dsip_temp_number < 16)ptMsg->dsip_temp_number=16;


                }
                else{ //key of selection function

                    ptMsg ->select_key_pressd_flag=1;
                    select_numbers ++;
                    if(select_numbers ==1);
    				key_pressed_flag++;

                 //  Led_Display_Content_Fun(select_numbers,confirm_number);

    			   if(select_numbers > 4) select_numbers =0;

                }

            }
        }
        else if (activate_member == xQueue2)  //confirm_key function
        {

            xQueueReceive(activate_member, &queue_recv, (TickType_t)xMaxBlockTime);

            if(queue_recv == 4){

              if(ptMsg ->select_key_pressd_flag==1 && ptMsg->ucMessgelongkey == 0){
                  if(gtimer_t.gTimer_select_fun_key_timer < 6){
                    //select led blink
                      if(select_numbers == 0) select_numbers =4;

                     //KEY_CONFIR  information
    			  //   KEY_Confirm_Handler(select_numbers,confirm_number,ptMsg->ucMessageID_setTempValue);


                     if(select_numbers == 4) select_numbers =0;
                     
                        ptMsg ->select_key_pressd_flag=0;

                  }
                  else{

                      ptMsg ->select_key_pressd_flag=0;

                  }



              }
              else if(ptMsg->ucMessgelongkey == 1){ //input temperature value of numbers -> is add numbers

                    ptMsg->dsip_temp_number --;
                    gtimer_t.gTimer_key_long_exit_timer =0;
                   
                    if(ptMsg ->dsip_temp_number < 0 )ptMsg->dsip_temp_number=30; //don't loop key
                    else if(ptMsg ->dsip_temp_number < 16)ptMsg->dsip_temp_number=16;


            }
            else if(ptMsg ->select_key_pressd_flag==0){


                  gtimer_t.gTimer_pro_disp_temp =0;
                  ptMsg->ucMessgelongkey=2;

                 
		        }
            }
            
        }
		else if (activate_member == xQueue3)  //Confirm long key set temperaure value is success 
        {
            xQueueReceive(activate_member, &queue_recv, (TickType_t)xMaxBlockTime);
			//KEY_CONFIR  information
            //printf("接收到来自xQueue2的消息: %d\r\n", queue_recv);

			if(queue_recv ==6){ //confirm set keep heat temperature value is success .

			    
	                ptMsg->ucMessageID_setTempValue=1;
                      
                     KEY_Long_Confirm_Handler();

			  }
				

			
                
        }
        else{


            if(ptMsg->ucMessgelongkey==0){

                if(gtimer_t.gTimer_read_adc_value_timer >5){
			      gtimer_t.gTimer_read_adc_value_timer =0;
		  
			    Read_NTC_Temperature_Value_Handler(ptMsg->ucMessageID_setTempValue, ptMsg->dsip_temp_number);
				Smg_Display_Temp_Degree_Value();
		    }
			
			if(gtimer_t.gTimer_smg_dis_temp_value > 2 ){
		      gtimer_t.gTimer_smg_dis_temp_value=0;
			
		      Smg_Display_Temp_Degree_Value();
			   
			}

			if(gtimer_t.gTimer_display_relay_led > 3){
			   gtimer_t.gTimer_display_relay_led =0;
			   //Relay_Confirm_Turn_OnOff_Fun();   
			  
          	}
  

            }
            else if(ptMsg->ucMessgelongkey == 1){

                if(gtimer_t.gTimer_key_long_exit_timer< 3){ //led of blink 

                   

		              Repeat_Keep_Heat_Setup_Digital_Numbers(ptMsg->dsip_temp_number);
		   
             }
		     else{
		           ptMsg->ucMessgelongkey=0;
        		   gtimer_t.gTimer_read_adc_value_timer  =50;  //at once return NTC read tempeerature
        		   Smg_Display_Temp_Degree_Value(); //display ntc of read temperature value 
        		  }

            }
            else if(ptMsg->ucMessgelongkey==2){
                    if(gtimer_t.gTimer_pro_disp_temp <2){
               
                     Repeat_Keep_Heat_Setup_Digital_Numbers(0);
              
                  }
                  else{
                     ptMsg->ucMessgelongkey=0;
                      gtimer_t.gTimer_read_adc_value_timer  =50;
                        Smg_Display_Temp_Degree_Value();
                  }
        
              }
       }
       else{

         KEEP_HEAT_LED_ON()	;
         HAL_Delay(200);

         KEEP_HEAT_LED_OFF()	;
         HAL_Delay(200);

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

    while(1)
    {
		/* 按键扫描 */
       if(init_gpio ==0 && gtimer_t.gTimer_init_gpio > 1){
           init_gpio++ ;
           SWDIO_GPIO_Init();

        }
		bsp_KeyScan();
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
    xTaskCreate( vTaskTaskUserIF,   	/* 任务函数  */
                 "vTaskUserIF",     	/* 任务名    */
                 128,               	/* 任务栈大小，单位word，也就是4字节 */
                 NULL,              	/* 任务参数  */
                 1,                 	/* 任务优先级 数值越小优先级越低，这个跟uCOS相反 */
                 &xHandleTaskUserIF );  /* 任务句柄  */
	
	
//	xTaskCreate( vTaskLED,    		/* 任务函数  */
//                 "vTaskLED",  		/* 任务名    */
//                 128,         		/* stack大小，单位word，也就是4字节 */
//                 NULL,        		/* 任务参数  */
//                 2,           		/* 任务优先级 数值越小优先级越低，这个跟uCOS相反 */
//                 &xHandleTaskLED ); /* 任务句柄  */
	
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
	#endif 

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
}





