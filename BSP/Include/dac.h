/**
 * @file    dac.h
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-07-18
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

#ifndef DAC_H  
#define DAC_H  

#include "stm32f4xx_hal.h"


void DAC_Init(void);
void TIM11_UpdataDuty(uint32_t NewDuty);
void TIM12_UpdataDuty(uint32_t NewDuty);
void TIM13_UpdataDuty(uint32_t NewDuty);
void TIM14_UpdataDuty(uint32_t NewDuty);

void TIM11_PWM_MspInit(void);
void TIM12_PWM_MspInit(void);
void TIM13_PWM_MspInit(void);
void TIM14_PWM_MspInit(void);

#endif /* end DAC_H */