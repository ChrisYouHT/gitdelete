/**
 * @file    delay.c
 * @author  ����
 * @version V0.0.0.1
 * @date    2018-05-11
 * @brief   ��ʱ����
 * 
 * @verbatim
   ���ļ�Ϊ��ʱ����

   ʹ����ʱ���ܱ������ȵ���Delay_Init()������Ȼ�����ʹ����ʱ����
   
 * @endverbatim
 * 
 * @attention
 *
 *
 *
 * <h2><center>&copy; COPYRIGHT 2018 �����гۺ����ܿƼ����޹�˾</center></h2>
 */


#include "delay.h"

/** 
 * @defgroup DELAY DELAY
 * @brief ��ʱ
 * @{
 */

/* DWT�Ĵ��� */
#define DWT_CYCCNT *(__IO unsigned int *)0xE0001004
#define DWT_CR *(__IO unsigned int *)0xE0001000
#define DEM_CR *(__IO unsigned int *)0xE000EDFC
#define DBGMCU_CR *(__IO unsigned int *)0xE0042004

#define DEM_CR_TRCENA (1 << 24)
#define DWT_CR_CYCCNTENA (1 << 0)

/**
 * @brief  dwt��ʼ��
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
 * @brief  us��ʱ
 * @param  nUs ��ʱʱ�䵥λus
 * @retval None
 */
void Delay_Us(uint32_t nUs)
{
    uint32_t tCnt, tDelayCnt;
    uint32_t tStart;

    tStart = DWT_CYCCNT; /* �ս���ʱ�ļ�����ֵ */
    tCnt = 0;
    tDelayCnt = nUs * (SystemCoreClock / 1000000); /* ��Ҫ�Ľ����� */

    while (tCnt < tDelayCnt)
    {
        tCnt = DWT_CYCCNT - tStart; /* ��������У����������һ��32λ���������¼�������Ȼ������ȷ���� */
    }
} /* end Delay_Us() */

/**
 * @brief  ms��ʱ
 * @param  nMs ��ʱʱ�䣬��λ����
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
