/**
 * @file    bsp.h
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-05-23
 * @brief   板级驱动接口文件
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

#ifndef BSP_H
#define BSP_H

#include "stm32f4xx_hal.h"
#define u8 unsigned char 	
#define s8 char 			    	
#define u16 unsigned short 
#define s16 short          
#define u32 unsigned long  
#define s32 long					 




void BSP_Init(void);

#endif /* end BSP */