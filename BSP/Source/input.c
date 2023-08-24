/**
 * @file    input.c
 * @author  ����
 * @version V0.0.0.1
 * @date    2018-07-10
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

#include "input.h"
#include "delay.h"

/**
 * @brief  ����˿ڳ�ʼ��
 * @param  None
 * @retval None
 */
void Input_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    INPUT_FAST_0_CLK_ENABLE();
    INPUT_FAST_1_CLK_ENABLE();
    INPUT_FAST_2_CLK_ENABLE();
    INPUT_FAST_3_CLK_ENABLE();

    GPIO_InitStruct.Pin = INPUT_FAST_0_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(INPUT_FAST_0_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_FAST_1_PIN;
    HAL_GPIO_Init(INPUT_FAST_1_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_FAST_2_PIN;
    HAL_GPIO_Init(INPUT_FAST_2_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_FAST_3_PIN;
    HAL_GPIO_Init(INPUT_FAST_3_PORT, &GPIO_InitStruct);

    /* ���ٶ˿� */
    INPUT_GROUP_A_CLK_ENABLE();
    INPUT_GROUP_B_CLK_ENABLE();
    INPUT_GROUP_C_CLK_ENABLE();
    INPUT_GROUP_D_CLK_ENABLE();
    INPUT_GROUP_E_CLK_ENABLE();
    INPUT_GROUP_F_CLK_ENABLE();
    INPUT_GROUP_G_CLK_ENABLE();
    INPUT_GROUP_H_CLK_ENABLE();
    INPUT_GROUP_I_CLK_ENABLE();

    INPUT_D0_CLK_ENABLE();
    INPUT_D1_CLK_ENABLE();
    INPUT_D2_CLK_ENABLE();
    INPUT_D3_CLK_ENABLE();
    INPUT_D4_CLK_ENABLE();
    INPUT_D5_CLK_ENABLE();
    INPUT_D6_CLK_ENABLE();
    INPUT_D7_CLK_ENABLE();

    GPIO_InitStruct.Pin = INPUT_GROUP_A_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(INPUT_GROUP_A_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_GROUP_B_PIN;
    HAL_GPIO_Init(INPUT_GROUP_B_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_GROUP_C_PIN;
    HAL_GPIO_Init(INPUT_GROUP_C_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_GROUP_D_PIN;
    HAL_GPIO_Init(INPUT_GROUP_D_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_GROUP_E_PIN;
    HAL_GPIO_Init(INPUT_GROUP_E_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_GROUP_F_PIN;
    HAL_GPIO_Init(INPUT_GROUP_F_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_GROUP_G_PIN;
    HAL_GPIO_Init(INPUT_GROUP_G_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_GROUP_H_PIN;
    HAL_GPIO_Init(INPUT_GROUP_H_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_GROUP_I_PIN;
    HAL_GPIO_Init(INPUT_GROUP_I_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_D0_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(INPUT_D0_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_D1_PIN;
    HAL_GPIO_Init(INPUT_D1_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_D2_PIN;
    HAL_GPIO_Init(INPUT_D2_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_D3_PIN;
    HAL_GPIO_Init(INPUT_D3_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_D4_PIN;
    HAL_GPIO_Init(INPUT_D4_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_D5_PIN;
    HAL_GPIO_Init(INPUT_D5_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_D6_PIN;
    HAL_GPIO_Init(INPUT_D6_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INPUT_D7_PIN;
    HAL_GPIO_Init(INPUT_D7_PORT, &GPIO_InitStruct);

    HAL_GPIO_WritePin(INPUT_GROUP_A_PORT, INPUT_GROUP_A_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(INPUT_GROUP_A_PORT, INPUT_GROUP_B_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(INPUT_GROUP_A_PORT, INPUT_GROUP_C_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(INPUT_GROUP_A_PORT, INPUT_GROUP_D_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(INPUT_GROUP_A_PORT, INPUT_GROUP_E_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(INPUT_GROUP_A_PORT, INPUT_GROUP_F_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(INPUT_GROUP_A_PORT, INPUT_GROUP_G_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(INPUT_GROUP_A_PORT, INPUT_GROUP_H_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(INPUT_GROUP_A_PORT, INPUT_GROUP_I_PIN, GPIO_PIN_SET);
} /* end Input_Init() */

/**
 * @brief  ��ȡ��������˿�����
 * @param  None
 * @retval ���ض˿����ݣ�����λ��Ч
 */
uint8_t Input_Fast_Read(void)
{
    uint8_t tmp = 0;
    tmp |= ((uint8_t)(HAL_GPIO_ReadPin(INPUT_FAST_3_PORT, INPUT_FAST_3_PIN)) << 3);
    tmp |= ((uint8_t)(HAL_GPIO_ReadPin(INPUT_FAST_2_PORT, INPUT_FAST_2_PIN)) << 2);
    tmp |= ((uint8_t)(HAL_GPIO_ReadPin(INPUT_FAST_1_PORT, INPUT_FAST_1_PIN)) << 1);
    tmp |= (uint8_t)(HAL_GPIO_ReadPin(INPUT_FAST_0_PORT, INPUT_FAST_0_PIN));

    return tmp;
} /* end Input_Fast_Read() */

/**
 * @brief  ��ȡ�������һλ����
 * @param  bit λ��
 * @retval 0 �͵�ƽ
 * @retval 1 �ߵ�ƽ
 * @retval -1 ����λ��
 */
static int8_t Input_Slow_ReadBit(enum Input_BitTypeDef bit)
{
    int8_t tmp = -1;

    switch(bit)
    {
        case 0 :
        {
            tmp = (int8_t)(HAL_GPIO_ReadPin(INPUT_D0_PORT, INPUT_D0_PIN));
            break;
        }

        case 1:
        {
            tmp = (int8_t)(HAL_GPIO_ReadPin(INPUT_D1_PORT, INPUT_D1_PIN));
            break;
        }

        case 2:
        {
            tmp = (int8_t)(HAL_GPIO_ReadPin(INPUT_D2_PORT, INPUT_D2_PIN));
            break;
        }

        case 3:
        {
            tmp = (int8_t)(HAL_GPIO_ReadPin(INPUT_D3_PORT, INPUT_D3_PIN));
            break;
        }

        case 4:
        {
            tmp = (int8_t)(HAL_GPIO_ReadPin(INPUT_D4_PORT, INPUT_D4_PIN));
            break;
        }

        case 5:
        {
            tmp = (int8_t)(HAL_GPIO_ReadPin(INPUT_D5_PORT, INPUT_D5_PIN));
            break;
        }

        case 6:
        {
            tmp = (int8_t)(HAL_GPIO_ReadPin(INPUT_D6_PORT, INPUT_D6_PIN));
            break;
        }

        case 7:
        {
            tmp = (int8_t)(HAL_GPIO_ReadPin(INPUT_D7_PORT, INPUT_D7_PIN));
            break;
        }

        default :
            break;
    }
    
    tmp = tmp ? 0 : 1;
    
    return tmp;
} /* end Input_Slow_ReadBit() */

/**
 * @brief  ʹ�ܶ�ȡ����
 * @param  port ���
 * @retval None
 */
static void Input_Slow_Enable(enum Input_GroupTypeDef port)
{
    switch(port)
    {
        case 0 :
        {
            HAL_GPIO_WritePin(INPUT_GROUP_A_PORT, INPUT_GROUP_A_PIN, GPIO_PIN_RESET);
            break;
        }

        case 1:
        {
            HAL_GPIO_WritePin(INPUT_GROUP_B_PORT, INPUT_GROUP_B_PIN, GPIO_PIN_RESET);
            break;
        }

        case 2:
        {
            HAL_GPIO_WritePin(INPUT_GROUP_C_PORT, INPUT_GROUP_C_PIN, GPIO_PIN_RESET);
            break;
        }

        case 3:
        {
            HAL_GPIO_WritePin(INPUT_GROUP_D_PORT, INPUT_GROUP_D_PIN, GPIO_PIN_RESET);
            break;
        }

        case 4:
        {
            HAL_GPIO_WritePin(INPUT_GROUP_E_PORT, INPUT_GROUP_E_PIN, GPIO_PIN_RESET);
            break;
        }

        case 5:
        {
            HAL_GPIO_WritePin(INPUT_GROUP_F_PORT, INPUT_GROUP_F_PIN, GPIO_PIN_RESET);
            break;
        }

        case 6:
        {
            HAL_GPIO_WritePin(INPUT_GROUP_G_PORT, INPUT_GROUP_G_PIN, GPIO_PIN_RESET);
            break;
        }

        case 7:
        {
            HAL_GPIO_WritePin(INPUT_GROUP_H_PORT, INPUT_GROUP_H_PIN, GPIO_PIN_RESET);
            break;
        }

        case 8:
        {
            HAL_GPIO_WritePin(INPUT_GROUP_I_PORT, INPUT_GROUP_I_PIN, GPIO_PIN_RESET);
            break;
        }

        default :
            break;
    }
} /* end Input_Slow_Enable() */

/**
 * @brief  ʧ�ܶ�ȡ����
 * @param  port ���
 * @retval None
 */
static void Input_Slow_Disable(enum Input_GroupTypeDef port)
{
    switch (port)
    {
    case 0:
    {
        HAL_GPIO_WritePin(INPUT_GROUP_A_PORT, INPUT_GROUP_A_PIN, GPIO_PIN_SET);
        break;
    }

    case 1:
    {
        HAL_GPIO_WritePin(INPUT_GROUP_B_PORT, INPUT_GROUP_B_PIN, GPIO_PIN_SET);
        break;
    }

    case 2:
    {
        HAL_GPIO_WritePin(INPUT_GROUP_C_PORT, INPUT_GROUP_C_PIN, GPIO_PIN_SET);
        break;
    }

    case 3:
    {
        HAL_GPIO_WritePin(INPUT_GROUP_D_PORT, INPUT_GROUP_D_PIN, GPIO_PIN_SET);
        break;
    }

    case 4:
    {
        HAL_GPIO_WritePin(INPUT_GROUP_E_PORT, INPUT_GROUP_E_PIN, GPIO_PIN_SET);
        break;
    }

    case 5:
    {
        HAL_GPIO_WritePin(INPUT_GROUP_F_PORT, INPUT_GROUP_F_PIN, GPIO_PIN_SET);
        break;
    }

    case 6:
    {
        HAL_GPIO_WritePin(INPUT_GROUP_G_PORT, INPUT_GROUP_G_PIN, GPIO_PIN_SET);
        break;
    }

    case 7:
    {
        HAL_GPIO_WritePin(INPUT_GROUP_H_PORT, INPUT_GROUP_H_PIN, GPIO_PIN_SET);
        break;
    }

    case 8:
    {
        HAL_GPIO_WritePin(INPUT_GROUP_I_PORT, INPUT_GROUP_I_PIN, GPIO_PIN_SET);
        break;
    }

    default:
        break;
    }
} /* end Input_Slow_Enable() */

/**
 * @brief  ��ȡ���ٶ˿�ָ�����1λ����
 * @param  port ��
 * @param  bit λ��
 * @retval 0 �͵�ƽ
 * @retval 1 �ߵ�ƽ
 * @retval -1 λ�Ŵ���
 * @retval -2 ��Ŵ���
 */
static int8_t Input_Slow_ReadPortBit(enum Input_GroupTypeDef port, enum Input_BitTypeDef bit)
{
    int8_t tmp = -2;

    Input_Slow_Enable(port);
  
    Delay_Us(1);

    switch (port)
    {
        case 0 :
        {
            
            tmp = (int8_t)(Input_Slow_ReadBit(bit));
            break;
        }

        case 1:
        {
            tmp = (int8_t)(Input_Slow_ReadBit(bit));
            break;
        }

        case 2:
        {
            tmp = (int8_t)(Input_Slow_ReadBit(bit));
            break;
        }

        case 3:
        {
            tmp = (int8_t)(Input_Slow_ReadBit(bit));
            break;
        }

        case 4:
        {
            tmp = (int8_t)(Input_Slow_ReadBit(bit));
            break;
        }

        case 5:
        {
            tmp = (int8_t)(Input_Slow_ReadBit(bit));
            break;
        }

        case 6:
        {
            tmp = (int8_t)(Input_Slow_ReadBit(bit));
            break;
        }

        case 7:
        {
            tmp = (int8_t)(Input_Slow_ReadBit(bit));
            break;
        }

        case 8 :
        {
            tmp = (int8_t)(Input_Slow_ReadBit(bit));
            break;
        }

        default :
            break;
    }

    Input_Slow_Disable(port);
    
    Delay_Us(1);
    
    return tmp;
} /* end Input_Slow_ReadBit() */

/**
 * @brief  ��ȡָ�����������
 * @param  x
 * @retval 0 �͵�ƽ
 * @retval 1 �ߵ�ƽ
 */
int8_t Input_Slow_Read(uint8_t x)
{
    int8_t tmp;
    enum Input_GroupTypeDef port;
    enum Input_BitTypeDef bit;

    port = (enum Input_GroupTypeDef)(x / 8);
    bit = (enum Input_BitTypeDef)(x % 8);

    tmp = Input_Slow_ReadPortBit(port, bit);

    return tmp;
} /* end Input_Slow_Read() */

uint8_t  Input_8Bit(void)
{
		uint32_t Input32;
		Input32 = GPIOF->IDR;
		return (uint8_t)(((Input32&0x00003000)>>6)|(Input32&0x0000003f));
	
}
//
//
//
uint32_t Input_32_63_Read(void)
{
		uint32_t ret;
	ret = 0;
		Input_Slow_Enable(0);
//Delay_Us(1);
		ret |= ((uint32_t)Input_8Bit())<<0;
		Input_Slow_Disable(0);
		Input_Slow_Enable(1);
//Delay_Us(1);
		ret |= ((uint32_t)Input_8Bit())<<8;
		Input_Slow_Disable(1);
		Input_Slow_Enable(2);
//Delay_Us(1);
		ret |= ((uint32_t)Input_8Bit())<<16;
		Input_Slow_Disable(2);
		Input_Slow_Enable(3);
//Delay_Us(1);
		ret |= ((uint32_t)Input_8Bit())<<24;
		Input_Slow_Disable(3);
		return ret;
}
//X000 X001 X002 
//
//
uint32_t Input_0_31_Read(void)
{
		uint32_t ret;
		ret = 0;
		Input_Slow_Enable(4);
//Delay_Us(1);
		ret |= ((uint32_t)Input_8Bit())<<0;
		Input_Slow_Disable(4);
		Input_Slow_Enable(5);
//Delay_Us(1);
		ret |= ((uint32_t)Input_8Bit())<<8;
		Input_Slow_Disable(5);
		Input_Slow_Enable(6);
//Delay_Us(1);
		ret |= ((uint32_t)Input_8Bit())<<16;
		Input_Slow_Disable(6);
		Input_Slow_Enable(7);
//Delay_Us(1);
		ret |= ((uint32_t)Input_8Bit())<<24;
		Input_Slow_Disable(7);
		return ret;

}

uint8_t Input_64_67_Read(void)
{
		uint8_t ret;
		ret = 0;
		Input_Slow_Enable(8);
		ret |= Input_8Bit();
		Input_Slow_Disable(8);
	
		return ret;
}

uint8_t Input_68_71_Read(void)
{
		return Input_Fast_Read();
}
