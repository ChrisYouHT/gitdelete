/**
 * @file    fram.c
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-07-20
 * @brief   
 * 
 @verbatim
 
 修改记录
 序号 | 日期 | 作者 | 说明
    --|  --  | --  | --
 @endverbatim
 *
 * @attention
 *
 *
 *
 * <h2><center>&copy; COPYRIGHT 2018 无锡市驰海智能科技有限公司</center></h2>
 */

#include "fram.h"
#include "delay.h"

/**
 * @brief  FRAM SCL管脚设置为输出   
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
 * @brief  FRAM SDA管脚设置为输出   
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
 * @brief  FRAM SDA管脚设置为输出   
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
 * @brief  FRAM SCL电平设置
 * @param  state 引脚状态
 * @retval None
 */
void FRAM_LL_SCL_Write(GPIO_PinState state)
{
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_7, state);
} /* end FRAM_LL_SCL_Write() */

/**
 * @brief  FRAM SDA电平设置
 * @param  state 引脚状态
 * @retval None
 */
void FRAM_LL_SDA_Write(GPIO_PinState state)
{
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_8, state);
} /* end FRAM_LL_SCL_Write() */

/**
 * @brief  读取SDA引脚电平
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
 * @brief  I2C起始信号
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
 * @brief  I2C停止信号
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
 * @brief  I2C等待应答信号
 * @param  None
 * @retval 0 表示接收应答成功
 * @retval -1 表示接收应答失败
 */
int8_t FRAM_LL_WaitAck(void)
{
    uint8_t TimeOut = 0;

    FRAM_LL_SDA_In();

    FRAM_LL_SCL_Write(GPIO_PIN_SET);
    FRAM_LL_SDA_Write(GPIO_PIN_SET); // 拉高，读取低电平

    Delay_Us(2);

    /* 等待低电平 */
    while ( FRAM_LL_SDA_Read() )
    {
        TimeOut++;

        if (TimeOut > 250)
        {
            /* 失败，停止 */
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
 * @brief  产生应答信号
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
 * @brief  产生非应答信号
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
 * @brief  I2C发送一个字节的数据
 * @param  data 数据字节
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
 * @brief  I2C读取一个字节数据
 * @param  pData 读取的字节
 * @param  ack 1 发送应答信号； 0 发送非应答信号
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
 * @brief  FRAM初始化
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
 * @brief  FRAM 写数据
 * @param  PageAddr 页地址
 * @param  WordAddr 字地址
 * @param  pData 数据指针
 * @param  length 数据长度 
 * @retval 0  表示成功
 * @retval -1 表示失败
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
 * @brief  FRAM 读数据
 * @param  PageAddr 页地址
 * @param  WordAddr 字地址
 * @param  pData 数据指针
 * @param  length 数据长度 
 * @retval 0  表示成功
 * @retval -1 表示失败
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
