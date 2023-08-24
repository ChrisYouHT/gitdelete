/**
 * @file    sdram.c
 * @author  ����
 * @version V0.0.0.0
 * @date    2018-07-17
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

#include "sdram.h"
#include "delay.h"
#include "rs232.h"

#define SDRAM_MODEREG_BURST_LENGTH_1 ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2 ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4 ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8 ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2 ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3 ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE ((uint16_t)0x0200)

SDRAM_HandleTypeDef hSDRAM;

/**
 * @brief  SDRAMӲ����ʼ��
 * @param  None
 * @retval None
 */
void SDRAM_FMC_MspInit(void)
{
    // GPIO_InitTypeDef GPIO_InitStruct;

    // /* Peripheral clock enable */
    // __HAL_RCC_FMC_CLK_ENABLE();

    // __HAL_RCC_GPIOF_CLK_ENABLE();
    // __HAL_RCC_GPIOH_CLK_ENABLE();
    // __HAL_RCC_GPIOC_CLK_ENABLE();
    // __HAL_RCC_GPIOG_CLK_ENABLE();
    // __HAL_RCC_GPIOE_CLK_ENABLE();
    // __HAL_RCC_GPIOD_CLK_ENABLE();

    // /** FMC GPIO Configuration  
    // PF0   ------> FMC_A0
    // PF1   ------> FMC_A1
    // PF2   ------> FMC_A2
    // PF3   ------> FMC_A3
    // PF4   ------> FMC_A4
    // PF5   ------> FMC_A5
    // PC0   ------> FMC_SDNWE
    // PH2   ------> FMC_SDCKE0
    // PH3   ------> FMC_SDNE0
    // PF11   ------> FMC_SDNRAS
    // PF12   ------> FMC_A6
    // PF13   ------> FMC_A7
    // PF14   ------> FMC_A8
    // PF15   ------> FMC_A9
    // PG0   ------> FMC_A10
    // PG1   ------> FMC_A11
    // PE7   ------> FMC_D4
    // PE8   ------> FMC_D5
    // PE9   ------> FMC_D6
    // PE10   ------> FMC_D7
    // PE11   ------> FMC_D8
    // PE12   ------> FMC_D9
    // PE13   ------> FMC_D10
    // PE14   ------> FMC_D11
    // PE15   ------> FMC_D12
    // PD8   ------> FMC_D13
    // PD9   ------> FMC_D14
    // PD10   ------> FMC_D15
    // PD14   ------> FMC_D0
    // PD15   ------> FMC_D1
    // PG2   ------> FMC_A12
    // PG4   ------> FMC_BA0
    // PG5   ------> FMC_BA1
    // PG8   ------> FMC_SDCLK
    // PD0   ------> FMC_D2
    // PD1   ------> FMC_D3
    // PG15   ------> FMC_SDNCAS
    // */
    // GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    // GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    // GPIO_InitStruct.Pull = GPIO_NOPULL;
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    // GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    // HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    // GPIO_InitStruct.Pin = GPIO_PIN_0;
    // GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    // GPIO_InitStruct.Pull = GPIO_NOPULL;
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    // GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    // HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    // GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    // GPIO_InitStruct.Pull = GPIO_NOPULL;
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    // GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    // HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    // GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15;
    // GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    // GPIO_InitStruct.Pull = GPIO_NOPULL;
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    // GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    // HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    // GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    // GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    // GPIO_InitStruct.Pull = GPIO_NOPULL;
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    // GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    // HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    // GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1;
    // GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    // GPIO_InitStruct.Pull = GPIO_NOPULL;
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    // GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    // HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_FMC_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    /* FMC GPIO
        PG4 ---> FMC_BA0
     */

    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;    //���츴��
    GPIO_InitStruct.Pull = GPIO_PULLUP;        //����
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;   //����
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC; //����ΪFMC
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);    //��ʼ��PC0,2,3

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct); //��ʼ��PD0,1,8,9,10,14,15

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct); //��ʼ��PE0,1,7,8,9,10,11,12,13,14,15

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct); //��ʼ��PF0,1,2,3,4,5,11,12,13,14,15

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct); //��ʼ��PG0,1,2,4,5,8,15

    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
} /* end SDRAM_FMC_MspInit() */

/**
 * @brief  sdram��ʼ������
 * @param  hsdram SDRAM���
 * @retval None
 */
