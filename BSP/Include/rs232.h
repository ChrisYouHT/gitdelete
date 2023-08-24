/**
 * @file    rs232.h
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-07-09
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

#ifndef RS232_H
#define RS232_H

#include "stm32f4xx_hal.h"

#define RS232A                          USART2
#define RS232A_CLK_ENABLE()             __HAL_RCC_USART2_CLK_ENABLE()
#define RS232A_IRQn                     USART2_IRQn
#define RS232A_IRQHandler               USART2_IRQHandler
#define RS232A_TXBUFFERSIZE             5
#define RS232A_RXBUFFERSIZE             RS232A_TXBUFFERSIZE

/* DMA TX */
#define RS232A_TX_DMA_INSTANCE          DMA1_Stream6
#define RS232A_TX_DMA_CHANNEL           DMA_CHANNEL_4
#define RS232A_TX_DMA_INSTANCE_IRQ      DMA1_Stream6_IRQn
#define RS232A_TX_DMA_INSTANCE_IRQHANDLER DMA1_Stream6_IRQHandler
#define RS232A_TX_DMA_CLK_ENABLE()      __HAL_RCC_DMA1_CLK_ENABLE()

#define RS232A_TX_PIN                   GPIO_PIN_2
#define RS232A_RX_PIN                   GPIO_PIN_3
#define RS232A_TX_PORT                  GPIOA
#define RS232A_RX_PORT                  GPIOA
#define RS232A_TX_PIN_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define RS232A_RX_PIN_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define RS232A_TX_PIN_AF                GPIO_AF7_USART2
#define RS232A_RX_PIN_AF                GPIO_AF7_USART2

#define RS232B                          USART3
#define RS232B_CLK_ENABLE()             __HAL_RCC_USART3_CLK_ENABLE()
#define RS232B_IRQn                     USART3_IRQn
#define RS232B_IRQHandler               USART3_IRQHandler
#define RS232B_TXBUFFERSIZE             5
#define RS232B_RXBUFFERSIZE             RS232B_TXBUFFERSIZE

#define RS232B_TX_PIN                   GPIO_PIN_10
#define RS232B_RX_PIN                   GPIO_PIN_11
#define RS232B_TX_PORT                  GPIOB
#define RS232B_RX_PORT                  GPIOB
#define RS232B_TX_PIN_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define RS232B_RX_PIN_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define RS232B_TX_PIN_AF                GPIO_AF7_USART3
#define RS232B_RX_PIN_AF                GPIO_AF7_USART3

extern UART_HandleTypeDef hRS232A;
extern UART_HandleTypeDef hRS232B;

extern uint8_t RS232A_TxBuffer[RS232A_TXBUFFERSIZE];
extern uint8_t RS232A_RxBuffer[RS232A_RXBUFFERSIZE];

extern uint8_t RS232B_TxBuffer[RS232B_TXBUFFERSIZE];
extern uint8_t RS232B_RxBuffer[RS232B_RXBUFFERSIZE];

extern DMA_HandleTypeDef hRS232A_TX_DMA;

void RS232_Init(void);
void RS232A_MspInit(UART_HandleTypeDef *huart);
void RS232B_MspInit(UART_HandleTypeDef *huart);
HAL_StatusTypeDef RS232A_SendBytes(uint8_t *pData, int16_t length, uint32_t TimeOut);
HAL_StatusTypeDef RS232A_SendBytes_DMA(uint8_t *pData, int16_t length);
HAL_StatusTypeDef RS232B_SendBytes(uint8_t *pData, int16_t length, uint32_t TimeOut);
void RS232A_RxneCallback(void);
void RS232B_RxneCallback(void);

#endif /* end RS232_H */