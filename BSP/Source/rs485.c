/**
 * @file    rs485.c
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-07-11
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


#include "rs485.h"
#include "plc_conf.h"
UART_HandleTypeDef hRS485A;
UART_HandleTypeDef hRS485B;

uint8_t RS485A_Tx_Buffer[RS485A_TXBUFFERSIZE];
uint8_t RS485A_Rx_Buffer[RS485A_RXBUFFERSIZE];

uint8_t RS485B_Tx_Buffer[RS485B_TXBUFFERSIZE];
uint8_t RS485B_Rx_Buffer[RS485B_RXBUFFERSIZE];

/**
 * @brief  RS485初始化
 * @param  None
 * @retval None
 */
void RS485_Init(void)
{
    hRS485A.Instance = RS485A;
    hRS485A.Init.BaudRate = 115200;
    hRS485A.Init.WordLength = UART_WORDLENGTH_8B;
    hRS485A.Init.StopBits = UART_STOPBITS_1;
    hRS485A.Init.Parity = UART_PARITY_NONE;
    hRS485A.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    hRS485A.Init.Mode = UART_MODE_TX_RX;
    hRS485A.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&hRS485A) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    } /* end if */

    hRS485B.Instance = RS485B;
    hRS485B.Init.BaudRate = 115200;
    hRS485B.Init.WordLength = UART_WORDLENGTH_8B;
    hRS485B.Init.StopBits = UART_STOPBITS_1;
    hRS485B.Init.Parity = UART_PARITY_NONE;
    hRS485B.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    hRS485B.Init.Mode = UART_MODE_TX_RX;
    hRS485B.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&hRS485B) != HAL_OK)
    {
        for (;;)
        {

        } /* end for */
    }     /* end if */

    RS485A_SetMode(RS485_MODE_RX);
    RS485B_SetMode(RS485_MODE_RX);
} /* end RS485_Init() */

/**
 * @brief  RS485A硬件初始化
 * @param  None
 * @retval None
 */
void RS485A_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RS485A_TX_CLK_ENABLE();
    RS485A_RX_CLK_ENABLE();
    RS485A_RE_CLK_ENABLE();
    RS485A_CLK_ENABLE();

    GPIO_InitStruct.Pin = RS485A_TX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = RS485A_AF;
    HAL_GPIO_Init(RS485A_TX_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = RS485A_RX_PIN;
    HAL_GPIO_Init(RS485A_RX_PORT, &GPIO_InitStruct);

    /* RE */
    GPIO_InitStruct.Pin = RS485A_RE_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(RS485A_RE_PORT, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(RS485A_IRQn, 14, 0);
    HAL_NVIC_EnableIRQ(RS485A_IRQn);
    __HAL_UART_ENABLE_IT(&hRS485A, UART_IT_RXNE);
} /* end RS485A_MspInit() */

/**
 * @brief  RS485B硬件初始化
 * @param  None
 * @retval None
 */
void RS485B_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RS485B_TX_CLK_ENABLE();
    RS485B_RX_CLK_ENABLE();
    RS485B_RE_CLK_ENABLE();
    RS485B_CLK_ENABLE();

    /* TX */
    GPIO_InitStruct.Pin = RS485B_TX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = RS485B_AF;
    HAL_GPIO_Init(RS485B_TX_PORT, &GPIO_InitStruct);

    /* RX */
    GPIO_InitStruct.Pin = RS485B_RX_PIN;
    HAL_GPIO_Init(RS485B_RX_PORT, &GPIO_InitStruct);

    /* RE */
    GPIO_InitStruct.Pin = RS485B_RE_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(RS485B_RE_PORT, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(RS485B_IRQn, 14, 0);
    HAL_NVIC_EnableIRQ(RS485B_IRQn);
    __HAL_UART_ENABLE_IT(&hRS485B, UART_IT_RXNE);
} /* end RS485A_MspInit() */

/**
 * @brief  RS485A模式设置
 * @param  mode
 * @retval None
 */
void RS485A_SetMode(enum RS485_ModeTypeDef mode)
{
    switch(mode)
    {
        /*  tx  */
        case 0 :
        {
            HAL_GPIO_WritePin(RS485A_RE_PORT, RS485A_RE_PIN, GPIO_PIN_SET);
            break;
        }

        /* RX */
        case 1 :
        {
            HAL_GPIO_WritePin(RS485A_RE_PORT, RS485A_RE_PIN, GPIO_PIN_RESET);
            break;
        }
        
        default :
            break;
    }
} /* end RS485A_SetMode() */

/**
 * @brief  RS485B模式设置
 * @param  mode
 * @retval None
 */
void RS485B_SetMode(enum RS485_ModeTypeDef mode)
{
    switch (mode)
    {
    /*  tx  */
    case 0:
    {
        HAL_GPIO_WritePin(RS485B_RE_PORT, RS485B_RE_PIN, GPIO_PIN_SET);
        break;
    }

    /* RX */
    case 1:
    {
        HAL_GPIO_WritePin(RS485B_RE_PORT, RS485B_RE_PIN, GPIO_PIN_RESET);
        break;
    }

    default:
        break;
    }
} /* end RS485A_SetMode() */

/**
 * @brief  RS485A发送数据
 * @param  pData 数据指针
 * @param  length 数据长度
 * @param  TimeOut 溢出时间
 * @retval None
 */
HAL_StatusTypeDef RS485A_SendBytes(uint8_t *pData, uint16_t length, uint16_t TimeOut)
{
    HAL_StatusTypeDef Status;

    RS485A_SetMode(RS485_MODE_TX);
    Status = HAL_UART_Transmit(&hRS485A, pData, length, TimeOut);
    RS485A_SetMode(RS485_MODE_RX);

    return Status;
} /* end RS485A_SendBytes() */

/**
 * @brief  RS485B发送数据
 * @param  pData 数据指针
 * @param  length 数据长度
 * @param  TimeOut 溢出时间
 * @retval None
 */
HAL_StatusTypeDef RS485B_SendBytes(uint8_t *pData, uint16_t length, uint16_t TimeOut)
{
    HAL_StatusTypeDef Status;

    RS485B_SetMode(RS485_MODE_TX);
    Status = HAL_UART_Transmit(&hRS485B, pData, length, TimeOut);
    RS485B_SetMode(RS485_MODE_RX);

    return Status;
} /* end RS485A_SendBytes() */

uint8_t RS485ARC[32];
uint16_t RS485APoint = 0;


/**
 * @brief  RS485A接收非空中断服务
 * @param  None
 * @retval None
 */
void RS485A_RxneCallback(void)
{
    uint8_t tmp = 0;
    tmp = (uint8_t)(hRS485A.Instance->DR & (uint8_t)0x00FF);
		RS485ARC[RS485APoint++] = tmp;
    //RS485A_SendBytes(&tmp, 1, 1000);
} /* end RS232A_RxneCallback() */

/**
 * @brief  RS485B接收非空中断服务
 * @param  None
 * @retval None
 */

uint8_t RS485BRC[32];
uint16_t RS485BPoint=0;

void RS485B_RxneCallback(void)
{
    uint8_t tmp = 0;
    tmp = (uint8_t)(hRS485B.Instance->DR & (uint8_t)0x00FF);
		RS485BRC[RS485BPoint++] = tmp;
    //RS485B_SendBytes(&tmp, 1, 1000);
} /* end RS232A_RxneCallback() */

void DatAnasys(void)
{
		
		


}