/**
 * @file    pulse.c
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

#include "pulse.h"

TIM_HandleTypeDef hTIM4;
TIM_HandleTypeDef hTIM5;
TIM_HandleTypeDef hTIM8;
TIM_HandleTypeDef hTIM10;


/**
 * @brief  Pulse 脉冲输出初始化
 * @param  None
 * @retval None
 */
void Pulse_Init(void)
{
    TIM_OC_InitTypeDef ConfigStruct;

    hTIM4.Instance = TIM4;
    hTIM4.Init.Period = 1000 - 1;    // 1Ms
    hTIM4.Init.Prescaler = 90 - 1;  //1MHz
    hTIM4.Init.ClockDivision = 0;
    hTIM4.Init.CounterMode = TIM_COUNTERMODE_UP;
    hTIM4.Init.RepetitionCounter = 0;

    if (HAL_TIM_PWM_Init(&hTIM4) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */

    } /* end if */

    ConfigStruct.OCMode = TIM_OCMODE_PWM1;
    ConfigStruct.OCFastMode = TIM_OCFAST_DISABLE;
    ConfigStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
    ConfigStruct.Pulse = 500;
    if (HAL_TIM_PWM_ConfigChannel(&hTIM4, &ConfigStruct, TIM_CHANNEL_2) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    }     /* end if */

    if (HAL_TIM_PWM_Start(&hTIM4, TIM_CHANNEL_2) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    }     /* end if */

    /* Pulse1 */
    hTIM5.Instance = TIM5;
    hTIM5.Init.Period = 1000 - 1;  // 1Ms
    hTIM5.Init.Prescaler = 90 - 1; //1MHz
    hTIM5.Init.ClockDivision = 0;
    hTIM5.Init.CounterMode = TIM_COUNTERMODE_UP;
    hTIM5.Init.RepetitionCounter = 0;

    if (HAL_TIM_PWM_Init(&hTIM5) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */

    } /* end if */

    ConfigStruct.OCMode = TIM_OCMODE_PWM1;
    ConfigStruct.OCFastMode = TIM_OCFAST_DISABLE;
    ConfigStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
    ConfigStruct.Pulse = 500;
    if (HAL_TIM_PWM_ConfigChannel(&hTIM5, &ConfigStruct, TIM_CHANNEL_1) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    }     /* end if */

    if (HAL_TIM_PWM_Start(&hTIM5, TIM_CHANNEL_1) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    }     /* end if */

    /* Pulse2 */
    hTIM8.Instance = TIM8;
    hTIM8.Init.Period = 1000 - 1;  // 1Ms
    hTIM8.Init.Prescaler = 180 - 1; //1MHz
    hTIM8.Init.ClockDivision = 0;
    hTIM8.Init.CounterMode = TIM_COUNTERMODE_UP;
    hTIM8.Init.RepetitionCounter = 0;

    if (HAL_TIM_PWM_Init(&hTIM8) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */

    } /* end if */

    ConfigStruct.OCMode = TIM_OCMODE_PWM1;
    ConfigStruct.OCFastMode = TIM_OCFAST_DISABLE;
    ConfigStruct.OCNPolarity = TIM_OCPOLARITY_HIGH;
    ConfigStruct.Pulse = 500;
    if (HAL_TIM_PWM_ConfigChannel(&hTIM8, &ConfigStruct, TIM_CHANNEL_2) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    }     /* end if */

    if (HAL_TIMEx_PWMN_Start(&hTIM8, TIM_CHANNEL_2) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    }     /* end if */

    /* Pulse3 */
    hTIM10.Instance = TIM10;
    hTIM10.Init.Period = 1000 - 1;  // 1Ms
    hTIM10.Init.Prescaler = 180 - 1; //1MHz
    hTIM10.Init.ClockDivision = 0;
    hTIM10.Init.CounterMode = TIM_COUNTERMODE_UP;
    hTIM10.Init.RepetitionCounter = 0;

    if (HAL_TIM_PWM_Init(&hTIM10) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */

    } /* end if */

    ConfigStruct.OCMode = TIM_OCMODE_PWM1;
    ConfigStruct.OCFastMode = TIM_OCFAST_DISABLE;
    ConfigStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
    ConfigStruct.Pulse = 500;
    if (HAL_TIM_PWM_ConfigChannel(&hTIM10, &ConfigStruct, TIM_CHANNEL_1) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    }     /* end if */

    if (HAL_TIM_PWM_Start(&hTIM10, TIM_CHANNEL_1) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    }     /* end if */
} /* end Pulse_Init() */

