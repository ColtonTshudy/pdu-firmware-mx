#include "bolt_communications.h"
#include "bolt_debug.h"
#include "stdbool.h"
#include "stdint.h"

/**
 * @brief Configures FDCAN1 for PCAN reception
 * @return HAL status
 */
void startPCAN(FDCAN_HandleTypeDef* hfdcan)
{
	HAL_FDCAN_Start(hfdcan);

	FDCAN_FilterTypeDef sFilterConfig;

	sFilterConfig.IdType = FDCAN_EXTENDED_ID;
	sFilterConfig.FilterIndex = 0;
	sFilterConfig.FilterType = FDCAN_FILTER_RANGE;
	sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	sFilterConfig.FilterID1 = 0x000;
	sFilterConfig.FilterID2 = 0x1FFFFFFF;

	if(HAL_FDCAN_ConfigFilter(hfdcan, &sFilterConfig) != HAL_OK)
	{
		/* Filter configuration Error */
		Error_Handler();
	}

	if(HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief Check FDCAN for received message
 * @param hfdcan: Pointer to FDCAN handle
 * @param msg: Pointer to CAN_RxMessage structure to store the received message
 * @return bool: true if message received, false if no message available
 */
bool checkPCAN(FDCAN_HandleTypeDef* hfdcan, CAN_RxMessage* msg)
{
	FDCAN_RxHeaderTypeDef rxHeader;

	// Check if a message is available in RX FIFO 0
	if(HAL_FDCAN_GetRxFifoFillLevel(hfdcan, FDCAN_RX_FIFO0) > 0)
	{
		// Retrieve message from RX FIFO 0
		if(HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rxHeader, msg->Data) == HAL_OK)
		{
			// Store message details in the provided structure
			msg->StdId = rxHeader.Identifier;
			msg->ExtId = rxHeader.Identifier;
			msg->DLC = rxHeader.DataLength >>
					   16; // DataLength is a 32-bit field, actual DLC is in the upper 16 bits

			return true; // Message received and stored
		}
	}

	return false; // No message available
}

void sendPCANMessage(FDCAN_HandleTypeDef* hfdcan, struct Application* app_p)
{
	(void)app_p;

	FDCAN_TxHeaderTypeDef TxHeader;
	uint8_t TxData[8];

	// Configure TX Header for FDCAN1
	TxHeader.Identifier = 0x11;
	TxHeader.IdType = FDCAN_STANDARD_ID;
	TxHeader.TxFrameType = FDCAN_DATA_FRAME;
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
	TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
	TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	TxHeader.MessageMarker = 0;

	TxData[0] = 50;
	TxData[1] = 0xAA;

	if(HAL_FDCAN_AddMessageToTxFifoQ(hfdcan, &TxHeader, TxData) != HAL_OK)
	{
		Error_Handler();
	}
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef* hfdcan, uint32_t RxFifo0ITs)
{
	FDCAN_RxHeaderTypeDef RxHeader;
	uint8_t RxData[8];

	if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
	{
		/* Retrieve Rx messages from RX FIFO0 */
		if(HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
		{
			Error_Handler();
		}

		LOG_DBG("CAN Rx: %08lx", RxHeader.Identifier);
		LOG_DBG("%02x %02x %02x %02x %02x %02x %02x %02x",
				RxData[0],
				RxData[1],
				RxData[2],
				RxData[3],
				RxData[4],
				RxData[5],
				RxData[6],
				RxData[7]);
	}
}