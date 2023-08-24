/**
 * @file    pulse.h
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-07-19
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

#ifndef PULSE_H
#define PULSE_H

#include "stm32f4xx_hal.h"

void Pulse_Init(void);
void TIM4_PWM_MspInit(void);
void TIM5_PWM_MspInit(void);
void TIM8_PWM_MspInit(void);
void TIM10_PWM_MspInit(void);
void Pulse0_Updata(uint32_t freq, uint8_t duty);
void Pulse1_Updata(uint32_t freq, uint8_t duty);
void Pulse2_Updata(uint32_t freq, uint8_t duty);
void Pulse3_Updata(uint32_t freq, uint8_t duty);
#endif /* end PULSE_H */
