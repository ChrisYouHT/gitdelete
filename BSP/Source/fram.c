/**
 * @file    fram.c
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

#include "fram.h"
#include "delay.h"

/**
 * @brief  FRAM SCL�ܽ�����Ϊ���   
 * @param  None
 * @retval None
 */
void FRAM_LL_SCL_Out(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
} /* end FRAM_LL_SCL_Out() */

/**
 * @brief  FRAM SDA�ܽ�����Ϊ���   
 * @param  None
 * @retval None
 */
void FRAM_LL_SDA_In(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
} /* end FRAM_LL_SDA_In() */

/**
 * @brief  FRAM SDA�ܽ�����Ϊ���   
 * @param  None
 * @retval None
 */
void FRAM_LL_SDA_Out(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
} /* end FRAM_LL_SDA_Out() */

/**
 * @brief  FRAM SCL��ƽ����
 * @param  state ����״̬
 * @retval None
 */
void FRAM_LL_SCL_Write(GPIO_PinState state)
{
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_7, state);
} /* end FRAM_LL_SCL_Write() */

/**
 * @brief  FRAM SDA��ƽ����
 * @param  state ����״̬
 * @retval None
 */
void FRAM_LL_SDA_Write(GPIO_PinState state)
{
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_8, state);
} /* end FRAM_LL_SCL_Write() */

/**
 * @brief  ��ȡSDA���ŵ�ƽ
 * @param  None
 * @retval None
 */
GPIO_PinState FRAM_LL_SDA_Read(void)
{
    GPIO_PinState state;

    state = HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_8);

    return state;
} /* end FRAM_LL_SDA_Read() */

/**
 * @brief  I2C��ʼ�ź�
 * @param  None
 * @retval None
 */
void FRAM_LL_Start(void)
{
    FRAM_LL_SDA_Out();

    FRAM_LL_SCL_Write(GPIO_PIN_SET);
    FRAM_LL_SDA_Write(GPIO_PIN_SET);

    Delay_Us(10);

    FRAM_LL_SDA_Write(GPIO_PIN_RESET);

    Delay_Us(2);

    FRAM_LL_SCL_Write(GPIO_PIN_RESET);
} /* end FRAM_LL_Start() */

/**
 * @brief  I2Cֹͣ�ź�
 * @param  None
 * @retval None
 */
void FRAM_LL_Stop(void)
{
    FRAM_LL_SDA_Out();

    FRAM_LL_SCL_Write(GPIO_PIN_RESET);
    FRAM_LL_SDA_Write(GPIO_PIN_RESET);

    Delay_Us(10);

    FRAM_LL_SCL_Write(GPIO_PIN_SET);

    Delay_Us(2);

    FRAM_LL_SDA_Write(GPIO_PIN_SET);
} /* end FRAM_LL_Stop() */

/**
 * @brief  I2C�ȴ�Ӧ���ź�
 * @param  None
 * @retval 0 ��ʾ����Ӧ��ɹ�
 * @retval -1 ��ʾ����Ӧ��ʧ��
 */
int8_t FRAM_LL_WaitAck(void)
{
    uint8_t TimeOut = 0;

    FRAM_LL_SDA_In();

    FRAM_LL_SCL_Write(GPIO_PIN_SET);
    FRAM_LL_SDA_Write(GPIO_PIN_SET); // ���ߣ���ȡ�͵�ƽ

    Delay_Us(2);

    /* �ȴ��͵�ƽ */
    while ( FRAM_LL_SDA_Read() )
    {
        TimeOut++;

        if (TimeOut > 250)
        {
            /* ʧ�ܣ�ֹͣ */
            FRAM_LL_Stop();

            return -1;
        } /* end if */

        Delay_Us(2);
    } /* end while */

    Delay_Us(2);

    FRAM_LL_SCL_Write(GPIO_PIN_RESET);

    return 0;
} /* end FRAM_LL_WaitAck() */

/**
 * @brief  ����Ӧ���ź�
 * @param  None
 * @retval None
 */
void FRAM_LL_Ack(void)
{
    FRAM_LL_SDA_Out();

    FRAM_LL_SCL_Write(GPIO_PIN_RESET);
    FRAM_LL_SDA_Write(GPIO_PIN_RESET);

    Delay_Us(2);

    FRAM_LL_SCL_Write(GPIO_PIN_SET);

    Delay_Us(2);

    FRAM_LL_SCL_Write(GPIO_PIN_RESET);
} /* end FRAM_LL_Ack() */

/**
 * @brief  ������Ӧ���ź�
 * @param  None
 * @retval None
 */
void FRAM_LL_NAck(void)
{
    FRAM_LL_SDA_Out();

    FRAM_LL_SCL_Write(GPIO_PIN_RESET);
    FRAM_LL_SDA_Write(GPIO_PIN_SET);

    Delay_Us(2);

    FRAM_LL_SCL_Write(GPIO_PIN_SET);

    Delay_Us(2);

    FRAM_LL_SCL_Write(GPIO_PIN_RESET);
} /* end FRAM_LL_NAck() */

/**
 * @brief  I2C����һ���ֽڵ�����
 * @param  data �����ֽ�
 * @retval None
 */
