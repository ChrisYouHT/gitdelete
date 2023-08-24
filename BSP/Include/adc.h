/**
 * @file    adc.h
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

#ifndef ADC_H
#define ADC_H

#include "stm32f4xx_hal.h"

void ADC_SPI_Init(void);
void ADC_SPI_MspInit(void);
int8_t ADC_SPI_ReadData(uint8_t channelx, uint16_t *pData);

#endif /* end ADC_H */