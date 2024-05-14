#ifndef __BSP_LED_H__
#define __BSP_LED_H__
#include "main.h"




#define KILL_LED_OFF()			HAL_GPIO_WritePin(LED_RELAY_C_GPIO_Port , LED_RELAY_C_Pin , GPIO_PIN_SET)
#define KILL_LED_ON()			HAL_GPIO_WritePin(LED_RELAY_C_GPIO_Port , LED_RELAY_C_Pin , GPIO_PIN_RESET)


#define TAPE_LED_OFF()			    HAL_GPIO_WritePin(LED_RELAY_A_GPIO_Port, LED_RELAY_A_Pin , GPIO_PIN_SET)
#define TAPE_LED_ON()					HAL_GPIO_WritePin(LED_RELAY_A_GPIO_Port, LED_RELAY_A_Pin , GPIO_PIN_RESET)

#define KEEP_HEAT_LED_OFF()				HAL_GPIO_WritePin(LED_RELAY_D_GPIO_Port , LED_RELAY_D_Pin , GPIO_PIN_SET)
#define KEEP_HEAT_LED_ON()				HAL_GPIO_WritePin(LED_RELAY_D_GPIO_Port , LED_RELAY_D_Pin , GPIO_PIN_RESET)


#define FAN_LED_OFF()			       HAL_GPIO_WritePin(LED_RELAY_B_GPIO_Port, LED_RELAY_B_Pin , GPIO_PIN_SET)
#define FAN_LED_ON()			       HAL_GPIO_WritePin(LED_RELAY_B_GPIO_Port, LED_RELAY_B_Pin, GPIO_PIN_RESET)


#define ADD_DEC_LED_OFF()			   HAL_GPIO_WritePin(LED_ADD_DEC_GPIO_Port  , LED_KEY_CTL_Pin , GPIO_PIN_SET)
#define ADD_DEC_LED_ON()			   HAL_GPIO_WritePin(LED_ADD_DEC_GPIO_Port  , LED_KEY_CTL_Pin , GPIO_PIN_RESET)

#define KEY_FUN_CONFIRM_LED_OFF()   			  	HAL_GPIO_WritePin(LED_KEY_CTL_GPIO_Port, LED_KEY_CTL_Pin , GPIO_PIN_SET)
#define KEY_FUN_CONFIRM_LED_ON()     				HAL_GPIO_WritePin(LED_KEY_CTL_GPIO_Port, LED_KEY_CTL_Pin , GPIO_PIN_RESET)




//circle led
  




typedef enum{

    LED_NULL,
	FAN_LED ,
    TAPE_LED,
    STERILIZATION_LED,
    KEEP_HEAT_LED,
    ADD_DEC_LED,
    LED_ALL_OFF,
    KEY_NULL
   
}led_content;

typedef enum{

   confirm_disable=0,
   fan_enable=0x01,
   tape_enable,
   sterilization_enable,
   keep_heat_enable,
   add_dec_enable,
   


}confirm_item;


typedef struct _led_t_{

    uint8_t gTimer_flicker;
	uint8_t gTimer_keey_heat_flicker;
    uint8_t gTimer_select_fun;
   




}LED_T;

extern LED_T led_t;


//void Led_Display_Content_Fun(uint8_t selitem);



void Led_Test_Fun(void);

void Tape_Led_Filcker(void);
void Fan_Led_Flicker(void);
void Sterilization_Led_Filcker(void);
void Keep_Heat_Led_Filcker(void);

void Keep_heat_SetUp_Led_Filcker(void);


void Led_Display_Content_Fun(uint8_t selitem, uint8_t confirm_key);




#endif 


