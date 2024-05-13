#include "interrupt_manager.h"
#include "bsp.h"

#if 0
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{

   if(GPIO_Pin == INPUT_KEY_CONFIRM_Pin){
	 if(CONFIRM_KEY_VALUE() == KEY_DOWN){

       pro_t.iwdg_detected_times =0;

	 }


   }

   if(GPIO_Pin == INPUT_KEY_FUN_Pin){
	 if(CONFIRM_KEY_VALUE() == KEY_DOWN){

       pro_t.iwdg_detected_times =0;

	 }


   }



}
#endif 

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

       if(tm0 > 999){

         tm0 =0;
         gtimer_t.gTimer_key_long_exit_timer ++ ;
         gtimer_t.gTimer_smg_dis_temp_value ++;
         gtimer_t.gTimer_display_relay_led++;
         gtimer_t.gTimer_pro_disp_temp++;
         gtimer_t.gTimer_select_fun_key_timer++;
         gtimer_t.gTimer_init_gpio++;


       }
	  
	   
	 
	}
 }


