/**
 * @file    cryptomem.c
 * @author  ����
 * @version V0.0.0.1
 * @date    2018-07-20
 * @brief   
 * 
 @verbatim
 
 �޸ļ�¼
 ��� | ���� | ���� | ˵��
    --|  --  | --  | --
 @endverbatim
 *
 * @attention
 *
 *
 *
 * <h2><center>&copy; COPYRIGHT 2018 �����гۺ����ܿƼ����޹�˾</center></h2>
 */

#include "cryptomem.h"
#include "delay.h"

/**
 * @brief  CMem SCL�ܽ�����Ϊ���   
 * @param  None
 * @retval None
 */
void CMem_LL_SCL_Out(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
} /* end CMem_LL_SCL_Out() */

/**
 * @brief  CMem SDA�ܽ�����Ϊ���   
 * @param  None
 * @retval None
 */
void CMem_LL_SDA_In(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
} /* end CMem_LL_SDA_In() */

/**
 * @brief  CMem SDA�ܽ�����Ϊ���   
 * @param  None
 * @retval None
 */
void CMem_LL_SDA_Out(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
} /* end CMem_LL_SDA_Out() */

/**
 * @brief  CMem SCL��ƽ����
 * @param  state ����״̬
 * @retval None
 */
void CMem_LL_SCL_Write(GPIO_PinState state)
{
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_4, state);
} /* end CMem_LL_SCL_Write() */

/**
 * @brief  CMem SDA��ƽ����
 * @param  state ����״̬
 * @retval None
 */
void CMem_LL_SDA_Write(GPIO_PinState state)
{
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_5, state);
} /* end CMem_LL_SCL_Write() */

/**
 * @brief  ��ȡSDA���ŵ�ƽ
 * @param  None
 * @retval None
 */
GPIO_PinState CMem_LL_SDA_Read(void)
{
    GPIO_PinState state;

    state = HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_5);

    return state;
} /* end CMem_LL_SDA_Read() */

/**
 * @brief  I2C��ʼ�ź�
 * @param  None
 * @retval None
 */
void CMem_LL_Start(void)
{
    CMem_LL_SDA_Out();

    CMem_LL_SCL_Write(GPIO_PIN_SET);
    CMem_LL_SDA_Write(GPIO_PIN_SET);

    Delay_Us(10);

    CMem_LL_SDA_Write(GPIO_PIN_RESET);

    Delay_Us(2);

    CMem_LL_SCL_Write(GPIO_PIN_RESET);
} /* end CMem_LL_Start() */

/**
 * @brief  I2Cֹͣ�ź�
 * @param  None
 * @retval None
 */
void CMem_LL_Stop(void)
{
    CMem_LL_SDA_Out();

    CMem_LL_SCL_Write(GPIO_PIN_RESET);
    CMem_LL_SDA_Write(GPIO_PIN_RESET);

    Delay_Us(10);

    CMem_LL_SCL_Write(GPIO_PIN_SET);

    Delay_Us(2);

    CMem_LL_SDA_Write(GPIO_PIN_SET);
} /* end CMem_LL_Stop() */

/**
 * @brief  I2C�ȴ�Ӧ���ź�
 * @param  None
 * @retval 0 ��ʾ����Ӧ��ɹ�
 * @retval -1 ��ʾ����Ӧ��ʧ��
 */
int8_t CMem_LL_WaitAck(void)
{
    uint8_t TimeOut = 0;

    CMem_LL_SDA_In();

    CMem_LL_SCL_Write(GPIO_PIN_SET);
    CMem_LL_SDA_Write(GPIO_PIN_SET); // ���ߣ���ȡ�͵�ƽ

    Delay_Us(2);

    /* �ȴ��͵�ƽ */
    while (CMem_LL_SDA_Read())
    {
        TimeOut++;

        if (TimeOut > 250)
        {
            /* ʧ�ܣ�ֹͣ */
            CMem_LL_Stop();

            return -1;
        } /* end if */

        Delay_Us(2);
    } /* end while */

    Delay_Us(2);

    CMem_LL_SCL_Write(GPIO_PIN_RESET);

    return 0;
} /* end CMem_LL_WaitAck() */

/**
 * @brief  ����Ӧ���ź�
 * @param  None
 * @retval None
 */
void CMem_LL_Ack(void)
{
    CMem_LL_SDA_Out();

    CMem_LL_SCL_Write(GPIO_PIN_RESET);
    CMem_LL_SDA_Write(GPIO_PIN_RESET);

    Delay_Us(2);

    CMem_LL_SCL_Write(GPIO_PIN_SET);

    Delay_Us(2);

    CMem_LL_SCL_Write(GPIO_PIN_RESET);
} /* end CMem_LL_Ack() */

/**
 * @brief  ������Ӧ���ź�
 * @param  None
 * @retval None
 */
