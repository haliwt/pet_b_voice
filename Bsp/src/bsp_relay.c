#include "bsp_relay.h"
#include "bsp.h"
#if 0
void Relay_Init(void)
{
    g_ntc.relay_tape_flag =0;
    g_ntc.relay_fan_flag =0;
    g_ntc.relay_kill_flag =0;
    g_ntc.relay_keep_temp_flag =0;


}

void Relay_Tape_State(void)
{
     if(relay_tape_state() == 1){
        TAPE_LED_ON();
		RELAY_TAPE_SetHigh();

	 }
	 else{
        TAPE_LED_OFF(); 
		RELAY_TAPE_SetLow();
    }

}

void Relay_Fan_State(void)
{

     if(relay_fan_state() == 1){
        FAN_LED_ON();
		RELAY_FAN_SetHigh();

	 }
	 else{
        FAN_LED_OFF(); 
		RELAY_FAN_SetLow();
    }
}

void Relay_Kill_State(void)
{
 if(relay_kill_state() == 1){
        KILL_LED_ON();
		RELAY_KILL_SetHigh();

	 }
	 else{
        KILL_LED_OFF(); 
		RELAY_KILL_SetLow();
    }
}

void Relay_Keep_Temp_State(void)
{
  relay_keep_temp_state();
}
#endif 
/********************************************************************************
*
*	函 数 名: void Main_Process(void)
*	功能说明: App 层 
*			 
*	形    参: 输入按键的键值
*	返 回 值: 无
*
*********************************************************************************/
#if 0
void Relay_Confirm_Turn_OnOff_Fun(void)
{

        Relay_Tape_State();
    
       
        Relay_Fan_State();
   
      
        Relay_Kill_State();
   
       
        Relay_Keep_Temp_State();  ////检查设置的温度值和实际检测到的温度值对比
    
    
}

#endif 



