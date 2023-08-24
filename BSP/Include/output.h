/**
 * @file    output.h
 * @author  张腾
 * @version V0.0.0.0
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

#ifndef OUTPUT_H
#define OUTPUT_H

#include "stm32f4xx_hal.h"

/* Slow */
#define OUTPUT_SLOW_DS                  GPIO_PIN_14
#define OUTPUT_SLOW_DS_PORT             GPIOG
#define OUTPUT_SLOW_DS_CLK_ENABLE()     __HAL_RCC_GPIOG_CLK_ENABLE()

#define OUTPUT_SLOW_STCP                GPIO_PIN_11
#define OUTPUT_SLOW_STCP_PORT           GPIOG
#define OUTPUT_SLOW_STCP_CLK_ENABLE()   __HAL_RCC_GPIOG_CLK_ENABLE()

#define OUTPUT_SLOW_SHCP                GPIO_PIN_13
#define OUTPUT_SLOW_SHCP_PORT           GPIOG
#define OUTPUT_SLOW_SHCP_CLK_ENABLE()   __HAL_RCC_GPIOG_CLK_ENABLE()

/* Fast */
#define OUTPUT_FAST_PIN_0               GPIO_PIN_7
#define OUTPUT_FAST_PORT_0              GPIOI
#define OUTPUT_FAST_PIN_0_CLK_ENABLE()  __HAL_RCC_GPIOI_CLK_ENABLE()

#define OUTPUT_FAST_PIN_1               GPIO_PIN_6
#define OUTPUT_FAST_PORT_1              GPIOI
#define OUTPUT_FAST_PIN_1_CLK_ENABLE()  __HAL_RCC_GPIOI_CLK_ENABLE()

#define OUTPUT_FAST_PIN_2               GPIO_PIN_5
#define OUTPUT_FAST_PORT_2              GPIOI
#define OUTPUT_FAST_PIN_2_CLK_ENABLE()  __HAL_RCC_GPIOI_CLK_ENABLE()

#define OUTPUT_FAST_PIN_3               GPIO_PIN_4
#define OUTPUT_FAST_PORT_3              GPIOI
#define OUTPUT_FAST_PIN_3_CLK_ENABLE()  __HAL_RCC_GPIOI_CLK_ENABLE()

#define OUTPUT_SET                      GPIO_PIN_SET
#define OUTPUT_RESET                    GPIO_PIN_RESET

void Output_Init(void);
void Output_Fast_Set(uint8_t byte);
int8_t Output_Fast_SetBit(uint8_t bit, GPIO_PinState NewState);
void Output_Slow_Set(uint64_t Data);

#endif /* end OUTPUT_H */