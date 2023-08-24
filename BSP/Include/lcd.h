/**
 * @file    lcd.h
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-07-13
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

#ifndef LCD_H
#define LCD_H

#include "stm32f4xx_hal.h"

#define LCD_BL_PIN                      GPIO_PIN_11
#define LCD_BL_PORT                     GPIOD
#define LCD_BL_CLK_ENABLE()             __HAL_RCC_GPIOD_CLK_ENABLE()

#define LCD_BL_ON                       0
#define LCD_BL_OFF                      1

#define LCD_RESET_PIN                   GPIO_PIN_9
#define LCD_RESET_PORT                  GPIOI
#define LCD_RESET_CLK_ENABLE()          __HAL_RCC_GPIOI_CLK_ENABLE()

/**
 * FSMC_A17连接LCD的DC引脚
 * 数据区基地址：
 *   LCD_CMD_ADDR + 2^17 * 2 = 0x60040000
 */
#define LCD_DATA_ADDR                   ((uint32_t)0x60040000)
#define LCD_CMD_ADDR                    ((uint32_t)0x60000000)

#define CMD_SET_ADDRESS_MODE            0x36
#define CMD_SET_PIXEL_FORMAT            0x3A

#define CMD_MCAP                        0xB0
#define CMD_DISPLAY_MODE                0xB4
#define CMD_DCR                         0xBF /*!< 读设备代码 */

#define CMD_PANEL_DRIVING_SETTING       0xC0

#define LCD_COLOR_WHITE                 0xFFFF
#define LCD_COLOR_BLACK                 0x0000
#define LCD_COLOR_BLUE                  0x001F
#define LCD_COLOR_BLUE2                 0x051F
#define LCD_COLOR_RED                   0xF800
#define LCD_COLOR_MAGENTA               0xF81F
#define LCD_COLOR_GREEN                 0x07E0
#define LCD_COLOR_CYAN                  0x7FFF
#define LCD_COLOR_YELLOW                0xFFE0

#define LCD_FONT_ASCII_1206             0U
#define LCD_FONT_ASCII_1608             1U
#define LCD_FONT_ASCII_2412             2U
#define LCD_FONT_ASCII_3216             3U

#define LCD_TOUCH                       SPI4
#define LCD_TOUCH_CLK_ENABLE()          __HAL_RCC_SPI4_CLK_ENABLE()

#define LCD_TOUCH_IRQn                  EXTI9_5_IRQn
#define LCD_TOUCH_IRQHandler            EXTI9_5_IRQHandler

#define LCD_TOUCH_MOSI_PIN              GPIO_PIN_6
#define LCD_TOUCH_MOSI_PORT             GPIOE
#define LCD_TOUCH_MOSI_CLK_ENABLE()     __HAL_RCC_GPIOE_CLK_ENABLE()

#define LCD_TOUCH_MISO_PIN              GPIO_PIN_5
#define LCD_TOUCH_MISO_PORT             GPIOE
#define LCD_TOUCH_MISO_CLK_ENABLE()     __HAL_RCC_GPIOE_CLK_ENABLE()

#define LCD_TOUCH_CLK_PIN               GPIO_PIN_2
#define LCD_TOUCH_CLK_PORT              GPIOE
#define LCD_TOUCH_CLK_CLK_ENABLE()      __HAL_RCC_GPIOE_CLK_ENABLE()

#define LCD_TOUCH_CS_PIN                GPIO_PIN_4
#define LCD_TOUCH_CS_PORT               GPIOE
#define LCD_TOUCH_CS_CLK_ENABLE()       __HAL_RCC_GPIOE_CLK_ENABLE()

#define LCD_TOUCH_IRQ_PIN               GPIO_PIN_6
#define LCD_TOUCH_IRQ_PORT              GPIOB
#define LCD_TOUCH_IRQ_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

#define LCD_TOUCH_BUSY_PIN              GPIO_PIN_13
#define LCD_TOUCH_BUSY_PORT             GPIOD
#define LCD_TOUCH_BUSY_CLK_ENABLE()     __HAL_RCC_GPIOD_CLK_ENABLE()

extern uint16_t LCD_Touch_X_PosData;
extern uint16_t LCD_Touch_Y_PosData;

void LCD_Init(void);
void LCD_BL_Set(uint8_t mode);
void LCD_ReadDeviceCode(void);
void LCD_RectFill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void LCD_Clear(uint16_t color);
void LCD_PixelFill(uint16_t x0, uint16_t y0, uint16_t color);
void LCD_DisplayCharAt(uint16_t x0, uint16_t y0, uint8_t font, uint16_t color, uint16_t BackGround, unsigned char *ch);
void LCD_DisplayNUMAt(uint16_t x0, uint16_t y0, uint8_t font, uint16_t color, uint16_t BackGround, unsigned short num);
void LCD_DisplayNUM32At(uint16_t x0, uint16_t y0, uint8_t font, uint16_t color, uint16_t BackGround, unsigned long num);
void LCD_Touch_MspInit(void);
void LCD_FMC_MspInit(void);
void LCD_Touch_SetEnable(uint8_t mode);
void LCD_Touch_IRQCallback(void);
HAL_StatusTypeDef LCD_Touch_ReadData(uint8_t cmd, uint16_t *pData);
#endif /* end LCD_H */