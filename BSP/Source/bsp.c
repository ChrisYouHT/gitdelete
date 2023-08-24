/**
 * @file    bsp.c
 * @author  张腾
 * @version V0.0.0.1
 * @date    2018-05-23
 * @brief   板级驱动文件
 * 
 * @verbatim
   
   
   
 * @endverbatim
 * 
 * @attention
 *
 *
 *
 * <h2><center>&copy; COPYRIGHT 2018 无锡市驰海智能科技有限公司</center></h2>
 */

#include "bsp.h"
#include "rs232.h"
#include "output.h"
#include "delay.h"
#include "input.h"
#include "rs485.h"
#include "can.h"
#include "led.h"
#include "lcd.h"
#include "sdram.h"
#include "dac.h"
#include "adc.h"
#include "pulse.h"
#include "encoder.h"
#include "key.h"
#include "buzzer.h"
#include "fram.h"
#include "cryptomem.h"

/**
 * @brief  板级驱动初始化
 * @param  None
 * @retval None
 */


 unsigned long errnum;
 unsigned long retnum;
 
 
void BSP_Init(void)
{
    HAL_StatusTypeDef status;
    uint8_t tmp = 0;

    unsigned i, j;
    // Delay_Init();
    RS232_Init();
//    Output_Init();
//    Input_Init();
//    RS485_Init();
//    CANx_Init();
    LED_Init();
    LCD_Init();
//    do
//    {
//        tmp++;
//        status = SDRAM_Init();

//        if (tmp > 5)
//        {
//            break;
//        } /* end if */

//    } while(status != HAL_OK); /* end do...while */

    DAC_Init();
    ADC_SPI_Init();
    Pulse_Init();
    Encoder_Init();
    Key_Init();
    Buzzer_Init();
    FRAM_Init();
    CMem_Init();

    //  *(unsigned long *)(0xc0000000) = 1;
    //  *(unsigned short *)(0xc0000000) = 1;
    //  *(unsigned char *)(0xc0000000) = 1;
    //
    //  for(i = 0;i < 1000000;i+=4)
    //  {
    //      *(unsigned long *)(0xc0001000 + i) = 0x12345678 + i;
    //  }
    //
    //
    //  for(i = 0;i < 1000000;i+=4)
    //  {
    //      retnum = (*(unsigned long *)(0xc0001000 + i));
    //
    //
    //      if(retnum != (0x12345678 + i))
    //      {
    //          errnum ++;
    //      }
    //  }  


  
  
  
  
} /* end BSP_Init() */
