/**
 * @file    led.h
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

#ifndef LED_H
#define LED_H

#include "stm32f4xx_hal.h"

#define LED0_PIN                        GPIO_PIN_10
#define LED0_PORT                       GPIOI
#define LED0_CLK_ENABLE()               __HAL_RCC_GPIOI_CLK_ENABLE()

#define LED1_PIN                        GPIO_PIN_11
#define LED1_PORT                       GPIOI
#define LED1_CLK_ENABLE()               __HAL_RCC_GPIOI_CLK_ENABLE()

#define LED_ON                          1
#define LED_OFF                         0

#define LED0                            0U
#define LED1                            1U


void LED_Init(void);
void LED_SetState(uint8_t LEDx, uint8_t NewState);

#endif /* end LED_H */
