/**
 * @file    dac.c
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-07-18
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

#include "dac.h"

TIM_HandleTypeDef hTIM11;
TIM_HandleTypeDef hTIM12;
TIM_HandleTypeDef hTIM13;
TIM_HandleTypeDef hTIM14;

uint32_t TIM11_DUTY = 0;
uint32_t TIM12_DUTY = 0;
uint32_t TIM13_DUTY = 0;
uint32_t TIM14_DUTY = 0;

/**
 * @brief  DAC初始化
 * @param  None
 * @retval None
 */
void DAC_Init(void)
{
    TIM_OC_InitTypeDef ConfigStruct;

    hTIM11.Instance = TIM11;
    hTIM11.Init.Period = 1000 - 1; // 1Ms
    hTIM11.Init.Prescaler = 180 - 1; //1MHz
    hTIM11.Init.ClockDivision = 0;
    hTIM11.Init.CounterMode = TIM_COUNTERMODE_UP;
    hTIM11.Init.RepetitionCounter = 0;

    if (HAL_TIM_PWM_Init(&hTIM11) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
      
    } /* end if */

    ConfigStruct.OCMode = TIM_OCMODE_PWM1;
    ConfigStruct.OCFastMode = TIM_OCFAST_DISABLE;
    ConfigStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
    ConfigStruct.Pulse = TIM11_DUTY;
    if (HAL_TIM_PWM_ConfigChannel(&hTIM11, &ConfigStruct, TIM_CHANNEL_1) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    } /* end if */

    if (HAL_TIM_PWM_Start(&hTIM11, TIM_CHANNEL_1) != HAL_OK)
    {
        for (;;)
        {
            ;
      } /* end for */
    } /* end if */
    
    /* CH1 */
    hTIM12.Instance = TIM12;
    hTIM12.Init.Period = 1000 - 1; // 1Ms
    hTIM12.Init.Prescaler = 90 - 1; //1MHz
    hTIM12.Init.ClockDivision = 0;
    hTIM12.Init.CounterMode = TIM_COUNTERMODE_UP;
    hTIM12.Init.RepetitionCounter = 0;

    if (HAL_TIM_PWM_Init(&hTIM12) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
      
    } /* end if */

    ConfigStruct.OCMode = TIM_OCMODE_PWM1;
    ConfigStruct.OCFastMode = TIM_OCFAST_DISABLE;
    ConfigStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
    ConfigStruct.Pulse = TIM12_DUTY;
    if (HAL_TIM_PWM_ConfigChannel(&hTIM12, &ConfigStruct, TIM_CHANNEL_1) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    } /* end if */

    if (HAL_TIM_PWM_Start(&hTIM12, TIM_CHANNEL_1) != HAL_OK)
    {
        for (;;)
        {
            ;
      } /* end for */
    } /* end if */
    
    /* CH2 */
    hTIM13.Instance = TIM13;
    hTIM13.Init.Period = 1000 - 1; // 1Ms
    hTIM13.Init.Prescaler = 90 - 1; //1MHz
    hTIM13.Init.ClockDivision = 0;
    hTIM13.Init.CounterMode = TIM_COUNTERMODE_UP;
    hTIM13.Init.RepetitionCounter = 0;

    if (HAL_TIM_PWM_Init(&hTIM13) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
      
    } /* end if */

    ConfigStruct.OCMode = TIM_OCMODE_PWM1;
    ConfigStruct.OCFastMode = TIM_OCFAST_DISABLE;
    ConfigStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
    ConfigStruct.Pulse = TIM13_DUTY;
    if (HAL_TIM_PWM_ConfigChannel(&hTIM13, &ConfigStruct, TIM_CHANNEL_1) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    } /* end if */

    if (HAL_TIM_PWM_Start(&hTIM13, TIM_CHANNEL_1) != HAL_OK)
    {
        for (;;)
        {
            ;
      } /* end for */
    } /* end if */
    
    /* CH3 */
    hTIM14.Instance = TIM14;
    hTIM14.Init.Period = 1000 - 1; // 1Ms
    hTIM14.Init.Prescaler = 90 - 1; //1MHz
    hTIM14.Init.ClockDivision = 0;
    hTIM14.Init.CounterMode = TIM_COUNTERMODE_UP;
    hTIM14.Init.RepetitionCounter = 0;

    if (HAL_TIM_PWM_Init(&hTIM14) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
      
    } /* end if */

    ConfigStruct.OCMode = TIM_OCMODE_PWM1;
    ConfigStruct.OCFastMode = TIM_OCFAST_DISABLE;
    ConfigStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
    ConfigStruct.Pulse = TIM14_DUTY;
    if (HAL_TIM_PWM_ConfigChannel(&hTIM14, &ConfigStruct, TIM_CHANNEL_1) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    } /* end if */

    if (HAL_TIM_PWM_Start(&hTIM14, TIM_CHANNEL_1) != HAL_OK)
    {
        for (;;)
        {
            ;
      } /* end for */
    } /* end if */

} /* end DAC_Init() */

/**
 * @brief  TIM 跟新占空比
 * @param  uint32_t NewDuty 0 - 100
 * @retval None
 */
void TIM11_UpdataDuty(uint32_t NewDuty)
{
    TIM11->CCR1 = NewDuty * 10;
} /* end TIM_UpdataDuty() */

/**
 * @brief  TIM 跟新占空比
 * @param  uint32_t NewDuty 0 - 100
 * @retval None
 */
void TIM12_UpdataDuty(uint32_t NewDuty)
{
    TIM12->CCR1 = NewDuty * 10;
} /* end TIM_UpdataDuty() */

/**
 * @brief  TIM 跟新占空比
 * @param  uint32_t NewDuty 0 - 100
 * @retval None
 */
void TIM13_UpdataDuty(uint32_t NewDuty)
{
    TIM13->CCR1 = NewDuty * 10;
} /* end TIM_UpdataDuty() */

/**
 * @brief  TIM 跟新占空比
 * @param  uint32_t NewDuty 0 - 100
 * @retval None
 */
void TIM14_UpdataDuty(uint32_t NewDuty)
{
    TIM14->CCR1 = NewDuty * 10;
} /* end TIM_UpdataDuty() */

/**
 * @brief  TIM11 硬件初始化
 * @param  None
 * @retval None
 */
void TIM11_PWM_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_TIM11_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF3_TIM11;

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
} /* end TIM11_PWM_MspInit() */

/**
 * @brief  TIM12 硬件初始化
 * @param  None
 * @retval None
 */
void TIM12_PWM_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_TIM12_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_TIM12;

    GPIO_InitStruct.Pin = GPIO_PIN_14;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
} /* end TIM11_PWM_MspInit() */

/**
 * @brief  TIM13 硬件初始化
 * @param  None
 * @retval None
 */
void TIM13_PWM_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_TIM13_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_TIM13;

    GPIO_InitStruct.Pin = GPIO_PIN_8;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
} /* end TIM11_PWM_MspInit() */

/**
 * @brief  TIM14 硬件初始化
 * @param  None
 * @retval None
 */
void TIM14_PWM_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_TIM14_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_TIM14;

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
} /* end TIM11_PWM_MspInit() */