/**
 * @file    key.c
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

#include "key.h"
#include "delay.h"

/**
 * @brief  Key 初始化
 * @param  None
 * @retval None
 */
void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;

    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_14;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_2;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
} /* end Key_Init() */

/**
 * @brief  按键扫描
 * @param  None
 * @retval None
 */
int8_t Key_Scan(void)
{
    int8_t key = -1;

    if (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_6) == RESET)
    {
        Delay_Ms(10);
        if (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_6) == RESET)
        {
            while (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_6) == RESET)
            {
                ;
            } /* end while */
            key = 0;
        }
        
    } /* end if */
    else if (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_7) == RESET)
    {
        Delay_Ms(10);
        if (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_7) == RESET)
        {
            while (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_7) == RESET)
            {
                ;
            } /* end while */
            key = 1;
        }
    } /* end if */
    else if (HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_13) == RESET)
    {
        Delay_Ms(10);
        if (HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_13) == RESET)
        {
            while (HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_13) == RESET)
            {
                ;
            } /* end while */
            key = 2;
        }
    } /* end if */
    else if (HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_14) == RESET)
    {
        Delay_Ms(10);
        if (HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_14) == RESET)
        {
            while (HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_14) == RESET)
            {
                ;
            } /* end while */
            key = 3;
        }
    } /* end if */
    else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == RESET)
    {
        Delay_Ms(10);
        if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == RESET)
        {
            while (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == RESET)
            {
                ;
            } /* end while */
            key = 4;
        }
    } /* end if */
    else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == RESET)
    {
        Delay_Ms(10);
        if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == RESET)
        {
            while (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == RESET)
            {
                ;
            } /* end while */
            key = 5;
        }
    } /* end if */

    return key;
} /* end Key_Scan() */