/**
 * @brief  TIM4 硬件初始化
 * @param  None
 * @retval None
 */
void TIM4_PWM_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_TIM4_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
} /* end TIM11_PWM_MspInit() */

/**
 * @brief  TIM5 硬件初始化
 * @param  None
 * @retval None
 */
void TIM5_PWM_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_TIM5_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
} /* end TIM5_PWM_MspInit() */

/**
 * @brief  TIM8 硬件初始化
 * @param  None
 * @retval None
 */
void TIM8_PWM_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_TIM8_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;

    GPIO_InitStruct.Pin = GPIO_PIN_0;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
} /* end TIM11_PWM_MspInit() */

/**
 * @brief  TIM10 硬件初始化
 * @param  None
 * @retval None
 */
void TIM10_PWM_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_TIM10_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF3_TIM10;

    GPIO_InitStruct.Pin = GPIO_PIN_8;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
} /* end TIM11_PWM_MspInit() */

/**
 * @brief  Pulse 频率，占空比更新
 * @param  freq 频率
 * @param  duty 占空比
 * @retval None
 */
void Pulse0_Updata(uint32_t freq, uint8_t duty)
{
		static uint32_t rfreq=0;
		static uint8_t  rduty=0;
		uint32_t count;
		
		if((freq == rfreq) && (duty == rduty))		
				return ;
		
		rfreq = freq;
		rduty = duty;

    

    count = 1 * 1000000 / freq;

    TIM4->CNT = 0x0000;
    TIM4->ARR = count - 1;
    TIM4->CCR2 = (uint32_t)(float)duty * count / 100.0;
} /* end Pulse_Updata() */

/**
 * @brief  Pulse 频率，占空比更新
 * @param  freq 频率
 * @param  duty 占空比
 * @retval None
 */
void Pulse1_Updata(uint32_t freq, uint8_t duty)
{
				static uint32_t rfreq=0;
		static uint8_t  rduty=0;
    uint32_t count;

		if((freq == rfreq) && (duty == rduty))		
				return ;
		
		rfreq = freq;
		rduty = duty;
				
    count = 1 * 1000000 / freq;
    
    TIM5->CNT = 0x0000;
    TIM5->ARR = count - 1;
    TIM5->CCR1 = (uint32_t)(float)duty * count / 100.0;
} /* end Pulse_Updata() */

/**
 * @brief  Pulse 频率，占空比更新
 * @param  freq 频率
 * @param  duty 占空比
 * @retval None
 */
void Pulse2_Updata(uint32_t freq, uint8_t duty)
{
			static uint32_t rfreq=0;
		static uint8_t  rduty=0;
    uint32_t count;

		if((freq == rfreq) && (duty == rduty))		
				return ;
		
		rfreq = freq;
		rduty = duty;
			
    count = 1 * 1000000 / freq;
  
    TIM8->CNT = 0x0000;
    TIM8->ARR = count - 1;
    TIM8->CCR2 = (uint32_t)(float)duty * count / 100.0;
} /* end Pulse_Updata() */

/**
 * @brief  Pulse 频率，占空比更新
 * @param  freq 频率
 * @param  duty 占空比
 * @retval None
 */
void Pulse3_Updata(uint32_t freq, uint8_t duty)
{
		static uint32_t rfreq=0;
		static uint8_t  rduty=0;
    uint32_t count;

		if((freq == rfreq) && (duty == rduty))		
				return ;
		
		rfreq = freq;
		rduty = duty;
			
    count = 1 * 1000000 / freq;
    
    TIM10->CNT = 0x0000;
    TIM10->ARR = count - 1;
    TIM10->CCR1 = (uint32_t)(float)duty * count / 100.0;
} /* end Pulse_Updata() */