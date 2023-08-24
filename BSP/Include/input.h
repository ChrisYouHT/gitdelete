/**
 * @file    input.h
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-07-10
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


#ifndef INPUT_H
#define INPUT_H

#include "stm32f4xx_hal.h"

/* 低速 */
#define INPUT_GROUP_A_PIN               GPIO_PIN_10
#define INPUT_GROUP_A_PORT              GPIOF
#define INPUT_GROUP_A_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()

#define INPUT_GROUP_B_PIN               GPIO_PIN_13
#define INPUT_GROUP_B_PORT              GPIOC
#define INPUT_GROUP_B_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()

#define INPUT_GROUP_C_PIN               GPIO_PIN_8
#define INPUT_GROUP_C_PORT              GPIOI
#define INPUT_GROUP_C_CLK_ENABLE()      __HAL_RCC_GPIOI_CLK_ENABLE()

#define INPUT_GROUP_D_PIN               GPIO_PIN_3
#define INPUT_GROUP_D_PORT              GPIOE
#define INPUT_GROUP_D_CLK_ENABLE()      __HAL_RCC_GPIOE_CLK_ENABLE()

#define INPUT_GROUP_E_PIN               GPIO_PIN_7
#define INPUT_GROUP_E_PORT              GPIOF
#define INPUT_GROUP_E_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()

#define INPUT_GROUP_F_PIN               GPIO_PIN_6
#define INPUT_GROUP_F_PORT              GPIOF
#define INPUT_GROUP_F_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()

#define INPUT_GROUP_G_PIN               GPIO_PIN_1
#define INPUT_GROUP_G_PORT              GPIOC
#define INPUT_GROUP_G_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()

#define INPUT_GROUP_H_PIN               GPIO_PIN_4
#define INPUT_GROUP_H_PORT              GPIOC
#define INPUT_GROUP_H_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()

#define INPUT_GROUP_I_PIN               GPIO_PIN_5
#define INPUT_GROUP_I_PORT              GPIOC
#define INPUT_GROUP_I_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()

#define INPUT_D0_PIN                    GPIO_PIN_0
#define INPUT_D0_PORT                   GPIOF
#define INPUT_D0_CLK_ENABLE()           __HAL_RCC_GPIOF_CLK_ENABLE()

#define INPUT_D1_PIN                    GPIO_PIN_1
#define INPUT_D1_PORT                   GPIOF
#define INPUT_D1_CLK_ENABLE()           __HAL_RCC_GPIOF_CLK_ENABLE()

#define INPUT_D2_PIN                    GPIO_PIN_2
#define INPUT_D2_PORT                   GPIOF
#define INPUT_D2_CLK_ENABLE()           __HAL_RCC_GPIOF_CLK_ENABLE()

#define INPUT_D3_PIN                    GPIO_PIN_3
#define INPUT_D3_PORT                   GPIOF
#define INPUT_D3_CLK_ENABLE()           __HAL_RCC_GPIOF_CLK_ENABLE()

#define INPUT_D4_PIN                    GPIO_PIN_4
#define INPUT_D4_PORT                   GPIOF
#define INPUT_D4_CLK_ENABLE()           __HAL_RCC_GPIOF_CLK_ENABLE()

#define INPUT_D5_PIN                    GPIO_PIN_5
#define INPUT_D5_PORT                   GPIOF
#define INPUT_D5_CLK_ENABLE()           __HAL_RCC_GPIOF_CLK_ENABLE()

#define INPUT_D6_PIN                    GPIO_PIN_12
#define INPUT_D6_PORT                   GPIOF
#define INPUT_D6_CLK_ENABLE()           __HAL_RCC_GPIOF_CLK_ENABLE()

#define INPUT_D7_PIN                    GPIO_PIN_13
#define INPUT_D7_PORT                   GPIOF
#define INPUT_D7_CLK_ENABLE()           __HAL_RCC_GPIOF_CLK_ENABLE()

/* 高速 */
#define INPUT_FAST_0_PIN                GPIO_PIN_9
#define INPUT_FAST_0_PORT               GPIOH
#define INPUT_FAST_0_CLK_ENABLE()       __HAL_RCC_GPIOH_CLK_ENABLE()

#define INPUT_FAST_1_PIN                GPIO_PIN_11
#define INPUT_FAST_1_PORT               GPIOH
#define INPUT_FAST_1_CLK_ENABLE()       __HAL_RCC_GPIOH_CLK_ENABLE()

#define INPUT_FAST_2_PIN                GPIO_PIN_6
#define INPUT_FAST_2_PORT               GPIOH
#define INPUT_FAST_2_CLK_ENABLE()       __HAL_RCC_GPIOH_CLK_ENABLE()

#define INPUT_FAST_3_PIN                GPIO_PIN_12
#define INPUT_FAST_3_PORT               GPIOH
#define INPUT_FAST_3_CLK_ENABLE()       __HAL_RCC_GPIOH_CLK_ENABLE()

enum Input_GroupTypeDef
{
    INPUT_GROUP_A,
    INPUT_GROUP_B,
    INPUT_GROUP_C,
    INPUT_GROUP_D,
    INPUT_GROUP_E,
    INPUT_GROUP_F,
    INPUT_GROUP_G,
    INPUT_GROUP_H,
    INPUT_GROUP_I
};

enum Input_BitTypeDef
{
    INPUT_BIT_0,
    INPUT_BIT_1,
    INPUT_BIT_2,
    INPUT_BIT_3,
    INPUT_BIT_4,
    INPUT_BIT_5,
    INPUT_BIT_6,
    INPUT_BIT_7
};

void Input_Init(void);
uint8_t Input_Fast_Read(void);
int8_t Input_Slow_Read(uint8_t x);

uint32_t Input_0_31_Read(void);
uint32_t Input_32_63_Read(void);
uint8_t Input_64_67_Read(void);
uint8_t Input_68_71_Read(void);
#endif /* end INPUT_H */