/**
 * @file    led.c
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

#include "led.h"

/**
 * @brief  LED初始化
 * @param  None
 * @retval None
 */
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    LED0_CLK_ENABLE();
    LED1_CLK_ENABLE();

    GPIO_InitStruct.Pin = LED0_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(LED0_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LED1_PIN;
    HAL_GPIO_Init(LED1_PORT, &GPIO_InitStruct);

    LED_SetState(LED0, LED_OFF);
    LED_SetState(LED1, LED_OFF);
} /* end LED_Init() */

/**
 * @brief  控制LED亮灭
 * @param  LEDx LED编号
 * @param  NewState 新状态
 * @retval None
 */
void LED_SetState(uint8_t LEDx, uint8_t NewState)
{
    switch(LEDx)
    {
        case LED0 :
        {
            if (NewState == LED_ON)
            {
                HAL_GPIO_WritePin(LED0_PORT, LED0_PIN, GPIO_PIN_SET);
            } /* end if */
            else
            {
                HAL_GPIO_WritePin(LED0_PORT, LED0_PIN, GPIO_PIN_RESET);
            } /* end else */
            break;
        }

        case LED1:
        {
            if (NewState == LED_ON)
            {
                HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET);
            } /* end if */
            else
            {
                HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);
            } /* end else */
            break;
        }

        default :
            break;
    }
} /* end LED_SetState() */