static HAL_StatusTypeDef SDRAM_InitSquence(SDRAM_HandleTypeDef *hsdram)
{
    FMC_SDRAM_CommandTypeDef Cmd;
    uint32_t i = 0;
    uint32_t tmpModeReg = 0;
    HAL_StatusTypeDef status;

    Cmd.CommandMode = FMC_SDRAM_CMD_NORMAL_MODE;
    Cmd.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Cmd.AutoRefreshNumber = 1;
    Cmd.ModeRegisterDefinition = 0;
  
    // Delay_Ms(1000); // �ȴ���Դ�ȶ�
  
    /* step1:����ʱ��ʹ������ */
    Cmd.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
    status = HAL_SDRAM_SendCommand(&hSDRAM, &Cmd, 0x1000);

    return status;
    /* ������ʱ200us */
    Delay_Us(500);
    // for (i = 0; i < 0x3FFF; i++) // 180MHz����ʱԼ550us
    // {
    //     ;
    // }

    /* step2:����Ԥ������� */
    Cmd.CommandMode = FMC_SDRAM_CMD_PALL;
    status = HAL_SDRAM_SendCommand(&hSDRAM, &Cmd, 0x1000);

    return status;

    /* step3:�����Զ�ˢ�´��� */
    Cmd.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    Cmd.AutoRefreshNumber = 8;
    HAL_SDRAM_SendCommand(&hSDRAM, &Cmd, 0x1000);

    /* step4:����ģʽ�Ĵ��� */
    tmpModeReg = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1 |
                 SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
                 SDRAM_MODEREG_CAS_LATENCY_3 |
                 SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                 SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
    Cmd.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
    Cmd.ModeRegisterDefinition = tmpModeReg;
    status = HAL_SDRAM_SendCommand(&hSDRAM, &Cmd, 0x1000);
    
    return status;
} /* end SDRAM_InitSquence() */

/**
 * @brief  SDRAM��ʼ��
 * @param  None
 * @retval None
 */
HAL_StatusTypeDef SDRAM_Init(void)
{
    FMC_SDRAM_TimingTypeDef FMC_SDRAM_TimingStruct;
    HAL_StatusTypeDef status;

    /* step1:�����ʼ�� */
    hSDRAM.Instance = FMC_SDRAM_DEVICE;
    hSDRAM.Init.SDBank = FMC_SDRAM_BANK1;
    hSDRAM.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9; // ������
    hSDRAM.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13;      // ������
    hSDRAM.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;   // ���ݿ��
    hSDRAM.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
    hSDRAM.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3; // �е�ַѡͨ��ʱ�����Ͷ�ȡ����֮����ʱ3��ʱ�����ڣ����ݶ˿�������Ч��
    hSDRAM.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
    hSDRAM.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_3; // SDRAMʱ������ΪHCLK/3=180M/3=60M��16.7ns
    hSDRAM.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
    hSDRAM.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1; // ��ͨ����ʱ

    FMC_SDRAM_TimingStruct.LoadToActiveDelay = 2;
    FMC_SDRAM_TimingStruct.ExitSelfRefreshDelay = 8; // �˳���ˢ��ģʽ��ʱ8������
    FMC_SDRAM_TimingStruct.SelfRefreshTime = 6;      // ��ˢ������
    FMC_SDRAM_TimingStruct.RowCycleDelay = 7;
    FMC_SDRAM_TimingStruct.WriteRecoveryTime = 4;
    FMC_SDRAM_TimingStruct.RPDelay = 2;
    FMC_SDRAM_TimingStruct.RCDDelay = 2;

    if(HAL_SDRAM_Init(&hSDRAM, &FMC_SDRAM_TimingStruct) != HAL_OK)
    {
        char tmp[] = "\r\nSDRAM Init Error\r\n";
        RS232A_SendBytes((uint8_t *)tmp, sizeof(tmp), 1000);
        for(;;)
        {
            ;
        }
    }
    
    {
    char tmp[] = "\r\nSDRAM Init OK\r\n";
    RS232A_SendBytes((uint8_t *)tmp, sizeof(tmp), 1000);
    }

    /* step2:SDRAM��ʼ�� */
    status = SDRAM_InitSquence(&hSDRAM);

    /* step3:����ˢ��Ƶ�� */
    HAL_SDRAM_ProgramRefreshRate(&hSDRAM, 214);

    return status;
} /* end SDRAM_Init() */

