/**
 * @file    rs232.c
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-07-09
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

#include "rs232.h"
#include "stdio.h"
void RX_Process(uint8_t dat);

UART_HandleTypeDef hRS232A;
UART_HandleTypeDef hRS232B;

uint8_t RS232A_TxBuffer[RS232A_TXBUFFERSIZE];
uint8_t RS232A_RxBuffer[RS232A_RXBUFFERSIZE];

uint8_t RS232B_TxBuffer[RS232B_TXBUFFERSIZE];
uint8_t RS232B_RxBuffer[RS232B_RXBUFFERSIZE];

DMA_HandleTypeDef hRS232A_TX_DMA;

/**
 * @brief  RS232初始化
 * @param  None
 * @retval None
 */
void RS232_Init(void)
{
    RS232A_CLK_ENABLE();

    hRS232A.Instance = RS232A;
    hRS232A.Init.BaudRate = 19200;
    hRS232A.Init.WordLength = UART_WORDLENGTH_8B;
    hRS232A.Init.StopBits = UART_STOPBITS_1;
    hRS232A.Init.Parity = UART_PARITY_NONE;
    hRS232A.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    hRS232A.Init.Mode = UART_MODE_TX_RX;
    hRS232A.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&hRS232A) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    } /* end if */
    

    RS232B_CLK_ENABLE();

    hRS232B.Instance = RS232B;
    hRS232B.Init.BaudRate = 19200;
    hRS232B.Init.WordLength = UART_WORDLENGTH_8B;
    hRS232B.Init.StopBits = UART_STOPBITS_1;
    hRS232B.Init.Parity = UART_PARITY_NONE;
    hRS232B.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    hRS232B.Init.Mode = UART_MODE_TX_RX;
    hRS232B.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&hRS232B) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    }     /* end if */
} /* end RS232_Init() */

/**
 * @brief  RS232A硬件初始化
 * @param  huart 串口句柄
 * @retval None
 */
void RS232A_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RS232A_TX_PIN_CLK_ENABLE();
    RS232A_TX_PIN_CLK_ENABLE();

    GPIO_InitStruct.Pin = RS232A_TX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = RS232A_TX_PIN_AF;

    HAL_GPIO_Init(RS232A_TX_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = RS232A_RX_PIN;
    GPIO_InitStruct.Alternate = RS232A_RX_PIN_AF;

    HAL_GPIO_Init(RS232A_RX_PORT, &GPIO_InitStruct);

    /* TX DMA */
    RS232A_TX_DMA_CLK_ENABLE();

    hRS232A_TX_DMA.Instance = RS232A_TX_DMA_INSTANCE;
    hRS232A_TX_DMA.Init.Channel = RS232A_TX_DMA_CHANNEL;
    hRS232A_TX_DMA.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hRS232A_TX_DMA.Init.MemInc = DMA_MINC_ENABLE;
    hRS232A_TX_DMA.Init.PeriphInc = DMA_PINC_DISABLE;
    hRS232A_TX_DMA.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hRS232A_TX_DMA.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hRS232A_TX_DMA.Init.Mode = DMA_NORMAL;
    hRS232A_TX_DMA.Init.Priority = DMA_PRIORITY_LOW;
    hRS232A_TX_DMA.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    hRS232A_TX_DMA.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    hRS232A_TX_DMA.Init.MemBurst = DMA_MBURST_INC4;
    hRS232A_TX_DMA.Init.PeriphBurst = DMA_PBURST_INC4;

    HAL_DMA_Init(&hRS232A_TX_DMA);
    __HAL_LINKDMA(huart, hdmatx, hRS232A_TX_DMA);



    HAL_NVIC_SetPriority(RS232A_TX_DMA_INSTANCE_IRQ, 14, 0);
    HAL_NVIC_EnableIRQ(RS232A_TX_DMA_INSTANCE_IRQ);
		


    HAL_NVIC_SetPriority(RS232A_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(RS232A_IRQn);
    __HAL_UART_ENABLE_IT(&hRS232A, UART_IT_RXNE);
} /* end RS232A_MspInit() */

/**
 * @brief  RS232B硬件初始化
 * @param  huart 串口句柄
 * @retval None
 */
void RS232B_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RS232B_TX_PIN_CLK_ENABLE();
    RS232B_TX_PIN_CLK_ENABLE();

    GPIO_InitStruct.Pin = RS232B_TX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = RS232B_TX_PIN_AF;

    HAL_GPIO_Init(RS232B_TX_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = RS232B_RX_PIN;
    GPIO_InitStruct.Alternate = RS232B_RX_PIN_AF;

    HAL_GPIO_Init(RS232B_RX_PORT, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(RS232B_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(RS232B_IRQn);
    __HAL_UART_ENABLE_IT(&hRS232B, UART_IT_RXNE);
} /* end RS232A_MspInit() */

/**
 * @brief  RS232A发送数据
 * @param  pData 数据地址
 * @param  length 数据长度
 * @param  TimeOut 超时时间，单位ms
 * @retval None
 */
HAL_StatusTypeDef RS232A_SendBytes(uint8_t *pData, int16_t length, uint32_t TimeOut)
{
    HAL_StatusTypeDef Status;

    Status = HAL_UART_Transmit(&hRS232A, pData, length, TimeOut);

    return Status;
} /* end RS232A_SendBytes() */

/**
 * @brief  RS232A DMA发送数据
 * @param  pData 数据地址
 * @param  length 数据长度
 * @retval None
 */
HAL_StatusTypeDef RS232A_SendBytes_DMA(uint8_t *pData, int16_t length)
{
    HAL_StatusTypeDef Status;

    Status = HAL_UART_Transmit_DMA(&hRS232A, pData, length);

    return Status;
} /* end RS232A_SendBytes_DMA() */


/**
 * @brief  RS232B发送数据
 * @param  pData 数据地址
 * @param  length 数据长度
 * @param  TimeOut 超时时间，单位ms
 * @retval None
 */
HAL_StatusTypeDef RS232B_SendBytes(uint8_t *pData, int16_t length, uint32_t TimeOut)
{
    HAL_StatusTypeDef Status;

    Status = HAL_UART_Transmit(&hRS232B, pData, length, TimeOut);

    return Status;
} /* end RS232A_SendBytes() */

/**
 * @brief  RS232A接收非空中断服务
 * @param  None
 * @retval None
 */
void RS232A_RxneCallback(void)
{
    uint8_t dat = 0;
    dat = (uint8_t)(hRS232A.Instance->DR & (uint8_t)0x00FF);

		RX_Process(dat);
	
    //RS232A_SendBytes(&tmp, 1, 1000);
} /* end RS232A_RxneCallback() */



/**
 * @brief  RS232B接收非空中断服务
 * @param  None
 * @retval None
 */
void RS232B_RxneCallback(void)
{
    uint8_t tmp = 0;
    tmp = (uint8_t)(hRS232B.Instance->DR & (uint8_t)0x00FF);
		RX_Process(tmp);
    //RS232B_SendBytes(&tmp, 1, 1000);
} /* end RS232A_RxneCallback() */

int fputc(int ch, FILE *f)
{
//		/* 发送一个字节数据到USART1 */
//		USART_SendData(USART2, (uint8_t) ch);
			RS232B_SendBytes((uint8_t *)&ch,1,1000);
//		/* 等待发送完毕 */
		
			while (__HAL_UART_GET_FLAG(&hRS232B, UART_FLAG_TC) == RESET);
		return (ch);
}
