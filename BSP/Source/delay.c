/**
 * @file    delay.c
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-05-11
 * @brief   延时驱动
 * 
 * @verbatim
   此文件为延时驱动

   使用延时功能必须首先调用Delay_Init()函数，然后才能使用延时函数
   
 * @endverbatim
 * 
 * @attention
 *
 *
 *
 * <h2><center>&copy; COPYRIGHT 2018 无锡市驰海智能科技有限公司</center></h2>
 */


#include "delay.h"

/** 
 * @defgroup DELAY DELAY
 * @brief 延时
 * @{
 */

/* DWT寄存器 */
#define DWT_CYCCNT *(__IO unsigned int *)0xE0001004
#define DWT_CR *(__IO unsigned int *)0xE0001000
#define DEM_CR *(__IO unsigned int *)0xE000EDFC
#define DBGMCU_CR *(__IO unsigned int *)0xE0042004

#define DEM_CR_TRCENA (1 << 24)
#define DWT_CR_CYCCNTENA (1 << 0)

/**
 * @brief  dwt初始化
 * @param  None
 * @retval None
 */
void Delay_Init(void)
{
    DEM_CR |= (unsigned int)DEM_CR_TRCENA; /* Enable Cortex-M4's DWT CYCCNT reg.  */
    DWT_CYCCNT = (unsigned int)0u;
    DWT_CR |= (unsigned int)DWT_CR_CYCCNTENA;
} /* end Delay_Init() */

/**
 * @brief  us延时
 * @param  nUs 延时时间单位us
 * @retval None
 */
void Delay_Us(uint32_t nUs)
{
    uint32_t tCnt, tDelayCnt;
    uint32_t tStart;

    tStart = DWT_CYCCNT; /* 刚进入时的计数器值 */
    tCnt = 0;
    tDelayCnt = nUs * (SystemCoreClock / 1000000); /* 需要的节拍数 */

    while (tCnt < tDelayCnt)
    {
        tCnt = DWT_CYCCNT - tStart; /* 求减过程中，如果发生第一次32位计数器重新计数，依然可以正确计算 */
    }
} /* end Delay_Us() */

/**
 * @brief  ms延时
 * @param  nMs 延时时间，单位毫秒
 * @retval None
 */
void Delay_Ms(uint32_t nMs)
{
    Delay_Us(1000 * nMs);
} /* end Delay_Ms() */

/**
 * @}
 */

/**
 * @}
 */
