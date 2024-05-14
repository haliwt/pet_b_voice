#include "bsp_ctl.h"
#include "bsp.h"






uint8_t led_on_of_number;
#if 0
void Voice_Run_Cmd(uint8_t cmd)
{
    uint8_t data1,data2,data3;
    switch(cmd){

    case open_tape:

         
         data2 = cmd - 0x22;

         data1 = data2 >> 1;

         data1 ++;

         data3 = cmd - data1;
         voice_send_function_cmd(data1,data3);

         

         return cmd;


    break;


    case close_tape:

        data2 = cmd - 0x22;

         data1 = data2 >> 1;

         data1 ++;

         data3 = cmd - data1;
         voice_send_function_cmd(data1,data3);

         return cmd;


    break;

    case   open_fan:

         data2 = cmd - 0x22;

         data1 = data2 >> 1;

         data1 ++;

         data3 = cmd - data1;
         voice_send_function_cmd(data1,data3);

         return cmd;

    break;


    case clouse_fan:

         data2 = cmd - 0x22;

         data1 = data2 >> 1;

         data1 ++;

         data3 = cmd - data1;
         voice_send_function_cmd(data1,data3);

         return cmd;


    break;


    case open_kill:

       data2 = cmd - 0x22;

         data1 = data2 >> 1;

         data1 ++;

         data3 = cmd - data1;
         voice_send_function_cmd(data1,data3);

         return cmd;

    break;

    case close_kill:

        data2 = cmd - 0x22;

         data1 = data2 >> 1;

         data1 ++;

         data3 = cmd - data1;
         voice_send_function_cmd(data1,data3);

         return cmd;

    break;

    case temp_degree_16 : // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return cmd;

      


    break;

    case temp_degree_17 : 

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return cmd;

      


    break;

    case temp_degree_18 : // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return cmd;

      


    break;


    case temp_degree_19 : // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return cmd;

      


    break;

    case temp_degree_20: // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return cmd;

      


    break;

    case temp_degree_21 : // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return cmd;

      


    break;

    case temp_degree_22: // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return cmd;

      


    break;

    case temp_degree_23 : // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return cmd;

      


    break;

    case temp_degree_24: // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return cmd;

      


    break;

    case temp_degree_25 : // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return cmd;

      


    break;

    case temp_degree_26: // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return cmd;

      


    break;

    case temp_degree_27 : // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return cmd;

      


    break;

    case temp_degree_28: // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return cmd;

      


    break;

    case temp_degree_29 : // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return cmd;

      


    break;

    case temp_degree_30: // = 0x2E,

       
            data2 = cmd - 0x22;
    
            data1 = data2 >> 1;
    
            data1 ++;
    
            data3 = cmd - data1;
            voice_send_function_cmd(data1,data3);
    
            return cmd;

      


    break;

    
    }

}
#endif 

#if 0

/*********************************************************************************************************
*	函 数 名: void Main_Process(void)
*	功能说明: App 层 
*			 
*	形    参: 输入按键的键值
*	返 回 值: 无
*********************************************************************************************************/
void Main_Process(uint8_t disp_item,uint8_t set_temp_flag,uint8_t set_temp_value)
{
   
   
    Relay_Tunr_OnOff_Fun(relay_id_led);

	switch(disp_item){

	   case 0:
			if(gtimer_t.gTimer_read_adc_value_timer >5){
			      gtimer_t.gTimer_read_adc_value_timer =0;
		  
			    Read_NTC_Temperature_Value_Handler(set_temp_flag,set_temp_value);
				Smg_Display_Temp_Degree_Value();
		    }
			
			if(gtimer_t.gTimer_smg_dis_temp_value > 2 ){
		      gtimer_t.gTimer_smg_dis_temp_value=0;
			
		      Smg_Display_Temp_Degree_Value();
			   
			}

			if(gtimer_t.gTimer_display_relay_led > 3){
			   gtimer_t.gTimer_display_relay_led =0;
			   Relay_Confirm_Turn_OnOff_Fun();   
			  
          	}

		break;

	   case 1: // 
    
		if(gtimer_t.gTimer_pro_disp_temp <2){

		   Repeat_Keep_Heat_Setup_Digital_Numbers(set_temp_value);
		   
		 }
		else{
		   disp_item =0;
		   gtimer_t.gTimer_read_adc_value_timer  =50;  //at once return NTC read tempeerature
		   Smg_Display_Temp_Degree_Value(); //display ntc of read temperature value 
		}

	   break;

	   case 2: //don't set up keep tempeature is 00 

	       if(gtimer_t.gTimer_pro_disp_temp <2){
	   	
	          Repeat_Keep_Heat_Setup_Digital_Numbers(0);
	   
		   }
		   else{
			   disp_item =0;
			   gtimer_t.gTimer_read_adc_value_timer  =50;
			  Smg_Display_Temp_Degree_Value();
		   }


	   break;

	   }

}



