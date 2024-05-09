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
#include "fdcan.h"

FDCAN_TxHeaderTypeDef TxHeader;
FDCAN_RxHeaderTypeDef RxHeader;

uint8_t TxData[2];
uint8_t RxData[2];

Application applicationSetup()
{
  Application app;
  app.nonblocking_led_timer = SWTimer_construct(MS_IN_SECONDS);
  SWTimer_start(&app.nonblocking_led_timer);

  FDCAN_Config();
  TxData[0] = 0xAA;
  TxData[1] = 0xAA;
  return app;
}

void applicationLoop(Application *app_p)
{
  nonBlockingLED(app_p);

  float test = 100;
  printVal(HAL_GetTick());
  HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData);
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

void FDCAN_Config(void) {
  // FDCAN_FilterTypeDef sFilterConfig;

  // /* Configure Rx filter */
  // sFilterConfig.IdType = FDCAN_STANDARD_ID;
  // sFilterConfig.FilterIndex = 0;
  // sFilterConfig.FilterType = FDCAN_FILTER_MASK;
  // sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  // sFilterConfig.FilterID1 = 0x321;
  // sFilterConfig.FilterID2 = 0x7FF;
  // if (HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK)
  // {
  //   Error_Handler();
  // }

  // /* Configure global filter:
  //   Filter all remote frames with STD and EXT ID
  //   Reject non matching frames with STD ID and EXT ID */
  // if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
  // {
  //   Error_Handler();
  // }

  // /* Start the FDCAN module */
  // if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK)
  // {
  //   Error_Handler();
  // }

  // if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
  // {
  //   Error_Handler();
  // }

  /* Prepare Tx Header */
  TxHeader.Identifier = 0x321;
  TxHeader.IdType = FDCAN_STANDARD_ID;
  TxHeader.TxFrameType = FDCAN_DATA_FRAME;
  TxHeader.DataLength = FDCAN_DLC_BYTES_2;
  TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
  TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
  TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
  TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
  TxHeader.MessageMarker = 0;
}