#include "interrupt_manager.h"
#include "bsp.h"




/*******************************************************************************
  *
  * Function Name: void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
  * Function: Tim14 interrupt call back function
  * Tim3 timer :timing time 1ms
  * 
********************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

    static uint16_t tm0;
	static uint8_t tm1;
    if(htim->Instance==TIM17){
       tm0++;
       tm1++;

       if(tm1 > 9){
           tm1 =0;
           gtimer_t.gTimer_led_blink++;
           led_t.gTimer_flicker++;
         }

       if(tm0 > 999){

         tm0 =0;
         gtimer_t.gTimer_key_long_exit_timer ++ ;
         gtimer_t.gTimer_smg_dis_temp_value ++;
         gtimer_t.gTimer_display_relay_led++;
         gtimer_t.gTimer_pro_disp_temp++;
         gtimer_t.gTimer_select_fun_key_timer++;
         gtimer_t.gTimer_init_gpio++;
         gtimer_t.gTimer_confirm_short_key++;
         
         gtimer_t.gTimer_disp_set_temp++;
         //led blink
         led_t.gTimer_select_fun ++;


       }
	  
	   
	 
	}
  
 }

/**
  * 函数功能：重新定向c库函数printf到DEBUG_USARTx
  * ÊäÈë²ÎÊý: ÎÞ
  * ·µ »Ø Öµ: ÎÞ
  * Ëµ    Ã÷£ºÎÞ
  */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}

/**
  * 函数功能： 重新定向c库函数getchar,scanf到DEBUG_USARTx
  * ÊäÈë²ÎÊý: ÎÞ
  * ·µ »Ø Öµ: ÎÞ
  * Ëµ    Ã÷£ºÎÞ
  */
int fgetc(FILE * f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart2,&ch, 1, 0xffff);
  return ch;
}


/********************************************************************************
**
*Function Name:void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
*Function :UART callback function  for UART interrupt for transmit data
*Input Ref: structure UART_HandleTypeDef pointer
*Return Ref:NO
*
*******************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==&huart2) //voice  sound send 
	{
		transOngoingFlag=0; //UART Transmit interrupt flag =0 ,RUN
	}

//	if(huart== &huart2){
//
//       usart2_transOngoingFlag =0;
//
//	}

}






