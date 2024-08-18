#include "bolt_communications.h"
#include "stdbool.h"
#include "stdint.h"

/**
 * @brief Configures FDCAN1 for PCAN reception
 * @return HAL status
 */
HAL_StatusTypeDef PCAN_Config_Reception(FDCAN_HandleTypeDef* hfdcan1)
{
	FDCAN_FilterTypeDef sFilterConfig;

	// Configure reception filter to accept all messages
	sFilterConfig.IdType = FDCAN_STANDARD_ID;
	sFilterConfig.FilterIndex = 0;
	sFilterConfig.FilterType = FDCAN_FILTER_MASK;
	sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	sFilterConfig.FilterID1 = 0x000;
	sFilterConfig.FilterID2 = 0x000; // Mask, 0x000 means accept all

	if(HAL_FDCAN_ConfigFilter(hfdcan1, &sFilterConfig) != HAL_OK)
	{
		return HAL_ERROR;
	}

	// Configure global filter to accept all messages
	if(HAL_FDCAN_ConfigGlobalFilter(
		   hfdcan1, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
	{
		return HAL_ERROR;
	}

	// Activate Rx FIFO 0 new message notification
	if(HAL_FDCAN_ActivateNotification(hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
	{
		return HAL_ERROR;
	}

	// Start FDCAN controller
	if(HAL_FDCAN_Start(hfdcan1) != HAL_OK)
	{
		return HAL_ERROR;
	}

	return HAL_OK;
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

void sendPCAN(struct Application* app_p)
{
	FDCAN_TxHeaderTypeDef TxHeader;
	uint8_t TxData[8];

	// Configure transmission header
	TxHeader.Identifier = 0x123;
	TxHeader.IdType = FDCAN_STANDARD_ID;
	TxHeader.TxFrameType = FDCAN_DATA_FRAME;
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
	TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
	TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	TxHeader.MessageMarker = 0;

	// Prepare data to transmit
	TxData[0] = 0x11;
	TxData[1] = 0x22;
	TxData[2] = 0x33;
	TxData[3] = 0x44;
	TxData[4] = 0x55;
	TxData[5] = 0x66;
	TxData[6] = 0x77;
	TxData[7] = 0x88;

	// Send message
	if(HAL_FDCAN_AddMessageToTxFifoQ(app_p->hfdcan1, &TxHeader, TxData) != HAL_OK)
	{
		Error_Handler();
	}
}