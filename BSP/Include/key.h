/**
 * @file    key.h
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

#ifndef KEY_H
#define KEY_H

#include "stm32f4xx_hal.h"

void Key_Init(void);
int8_t Key_Scan(void);

#endif /* end KEY_H */
