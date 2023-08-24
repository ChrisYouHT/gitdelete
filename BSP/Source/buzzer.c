/**
 * @file    buzzer.c
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-07-19
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

#include "buzzer.h"

/**
 * @brief  蜂鸣器初始化
 * @param  None
 * @retval None
 */
void Buzzer_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_GPIOH_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
} /* end Buzzer_Init() */

/**
 * @brief  蜂鸣器设置
 * @param  None
 * @retval None
 */
void Buzzer_Set(uint8_t onoff)
{
    if (onoff == 0)
    {
        HAL_GPIO_WritePin(GPIOH, GPIO_PIN_15, GPIO_PIN_RESET);
    } /* end if */
    else
    {
        HAL_GPIO_WritePin(GPIOH, GPIO_PIN_15, GPIO_PIN_SET);
    } /* end else */
} /* end Buzzer_Set() */