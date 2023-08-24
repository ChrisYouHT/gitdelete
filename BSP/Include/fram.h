/**
 * @file    fram.h
 * @author  张腾
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
 * <h2><center>&copy; COPYRIGHT 2017 无锡市驰海智能科技有限公司</center></h2>
 */

#ifndef FRAM_H
#define FRAM_H

#include "stm32f4xx_hal.h"

void FRAM_Init(void);
int8_t FRAM_WriteData(uint8_t PageAddr, uint8_t WordAddr, uint8_t *pData, uint16_t length);
int8_t FRAM_ReadData(uint8_t PageAddr, uint8_t WordAddr, uint8_t *pData, uint16_t length);
#endif /* end FRAM_H */