#ifndef __BSP_CTL_H__
#define __BSP_CTL_H__
#include "main.h"


typedef enum {
    KEY_FUNCTION_ITEM=0x01,
	KEY_CONFIRM_ITEM=0x02


}key_item;

typedef enum{

    close,
	open


}open_state;


typedef enum{

    relay_tape_led_on=0x01,
	relay_fan_led_on ,
	relay_kill_led_on,
	relay_keep_temp_led_on,
	
	
}reelay_led_state;











void bsp_ctl_init(void);


//void Run_InputKey_Model(uint8_t keyvalue);
//
//void Run_BoardCommand_Handler(void);
//
//
//void Default_TurnOff_Ptc(void);



//void Main_Process(uint8_t set_temp_flag, uint8_t set_temp_value);



void KEY_Confirm_Handler(uint8_t select_num, uint8_t *ptmsg,uint8_t key_long);



void Confirm_KEY_Long_Handler(void);


void Voice_Run_Cmd(uint8_t cmd);

#endif 



