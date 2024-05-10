/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

//KEY SELECT GPIO 
#define KEY_SELECT_Pin 							GPIO_PIN_0
#define KEY_SELECT_GPIO_Port 					GPIOB


//EKY CONFIRM GPIO
#define KEY_CONFIRM_Pin 						GPIO_PIN_3
#define KEY_CONFIRM_GPIO_Port 					GPIOB





//LED RELAY GPIO
#define LED_RELAY_A_Pin 					GPIO_PIN_4
#define LED_RELAY_A_GPIO_Port 				GPIOA

#define LED_RELAY_B_Pin 					GPIO_PIN_5
#define LED_RELAY_B_GPIO_Port 				GPIOA

#define LED_RELAY_C_Pin 					GPIO_PIN_6
#define LED_RELAY_C_GPIO_Port 				GPIOA

#define LED_RELAY_D_Pin 					GPIO_PIN_7
#define LED_RELAY_D_GPIO_Port 				GPIOA

//LED OF KEY
#define LED_KEY_CTL_Pin 					GPIO_PIN_1
#define LED_KEY_CTL_GPIO_Port 				GPIOA




#define LED_ADD_DEC_Pin GPIO_PIN_11
#define LED_ADD_DEC_GPIO_Port GPIOA

//RELAY GPIO
#define RELAY_A_Pin 					GPIO_PIN_12
#define RELAY_A_GPIO_Port 				GPIOA

#define RELAY_C_Pin 				GPIO_PIN_13
#define RELAY_C_GPIO_Port 			GPIOA


#define RELAY_B_Pin 						GPIO_PIN_3
#define RELAY_B_GPIO_Port 					GPIOA

#define RELAY_D_Pin 						GPIO_PIN_15
#define RELAY_D_GPIO_Port 					GPIOC





/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
