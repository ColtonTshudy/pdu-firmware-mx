/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32g4xx_hal_msp.c
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim);
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{

	/* USER CODE BEGIN MspInit 0 */

	/* USER CODE END MspInit 0 */

	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();

	/* System interrupt init*/

	/** Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
  */
	HAL_PWREx_DisableUCPDDeadBattery();

	/* USER CODE BEGIN MspInit 1 */

	/* USER CODE END MspInit 1 */
}

/**
* @brief ADC MSP Initialization
* This function configures the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
	if(hadc->Instance == ADC1)
	{
		/* USER CODE BEGIN ADC1_MspInit 0 */

		/* USER CODE END ADC1_MspInit 0 */

		/** Initializes the peripherals clocks
  */
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC12;
		PeriphClkInit.Adc12ClockSelection = RCC_ADC12CLKSOURCE_SYSCLK;
		if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
		{
			Error_Handler();
		}

		/* Peripheral clock enable */
		__HAL_RCC_ADC12_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**ADC1 GPIO Configuration
    PC0     ------> ADC1_IN6
    PC1     ------> ADC1_IN7
    PA0     ------> ADC1_IN1
    PA1     ------> ADC1_IN2
    PB14     ------> ADC1_IN5
    */
		GPIO_InitStruct.Pin = ADC_CURR_3V3_Pin | ADC_VCC_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = ADC_CURR_VCC_Pin | ADC_CURR_12_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = ADC_CURR_5_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(ADC_CURR_5_GPIO_Port, &GPIO_InitStruct);

		/* USER CODE BEGIN ADC1_MspInit 1 */

		/* USER CODE END ADC1_MspInit 1 */
	}
}

/**
* @brief ADC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
	if(hadc->Instance == ADC1)
	{
		/* USER CODE BEGIN ADC1_MspDeInit 0 */

		/* USER CODE END ADC1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_ADC12_CLK_DISABLE();

		/**ADC1 GPIO Configuration
    PC0     ------> ADC1_IN6
    PC1     ------> ADC1_IN7
    PA0     ------> ADC1_IN1
    PA1     ------> ADC1_IN2
    PB14     ------> ADC1_IN5
    */
		HAL_GPIO_DeInit(GPIOC, ADC_CURR_3V3_Pin | ADC_VCC_Pin);

		HAL_GPIO_DeInit(GPIOA, ADC_CURR_VCC_Pin | ADC_CURR_12_Pin);

		HAL_GPIO_DeInit(ADC_CURR_5_GPIO_Port, ADC_CURR_5_Pin);

		/* USER CODE BEGIN ADC1_MspDeInit 1 */

		/* USER CODE END ADC1_MspDeInit 1 */
	}
}

static uint32_t HAL_RCC_FDCAN_CLK_ENABLED = 0;

/**
* @brief FDCAN MSP Initialization
* This function configures the hardware resources used in this example
* @param hfdcan: FDCAN handle pointer
* @retval None
*/
void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef* hfdcan)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
	if(hfdcan->Instance == FDCAN1)
	{
		/* USER CODE BEGIN FDCAN1_MspInit 0 */

		/* USER CODE END FDCAN1_MspInit 0 */

		/** Initializes the peripherals clocks
  */
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
		PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
		if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
		{
			Error_Handler();
		}

		/* Peripheral clock enable */
		HAL_RCC_FDCAN_CLK_ENABLED++;
		if(HAL_RCC_FDCAN_CLK_ENABLED == 1)
		{
			__HAL_RCC_FDCAN_CLK_ENABLE();
		}

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**FDCAN1 GPIO Configuration
    PA11     ------> FDCAN1_RX
    PA12     ------> FDCAN1_TX
    */
		GPIO_InitStruct.Pin = PCAN_RX_Pin | PCAN_TX_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN FDCAN1_MspInit 1 */

		/* USER CODE END FDCAN1_MspInit 1 */
	}
	else if(hfdcan->Instance == FDCAN2)
	{
		/* USER CODE BEGIN FDCAN2_MspInit 0 */

		/* USER CODE END FDCAN2_MspInit 0 */

		/** Initializes the peripherals clocks
  */
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
		PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
		if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
		{
			Error_Handler();
		}

		/* Peripheral clock enable */
		HAL_RCC_FDCAN_CLK_ENABLED++;
		if(HAL_RCC_FDCAN_CLK_ENABLED == 1)
		{
			__HAL_RCC_FDCAN_CLK_ENABLE();
		}

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**FDCAN2 GPIO Configuration
    PB12     ------> FDCAN2_RX
    PB13     ------> FDCAN2_TX
    */
		GPIO_InitStruct.Pin = XCAN_RX_Pin | XCAN_TX_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USER CODE BEGIN FDCAN2_MspInit 1 */

		/* USER CODE END FDCAN2_MspInit 1 */
	}
}