/***********************************************************
	*
	*Function Name:uint8_t relay_tape_fun(void)
	*Function: open of clouse relay
	*Input Ref: NO
	*Retrun Ref: 1->open 0->close
	*
***********************************************************/
static uint8_t relay_tape_fun(void)
{
     if(g_ntc.relay_tape_flag==1)return 1;
	 else return 0;

}

/***********************************************************
	*
	*Function Name:static uint8_t relay_kill_fun(void) 
	*Function: open of clouse relay
	*Input Ref: NO
	*Retrun Ref: 1->open 0->close
	*
***********************************************************/
static uint8_t relay_fan_fun(void)
{
   if(g_ntc.relay_fan_flag==1) return 1;
   else return 0;

}

/***********************************************************
	*
	*Function Name:static uint8_t relay_kill_fun(void) 
	*Function: open of clouse relay
	*Input Ref: NO
	*Retrun Ref: 1->open 0->close
	*
***********************************************************/
static uint8_t relay_kill_fun(void)
{
	if(g_ntc.relay_kill_flag==1) return 1;
	else return 0;

}

/***********************************************************
	*
	*Function Name:static uint8_t relay_temp_flag_fun(void)
	*Function: open of clouse relay
	*Input Ref: NO
	*Retrun Ref: 1->open 0->close
	*
***********************************************************/
static uint8_t relay_temp_flag_fun(void)
{
   if(pro_t.set_keep_temp_fun_flag==1) return 1;
   else return 0;

}

/***********************************************************
	*
	*Function Name: static uint8_t relay_keep_temp_fun(void)
	*Function: open of clouse relay
	*Input Ref: NO
	*Retrun Ref: 1->open 0->close
	*
***********************************************************/
static uint8_t relay_keep_temp_fun(void)
{
   
	static uint8_t set_value_off_flag;

	if(relay_temp_flag_state() ==1){
	  if(pro_t.set_keep_temp_value > g_ntc.temperature_value){
		  
		  if(g_ntc.temperature_value==29){
				g_ntc.relay_keep_temp_flag =0;
				  KEEP_HEAT_LED_OFF();
				  RELAY_KEEP_TEMP_SetLow();
				  KEY_FUN_CONFIRM_LED_ON() ;
				  ADD_DEC_LED_OFF();
			      set_value_off_flag =1;
			  
		   }
		   else{
			   g_ntc.relay_keep_temp_flag =1; //open keep temperature "relay_d" 
			   KEEP_HEAT_LED_ON();
			   RELAY_KEEP_TEMP_SetHigh();
			   KEY_FUN_CONFIRM_LED_ON() ;  
			   ADD_DEC_LED_OFF();
		   }

	    }
		else{
			
		  if(set_value_off_flag ==1 && (g_ntc.temperature_value < 28)){
			   set_value_off_flag =0;
			   g_ntc.relay_keep_temp_flag =1; //open keep temperature "relay_d" 
			   KEEP_HEAT_LED_ON();
			   RELAY_KEEP_TEMP_SetHigh();
			   KEY_FUN_CONFIRM_LED_ON() ;  
			   ADD_DEC_LED_OFF();
		  
		  }
		  else{
			  g_ntc.relay_keep_temp_flag =0;
			  KEEP_HEAT_LED_OFF();
			  RELAY_KEEP_TEMP_SetLow();
			  KEY_FUN_CONFIRM_LED_ON() ;
			   ADD_DEC_LED_OFF();
		  }

         }
	}
	else{
		KEEP_HEAT_LED_OFF();
		RELAY_KEEP_TEMP_SetLow();
		KEY_FUN_CONFIRM_LED_ON() ;
		ADD_DEC_LED_OFF();
	}
}

