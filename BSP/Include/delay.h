/**
 * @file    delay.h
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-05-11
 * @brief   延时驱动头文件
 * 
 * @verbatim
   
 * @endverbatim
 * 
 * @attention
 *
 *
 *
 * <h2><center>&copy; COPYRIGHT 2018 无锡市驰海智能科技有限责任公司</center></h2>
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