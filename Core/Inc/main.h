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
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

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

	void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim);

	/* Exported functions prototypes ---------------------------------------------*/
	void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define ADC_CURR_3V3_Pin GPIO_PIN_0
#define ADC_CURR_3V3_GPIO_Port GPIOC
#define ADC_VCC_Pin GPIO_PIN_1
#define ADC_VCC_GPIO_Port GPIOC
#define ADC_CURR_VCC_Pin GPIO_PIN_0
#define ADC_CURR_VCC_GPIO_Port GPIOA
#define ADC_CURR_12_Pin GPIO_PIN_1
#define ADC_CURR_12_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define PWM_FAN_Pin GPIO_PIN_6
#define PWM_FAN_GPIO_Port GPIOA
#define GPIO_ACC1_Pin GPIO_PIN_5
#define GPIO_ACC1_GPIO_Port GPIOC
#define GPIO_PDU_STATUS_Pin GPIO_PIN_1
#define GPIO_PDU_STATUS_GPIO_Port GPIOB
#define GPIO_AUX_LOW_Pin GPIO_PIN_2
#define GPIO_AUX_LOW_GPIO_Port GPIOB
#define XCAN_RX_Pin GPIO_PIN_12
#define XCAN_RX_GPIO_Port GPIOB
#define XCAN_TX_Pin GPIO_PIN_13
#define XCAN_TX_GPIO_Port GPIOB
#define ADC_CURR_5_Pin GPIO_PIN_14
#define ADC_CURR_5_GPIO_Port GPIOB
#define GPIO_ACC2_Pin GPIO_PIN_6
#define GPIO_ACC2_GPIO_Port GPIOC
#define GPIO_ACC3_Pin GPIO_PIN_8
#define GPIO_ACC3_GPIO_Port GPIOC
#define GPIO_ACC4_Pin GPIO_PIN_9
#define GPIO_ACC4_GPIO_Port GPIOC
#define PWM_PUMP_Pin GPIO_PIN_8
#define PWM_PUMP_GPIO_Port GPIOA
#define GPIO_CON_2_L_Pin GPIO_PIN_9
#define GPIO_CON_2_L_GPIO_Port GPIOA
#define PCAN_RX_Pin GPIO_PIN_11
#define PCAN_RX_GPIO_Port GPIOA
#define PCAN_TX_Pin GPIO_PIN_12
#define PCAN_TX_GPIO_Port GPIOA
#define T_SWDIO_Pin GPIO_PIN_13
#define T_SWDIO_GPIO_Port GPIOA
#define T_SWCLK_Pin GPIO_PIN_14
#define T_SWCLK_GPIO_Port GPIOA
#define GPIO_MC_IGN_EN_Pin GPIO_PIN_2
#define GPIO_MC_IGN_EN_GPIO_Port GPIOD
#define T_SWO_Pin GPIO_PIN_3
#define T_SWO_GPIO_Port GPIOB
#define GPIO_FAN_TACH_Pin GPIO_PIN_7
#define GPIO_FAN_TACH_GPIO_Port GPIOB
#define GPIO_ACC_ON_Pin GPIO_PIN_8
#define GPIO_ACC_ON_GPIO_Port GPIOB
#define GPIO_MC_START_Pin GPIO_PIN_9
#define GPIO_MC_START_GPIO_Port GPIOB

	/* USER CODE BEGIN Private defines */

	/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
