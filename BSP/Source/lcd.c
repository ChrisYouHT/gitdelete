/**
 * @file    lcd.c
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-07-13
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
#include "stdint.h"
#include "lcd.h"
#include "Delay.h"
#include "font_ascii.h"
#include "rs232.h"

// SRAM_HandleTypeDef hLCD_SRAM;
SPI_HandleTypeDef hLCD_Touch;
NOR_HandleTypeDef hLCD_NOR;

void LCD_Reset(void);
void LCD_WriteCmd(uint16_t cmd);
void LCD_WriteData(uint16_t data);
uint16_t LCD_ReadData(void);

uint8_t DeviceCode[4] = {0}; // 正常为0x01 0x22 0x15 0x29

uint16_t LCD_Touch_X_PosData = 0;
uint16_t LCD_Touch_Y_PosData = 0;

uint8_t LCD_Printf_Flag=0;

// /**
//  * @brief  FMC初始化
//  * @param  None
//  * @retval None
//  */
// static void LCD_FMC_Init(void)
// {
//     FMC_NORSRAM_TimingTypeDef TimingStruct;

//     hLCD_SRAM.Instance = FMC_NORSRAM_DEVICE;
//     hLCD_SRAM.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
//     hLCD_SRAM.Init.NSBank = FMC_NORSRAM_BANK1;
//     hLCD_SRAM.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
//     hLCD_SRAM.Init.MemoryType = FMC_MEMORY_TYPE_SRAM;
//     hLCD_SRAM.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;
//     hLCD_SRAM.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
//     hLCD_SRAM.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
//     hLCD_SRAM.Init.WrapMode = FMC_WRAP_MODE_DISABLE;
//     hLCD_SRAM.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
//     hLCD_SRAM.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
//     hLCD_SRAM.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
//     hLCD_SRAM.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
//     hLCD_SRAM.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_DISABLE;
//     hLCD_SRAM.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
//     hLCD_SRAM.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
//     hLCD_SRAM.Init.PageSize = FMC_PAGE_SIZE_NONE;
//     /* Timing */
//     TimingStruct.AddressSetupTime = 2;
//     TimingStruct.AddressHoldTime = 0;
//     TimingStruct.DataSetupTime = 5;
//     TimingStruct.BusTurnAroundDuration = 0;
//     TimingStruct.CLKDivision = 0;
//     TimingStruct.DataLatency = 0;
//     TimingStruct.AccessMode = FMC_ACCESS_MODE_B;

//     if (HAL_SRAM_Init(&hLCD_SRAM, &TimingStruct, NULL) != HAL_OK)
//     {
//         for (;;)
//         {
//             ;
//         } /* end for */
//     }     /* end if */
// } /* end LCD_FMC_Init() */

/**
 * @brief  FMC初始化
 * @param  None
 * @retval None
 */
static void LCD_FMC_Init(void)
{
    FMC_NORSRAM_TimingTypeDef TimingStruct;

    hLCD_NOR.Instance = FMC_NORSRAM_DEVICE;
    hLCD_NOR.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
    hLCD_NOR.Init.NSBank = FMC_NORSRAM_BANK1;
    hLCD_NOR.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
    hLCD_NOR.Init.MemoryType = FMC_MEMORY_TYPE_NOR;
    hLCD_NOR.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;
    hLCD_NOR.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
    hLCD_NOR.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
    hLCD_NOR.Init.WrapMode = FMC_WRAP_MODE_DISABLE;
    hLCD_NOR.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
    hLCD_NOR.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
    hLCD_NOR.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
    hLCD_NOR.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
    hLCD_NOR.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_DISABLE;
    hLCD_NOR.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
    hLCD_NOR.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
    hLCD_NOR.Init.PageSize = FMC_PAGE_SIZE_NONE;
    /* Timing */
    TimingStruct.AddressSetupTime = 2;
    TimingStruct.AddressHoldTime = 0;
    TimingStruct.DataSetupTime = 5;
    TimingStruct.BusTurnAroundDuration = 0;
    TimingStruct.CLKDivision = 0;
    TimingStruct.DataLatency = 0;
    TimingStruct.AccessMode = FMC_ACCESS_MODE_B;

    if (HAL_NOR_Init(&hLCD_NOR, &TimingStruct, NULL) != HAL_OK)
    {
        for (;;)
        {
            ;
        } /* end for */
    }     /* end if */
} /* end LCD_FMC_Init() */

