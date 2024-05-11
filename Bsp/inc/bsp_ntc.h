#ifndef __BSP_NTC_H_
#define __BSP_NTC_H_
#include "main.h"

typedef enum{
   decimals,
   integer

}read_ntc_value;


void Read_NTC_Temperature_Power_On(void);

void Read_NTC_Temperature_Value_Handler(uint8_t set_temp_flag,uint8_t temp_value);



void Display_Speicial_Temperature_Value(uint8_t temp);

void Smg_Display_Temp_Degree_Value(void);


#endif 
