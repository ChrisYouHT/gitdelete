/**
 * @file    can.h
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-07-12
 * @brief   
 * 
 @verbatim
 
 @endverbatim
 *
 * @attention
 *
 *
 *
 * <h2><center>&copy; COPYRIGHT 2017 无锡市驰海智能科技有限公司</center></h2>
 */

#ifndef CAN_H
#define CAN_H

#include "stm32f4xx_hal.h"

#define CANx                            CAN2
#define CANx_CLK_ENABLE()               __HAL_RCC_CAN2_CLK_ENABLE()
#define CANx_AF                         GPIO_AF9_CAN2
#define CANx_RX0_IRQn                   CAN2_RX0_IRQn
#define CANx_RX0_IRQHandler             CAN2_RX0_IRQHandler
#define CANx_TXBUFFERSIZE               64U
#define CANx_RXBUFFERSIZE               CANx_TXBUFFERSIZE

#define CANx_TX_PIN                     GPIO_PIN_13
#define CANx_TX_PORT                    GPIOB
#define CANx_TX_CLK_ENABLE()            __HAL_RCC_GPIOB_CLK_ENABLE()

#define CANx_RX_PIN                     GPIO_PIN_12
#define CANx_RX_PORT                    GPIOB
#define CANx_RX_CLK_ENABLE()            __HAL_RCC_GPIOB_CLK_ENABLE()

extern CAN_HandleTypeDef hCANx;
extern CAN_TxHeaderTypeDef hCANx_TxHeader;
extern CAN_RxHeaderTypeDef hCANx_RxHeader;

extern uint8_t CANx_TxBuffer[];
extern uint8_t CANx_RxBuffer[];
extern uint32_t CANx_TxMailBox;

void CANx_Init(void);
void CANx_MspInit(void);
HAL_StatusTypeDef CANx_SendData(CAN_TxHeaderTypeDef *pTxHeader, uint8_t *pData, uint32_t *pTxMail);
HAL_StatusTypeDef CANx_GetData(CAN_RxHeaderTypeDef *pRxHeader, uint8_t *pData);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);

#endif /* end CAN_H */