/**
 * @brief  LCD初始化
 * @param  None
 * @retval None
 */
void LCD_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* 背光 */
    LCD_BL_CLK_ENABLE();
    GPIO_InitStruct.Pin = LCD_BL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(LCD_BL_PORT, &GPIO_InitStruct);

    /* 复位 */
    LCD_RESET_CLK_ENABLE();
    GPIO_InitStruct.Pin = LCD_RESET_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(LCD_RESET_PORT, &GPIO_InitStruct);

    LCD_FMC_Init();

    Delay_Ms(1);

    LCD_Reset();

    Delay_Ms(1);

    /* 读取设备代码 */
     LCD_ReadDeviceCode();

    /* 初始化序列 */
    LCD_WriteCmd(CMD_MCAP);
    LCD_WriteData(0x00);

    LCD_WriteCmd(CMD_SET_ADDRESS_MODE);
    LCD_WriteData(0x80); // Page Address Order

    LCD_WriteCmd(CMD_SET_PIXEL_FORMAT);
    LCD_WriteData(0x55); // 16 bits/pixel (65,536 colors)

    LCD_WriteCmd(CMD_DISPLAY_MODE);
    LCD_WriteData(0x00); // Internal oscillation clock

    LCD_WriteCmd(CMD_PANEL_DRIVING_SETTING);
    LCD_WriteData(0x03);
    LCD_WriteData(0xDF); //480
    LCD_WriteData(0x40);
    LCD_WriteData(0x12);
    LCD_WriteData(0x00);
    LCD_WriteData(0x01);
    LCD_WriteData(0x00);
    LCD_WriteData(0x43);

    LCD_WriteCmd(0xC1);  //frame frequency
    LCD_WriteData(0x05); //BCn,DIVn[1:0
    LCD_WriteData(0x2f); //RTNn[4:0]
    LCD_WriteData(0x08); // BPn[7:0]
    LCD_WriteData(0x08); // FPn[7:0]
    LCD_WriteData(0x00);

    LCD_WriteCmd(0xC4);
    LCD_WriteData(0x63);
    LCD_WriteData(0x00);
    LCD_WriteData(0x08);
    LCD_WriteData(0x08);

    LCD_WriteCmd(0xC8); //Gamma
    LCD_WriteData(0x06);
    LCD_WriteData(0x0c);
    LCD_WriteData(0x16);
    LCD_WriteData(0x24); //26
    LCD_WriteData(0x30); //32
    LCD_WriteData(0x48);
    LCD_WriteData(0x3d);
    LCD_WriteData(0x28);
    LCD_WriteData(0x20);
    LCD_WriteData(0x14);
    LCD_WriteData(0x0c);
    LCD_WriteData(0x04);

    LCD_WriteData(0x06);
    LCD_WriteData(0x0c);
    LCD_WriteData(0x16);
    LCD_WriteData(0x24);
    LCD_WriteData(0x30);
    LCD_WriteData(0x48);
    LCD_WriteData(0x3d);
    LCD_WriteData(0x28);
    LCD_WriteData(0x20);
    LCD_WriteData(0x14);
    LCD_WriteData(0x0c);
    LCD_WriteData(0x04);

    LCD_WriteCmd(0xC9); //Gamma
    LCD_WriteData(0x06);
    LCD_WriteData(0x0c);
    LCD_WriteData(0x16);
    LCD_WriteData(0x24); //26
    LCD_WriteData(0x30); //32
    LCD_WriteData(0x48);
    LCD_WriteData(0x3d);
    LCD_WriteData(0x28);
    LCD_WriteData(0x20);
    LCD_WriteData(0x14);
    LCD_WriteData(0x0c);
    LCD_WriteData(0x04);

    LCD_WriteData(0x06);
    LCD_WriteData(0x0c);
    LCD_WriteData(0x16);
    LCD_WriteData(0x24);
    LCD_WriteData(0x30);
    LCD_WriteData(0x48);
    LCD_WriteData(0x3d);
    LCD_WriteData(0x28);
    LCD_WriteData(0x20);
    LCD_WriteData(0x14);
    LCD_WriteData(0x0c);
    LCD_WriteData(0x04);

    LCD_WriteCmd(0xCA); //Gamma
    LCD_WriteData(0x06);
    LCD_WriteData(0x0c);
    LCD_WriteData(0x16);
    LCD_WriteData(0x24); //26
    LCD_WriteData(0x30); //32
    LCD_WriteData(0x48);
    LCD_WriteData(0x3d);
    LCD_WriteData(0x28);
    LCD_WriteData(0x20);
    LCD_WriteData(0x14);
    LCD_WriteData(0x0c);
    LCD_WriteData(0x04);

    LCD_WriteData(0x06);
    LCD_WriteData(0x0c);
    LCD_WriteData(0x16);
    LCD_WriteData(0x24);
    LCD_WriteData(0x30);
    LCD_WriteData(0x48);
    LCD_WriteData(0x3d);
    LCD_WriteData(0x28);
    LCD_WriteData(0x20);
    LCD_WriteData(0x14);
    LCD_WriteData(0x0c);
    LCD_WriteData(0x04);

    LCD_WriteCmd(0xD0);
    LCD_WriteData(0x95);
    LCD_WriteData(0x06);
    LCD_WriteData(0x08);
    LCD_WriteData(0x10);
    LCD_WriteData(0x3f);

    LCD_WriteCmd(0xD1);
    LCD_WriteData(0x02);
    LCD_WriteData(0x28);
    LCD_WriteData(0x28);
    LCD_WriteData(0x40);

    LCD_WriteCmd(0xE1);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);

    LCD_WriteCmd(0xE2);
    LCD_WriteData(0x80);

    LCD_WriteCmd(0x2A);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x01);
    LCD_WriteData(0x3F);

    LCD_WriteCmd(0x2B);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x01);
    LCD_WriteData(0xDF);

    LCD_WriteCmd(0x11);

    Delay_Ms(120);

    LCD_WriteCmd(0x29);

    LCD_WriteCmd(0xC1);  //frame frequency
    LCD_WriteData(0x05); //BCn,DIVn[1:0
    LCD_WriteData(0x2f); //RTNn[4:0]
    LCD_WriteData(0x08); // BPn[7:0]
    LCD_WriteData(0x08); // FPn[7:0]
    LCD_WriteData(0x00);

    LCD_BL_Set(LCD_BL_ON);

    /* 触摸屏初始化 */