void Default_TurnOff_Ptc(void)
{
	if(g_ntc.temperature_value > 29){
		KEEP_HEAT_LED_OFF();
		RELAY_KEEP_TEMP_SetLow();
		//KEY_FUN_CONFIRM_LED_ON() ;
		//ADD_DEC_LED_OFF();

	}



}

/*
*********************************************************************************************************
*	函 数 名: BEBufToUint16
*	功能说明: 将2字节数组(大端Big Endian次序，高字节在前)转换为16位整数 big 
*	形    参: _pBuf : 数组
*	返 回 值: 16位整数值
*
*   大端(Big Endian)与小端(Little Endian)
*********************************************************************************************************
*/
uint16_t LEBufToUint16(uint8_t *_pBuf)
{
    return (((uint16_t)_pBuf[1] << 8) | _pBuf[0]);
}


/*
*********************************************************************************************************
*	函 数 名: LEBufToUint16
*	功能说明: 将2字节数组(小端Little Endian，低字节在前)转换为16位整数
*	形    参: _pBuf : 数组
*	返 回 值: 16位整数值
*********************************************************************************************************
*/
uint16_t BEBufToUint16(uint8_t *_pBuf)
{
    return (((uint16_t)_pBuf[0] << 8) | _pBuf[1]);
}


/*
*********************************************************************************************************
*	函 数 名: BEBufToUint32
*	功能说明: 将4字节数组(大端Big Endian次序，高字节在前)转换为16位整数
*	形    参: _pBuf : 数组
*	返 回 值: 16位整数值
*
*   大端(Big Endian)与小端(Little Endian)
*********************************************************************************************************
*/
uint32_t BEBufToUint32(uint8_t *_pBuf)
{
 return (((uint32_t)_pBuf[3] << 24) | ((uint32_t)_pBuf[2] << 16) | ((uint32_t)_pBuf[1] << 8) | _pBuf[0]);
}

/***********************************************************************************
	*
	*Function Name: void Relay_Tape_Process(uint8_t(*relay_tape_handler)(void))
	*Function: open of clouse relay
	*Input Ref: NO
	*Retrun Ref: 1->open 0->close
	*
************************************************************************************/
void Relay_Tape_Process(uint8_t(*relay_tape_handler)(void))
{
   relay_tape_state = relay_tape_handler;
}
void Relay_Fan_Process(uint8_t(*relay_fan_handler)(void))
{
	relay_fan_state = relay_fan_handler;
}
void Relay_Kill_Process(uint8_t(*relay_kill_handler)(void))
{
   relay_kill_state = relay_kill_handler;

}
void Relay_Keep_Temp_Process(uint8_t(*relay_temp_handler)(void))
{
   relay_keep_temp_state = relay_temp_handler;

}
void Relay_Temp_Flag_Handler(uint8_t(*relay_temp_flag_handler)(void))
{

	relay_temp_flag_state = relay_temp_flag_handler;

}


