/**
 * @file    sdram.h
 * @author  张腾
 * @version V0.0.0.0
 * @date    2018-07-17
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
#ifndef SDRAM_H
#define SDRAM_H

#include "stm32f4xx_hal.h"

#define SDRAM_ADDRESS ((uint32_t*)0xC0000000)

extern SDRAM_HandleTypeDef hSDRAM;

void SDRAM_FMC_MspInit(void);
HAL_StatusTypeDef SDRAM_Init(void);

#endif /* end SDRAM_H   */