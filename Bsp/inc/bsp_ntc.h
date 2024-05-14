#ifndef __BSP_NTC_H_
#define __BSP_NTC_H_
#include "main.h"



void Display_Speicial_Temperature_Value(uint8_t temp);

void Smg_Display_Temp_Degree_Value(void);

uint8_t Read_NTC_Temperature_Degree(void);

void Read_NTC_Temperature_Value_Handler(void);


#endif 