/*
*********************************************************************************************************
*	函 数 名: Key_Handler(uint8_t pro_t.key_value)
*	功能说明: 中间层 
*			 
*	形    参: 输入按键的键值
*	返 回 值: 无
*********************************************************************************************************
*/
void Key_Handler(uint8_t key_value)
{
 
  switch(key_value){


     case fun_key:  //fun key 

        switch(pro_t.key_as_numbers_input_flag){

		 case 1: //keep temperature value that as inupt number of key
             pro_t.iwdg_detected_times=0;
			 
			g_ntc.gTimer_select_fun=0;
			disp_keep_temp_value =0xff;
			pro_t.gTimer_pro_disp_temp=0; //display set keep temperature timer timing 
			//
			g_ntc.digital_numbers++; //scope : 16~30度
			if(g_ntc.digital_numbers <16)g_ntc.digital_numbers =16;
			if(g_ntc.digital_numbers>30) g_ntc.digital_numbers=30;
			Run_Keep_Heat_Setup_Digital_Numbers(g_ntc.digital_numbers);
			  
			break;

		 case 0:
		 pro_t.iwdg_detected_times=0;
		 KEY_FUN_CONFIRM_LED_ON() ; 
         pro_t.key_fun++;
		 
			 
		 if(pro_t.key_fun > 4){
		 	pro_t.key_fun=1;

		 }
         switch(pro_t.key_fun){

		    case relay_a_tape_led:

		        relay_id_led = relay_tape_led_on;
				g_ntc.gTimer_select_fun=0;
				pro_t.fun_key_counter=1;
		 

		   break;
		 
		    case relay_b_fan_led:
				relay_id_led = relay_fan_led_on;
				g_ntc.gTimer_select_fun=0;
				pro_t.key_short_confirm_flag=0;
				pro_t.fun_key_counter=1;
				

		    break;

			case relay_c_kill_led:  // 
				relay_id_led = relay_kill_led_on;
				g_ntc.gTimer_select_fun=0;
				pro_t.key_short_confirm_flag=0;
				 pro_t.fun_key_counter=1;
				
		    break;

			case relay_keep_temp: //keep temperature value

			   
				relay_id_led = relay_keep_temp_led_on;
				g_ntc.gTimer_select_fun=0;
				pro_t.key_short_confirm_flag=0;//WT.EDIT 2023.12.20
				pro_t.fun_key_counter=1;
			 
		    break;

           }
		  break;
		
        }
     break;
		
     //confirm key 
	case confirm_short_key: // confirm key

      pro_t.iwdg_detected_times=0;
	  if(pro_t.fun_key_counter==0){
        
		if( pro_t.set_keep_temp_fun_flag == 1){ //display has been set keep heat temperatur value .
		pro_t.gTimer_pro_disp_temp=0;
	
		disp_keep_temp_value =1;

		}
		else{ //display "00:00"
		  pro_t.gTimer_pro_disp_temp=0;
		
		  disp_keep_temp_value =2;
		

		}


     }
	 else{// confrim key define speical led on or off.

      switch(relay_id_led){

		 case relay_tape_led_on:

		      if(g_ntc.relay_tape_flag ==0){
				 g_ntc.relay_tape_flag =1;
				  TAPE_LED_ON();
				  RELAY_TAPE_SetHigh();
			  } 
			  else{
				  g_ntc.relay_tape_flag =0;
				   TAPE_LED_OFF(); 
				  RELAY_TAPE_SetLow();
			  } 
		      pro_t.fun_key_counter=0;

		   break;
		 
		    case relay_fan_led_on:
				if(g_ntc.relay_fan_flag==0){
					g_ntc.relay_fan_flag=1;
					 FAN_LED_ON();
					RELAY_FAN_SetHigh();
				}
				else{
					g_ntc.relay_fan_flag=0;
					FAN_LED_OFF(); 
		            RELAY_FAN_SetLow();
				}
				 pro_t.fun_key_counter=0;
			break;

			case relay_kill_led_on:  // 
				if(g_ntc.relay_kill_flag==0){
					g_ntc.relay_kill_flag=1;
					KILL_LED_ON();
		            RELAY_KILL_SetHigh();
				}else{
					g_ntc.relay_kill_flag=0;
					 KILL_LED_OFF(); 
		             RELAY_KILL_SetLow();
				}
				 pro_t.fun_key_counter=0;
				
				
		    break;

			case relay_keep_temp_led_on: //keep temperature value

			  switch(pro_t.set_keep_temp_fun_flag){

			   case 1:
  
			
			 	 pro_t.set_keep_temp_fun_flag=0;
                 g_ntc.relay_keep_temp_flag =0;
				 g_ntc.gTimer_select_fun =10;
				 pro_t.key_short_confirm_flag =1;
			
				 KEY_FUN_CONFIRM_LED_OFF() ;  
			     pro_t.fun_key_counter=0;
				  KEEP_HEAT_LED_OFF();
	              RELAY_KEEP_TEMP_SetLow();
				  KEY_FUN_CONFIRM_LED_ON() ;
				  ADD_DEC_LED_OFF();

			 
			  break;

			 case 0: //confirm key as input numbers key

			  if(pro_t.key_as_numbers_input_flag ==0){
				  pro_t.key_as_numbers_input_flag =1;
				  g_ntc.gTimer_select_fun=0;
		          ADD_DEC_LED_ON();

			  }
			  else{

			    g_ntc.gTimer_select_fun=0;
				pro_t.gTimer_pro_disp_temp=0;
				disp_keep_temp_value = 0xff;
				g_ntc.digital_numbers--; //scope : 16~30度
				if(g_ntc.digital_numbers <16) g_ntc.digital_numbers=16;
				Run_Keep_Heat_Setup_Digital_Numbers(g_ntc.digital_numbers);
			  }
			  
			  break;

		     }

		  break;
      }
	 }
	  break;
	  
     //function key long be pressed 
	 case confirm_long_key: //confirm long by pressed 
         pro_t.iwdg_detected_times=0;
	    if(pro_t.key_as_numbers_input_flag ==1){

	        g_ntc.gTimer_select_fun=20;
			pro_t.key_as_numbers_input_flag =0;
		
			ADD_DEC_LED_OFF();
		
		   pro_t.set_keep_temp_fun_flag = 1; //set keep temperature is complete.
		   pro_t.long_key_flag =0; //repeat by pressed key_confirm .
		   disp_keep_temp_value =0;
		   g_ntc.gTimer_read_adc =20;
		
		   pro_t.set_keep_temp_value = g_ntc.digital_numbers;
			   if(pro_t.set_keep_temp_value >= g_ntc.temperature_value ){
                   g_ntc.relay_keep_temp_flag =1; //open keep temperature "relay_d" 
			       KEEP_HEAT_LED_ON();
	               RELAY_KEEP_TEMP_SetHigh();
				   KEY_FUN_CONFIRM_LED_ON() ;  
				   ADD_DEC_LED_OFF();

			  }
              else{
                  g_ntc.relay_keep_temp_flag =0;
			      KEEP_HEAT_LED_OFF();
	              RELAY_KEEP_TEMP_SetLow();
				  KEY_FUN_CONFIRM_LED_ON() ;
				  ADD_DEC_LED_OFF();

              }
			  pro_t.fun_key_counter=0;
		}

	 break;
  
	}
}