//    hLCD_Touch.Instance = LCD_TOUCH;
//    hLCD_Touch.Init.Mode = SPI_MODE_MASTER;
//    hLCD_Touch.Init.Direction = SPI_DIRECTION_2LINES;
//    hLCD_Touch.Init.DataSize = SPI_DATASIZE_8BIT;
//    hLCD_Touch.Init.CLKPolarity = SPI_POLARITY_LOW;
//    hLCD_Touch.Init.CLKPhase = SPI_PHASE_1EDGE;
//    hLCD_Touch.Init.NSS = SPI_NSS_SOFT;
//    hLCD_Touch.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
//    hLCD_Touch.Init.FirstBit = SPI_FIRSTBIT_MSB;
//    hLCD_Touch.Init.TIMode = SPI_TIMODE_DISABLE;
//    hLCD_Touch.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
//    hLCD_Touch.Init.CRCPolynomial = 10;

//    if (HAL_SPI_Init(&hLCD_Touch) != HAL_OK)
//    {
//        for (;;)
//        {
//            ;
//        } /* end for */
//    } /* end if */

//    LCD_TOUCH_BUSY_CLK_ENABLE();
//    LCD_TOUCH_IRQ_CLK_ENABLE();
//    LCD_TOUCH_CS_CLK_ENABLE();

//    /* CS */
//    GPIO_InitStruct.Pin = LCD_TOUCH_CS_PIN;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Pull = GPIO_PULLUP;
//    HAL_GPIO_Init(LCD_TOUCH_CS_PORT, &GPIO_InitStruct);

