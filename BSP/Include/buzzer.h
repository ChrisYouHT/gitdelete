/**
 * @file    buzzer.h
 * @author  ����
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
 * <h2><center>&copy; COPYRIGHT 2017 �����гۺ����ܿƼ����޹�˾</center></h2>
 */

#ifndef BUZZER_H
#define BUZZER_H

#include "stm32f4xx_hal.h"

void Buzzer_Init(void);
void Buzzer_Set(uint8_t onoff);
#endif /* end BUZZER_H */