void KEY_Confirm_Handler(uint8_t select_num, uint8_t *ptmsg, uint8_t set_temp_flag)
{


       switch(select_num){
        
		   case relay_tape_led_on:

		     if(ptmsg[0] ==0){
				ptmsg[0] =1;
				  TAPE_LED_ON();
				  RELAY_TAPE_SetHigh();
			  } 
			  else{
				  ptmsg[0] =0;
				   TAPE_LED_OFF(); 
				  RELAY_TAPE_SetLow();
			  } 
		    
		   break;
		 
		    case relay_fan_led_on:
				if(ptmsg[1]==0){
					ptmsg[1]=1;
					 FAN_LED_ON();
					RELAY_FAN_SetHigh();
				}
				else{
					ptmsg[1]=0;
					FAN_LED_OFF(); 
		            RELAY_FAN_SetLow();
				}
				 
			break;

			case relay_kill_led_on:  // 
				if(ptmsg[2]==0){
					ptmsg[2]=1;
					KILL_LED_ON();
		            RELAY_KILL_SetHigh();
				}else{
					ptmsg[2]=0;
					 KILL_LED_OFF(); 
		             RELAY_KILL_SetLow();
				}

				
				
		    break;

            case relay_keep_temp_led_on:

               switch(set_temp_flag){

			   case 1:
  
		          set_temp_flag =0;
                 g_ntc.relay_keep_temp_flag =0;
			
			      KEY_FUN_CONFIRM_LED_OFF() ;  
			    
				  KEEP_HEAT_LED_OFF();
	              RELAY_KEEP_TEMP_SetLow();
				  KEY_FUN_CONFIRM_LED_ON() ;
				  ADD_DEC_LED_OFF();

			 
			  break;

			 case 0: //confirm key as input numbers key

              set_temp_flag=1;
                
			  if(pro_t.key_as_numbers_input_flag ==0){
				  
				   ADD_DEC_LED_ON();

			  }
			  else{

			    g_ntc.gTimer_select_fun=0;
				pro_t.gTimer_pro_disp_temp=0;
				disp_keep_temp_value = 0xff;
				g_ntc.digital_numbers--; //scope : 16~30度
				if(g_ntc.digital_numbers <16) g_ntc.digital_numbers=16;
				Run_Keep_Heat_Setup_Digital_Numbers(g_ntc.digital_numbers);
			  }
			  
			  break;

		     }

		
             }


            break;

      	}

}


