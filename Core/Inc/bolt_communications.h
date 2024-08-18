#include "bolt_application.h"
#include "bolt_config.h"
#include "stdbool.h"
#include "stdint.h"
#include "stm32g4xx_hal.h"

typedef struct
{
	uint32_t StdId;
	uint32_t ExtId;
	uint32_t DLC;
	uint8_t Data[8];
} CAN_RxMessage;

//!< Set up FDCAN1 to recieve PCAN messages
void startPCAN(FDCAN_HandleTypeDef*);

//!< Check PCAN for RX messages
bool checkPCAN(FDCAN_HandleTypeDef*, CAN_RxMessage*);

void sendPCANMessage(FDCAN_HandleTypeDef*, struct Application*);