//    /* IRQ */
//    GPIO_InitStruct.Pin = LCD_TOUCH_IRQ_PIN;
//    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(LCD_TOUCH_IRQ_PORT, &GPIO_InitStruct);

//    /* busy */
//    GPIO_InitStruct.Pin = LCD_TOUCH_BUSY_PIN;
//    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//    HAL_GPIO_Init(LCD_TOUCH_BUSY_PORT, &GPIO_InitStruct);

//    LCD_Touch_SetEnable(0);

//    HAL_NVIC_SetPriority(LCD_TOUCH_IRQn, 12, 0);
//    HAL_NVIC_EnableIRQ(LCD_TOUCH_IRQn);
} /* end LCD_Init() */

/**
 * @brief  LCD FMC硬件初始化
 * @param  None
 * @retval None
 */
void LCD_FMC_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_FMC_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /** FMC GPIO Configuration  
    PE7   ------> FMC_D4
    PE8   ------> FMC_D5
    PE9   ------> FMC_D6
    PE10   ------> FMC_D7
    PE11   ------> FMC_D8
    PE12   ------> FMC_D9
    PE13   ------> FMC_D10
    PE14   ------> FMC_D11
    PE15   ------> FMC_D12
    PD8   ------> FMC_D13
    PD9   ------> FMC_D14
    PD10   ------> FMC_D15
    PD12   ------> FMC_A17
    PD14   ------> FMC_D0
    PD15   ------> FMC_D1
    PD0   ------> FMC_D2
    PD1   ------> FMC_D3
    PD4   ------> FMC_NOE
    PD5   ------> FMC_NWE
    PD7   ------> FMC_NE1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_12 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
} /* end LCD_FMC_MspInit() */

/**
 * @brief  LCD Touch硬件初始化
 * @param  None
 * @retval None
 */
void LCD_Touch_MspInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    LCD_TOUCH_CLK_ENABLE();
    LCD_TOUCH_MISO_CLK_ENABLE();
    LCD_TOUCH_MOSI_CLK_ENABLE();

    /**SPI4 GPIO Configuration    
    PE2     ------> SPI4_SCK
    PE5     ------> SPI4_MISO
    PE6     ------> SPI4_MOSI 
    */
    GPIO_InitStruct.Pin = LCD_TOUCH_CLK_PIN | LCD_TOUCH_MISO_PIN | LCD_TOUCH_MOSI_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI4;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

} /* end LCD_Touch_MspInit() */

/**
 * @brief  LCD背光控制
 * @param  mode 背光模式
 * @retval None
 */
void LCD_BL_Set(uint8_t mode)
{
    switch (mode)
    {
    case LCD_BL_ON:
    {
        HAL_GPIO_WritePin(LCD_BL_PORT, LCD_BL_PIN, GPIO_PIN_SET);
        break;
    }

    case LCD_BL_OFF:
    {
        HAL_GPIO_WritePin(LCD_BL_PORT, LCD_BL_PIN, GPIO_PIN_RESET);
        break;
    }

    default:
        break;
    }
} /* end LCD_BL_Set() */

/**
 * @brief  LCD复位
 * @param  None
 * @retval None
 */
void LCD_Reset(void)
{
    HAL_GPIO_WritePin(LCD_RESET_PORT, LCD_RESET_PIN, GPIO_PIN_RESET);
    Delay_Ms(50);
    HAL_GPIO_WritePin(LCD_RESET_PORT, LCD_RESET_PIN, GPIO_PIN_SET);
    Delay_Ms(50);
} /* end LCD_Reset() */

/**
 * @brief  LCD写命令
 * @param  cmd 命令
 * @retval None
 */
void LCD_WriteCmd(uint16_t cmd)
{
    *(__IO uint16_t *)(LCD_CMD_ADDR) = cmd;
} /* end LCD_WriteCMD() */

/**
 * @brief  LCD些数据
 * @param  data 数据
 * @retval None
 */
void LCD_WriteData(uint16_t data)
{
    *(__IO uint16_t *)(LCD_DATA_ADDR) = data;
} /* end LCD_WriteData() */

