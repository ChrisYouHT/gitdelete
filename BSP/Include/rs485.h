/**
 * @file    rs485.h
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-07-11
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

#ifndef RS485_H
#define RS485_H

#include "stm32f4xx_hal.h"

/* RS485A */
#define RS485A                          UART4
#define RS485A_CLK_ENABLE()             __HAL_RCC_UART4_CLK_ENABLE()
#define RS485A_IRQn                     UART4_IRQn
#define RS485A_IRQHandler               UART4_IRQHandler
#define RS485A_TXBUFFERSIZE             5U
#define RS485A_RXBUFFERSIZE             RS485A_TXBUFFERSIZE
#define RS485A_AF                       GPIO_AF8_UART4

#define RS485A_TX_PIN                   GPIO_PIN_0
#define RS485A_TX_PORT                  GPIOA
#define RS485A_TX_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()

#define RS485A_RX_PIN                   GPIO_PIN_1
#define RS485A_RX_PORT                  GPIOA
#define RS485A_RX_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()

#define RS485A_RE_PIN                   GPIO_PIN_15
#define RS485A_RE_PORT                  GPIOB
#define RS485A_RE_CLK_ENABLE()          __HAL_RCC_GPIOB_CLK_ENABLE()


/* RS485B */
#define RS485B                          USART6
#define RS485B_CLK_ENABLE()             __HAL_RCC_USART6_CLK_ENABLE()
#define RS485B_IRQn                     USART6_IRQn
#define RS485B_IRQHandler               USART6_IRQHandler
#define RS485B_TXBUFFERSIZE             5U
#define RS485B_RXBUFFERSIZE             RS485B_TXBUFFERSIZE
#define RS485B_AF                       GPIO_AF8_USART6

#define RS485B_TX_PIN                   GPIO_PIN_6
#define RS485B_TX_PORT                  GPIOC
#define RS485B_TX_CLK_ENABLE()          __HAL_RCC_GPIOC_CLK_ENABLE()

#define RS485B_RX_PIN                   GPIO_PIN_7
#define RS485B_RX_PORT                  GPIOC
#define RS485B_RX_CLK_ENABLE()          __HAL_RCC_GPIOC_CLK_ENABLE()

#define RS485B_RE_PIN                   GPIO_PIN_8
#define RS485B_RE_PORT                  GPIOC
#define RS485B_RE_CLK_ENABLE()          __HAL_RCC_GPIOC_CLK_ENABLE()

enum RS485_ModeTypeDef
{
    RS485_MODE_TX,
    RS485_MODE_RX
};

extern UART_HandleTypeDef hRS485A;
extern UART_HandleTypeDef hRS485B;

extern uint8_t RS485A_Tx_Buffer[RS485A_TXBUFFERSIZE];
extern uint8_t RS485A_Rx_Buffer[RS485A_RXBUFFERSIZE];

extern uint8_t RS485B_Tx_Buffer[RS485B_TXBUFFERSIZE];
extern uint8_t RS485B_Rx_Buffer[RS485B_RXBUFFERSIZE];

void RS485_Init(void);
void RS485A_MspInit(void);
void RS485B_MspInit(void);
void RS485A_SetMode(enum RS485_ModeTypeDef mode);
void RS485B_SetMode(enum RS485_ModeTypeDef mode);
HAL_StatusTypeDef RS485A_SendBytes(uint8_t *pData, uint16_t length, uint16_t TimeOut);
HAL_StatusTypeDef RS485B_SendBytes(uint8_t *pData, uint16_t length, uint16_t TimeOut);
void RS485A_RxneCallback(void);
void RS485B_RxneCallback(void);

#endif /* end RS485_H */