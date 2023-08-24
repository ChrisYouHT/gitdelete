/**
 * @file    ab.c
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

#include "encoder.h"

TIM_HandleTypeDef hEncoder0;
TIM_HandleTypeDef hEncoder1;
TIM_HandleTypeDef hEncoder2;

int32_t Encoder0_Value;
int32_t Encoder1_Value;
int32_t Encoder2_Value;

/**
 * @brief  编码器初始化
 * @param  None
 * @retval None
 */
void Encoder_Init(void)
{
    TIM_Encoder_InitTypeDef EncoderConfig;

    hEncoder2.Instance = TIM3;
    hEncoder2.Init.Period = 65535;
    hEncoder2.Init.Prescaler = 0;
    hEncoder2.Init.ClockDivision = 0;
    hEncoder2.Init.CounterMode = TIM_COUNTERMODE_UP;
    hEncoder2.Init.RepetitionCounter = 0;

    EncoderConfig.EncoderMode = TIM_ENCODERMODE_TI12;

    EncoderConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
    EncoderConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    EncoderConfig.IC1Prescaler = TIM_ICPSC_DIV1;
    EncoderConfig.IC1Filter = 0;

    EncoderConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
    EncoderConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    EncoderConfig.IC2Prescaler = TIM_ICPSC_DIV1;
    EncoderConfig.IC2Filter = 0;

    if (HAL_TIM_Encoder_Init(&hEncoder2, &EncoderConfig) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    } /* end if */

    HAL_TIM_Encoder_Start(&hEncoder2, TIM_CHANNEL_ALL);
} /* end Encoder_Init() */

/**
 * @brief  Encoder0 硬件初始化
 * @param  None
 * @retval None
 */
void Encoder2_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;

    /* Channel 1 configuration */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Channel 2 configuration */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
} /* end Encoder0_MspInit() */

/**
 * @brief  读取编码器数据
 * @param  None
 * @retval None
 */
void Encoder2_GetAbsCounter(void)
{
    uint16_t Counter = 0;
    static uint16_t LastCounter = 0;

    Counter = __HAL_TIM_GET_COUNTER(&hEncoder2);

    Encoder2_Value = (int16_t)(Counter - LastCounter) + Encoder2_Value;

    LastCounter = Counter;
}