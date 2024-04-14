/**
 ******************************************************************************
 * @file    gpio.c
 * @brief   This file provides code for the configuration
 *          of all used GPIO pins.
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

#include "bolt_application.h"
#include "main.h"
#include "usart.h"

Application applicationSetup()
{
  Application app;
  app.nonblocking_led_timer = SWTimer_construct(MS_IN_SECONDS);
  return app;
}

void applicationLoop(Application *app_p)
{
  // Blink LED to make sure application is not halted
  // Think of it as the PDU's "heartbeat"...
  nonBlockingLED(app_p);

  char message[] = "Hello, UART!\r\n";
  HAL_UART_Transmit(&hlpuart1, (uint8_t *)message, 14, HAL_MAX_DELAY);
}

void nonBlockingLED(Application *app_p)
{
  if (SWTimer_expired(&app_p->nonblocking_led_timer))
  {
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
  }
}