/**
 * @brief  LCD读取数据
 * @param  None
 * @retval None
 */
uint16_t LCD_ReadData(void)
{
    return *(__IO uint16_t *)(LCD_DATA_ADDR);
} /* end LCD_ReadData() */

/**
 * @brief  读取LCD设备代买
 * @param  None
 * @retval None
 */
void LCD_ReadDeviceCode(void)
{
    LCD_WriteCmd(CMD_MCAP);
    LCD_WriteData(0x00); // B0 B1-BF C0-FF 关闭保护

    LCD_WriteCmd(CMD_DCR);
    LCD_ReadData(); // 第一个字节丢弃
    DeviceCode[0] = LCD_ReadData();
    DeviceCode[1] = LCD_ReadData();
    DeviceCode[2] = LCD_ReadData();
    DeviceCode[3] = LCD_ReadData();
} /* end LCD_ReadDeviceCode() */

/**
 * @brief  LCD开窗
 * @param  x0, y0 起点坐标
 * @param  x1, y1 终点坐标
 * @retval None
 */
void LCD_OpenWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    LCD_WriteCmd(0x2A);
    LCD_WriteData(x0 >> 8);
    LCD_WriteData(x0 & 0xFF);
    LCD_WriteData(x1 >> 8);
    LCD_WriteData(x1 & 0xFF);

    LCD_WriteCmd(0x2B);
    LCD_WriteData(y0 >> 8);
    LCD_WriteData(y0 & 0xFF);
    LCD_WriteData(y1 >> 8);
    LCD_WriteData(y1 & 0xFF);

    LCD_WriteCmd(0x2C);
} /* end LCD_OpenWindow() */

/**
 * @brief  LCD矩形填充
 * @param  x0, y0 起始坐标
 * @param  x1, y1 终点坐标
 * @retval None
 */
void LCD_RectFill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    int16_t xSize;
    int16_t ySize;
    uint16_t tmp = 0;
    uint32_t i = 0;

    if (x1 < x0)
    {
        tmp = x1;
        x1 = x0;
        x0 = tmp;
    } /* end if */

    if (y1 < y0)
    {
        tmp = y1;
        y1 = y0;
        y0 = tmp;
    } /* end if */

    xSize = x1 - x0 + 1;
    ySize = y1 - y0 + 1;

    LCD_OpenWindow(x0, y0, x1, y1);

    for (i = 0; i < (xSize * ySize); i++)
    {
        LCD_WriteData(color);
    } /* end for */
} /* end LCD_RectFill() */

/**
 * @brief  LCD清屏
 * @param  color 清屏颜色
 * @retval None
 */
void LCD_Clear(uint16_t color)
{
    LCD_RectFill(0, 0, 320, 480, color);
} /* end LCD_Clear() */

/**
 * @brief  LCD像素填充
 * @param  x0, y0 像素坐标
 * @param  color 填充颜色
 * @retval None
 */
void LCD_PixelFill(uint16_t x0, uint16_t y0, uint16_t color)
{
    LCD_OpenWindow(x0, y0, x0 + 1, y0 + 1);

    LCD_WriteData(color);
} /* end LCD_PixelFill() */

/**
* @brief  LCD显示ASCII码字符
* @param  x0, y0 起点坐标
* @param  font 字体
* @param  BackGround 背景
* @param  color 颜色
* @param  ch 字符
* @retval None
*/
void LCD_DisplayCharAt(uint16_t x0, uint16_t y0, uint8_t font, uint16_t color, uint16_t BackGround, unsigned char *ch)
{
    uint16_t tmp;
    uint8_t data;
		uint32_t i,j;
		uint16_t y00,x00;
		unsigned char * asc;
		LCD_Printf_Flag = 1;
	
		LCD_Printf_Flag = 0;
		asc = ch;
	  y00 = y0;
		x00 = x0;
		while(*asc != '\n')
		{
	
				switch (font)
				{
		//    case LCD_FONT_ASCII_1206:
		//    {
		//        LCD_OpenWindow(x0, y0, x0 + 16, y0 + 8);

		//        for (i = 0; i < 16; i++)
		//        {
		//            data = Ascii_1206[ch-32][i];

		//            for (j = 0; j < 8; j++)
		//            {
		//                tmp = (data & 0x80) ? color : BackGround;
		//                LCD_WriteData(tmp);

		//                data <<= 1;
		//            } /* end for */

		//        } /* end for */

		//        break;
		//    }

				case LCD_FONT_ASCII_3216:
				{
						LCD_OpenWindow(x00, y00, x00 + 8 -1, y00 + 16 -1 );

						for (i = 0; i < 16; i++)
						{
								data = Ascii_1608[(*asc)-32][16-i];

								for (j = 0; j < 8; j++)
								{
										tmp = (data & 0x80) ? color : BackGround;
										 LCD_WriteData(tmp);
										 //Delay_Ms(10);
										data <<= 1;
								} /* end for */

						} /* end for */
						break;
				}

				default:
						break;
				}
				x00 += 8;
				asc ++;
		}
} /* end LCD_DisplayCharAt() */