void Confirm_KEY_Long_Handler(void)
{
     
	   
		switch(ptmsg[3]){

			   case 1:
  
			
			 	 ptmsg[3]=0;
                 g_ntc.relay_keep_temp_flag =0;
			
			      KEY_FUN_CONFIRM_LED_OFF() ;  
			    
				  KEEP_HEAT_LED_OFF();
	              RELAY_KEEP_TEMP_SetLow();
				  KEY_FUN_CONFIRM_LED_ON() ;
				  ADD_DEC_LED_OFF();

			 
			  break;

			 case 0: //confirm key as input numbers key

			  if(pro_t.key_as_numbers_input_flag ==0){
				  
				   ADD_DEC_LED_ON();

			  }
			  else{

			    g_ntc.gTimer_select_fun=0;
				pro_t.gTimer_pro_disp_temp=0;
				disp_keep_temp_value = 0xff;
				g_ntc.digital_numbers--; //scope : 16~30度
				if(g_ntc.digital_numbers <16) g_ntc.digital_numbers=16;
				Run_Keep_Heat_Setup_Digital_Numbers(g_ntc.digital_numbers);
			  }
			  
			  break;

		     }

		
      }
	
}


void KEY_Long_Confirm_Handler(void)
{

//	  switch(long_key_flag){
//
//
//	    case 1:
//			
//				 
//		  KEEP_HEAT_LED_ON();
//		  RELAY_KEEP_TEMP_SetHigh();
//		  KEY_FUN_CONFIRM_LED_ON() ;  
//		  ADD_DEC_LED_ON();
//
//			 
//	   break;
//	  
//	   case 0: 
	

	      ADD_DEC_LED_OFF();
	   
	    //  KEEP_HEAT_LED_OFF();
		// RELAY_KEEP_TEMP_SetLow();
		// KEY_FUN_CONFIRM_LED_ON() ;
	




			 
			
 }

#endif 

void KEY_Long_Confirm_Handler(void)
{



}

