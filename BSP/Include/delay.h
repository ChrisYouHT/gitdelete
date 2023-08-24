/**
 * @file    delay.h
 * @author  ����
 * @version V0.0.0.1
 * @date    2018-05-11
 * @brief   ��ʱ����ͷ�ļ�
 * 
 * @verbatim
   
 * @endverbatim
 * 
 * @attention
 *
 *
 *
 * <h2><center>&copy; COPYRIGHT 2018 �����гۺ����ܿƼ��������ι�˾</center></h2>
 */


#ifndef DELAY_H
#define DELAY_H

#include "stm32f4xx_hal.h"

/**
 * @addtogroup Delay
 * @{
 */

void Delay_Ms(uint32_t nMs);
void Delay_Us(uint32_t nUs);
void Delay_Init(void);

/**
 * @}
 */
#endif /* end DELAY_H */