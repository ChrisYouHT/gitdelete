/**
 * @file    ab.h
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

#ifndef ENCODER_H
#define ENCODER_H

#include "stm32f4xx_hal.h"

extern int32_t Encoder0_Value;
extern int32_t Encoder1_Value;
extern int32_t Encoder2_Value;

void Encoder_Init(void);
void Encoder2_MspInit(void);
void Encoder2_GetAbsCounter(void);
#endif /* end AB_H */