/**
* @brief FDCAN MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hfdcan: FDCAN handle pointer
* @retval None
*/
void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef* hfdcan)
{
	if(hfdcan->Instance == FDCAN1)
	{
		/* USER CODE BEGIN FDCAN1_MspDeInit 0 */

		/* USER CODE END FDCAN1_MspDeInit 0 */
		/* Peripheral clock disable */
		HAL_RCC_FDCAN_CLK_ENABLED--;
		if(HAL_RCC_FDCAN_CLK_ENABLED == 0)
		{
			__HAL_RCC_FDCAN_CLK_DISABLE();
		}

		/**FDCAN1 GPIO Configuration
    PA11     ------> FDCAN1_RX
    PA12     ------> FDCAN1_TX
    */
		HAL_GPIO_DeInit(GPIOA, PCAN_RX_Pin | PCAN_TX_Pin);

		/* USER CODE BEGIN FDCAN1_MspDeInit 1 */

		/* USER CODE END FDCAN1_MspDeInit 1 */
	}
	else if(hfdcan->Instance == FDCAN2)
	{
		/* USER CODE BEGIN FDCAN2_MspDeInit 0 */

		/* USER CODE END FDCAN2_MspDeInit 0 */
		/* Peripheral clock disable */
		HAL_RCC_FDCAN_CLK_ENABLED--;
		if(HAL_RCC_FDCAN_CLK_ENABLED == 0)
		{
			__HAL_RCC_FDCAN_CLK_DISABLE();
		}

		/**FDCAN2 GPIO Configuration
    PB12     ------> FDCAN2_RX
    PB13     ------> FDCAN2_TX
    */
		HAL_GPIO_DeInit(GPIOB, XCAN_RX_Pin | XCAN_TX_Pin);

		/* USER CODE BEGIN FDCAN2_MspDeInit 1 */

		/* USER CODE END FDCAN2_MspDeInit 1 */
	}
}

/**
* @brief UART MSP Initialization
* This function configures the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
	if(huart->Instance == LPUART1)
	{
		/* USER CODE BEGIN LPUART1_MspInit 0 */

		/* USER CODE END LPUART1_MspInit 0 */

		/** Initializes the peripherals clocks
  */
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
		PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
		if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
		{
			Error_Handler();
		}

		/* Peripheral clock enable */
		__HAL_RCC_LPUART1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**LPUART1 GPIO Configuration
    PA2     ------> LPUART1_TX
    PA3     ------> LPUART1_RX
    */
		GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF12_LPUART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN LPUART1_MspInit 1 */

		/* USER CODE END LPUART1_MspInit 1 */
	}
}

/**
* @brief UART MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
	if(huart->Instance == LPUART1)
	{
		/* USER CODE BEGIN LPUART1_MspDeInit 0 */

		/* USER CODE END LPUART1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_LPUART1_CLK_DISABLE();

		/**LPUART1 GPIO Configuration
    PA2     ------> LPUART1_TX
    PA3     ------> LPUART1_RX
    */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);

		/* USER CODE BEGIN LPUART1_MspDeInit 1 */

		/* USER CODE END LPUART1_MspDeInit 1 */
	}
}

/**
* @brief TIM_Base MSP Initialization
* This function configures the hardware resources used in this example
* @param htim_base: TIM_Base handle pointer
* @retval None
*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
	if(htim_base->Instance == TIM1)
	{
		/* USER CODE BEGIN TIM1_MspInit 0 */

		/* USER CODE END TIM1_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_TIM1_CLK_ENABLE();
		/* USER CODE BEGIN TIM1_MspInit 1 */

		/* USER CODE END TIM1_MspInit 1 */
	}
	else if(htim_base->Instance == TIM3)
	{
		/* USER CODE BEGIN TIM3_MspInit 0 */

		/* USER CODE END TIM3_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_TIM3_CLK_ENABLE();
		/* USER CODE BEGIN TIM3_MspInit 1 */

		/* USER CODE END TIM3_MspInit 1 */
	}
}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(htim->Instance == TIM1)
	{
		/* USER CODE BEGIN TIM1_MspPostInit 0 */

		/* USER CODE END TIM1_MspPostInit 0 */
		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**TIM1 GPIO Configuration
    PA8     ------> TIM1_CH1
    */
		GPIO_InitStruct.Pin = PWM_PUMP_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF6_TIM1;
		HAL_GPIO_Init(PWM_PUMP_GPIO_Port, &GPIO_InitStruct);

		/* USER CODE BEGIN TIM1_MspPostInit 1 */

		/* USER CODE END TIM1_MspPostInit 1 */
	}
	else if(htim->Instance == TIM3)
	{
		/* USER CODE BEGIN TIM3_MspPostInit 0 */

		/* USER CODE END TIM3_MspPostInit 0 */

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**TIM3 GPIO Configuration
    PA6     ------> TIM3_CH1
    */
		GPIO_InitStruct.Pin = PWM_FAN_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
		HAL_GPIO_Init(PWM_FAN_GPIO_Port, &GPIO_InitStruct);

		/* USER CODE BEGIN TIM3_MspPostInit 1 */

		/* USER CODE END TIM3_MspPostInit 1 */
	}
}
/**
* @brief TIM_Base MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param htim_base: TIM_Base handle pointer
* @retval None
*/
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{
	if(htim_base->Instance == TIM1)
	{
		/* USER CODE BEGIN TIM1_MspDeInit 0 */

		/* USER CODE END TIM1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM1_CLK_DISABLE();
		/* USER CODE BEGIN TIM1_MspDeInit 1 */

		/* USER CODE END TIM1_MspDeInit 1 */
	}
	else if(htim_base->Instance == TIM3)
	{
		/* USER CODE BEGIN TIM3_MspDeInit 0 */

		/* USER CODE END TIM3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM3_CLK_DISABLE();
		/* USER CODE BEGIN TIM3_MspDeInit 1 */

		/* USER CODE END TIM3_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