void LCD_DisplayNUMAt(uint16_t x0, uint16_t y0, uint8_t font, uint16_t color, uint16_t BackGround, unsigned short num)
{
    uint16_t tmp;
    uint8_t data;
		uint32_t i,j;
		uint16_t y00,x00;
		unsigned char shownum[5];
		unsigned char * asc;
		LCD_Printf_Flag = 1;
		shownum[0] = num / 0XFFF;
		num %= 0XFFF;
		shownum[1] = num / 0XFF;
		num %= 0XFF;
		shownum[2] = num / 0XF;
		num %= 0XF;
		shownum[3] = num ;

		if(shownum[0] <= 9)shownum[0] += 48;
			else shownum[0] += (65 - 10);
	
		if(shownum[1] <= 9)shownum[1] += 48;
			else shownum[1] += (65 - 10);

		if(shownum[2] <= 9)shownum[2] += 48;
			else shownum[2] += (65 - 10);

		if(shownum[3] <= 9)shownum[3] += 48;
			else shownum[3] += (65 - 10);

		shownum[4] = '\n';

		LCD_Printf_Flag = 0;
		asc = shownum;
	  y00 = y0;
		x00 = x0;
		while(*asc != '\n')
		{
	
				switch (font)
				{
		//    case LCD_FONT_ASCII_1206:
		//    {
		//        LCD_OpenWindow(x0, y0, x0 + 16, y0 + 8);

		//        for (i = 0; i < 16; i++)
		//        {
		//            data = Ascii_1206[ch-32][i];

		//            for (j = 0; j < 8; j++)
		//            {
		//                tmp = (data & 0x80) ? color : BackGround;
		//                LCD_WriteData(tmp);

		//                data <<= 1;
		//            } /* end for */

		//        } /* end for */

		//        break;
		//    }

				case LCD_FONT_ASCII_3216:
				{
						LCD_OpenWindow(x00, y00, x00 + 8 -1, y00 + 16 -1 );

						for (i = 0; i < 16; i++)
						{
								data = Ascii_1608[(*asc)-32][16-i];

								for (j = 0; j < 8; j++)
								{
										tmp = (data & 0x80) ? color : BackGround;
										 LCD_WriteData(tmp);
										 //Delay_Ms(10);
										data <<= 1;
								} /* end for */

						} /* end for */
						break;
				}

				default:
						break;
				}
				x00 += 8;
				asc ++;
		}
} /* end LCD_DisplayCharAt() */


