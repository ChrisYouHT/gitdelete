/**
 * @file    adc.c
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-07-19
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

#include "adc.h"

SPI_HandleTypeDef hADC_SPI;

/**
 * @brief  ADC 初始化
 * @param  None
 * @retval None
 */
void ADC_SPI_Init(void)
{
    hADC_SPI.Instance = SPI2;
    hADC_SPI.Init.Mode = SPI_MODE_MASTER;
    hADC_SPI.Init.Direction = SPI_DIRECTION_2LINES;
    hADC_SPI.Init.DataSize = SPI_DATASIZE_8BIT;
    hADC_SPI.Init.CLKPolarity = SPI_POLARITY_LOW;
    hADC_SPI.Init.CLKPhase = SPI_PHASE_1EDGE;
    hADC_SPI.Init.NSS = SPI_NSS_SOFT;
    hADC_SPI.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
    hADC_SPI.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hADC_SPI.Init.TIMode = SPI_TIMODE_DISABLE;
    hADC_SPI.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hADC_SPI.Init.CRCPolynomial = 10;

    if (HAL_SPI_Init(&hADC_SPI) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    } /* end if */

} /* end ADC_Init() */

/**
 * @brief  ADC SPI 硬件初始化
 * @param  None
 * @retval None
 */
void ADC_SPI_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_SPI2_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /**SPI2 GPIO Configuration    
    PI1     ------> SPI4_SCK
    PC2     ------> SPI4_MISO
    PC3     ------> SPI4_MOSI 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_1;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    /* CS ---> PI0 */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
} /* end ADC_SPI_MspInit() */

/**
 * @brief  ADC SPI 读取数据
 * @param  channelx 通道
 * @param  pData 测量数据
 * @retval 返回测量结果
 */
int8_t ADC_SPI_ReadData(uint8_t channelx, uint16_t *pData)
{
    uint8_t tmpCmd[3];
    uint8_t tmpData[3];
    HAL_StatusTypeDef status;

    tmpCmd[0] = 0x06; // 单端
    tmpCmd[2] = 0x00;

    HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0, GPIO_PIN_RESET);

    switch(channelx)
    {
        case 0 :
        {
            tmpCmd[1] = 0x00;
            break;
        }

        case 1 :
        {
            tmpCmd[1] = 0x40;
            break;
        }

        case 2 :
        {
            tmpCmd[1] = 0x80;
            break;
        }

        default :
            HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0, GPIO_PIN_SET);
            return -1;
            break;
    }

    status = HAL_SPI_TransmitReceive(&hADC_SPI, tmpCmd, tmpData, 3, 1000);

    if (status != HAL_OK)
    {
        HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0, GPIO_PIN_SET);
        return -1;
    } /* end if */

    *pData = ((tmpData[1] & 0x0F) << 8) | (tmpData[2]);      //左移8位溢陈吗？？？

    HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0, GPIO_PIN_SET);
    return 0;
} /* end ADC_SPI_ReadData() */
