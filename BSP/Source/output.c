/**
 * @file    output.c
 * @author  张腾
 * @version V0.0.0.0
 * @date    2018-07-09
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

#include "output.h"
#include "delay.h"

/**
 * @brief  Output初始化
 * @param  None
 * @retval None
 */
void Output_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* Slow */
    OUTPUT_SLOW_DS_CLK_ENABLE();
    OUTPUT_SLOW_STCP_CLK_ENABLE();
    OUTPUT_SLOW_SHCP_CLK_ENABLE();

    GPIO_InitStruct.Pin = OUTPUT_SLOW_DS;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(OUTPUT_SLOW_DS_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = OUTPUT_SLOW_STCP;
    HAL_GPIO_Init(OUTPUT_SLOW_STCP_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = OUTPUT_SLOW_SHCP;
    HAL_GPIO_Init(OUTPUT_SLOW_SHCP_PORT, &GPIO_InitStruct);

    HAL_GPIO_WritePin(OUTPUT_SLOW_DS_PORT, OUTPUT_SLOW_DS, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(OUTPUT_SLOW_STCP_PORT, OUTPUT_SLOW_STCP, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(OUTPUT_SLOW_SHCP_PORT, OUTPUT_SLOW_SHCP, GPIO_PIN_RESET);

    Output_Slow_Set(0x000000000000);

    /* Fast */
    OUTPUT_FAST_PIN_0_CLK_ENABLE();
    OUTPUT_FAST_PIN_1_CLK_ENABLE();
    OUTPUT_FAST_PIN_2_CLK_ENABLE();
    OUTPUT_FAST_PIN_3_CLK_ENABLE();

    GPIO_InitStruct.Pin = OUTPUT_FAST_PIN_0;
    HAL_GPIO_Init(OUTPUT_FAST_PORT_0, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = OUTPUT_FAST_PIN_1;
    HAL_GPIO_Init(OUTPUT_FAST_PORT_1, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = OUTPUT_FAST_PIN_2;
    HAL_GPIO_Init(OUTPUT_FAST_PORT_2, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = OUTPUT_FAST_PIN_3;
    HAL_GPIO_Init(OUTPUT_FAST_PORT_3, &GPIO_InitStruct);

    Output_Fast_Set(0x00);
} /* end Output_Init() */

/**
 * @brief  高速端口输出设置
 * @param  byte 待输出数据，低4位有效
 * @retval None
 */
void Output_Fast_Set(uint8_t byte)
{
    uint8_t tmp = byte & 0x0F;

    HAL_GPIO_WritePin(OUTPUT_FAST_PORT_0, OUTPUT_FAST_PIN_0, (GPIO_PinState)(tmp & 0x01));
    HAL_GPIO_WritePin(OUTPUT_FAST_PORT_1, OUTPUT_FAST_PIN_1, (GPIO_PinState)(tmp & 0x02));
    HAL_GPIO_WritePin(OUTPUT_FAST_PORT_2, OUTPUT_FAST_PIN_2, (GPIO_PinState)(tmp & 0x04));
    HAL_GPIO_WritePin(OUTPUT_FAST_PORT_3, OUTPUT_FAST_PIN_3, (GPIO_PinState)(tmp & 0x08));
} /* end Outout_Fast_Set() */

/**
 * @brief  高速端口输出按位设置
 * @param  bit 位号
 * @param  NewState 状态
 * @retval 0  成功
 * @retval -1 失败
 */
int8_t Output_Fast_SetBit(uint8_t bit, GPIO_PinState NewState)
{
    int8_t err = 0;

    switch (bit)
    {
        case 0 :
        {
            HAL_GPIO_WritePin(OUTPUT_FAST_PORT_0, OUTPUT_FAST_PIN_0, NewState);
            break;
        }

        case 1 :
        {
            HAL_GPIO_WritePin(OUTPUT_FAST_PORT_1, OUTPUT_FAST_PIN_1, NewState);
            break;
        }

        case 2 :
        {
            HAL_GPIO_WritePin(OUTPUT_FAST_PORT_2, OUTPUT_FAST_PIN_2, NewState);
            break;
        }

        case 3 :
        {
            HAL_GPIO_WritePin(OUTPUT_FAST_PORT_3, OUTPUT_FAST_PIN_3, NewState);
            break;
        }

        default:
            err =  -1;
            break;
    }

    return err;
} /* end Output_Fast_SetBit() */

/**
 * @brief  将1位数据移入存储器
 * @param  NewState 新的状态
 * @retval None
 */
void Output_Slow_LL_ShiftBit(GPIO_PinState NewState)
{
    HAL_GPIO_WritePin(OUTPUT_SLOW_SHCP_PORT, OUTPUT_SLOW_SHCP, GPIO_PIN_RESET);
	__nop();
    //Delay_Us(1);

    /* 准备数据 */
    HAL_GPIO_WritePin(OUTPUT_SLOW_DS_PORT, OUTPUT_SLOW_DS, NewState);
    __nop();
		//Delay_Us(1);
    /* 上升沿读数据 */
    HAL_GPIO_WritePin(OUTPUT_SLOW_SHCP_PORT, OUTPUT_SLOW_SHCP, GPIO_PIN_SET);
		__nop();
		//Delay_Us(1);

    HAL_GPIO_WritePin(OUTPUT_SLOW_STCP_PORT, OUTPUT_SLOW_STCP, GPIO_PIN_RESET);
} /* end Output_Slow_LL_Shift() */

/**
 * @brief  低速端口输出使能
 * @param  None
 * @retval None
 */
static void Output_Slow_LL_Enable(void)
{
    HAL_GPIO_WritePin(OUTPUT_SLOW_STCP_PORT, OUTPUT_SLOW_STCP, GPIO_PIN_RESET);
  __nop();  
	//Delay_Us(1);

    HAL_GPIO_WritePin(OUTPUT_SLOW_STCP_PORT, OUTPUT_SLOW_STCP, GPIO_PIN_SET);
  __nop();  
	//Delay_Us(1);

    HAL_GPIO_WritePin(OUTPUT_SLOW_STCP_PORT, OUTPUT_SLOW_STCP, GPIO_PIN_RESET);

} /* end Output_Slow_LL_Enable() */

/**
 * @brief  低速输出端口设置
 * @param  Data
 * @retval None
 *///此处有一个BUG  在10 11 位为空位
//Y035 - Y000
void Output_Slow_Set(uint64_t Data)
{
    uint64_t tmp = ~Data & 0x000000FFFFFFFFFF;
    uint8_t i;
    GPIO_PinState state;
		tmp = (tmp&0x0000000000003FFF)|((tmp&0x0000000FFFFFC000)<<2); //此处有BUG
    for (i = 0; i < 44; i++)
    {
        state = ((tmp & 0x0000080000000000) ? (GPIO_PIN_SET) : (GPIO_PIN_RESET));
        Output_Slow_LL_ShiftBit(state);

        tmp <<= 1;
    } /* end for */

    Output_Slow_LL_Enable();

} /* end FunctionName() */

