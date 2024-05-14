#ifndef __BSP_VOICE_H
#define __BSP_VOICE_H
#include "main.h"

#define  RX_BUF_SIZE  3



//#define VOICE_OUTPUT_SOUND_ENABLE()       do{MUTE_GPIO_Port->BSRR |= MUTE_Pin;}while(0)
//#define VOICE_OUTPUT_SOUND_DISABLE()      do{MUTE_GPIO_Port->BSRR |= (uint32_t)MUTE_Pin<<16;}while(0)


extern uint8_t voice_inputBuf[1];

extern uint8_t transOngoingFlag;



typedef enum decode_fun{

   open_tape = 0x22,
   close_tape =0x24,
   open_fan = 0x26,
   close_fan =0x28,

   open_kill = 0x2A,
   close_kill = 0x2C
   
}voice_fun_t;

typedef enum decode_set_temp{

   temp_degree_16 = 0x2E,
   temp_degree_17 = 0x30,
   temp_degree_18 = 0x32,
   temp_degree_19 = 0x34,
   temp_degree_20 = 0x36,
   temp_degree_21 = 0x38,
   temp_degree_22 = 0x3A,
   temp_degree_23 = 0x3C,
   temp_degree_24 = 0x3E,
   temp_degree_25 = 0x40,
   temp_degree_26 = 0x42,
   temp_degree_27 = 0x44,
   temp_degree_28 = 0x46,
   temp_degree_29 = 0x48,
   temp_degree_30 = 0x4A,
   
}voice_set_temp;


void voice_send_function_cmd(uint8_t cmd1,uint8_t cmd2);


//uint8_t  Voice_Decoder_Fun(uint8 cmd);



//uint8_t Voice_Decoder_SetTemp_Fun(uint8_t value);









#endif 

