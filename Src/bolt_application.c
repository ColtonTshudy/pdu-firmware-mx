/**
 * @file bolt_application.c
 * @author Colton Tshudy (coltont@vt.edu)
 * @brief 
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024 BOLT at Virginia Tech
 * 
 */

#include "bolt_application.h"
#include "main.h"
#include "usart.h"

Application applicationSetup()
{
  Application app;
  app.nonblocking_led_timer = SWTimer_construct(MS_IN_SECONDS);
  SWTimer_start(&app.nonblocking_led_timer);
  return app;
}

void applicationLoop(Application *app_p)
{
  nonBlockingLED(app_p);

  float test = 100;
  printVal(HAL_GetTick());
}

/**
 * @brief Blinks LD2 to visually indicate firmware is not halted
 * 
 * @param app_p 
 */
void nonBlockingLED(Application *app_p)
{
  if (SWTimer_expired(&app_p->nonblocking_led_timer))
  {
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    HAL_GPIO_TogglePin(GPIO_PDU_STATUS_GPIO_Port, GPIO_PDU_STATUS_Pin);
    SWTimer_start(&app_p->nonblocking_led_timer);
  }
}

/**
 * @brief Prints a value to lpuart1
 *
 * @param val
 */
void printVal(uint32_t val)
{
  char buf[100];
  int len = snprintf(buf, sizeof buf, "%d\n\r", val);
  HAL_UART_Transmit(&hlpuart1, buf, len, HAL_MAX_DELAY);
}