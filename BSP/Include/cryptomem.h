/**
 * @file    cryptomem.h
 * @author  ����
 * @version V0.0.0.1
 * @date    2018-07-20
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

#ifndef CRYPTOMEM_H
#define CRYPTOMEM_H

#include "stm32f4xx_hal.h"

void CMem_Init(void);
int8_t CMem_ReadConfigZone(uint8_t addr, uint8_t N, uint8_t *pData);

#endif /* end CRYPTOMEM_H */
