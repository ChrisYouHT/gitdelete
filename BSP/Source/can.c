/**
 * @file    can.c
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-07-12
 * @brief   
 * 
 @verbatim
 
 修改记录
 序号 | 日期 | 作者 | 说明
    --|  --  | --  | --
 @endverbatim
 *
 * @attention
 *
 *
 *
 * <h2><center>&copy; COPYRIGHT 2018 无锡市驰海智能科技有限公司</center></h2>
 */

#include "can.h"
#include <string.h>

CAN_HandleTypeDef hCANx;
CAN_TxHeaderTypeDef hCANx_TxHeader;
CAN_RxHeaderTypeDef hCANx_RxHeader;

uint8_t CANx_TxBuffer[CANx_TXBUFFERSIZE];
uint8_t CANx_RxBuffer[CANx_RXBUFFERSIZE];
uint32_t CANx_TxMailBox;

/**
 * @brief  CANx初始化
 * @param  None
 * @retval None
 */
void CANx_Init(void)
{
    CAN_FilterTypeDef CAN_FilterStruct;

    hCANx.Instance = CANx;
    hCANx.Init.TimeTriggeredMode = DISABLE;
    hCANx.Init.AutoBusOff = DISABLE;
    hCANx.Init.AutoRetransmission = ENABLE;
    hCANx.Init.AutoWakeUp = DISABLE;
    hCANx.Init.ReceiveFifoLocked = DISABLE;
    hCANx.Init.TransmitFifoPriority = DISABLE;
    hCANx.Init.Prescaler = 6;
    hCANx.Init.Mode = CAN_MODE_NORMAL;
    hCANx.Init.SyncJumpWidth = CAN_SJW_1TQ;
    hCANx.Init.TimeSeg1 = CAN_BS1_8TQ;
    hCANx.Init.TimeSeg2 = CAN_BS2_6TQ;

    if (HAL_CAN_Init(&hCANx) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    } /* end if */

    __HAL_RCC_CAN1_CLK_ENABLE();

    CAN_FilterStruct.FilterBank = 14;
    CAN_FilterStruct.FilterMode = CAN_FILTERMODE_IDMASK;
    CAN_FilterStruct.FilterScale = CAN_FILTERSCALE_32BIT;
    CAN_FilterStruct.FilterIdHigh = 0x0000;
    CAN_FilterStruct.FilterIdLow = 0x0000;
    CAN_FilterStruct.FilterMaskIdHigh = 0x0000;
    CAN_FilterStruct.FilterMaskIdLow = 0x0000;
    CAN_FilterStruct.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    CAN_FilterStruct.FilterActivation = ENABLE;
    CAN_FilterStruct.SlaveStartFilterBank = 14;
    
    if (HAL_CAN_ConfigFilter(&hCANx, &CAN_FilterStruct) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    } /* end if */

    if (HAL_CAN_Start(&hCANx) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    } /* end if */

    if (HAL_CAN_ActivateNotification(&hCANx, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
      
    } /* end if */
} /* end CANx_Init() */

/**
 * @brief  CANx硬件初始化
 * @param  None
 * @retval None
 */
void CANx_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    CANx_TX_CLK_ENABLE();
    CANx_RX_CLK_ENABLE();
    CANx_CLK_ENABLE();

    GPIO_InitStruct.Pin = CANx_TX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = CANx_AF;
    HAL_GPIO_Init(CANx_TX_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = CANx_RX_PIN;
    HAL_GPIO_Init(CANx_RX_PORT, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(CANx_RX0_IRQn, 13, 0);
    HAL_NVIC_EnableIRQ(CANx_RX0_IRQn);
} /* end CANx_MspInit() */

/**
 * @brief  CANx发送数据
 * @param  pTxHeader
 * @param  pData
 * @param  pTxMail     
 * @retval None
 */
HAL_StatusTypeDef CANx_SendData(CAN_TxHeaderTypeDef *pTxHeader, uint8_t *pData, uint32_t *pTxMail)
{
    HAL_StatusTypeDef status;

    status = HAL_CAN_AddTxMessage(&hCANx, pTxHeader, pData, pTxMail);

    return status;
} /* end CANx_SendData() */

/**
 * @brief  CANx读取数据
 * @param  None
 * @retval None
 */
HAL_StatusTypeDef CANx_GetData(CAN_RxHeaderTypeDef *pRxHeader, uint8_t *pData)
{
    HAL_StatusTypeDef status;

    status = HAL_CAN_GetRxMessage(&hCANx, CAN_RX_FIFO0, pRxHeader, pData);

    return status;
} /* end CANx_GetData() */

/**
 * @brief  挂起回调函数
 * @param  None
 * @retval None
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    HAL_StatusTypeDef status;

    if (hcan->Instance == CANx)
    {
        HAL_NVIC_DisableIRQ(CANx_RX0_IRQn);

        status = CANx_GetData(&hCANx_RxHeader, CANx_RxBuffer);
        if (status == HAL_OK)
        {
            uint8_t i = 0;
            
            memcpy(CANx_TxBuffer, CANx_RxBuffer, 8);

            hCANx_TxHeader.StdId = 0x12;
            hCANx_TxHeader.DLC = 8;
            hCANx_TxHeader.ExtId = 0x12;
            hCANx_TxHeader.RTR = CAN_RTR_DATA;
            hCANx_TxHeader.IDE = CAN_ID_STD;
            hCANx_TxHeader.TransmitGlobalTime = DISABLE;

            CANx_SendData(&hCANx_TxHeader, CANx_TxBuffer, &CANx_TxMailBox);

            for (i =0; i < 8; i++)
            {
                CANx_TxBuffer[i] = 0;
                CANx_RxBuffer[i] = 0;
            } /* end for */
        } /* end if */

        HAL_NVIC_EnableIRQ(CANx_RX0_IRQn);
    } /* end if */
} /* end HAL_CAN_RxFifo0() */