void CMem_LL_NAck(void)
{
    CMem_LL_SDA_Out();

    CMem_LL_SCL_Write(GPIO_PIN_RESET);
    CMem_LL_SDA_Write(GPIO_PIN_SET);

    Delay_Us(2);

    CMem_LL_SCL_Write(GPIO_PIN_SET);

    Delay_Us(2);

    CMem_LL_SCL_Write(GPIO_PIN_RESET);
} /* end CMem_LL_NAck() */

/**
 * @brief  I2C����һ���ֽڵ�����
 * @param  data �����ֽ�
 * @retval None
 */
void CMem_LL_WriteData(uint8_t data)
{
    uint8_t cnt = 0;
    uint8_t TmpBit = 0;

    CMem_LL_SDA_Out();

    CMem_LL_SCL_Write(GPIO_PIN_RESET);

    for (cnt = 0; cnt < 8; cnt++)
    {
        TmpBit = (data & 0x80) >> 7;
        CMem_LL_SDA_Write((GPIO_PinState)TmpBit);
        data <<= 1;

        Delay_Us(2);

        CMem_LL_SCL_Write(GPIO_PIN_SET);

        Delay_Us(2);

        CMem_LL_SCL_Write(GPIO_PIN_RESET);

        Delay_Us(2);
    } /* end for */

} /* end CMem_LL_WriteData() */

/**
 * @brief  I2C��ȡһ���ֽ�����
 * @param  pData ��ȡ���ֽ�
 * @param  AckEnable 1 ����Ӧ����߷�Ӧ�����ͺţ�0 �������κ�Ӧ���ź�
 * @param  ack 1 ����Ӧ���źţ� 0 ���ͷ�Ӧ���ź�
 * @retval None
 */
void CMem_LL_ReadData(uint8_t *pData, uint8_t AckEnable, uint8_t ack)
{
    uint8_t cnt = 0;
    uint8_t TmpData = 0;

    CMem_LL_SDA_In();

    Delay_Us(10);

    for (cnt = 0; cnt < 8; cnt++)
    {
        CMem_LL_SCL_Write(GPIO_PIN_RESET);

        Delay_Us(2);

        CMem_LL_SCL_Write(GPIO_PIN_SET);

        TmpData <<= 1;

        if (CMem_LL_SDA_Read())
        {
            TmpData++;
        } /* end if */

        Delay_Us(2);
    } /* end for */

    CMem_LL_SCL_Write(GPIO_PIN_RESET);

    if (AckEnable)
    {
        if (ack)
        {
            CMem_LL_Ack();
        } /* end if */
        else
        {
            CMem_LL_NAck();
        } /* end else */
    } /* end if */

    *pData = TmpData;
} /* end CMem_LL_ReadData() */

/**
 * @brief  CMem��ʼ��
 * @param  None
 * @retval None
 */
void CMem_Init(void)
{
    uint8_t i = 0;

    __HAL_RCC_GPIOH_CLK_ENABLE();

    CMem_LL_SCL_Out();
    CMem_LL_SDA_Out();

    CMem_LL_SCL_Write(GPIO_PIN_SET);
    CMem_LL_SDA_Write(GPIO_PIN_SET);

    for (i = 0; i < 5; i++)
    {
        CMem_LL_SCL_Write(GPIO_PIN_RESET);
        Delay_Us(10);
        CMem_LL_SCL_Write(GPIO_PIN_SET);
        Delay_Us(10);
    } /* end for */
} /* end FRAM_Init() */

/**
 * @brief  ��ȡConfig Zone
 * @param  addr ��ַ
 * @param  N ����
 * @param  pData ����ָ��
 * @retval 0  ��ȡ�ɹ�
 * @retval -1 ��ȡʧ��
 */
int8_t CMem_ReadConfigZone(uint8_t addr, uint8_t N, uint8_t *pData)
{
    uint8_t cnt = 0;
  
    CMem_LL_Start();

    CMem_LL_WriteData(0xB6);

    while (CMem_LL_WaitAck() != 0)
    {
        CMem_LL_Stop();

        return -1;
    } /* end while */

    CMem_LL_WriteData(0x00);
    while (CMem_LL_WaitAck() != 0)
    {
        CMem_LL_Stop();

        return -1;
    } /* end while */

    CMem_LL_WriteData(addr);
    while (CMem_LL_WaitAck() != 0)
    {
        CMem_LL_Stop();

        return -1;
    } /* end while */

    CMem_LL_WriteData(N);
    while (CMem_LL_WaitAck() != 0)
    {
        CMem_LL_Stop();

        return -1;
    } /* end while */

    for (cnt = 0; cnt < N; cnt++)
    {
        CMem_LL_ReadData(pData, 1, (cnt == (N - 1)) ? 0 : 1);
        pData++;
    } /* end for */

    CMem_LL_Stop();

    return 0;
} /* end CMem_ReadConfigZone() */