void FRAM_LL_WriteData(uint8_t data)
{
    uint8_t cnt = 0;
    uint8_t TmpBit = 0;

    FRAM_LL_SDA_Out();

    FRAM_LL_SCL_Write(GPIO_PIN_RESET);

    for (cnt = 0; cnt < 8; cnt ++)
    {
        TmpBit = (data & 0x80) >> 7;
        FRAM_LL_SDA_Write((GPIO_PinState)TmpBit);
        data <<= 1;

        Delay_Us(2);

        FRAM_LL_SCL_Write(GPIO_PIN_SET);

        Delay_Us(2);

        FRAM_LL_SCL_Write(GPIO_PIN_RESET);

        Delay_Us(2);
  } /* end for */

} /* end FRAM_LL_WriteData() */

/**
 * @brief  I2C��ȡһ���ֽ�����
 * @param  pData ��ȡ���ֽ�
 * @param  ack 1 ����Ӧ���źţ� 0 ���ͷ�Ӧ���ź�
 * @retval None
 */
void FRAM_LL_ReadData(uint8_t *pData, uint8_t ack)
{
    uint8_t cnt = 0;
    uint8_t TmpData = 0;

    FRAM_LL_SDA_In();

    Delay_Us(10);

    for (cnt = 0; cnt < 8; cnt++)
    {
        FRAM_LL_SCL_Write(GPIO_PIN_RESET);

        Delay_Us(2);

        FRAM_LL_SCL_Write(GPIO_PIN_SET);

        TmpData <<= 1;

        if (FRAM_LL_SDA_Read())
        {
            TmpData++;
        } /* end if */

        Delay_Us(2);
    } /* end for */

    FRAM_LL_SCL_Write(GPIO_PIN_RESET);

    if (ack)
    {
        FRAM_LL_Ack();
    } /* end if */
    else
    {
        FRAM_LL_NAck();
    } /* end else */

    *pData = TmpData;
} /* end FRAM_LL_ReadData() */

/**
 * @brief  FRAM��ʼ��
 * @param  None
 * @retval None
 */
void FRAM_Init(void)
{
    __HAL_RCC_GPIOH_CLK_ENABLE();

    FRAM_LL_SCL_Out();
    FRAM_LL_SDA_Out();

    FRAM_LL_SCL_Write(GPIO_PIN_SET);
    FRAM_LL_SDA_Write(GPIO_PIN_SET);
} /* end FRAM_Init() */

/**
 * @brief  FRAM д����
 * @param  PageAddr ҳ��ַ
 * @param  WordAddr �ֵ�ַ
 * @param  pData ����ָ��
 * @param  length ���ݳ��� 
 * @retval 0  ��ʾ�ɹ�
 * @retval -1 ��ʾʧ��
 */
int8_t FRAM_WriteData(uint8_t PageAddr, uint8_t WordAddr, uint8_t *pData, uint16_t length)
{
    uint8_t TmpReg = 0;
    uint16_t cnt = 0;

    FRAM_LL_Start();

    TmpReg |= 0xA0 | (PageAddr << 1) | 0x00;
    FRAM_LL_WriteData(TmpReg);

    if(FRAM_LL_WaitAck() != 0)
    {
        FRAM_LL_Stop();

        return -1;
    }

    FRAM_LL_WriteData(WordAddr);

    if (FRAM_LL_WaitAck() != 0)
    {
        FRAM_LL_Stop();

        return -1;
    }

    for (cnt = 0; cnt < length; cnt++)
    {
        FRAM_LL_WriteData(*pData);

        if (FRAM_LL_WaitAck() != 0)
        {
            FRAM_LL_Stop();

            return -1;
        }

        pData++;
    } /* end for */

    FRAM_LL_Stop();

    return 0;
} /* end FRAM_WriteData() */

/**
 * @brief  FRAM ������
 * @param  PageAddr ҳ��ַ
 * @param  WordAddr �ֵ�ַ
 * @param  pData ����ָ��
 * @param  length ���ݳ��� 
 * @retval 0  ��ʾ�ɹ�
 * @retval -1 ��ʾʧ��
 */
int8_t FRAM_ReadData(uint8_t PageAddr, uint8_t WordAddr, uint8_t *pData, uint16_t length)
{
    uint8_t TmpReg = 0;
    uint16_t cnt = 0;

    FRAM_LL_Start();

    TmpReg = 0xA0 | (PageAddr << 1) | 0x00;
    FRAM_LL_WriteData(TmpReg);


    if (FRAM_LL_WaitAck() != 0)
    {
        FRAM_LL_Stop();

        return -1;
    }

    FRAM_LL_WriteData(WordAddr);

    if (FRAM_LL_WaitAck() != 0)
    {
        FRAM_LL_Stop();

        return -1;
    }

    FRAM_LL_Start();

    TmpReg = 0xA0 | (PageAddr << 1) | 0x01;
    FRAM_LL_WriteData(TmpReg);

    if (FRAM_LL_WaitAck() != 0)
    {
        FRAM_LL_Stop();

        return -1;
    }

    for (cnt = 0; cnt < length; cnt++)
    {
        FRAM_LL_ReadData(pData, (cnt == (length - 1)) ? 0 : 1);
        pData++;
    } /* end for */

    FRAM_LL_Stop();
    
    return 0;
} /* end FRAM_ReadData() */