void LCD_DisplayNUM32At(uint16_t x0, uint16_t y0, uint8_t font, uint16_t color, uint16_t BackGround, unsigned long num)
{
       uint16_t tmp;
    uint8_t data;
		uint32_t i,j;
		uint16_t y00,x00;
		unsigned char shownum[9];
		unsigned char * asc;
		unsigned long mask = 0x0FFFFFFF;
	LCD_Printf_Flag = 1;
		mask = 0x0FFFFFFF;
		for(i=0;i<<8;i++)
		{
				shownum[i] = num / mask;
				num %= mask;
				mask >>= 4;
		}
		for(i=0;i<<8;i++)
		{
			if(shownum[i] <= 9)shownum[i] += 48;
					else shownum[i] += (65 - 10);

		}



		shownum[8] = '\n';

		LCD_Printf_Flag = 0;
		asc = shownum;
	  y00 = y0;
		x00 = x0;
		while(*asc != '\n')
		{
	
				switch (font)
				{
		//    case LCD_FONT_ASCII_1206:
		//    {
		//        LCD_OpenWindow(x0, y0, x0 + 16, y0 + 8);

		//        for (i = 0; i < 16; i++)
		//        {
		//            data = Ascii_1206[ch-32][i];

		//            for (j = 0; j < 8; j++)
		//            {
		//                tmp = (data & 0x80) ? color : BackGround;
		//                LCD_WriteData(tmp);

		//                data <<= 1;
		//            } /* end for */

		//        } /* end for */

		//        break;
		//    }

				case LCD_FONT_ASCII_3216:
				{
						LCD_OpenWindow(x00, y00, x00 + 8 -1, y00 + 16 -1 );

						for (i = 0; i < 16; i++)
						{
								data = Ascii_1608[(*asc)-32][16-i];

								for (j = 0; j < 8; j++)
								{
										tmp = (data & 0x80) ? color : BackGround;
										 LCD_WriteData(tmp);
										 //Delay_Ms(10);
										data <<= 1;
								} /* end for */

						} /* end for */
						break;
				}

				default:
						break;
				}
				x00 += 8;
				asc ++;
		}
} /* end LCD_DisplayCharAt() */


/**
 * @brief  LCD Touch 片选
 * @param  mode 0表示使能，1表示失能
 * @retval None
 */
void LCD_Touch_SetEnable(uint8_t mode)
{
    switch(mode)
    {
        case 0 :
        {
            HAL_GPIO_WritePin(LCD_TOUCH_CS_PORT, LCD_TOUCH_CS_PIN, GPIO_PIN_RESET);
            break;
        }

        case 1:
        {
            HAL_GPIO_WritePin(LCD_TOUCH_CS_PORT, LCD_TOUCH_CS_PIN, GPIO_PIN_SET);
            break;
        }
        default :
            break;
    }
} /* end LCD_Touch_SetEnable() */

/**
 * @brief  LCD Touch 读取数据
 * @param  cmd 命令
 * @param  pData 数据指针
 * @retval 收发状态
 */
HAL_StatusTypeDef LCD_Touch_ReadData(uint8_t cmd, uint16_t *pData)
{
    HAL_StatusTypeDef status = HAL_OK;
    uint8_t tmp[2];

    LCD_Touch_SetEnable(0);

    status = HAL_SPI_Transmit(&hLCD_Touch, &cmd, 1, 1000);
    if (status != HAL_OK)
    {
        return status;
    } /* end if */

    Delay_Us(10);

    status = HAL_SPI_Receive(&hLCD_Touch, tmp, 1, 1000);
    if (status != HAL_OK)
    {
        return status;
    } /* end if */

    status = HAL_SPI_Receive(&hLCD_Touch, tmp + 1, 1, 1000);
    if (status != HAL_OK)
    {
        return status;
    } /* end if */

    *pData = ((uint16_t)tmp[0] << 4) | (tmp[1] >> 4);

    LCD_Touch_SetEnable(1);

    return status;
} /* end FunctionName() */

/**
 * @brief  LCD Touch 中断
 * @param  None
 * @retval None
 */
void LCD_Touch_IRQCallback(void)
{
    char tmp[100];
    uint16_t length = 0;
    
    LCD_Touch_SetEnable(1);

    HAL_NVIC_DisableIRQ(LCD_TOUCH_IRQn);

    LCD_Touch_ReadData(0xD0, &LCD_Touch_X_PosData);
    LCD_Touch_ReadData(0x90, &LCD_Touch_Y_PosData);

    length = sprintf(tmp, "\r\n X:%d Y:%d \r\n ", LCD_Touch_X_PosData, LCD_Touch_Y_PosData);
    RS232A_SendBytes((uint8_t *)tmp, length, 1000);
    

    HAL_NVIC_EnableIRQ(LCD_TOUCH_IRQn);
    
  LCD_Touch_SetEnable(0);
} /* end LCD_Touch_IRQCallback() */
