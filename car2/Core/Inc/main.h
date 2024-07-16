/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
extern unsigned int MotorSpeed1,MotorSpeed2;  // 电机当前速度数值，从编码器中获取
extern int MotorOutput1,MotorOutput2;		  // 电机输出
extern float motor_2_pwm_nomal;		//测试电机启转承霿PWM倿
extern float motor_1_pwm_nomal;
extern uint8_t test;
extern uint8_t flag_go;
extern uint8_t flag_turn;
extern uint8_t flag_turn_go;
extern int a;
extern float feedbackValue;
extern char str[50];
extern	uint8_t CS;
extern uint8_t cross;
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
#define BIN1_Pin GPIO_PIN_11
#define BIN1_GPIO_Port GPIOB
#define BIN2_Pin GPIO_PIN_12
#define BIN2_GPIO_Port GPIOB
#define AIN2_Pin GPIO_PIN_9
#define AIN2_GPIO_Port GPIOC
#define AIN1_Pin GPIO_PIN_15
#define AIN1_GPIO_Port GPIOA
#define LCD_DC_Pin GPIO_PIN_4
#define LCD_DC_GPIO_Port GPIOB
#define LCD_RST_Pin GPIO_PIN_6
#define LCD_RST_GPIO_Port GPIOB
#define LCD_PWR_Pin GPIO_PIN_7
#define LCD_PWR_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  
typedef const int16_t sc16;  
typedef const int8_t sc8;  

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  
typedef __I int16_t vsc16; 
typedef __I int8_t vsc8;   

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  
typedef const uint16_t uc16;  
typedef const uint8_t uc8; 

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  
typedef __I uint16_t vuc16; 
typedef __I uint8_t vuc8; 
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
