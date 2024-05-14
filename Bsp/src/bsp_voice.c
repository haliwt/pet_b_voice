/*****************************************************************************

** Pet_B voice sound of codes.
** DATA.2024.05.14
** not wakeword has voice sound output

*****************************************************************************/
#include "bsp_voice.h"
#include "bsp.h"
#include <string.h>


uint8_t transOngoingFlag;




         

//算法是:data4 + data6 = element
static uint8_t const voice_sound_data[21]={
    //fucntion voice sound
    0x22,0x24,0x26,0x28,0x2a, //0x24 = power_on ,0x26= power_off
	0x2c,  //fucntion voice sound
	//温度设置16~30度（16~36）
	0x2e,0x30,0x32,0x34,0x36,
	0x38,0x3a,0x3c,0x3e,0x40,
	0x42,0x44,0x46,0x48,0x4a,
	

};

//uint8_t voice_cmd_flag;

#if 0

/***********************************************************
 *  *
    *Function Name: void Rx_Voice_Data_Handler(void(*rx_voice_handler)(uint8_t data))
    *Function: 
    *Input Ref: function of pointer o
    *Return Ref:  NO
    * 
***********************************************************/
void Rx_Voice_Data_Handler(void(*rx_voice_handler)(uint8_t data))
{

   rx_voice_data = rx_voice_handler;

}

uint8_t  Voice_Decoder_Fun(voice_fun_t cmd)
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

/***********************************************************
 *  *
    *Function Name: void Voice_Decoder_Handler(void);
    *Function: decoder to command 
    *Input Ref: NO
    *Return Ref:  NO
    * 
***********************************************************/
void Voice_Decoder_Handler(void)
{

  while(v_t.voice_power_on_cmd){

	  	v_t.voice_power_on_cmd=0;
			
		 if(v_t.gTimer_voice_time_counter_start< 15){
	       key= v_t.RxBuf[0] + v_t.RxBuf[1]; //key= data4+ data6 = ; //A5 FA 00 81 01 00 21 FB 
	    
	
			result = BinarySearch_Voice_Data(voice_sound_data,key);
			
	
	    if(result < 0x10 ){
		   voice_cmd_fun(result);
		
	
		}
		else if(result > 15 && result < 37){ //set temperature value 
			   
			   voice_set_temperature_value(result);
		
	   }
	   else if(result > 36 && result <62){ //set timer timing value 
		
	
			voice_set_timer_timing_value(result);
			
		 }
	     else if(result==62){

			
            voice_cancel_timer_timing();

		 }

	   
		}
	   
	 }

}




#endif 



/********************************************************************************
	**
	*Function Name:sendData_Real_TimeHum(uint8_t hum,uint8_t temp)
	*Function :
	*Input Ref: humidity value and temperature value
	*Return Ref:NO
	*
*******************************************************************************/
void voice_send_function_cmd(uint8_t cmd1,uint8_t cmd2)
{
	
   uint8_t transferSize =8;
   uint8_t outputBuf[8];

   outputBuf[0]=0xA5; //master
   outputBuf[1]=0XFA; //41
   outputBuf[2]=0X00; //44 // 'D' data
   outputBuf[3]=0X03; //   // 'R' rotator motor for select filter
   outputBuf[4]=cmd1; // // one command parameter
   outputBuf[5]=0X00;
   outputBuf[6]=cmd2;
   outputBuf[7]=0XFB;
   

   transferSize=8;
   if(transferSize)
   {
	   while(transOngoingFlag); //UART interrupt transmit flag ,disable one more send data.
	   transOngoingFlag=1;
	   HAL_UART_Transmit_IT(&huart2,outputBuf,transferSize);
   }
	



}



