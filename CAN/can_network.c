/*
*********************************************************************************************************
*	                                  
*	ģ������ : CAN����ͨ�ų���
*	�ļ����� : can_network.c
*	��    �� : V1.0.1
*	˵    �� : ʵ�ֶ��CAN�ڵ㣨�ڵ�ĳ�����ͬ��֮���ͨ�š�
*	�޸ļ�¼ :
*		�汾��       ����       ����    ˵��
*		V1.0.1   2017-11-02    ���˼�  ST�̼���V3.5.0�汾��
*
*	Copyright (C), 2017-2020, ���˼� �Ա���ַshop148504253.taobao.com
*
*********************************************************************************************************
*/

/*
	һ��Ӧ�ò�Э��:���Զ����Э�飩	
	
       ��� �����루1�ֽڣ�+ ����ʼ��ַ��2�ֽ�)��+ ���ֽ�����1�ֽ�)��+ [����]��N�ֽڣ�+ У�飨2�ֽڣ�
							 ������   0x03 ��  ����ַ0xFFFF��CAN�ӻ�����������Ĵ���������
											  0x10 д	
*/

#include <string.h>
//#include "stm32f10x_can.h"
#include "can_network.h"
#include "PLC_Dialogue.h"
#include "bsp_user_lib.h"

/********HAL*********/
#include "can.h"
/******end HAL******/

#if CAN_FUNC

/* ����ȫ�ֱ��� */
//CanTxMsg g_tCanTxMsg;	/* ���ڷ��� */
//CanRxMsg g_tCanRxMsg;	/* ���ڽ��� */
uint8_t g_ucLedNo = 0;	/* ������LED����ţ�0-3 */


// canӦ��
sCanComm canComm;



/* �������ļ��ڵ��õĺ������� */
static void can_NVIC_Config(void);

/**********************************************************************************************************
*	�� �� ��: can_Init
*	����˵��: ����CANӲ��
*	��    �Σ���
*	�� �� ֵ: ��
* ���ߣ� ���˼� �Ա���ַshop148504253.taobao.com
**********************************************************************************************************/
void can_Init(void)
{
	// GPIO_InitTypeDef GPIO_InitStructure;
	// CAN_InitTypeDef CAN_InitStructure;
	// CAN_FilterInitTypeDef CAN_FilterInitStructure;	
		
	// /* PB8��PB9��������ΪAFIOģʽ, �л���CAN���� */
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	// /* ʹ��GPIOʱ�� */
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// /* ����CAN�źŽ�������: RX */
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	/* GPIO����Ϊ��������ģʽ */
	// GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// /* ����CAN�źŷ�������: TX */
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		/* ����Ϊ����������� */
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	/* ����GPIO����ٶ� */
	// GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// /* ԭ����CAN���ź�USB��������ͬ�Ŀ��ߣ�������������ʹ�����ŵ���ӳ�书�ܽ�CAN�����л���PB8��PB9 */
	// GPIO_PinRemapConfig(GPIO_Remap1_CAN1 , ENABLE);	/* ʹ��CAN1����ӳ�� */
	
	// /* ʹ��CAN����ʱ�� */
	// RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	// CAN_DeInit(CAN1);						/* ��λCAN�Ĵ��� */
	// CAN_StructInit(&CAN_InitStructure);		/* ���CAN�����ṹ���ԱΪȱʡֵ */
	
	// /*
	// 	TTCM = time triggered communication mode
	// 	ABOM = automatic bus-off management 
	// 	AWUM = automatic wake-up mode
	// 	NART = no automatic retransmission
	// 	RFLM = receive FIFO locked mode 
	// 	TXFP = transmit FIFO priority		
	// */
	// CAN_InitStructure.CAN_TTCM = DISABLE;			/* ��ֹʱ�䴥��ģʽ��������ʱ���), T  */
	// CAN_InitStructure.CAN_ABOM = DISABLE;			/* ��ֹ�Զ����߹رչ��� */
	// CAN_InitStructure.CAN_AWUM = DISABLE;			/* ��ֹ�Զ�����ģʽ */
	// CAN_InitStructure.CAN_NART = DISABLE;			/* ��ֹ�ٲö�ʧ��������Զ��ش����� */
	// CAN_InitStructure.CAN_RFLM = DISABLE;			/* ��ֹ����FIFO����ģʽ */
	// CAN_InitStructure.CAN_TXFP = DISABLE;			/* ��ֹ����FIFO���ȼ� */
	// CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;	/* ����CANΪ��������ģʽ */
	
	// /* 
	// 	CAN ������ = RCC_APB1Periph_CAN / Prescaler / (SJW + BS1 + BS2);
		
	// 	SJW = synchronisation_jump_width 
	// 	BS = bit_segment
		
	// 	�����У�����CAN������Ϊ500Kbps		
	// 	CAN ������ = 360000000 / 6 / (1 + 6 + 5) / = 500kHz		
	// */
	
	// CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	// CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
	// CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
	// CAN_InitStructure.CAN_Prescaler = 6;
	// CAN_Init(CAN1, &CAN_InitStructure);
	
	// /* ����CAN�˲���0 */
	// CAN_FilterInitStructure.CAN_FilterNumber = 0;		                  /* �˲�����ţ�0-13����14���˲��� */
	// CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;		/* �˲���ģʽ������ID����ģʽ */
	// CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;	/* 32λ�˲� */
	// CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;					      /* Ҫ���˵�ID��16bit */
	// CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;					        /* Ҫ���˵�ID��16bit */
	
	// /* λΪ0��ζ���յ�������֡�е���Ӧλ��ID��һ����Ҫ�����õ�IDһ���� */
	// CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;				    /* ID����ֵ��16bit */
	// CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;				      /* ID����ֵ��16bit */
	// CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;		  /* �˲�����FIFO 0 */
	// CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;				    /* ʹ���˲��� */
	// CAN_FilterInit(&CAN_FilterInitStructure);
	
	// /* �˴���ʱ������ */	

	// can_NVIC_Config();		/* ����CAN�ж� */	
  
  /********************HAL***********************/
  CANx_Init();
  /******************end HAL ********************/
}     

/**********************************************************************************************************
*	�� �� ��: can_DeInit
*	����˵��: �˳�CANӲ��Ӳ�ʣ��ָ�CPU��ص�GPIOΪȱʡ���ر�CAN�ж�
*	��    �Σ���
*	�� �� ֵ: ��
* ���ߣ� ���˼� �Ա���ַshop148504253.taobao.com
**********************************************************************************************************/
void can_DeInit(void)
{
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, DISABLE);	/* �ر�CAN1ʱ�� */

//	{
//		NVIC_InitTypeDef  NVIC_InitStructure;
//		
//		NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
//		NVIC_Init(&NVIC_InitStructure);
//	
//		/* CAN FIFO0 ��Ϣ�����ж�ʹ�� */ 
//		CAN_ITConfig(CAN1, CAN_IT_FMP0, DISABLE);	
//	}
}

/**********************************************************************************************************
*	�� �� ��: can_NVIC_Config
*	����˵��: ����CAN�ж�
*	��    �Σ���
*	�� �� ֵ: ��
* ���ߣ� ���˼� �Ա���ַshop148504253.taobao.com
**********************************************************************************************************/  
static void can_NVIC_Config(void)
{
//	NVIC_InitTypeDef  NVIC_InitStructure;
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//	
//	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
//	/* CAN FIFO0 ��Ϣ�����ж�ʹ�� */ 
//	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);	
}

/**********************************************************************************************************
*	�� �� ��: can_ISR
*	����˵��: CAN�жϷ������. ��������� stm32f10x_it.c�б�����
*	��    �Σ���
*	�� �� ֵ: ��
* ���ߣ� ���˼� �Ա���ַshop148504253.taobao.com
**********************************************************************************************************/ 
void can_ISR(void)
{
//	CAN_Receive(CAN1, CAN_FIFO0, &g_tCanRxMsg);
//	
//	if(canComm.localDevAddr ==0) // ����
//		canComm.currDevAddr = canComm.slaveCnt;
//	else // �ӻ�
//		canComm.currDevAddr =  canComm.localDevAddr;
//	
//	/* �޽�����ɵ����ݴ����ҵ�ַ����׼֡�����ȶ���Գɹ� */
//	if ( (canComm.rxFlg !=2)&&(g_tCanRxMsg.StdId == canComm.currDevAddr) && (g_tCanRxMsg.IDE == CAN_ID_STD) && (0 < g_tCanRxMsg.DLC))
//	{
//     memcpy((uint8_t *)&canComm.rxBuf[canComm.rxCnt], g_tCanRxMsg.Data, g_tCanRxMsg.DLC);
//		 canComm.rxCnt +=g_tCanRxMsg.DLC; // �������ݳ����ۼ�
//		 if (CAN_BUF_LEN <= canComm.rxCnt) // ����
//       canComm.rxCnt = 0;
//		
//		 canComm.rxTimeout =1; // �����ȴ�
//		 canComm.rxFlg =1;     // ����ѽ��յ�����		 
//		 
//		 canComm.txTimeout =0; // ��ֹ���ͳ�ʱ��ʱ
//		
//	} 
//	else
//	{
//	   CAN_FIFORelease(CAN1, CAN_FIFO0);	
//	}
}

/**********************************************************************************************************
*	�� �� ��: USB_LP_CAN1_RX0_IRQHandler
*	����˵��: CAN�жϷ������. ��������� stm32f10x_it.c�б�����
*	��    �Σ���
*	�� �� ֵ: ��
* ���ߣ� ���˼� �Ա���ַshop148504253.taobao.com
**********************************************************************************************************/ 
#if 0		// �˺����ŵ� stm32f10x_it.c , USB�жϺ�CAN����
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	can_ISR();
}
#endif


/**********************************************************************************************************
*	�� �� ��: can_SendPacket
*	����˵��: ����һ������
*	��    �Σ�_DataBuf ���ݻ�����
*			  _Len ���ݳ���, 0-8�ֽ�
*	�� �� ֵ: ��
* ���ߣ� ���˼� �Ա���ַshop148504253.taobao.com
**********************************************************************************************************/
void CAN_SendPacket(uint8_t _addr,uint8_t *_DataBuf, uint8_t _Len)
{		
		/* ��䷢�Ͳ����� Ҳ������ÿ�η��͵�ʱ���� */
//		g_tCanTxMsg.StdId = _addr;      // ��׼֡ID,���Ҫ������չ֡�����Բ�����
//		g_tCanTxMsg.ExtId = 0x0;        // ��չ֡ID,���Ҫ���ͱ�׼֡�����Բ�����
//		g_tCanTxMsg.RTR = CAN_RTR_DATA; // ����֡��Զ��֡
//		g_tCanTxMsg.IDE = CAN_ID_STD;   // ��׼֡����չ֡
//		g_tCanTxMsg.DLC = _Len;
//						
//    memcpy(g_tCanTxMsg.Data, _DataBuf, _Len);
//    CAN_Transmit(CAN1, &g_tCanTxMsg);	
}

/**********************************************************************************************************
*	�� �� ��: CAN_GetInfo
*	����˵��: ��ȡ��Ϣ����¼��CAN�ӻ�����������Ĵ���������
*	��    �Σ�_addr �豸��ַ 0 ��ʾ�㲥��
*	�� �� ֵ: ��
* ��ע��
				��� �����루1�ֽڣ�+ ����ʼ��ַ��2�ֽ�)��+ ���ֽ�����1�ֽ�)��+ �����ݡ���N�ֽڣ� + У�飨2�ֽڣ�
							 ������   0x03 ��  ����ַ0xFFFF��CAN�ӻ�����������Ĵ���������
											  0x10 д								
* ���ߣ� ���˼� �Ա���ַshop148504253.taobao.com				
**********************************************************************************************************/
void CAN_GetInfo(uint8_t _addr)
{		
//	/* ��䷢�Ͳ����� Ҳ������ÿ�η��͵�ʱ���� */
//	g_tCanTxMsg.StdId = _addr;
//	g_tCanTxMsg.ExtId = 0x0;
//	g_tCanTxMsg.RTR = CAN_RTR_DATA;
//	g_tCanTxMsg.IDE = CAN_ID_STD;
//	
//	g_tCanTxMsg.DLC = 6; 						
//	g_tCanTxMsg.Data[0] = 0x03;
//	ACCESS_U16(g_tCanTxMsg.Data[1]) = 0xFFFF;
//	g_tCanTxMsg.Data[3] = g_tCanTxMsg.DLC;
//	ACCESS_U16(g_tCanTxMsg.Data[4]) = CRC16_Modbus(g_tCanTxMsg.Data, g_tCanTxMsg.DLC - 2);		
//  CAN_Transmit(CAN1, &g_tCanTxMsg);	
//	
//	canComm.txTimeout =1; // �������ͳ�ʱ����
//	canComm.txFlg =0; // ��ֹ����
//	canComm.retryFlg =0;
//	
//	// ��������
//	canComm.rxCnt =0;
//	canComm.rxTimeout =0;
//	canComm.rxFlg =0;
}

/**********************************************************************************************************
*	�� �� ��: CAN_GetShareRegData
*	����˵��: ��ȡ���ݣ�����Ĵ�����
*	��    �Σ�_addr �豸��ַ 0 ��ʾ�㲥�ģ�
*	�� �� ֵ: ��
* ��ע��
				��� �����루1�ֽڣ�+ ����ʼ��ַ��2�ֽ�)��+ ���ֽ�����1�ֽ�)��+ �����ݡ���N�ֽڣ� + У�飨2�ֽڣ�
							 ������   0x03 ��  ����ַ0xFFFF��CAN�ӻ�����������Ĵ���������
											  0x10 д		
* ���ߣ� ���˼� �Ա���ַshop148504253.taobao.com
**********************************************************************************************************/
void CAN_GetShareRegData(uint8_t _addr)
{		
//	/* ��䷢�Ͳ����� Ҳ������ÿ�η��͵�ʱ���� */
//	uint16_t shareRegStartIndex =CAN_SHARED_REG_START_INDEX + CAN_UNIT_NUM * _addr;	
//	
//	g_tCanTxMsg.StdId = _addr;
//	g_tCanTxMsg.ExtId = 0x0;
//	g_tCanTxMsg.RTR = CAN_RTR_DATA;
//	g_tCanTxMsg.IDE = CAN_ID_STD;	
//	g_tCanTxMsg.DLC = 7; 
//	
//	g_tCanTxMsg.Data[0] = 0x03;
//	ACCESS_U16(g_tCanTxMsg.Data[1]) = shareRegStartIndex;
//	g_tCanTxMsg.Data[3] = g_tCanTxMsg.DLC;
//	g_tCanTxMsg.Data[4] = canComm.shareRegNum[_addr];
//	ACCESS_U16(g_tCanTxMsg.Data[5]) = CRC16_Modbus(g_tCanTxMsg.Data, g_tCanTxMsg.DLC-2);	
//  CAN_Transmit(CAN1, &g_tCanTxMsg);
//	
//	canComm.txTimeout =1; // �������ͳ�ʱ����
//	canComm.txFlg =0; // ��ֹ����
//	canComm.retryFlg =0; 
//	
//	// ��������
//	canComm.rxCnt =0;
//	canComm.rxTimeout =0;
//	canComm.rxFlg =0;	
}

/* ��ʱ */
void SimpleDelay(uint16_t value)
{
  uint16_t i,j;
	for(i=0;i < value;i++)
	  for(j=0;j <1000; j++);
}

/**********************************************************************************************************
*	�� �� ��: CAN_WriteShareRegData
*	����˵��: ����ͨ�Ŷ�����Ĺ���Ĵ�����
*	��    �Σ�_addr �豸��ַ 0 ��ʾ�㲥��
*			  _led_no �� LEDָʾ�����
*	�� �� ֵ: ��
* ��ע:
       ��� �����루1�ֽڣ�+ ����ʼ��ַ��2�ֽ�)��+ ���ֽ�����1�ֽ�)��+ [����]��N�ֽڣ�+ У�飨2�ֽڣ�
							 ������   0x03 ��  ����ַ0xFFFF��CAN�ӻ�����������Ĵ���������
											  0x10 д		
* ���ߣ� ���˼� �Ա���ַshop148504253.taobao.com
**********************************************************************************************************/
void CAN_ReplyShareRegData(uint8_t _addr)
{		
		static uint8_t mod =0;	
		uint8_t bytes =0;
		uint8_t i=0;
	 	if(canComm.retryFlg ==0) // ���ط�ʱ����
		{		
				uint16_t shareRegStartIndex =CAN_SHARED_REG_START_INDEX + CAN_UNIT_NUM * _addr;	
			
				canComm.txBuf[0] = 0x03; // �����룺д��1���ֽڣ�		
				ACCESS_U16(canComm.txBuf[1]) = shareRegStartIndex; // ��ʼ��ַ��2���ֽڣ�
				canComm.txCnt = 7 + (canComm.shareRegNum[_addr] <<1); // 6 = �����루1��+ ��ʼ��ַ��2�� + �ֽ�����1�� + CRC(2) + �������ݣ�1��			
				canComm.txBuf[3] = canComm.txCnt; // �ֽ�����1���ֽڣ�	
				// ����
				canComm.txBuf[4] = canComm.shareRegNum[_addr]; // ����ӻ������ݷ��ദ��   			
				memcpy((uint8_t *)&canComm.txBuf[5], (uint8_t *)&plc_16BitBuf[shareRegStartIndex], canComm.shareRegNum[_addr] <<1);		
				ACCESS_U16(canComm.txBuf[canComm.txCnt - 2])= CRC16_Modbus(canComm.txBuf, canComm.txCnt - 2);		
				 
				mod = canComm.txCnt % 8;
				canComm.totalPacket = (mod)? (canComm.txCnt/8 +1) : (canComm.txCnt/8);		
	  }	
		
		while(i < canComm.totalPacket)
		{
				if(((i+1) == canComm.totalPacket) && (mod)) // ���һ�����Ҳ���8�ֽ�
					bytes = mod;
				else
					bytes =8;
				CAN_SendPacket(_addr,(uint8_t *)&canComm.txBuf[i << 3],bytes);
				i++;				
				SimpleDelay(2);
		}			
							
		canComm.txFlg =0; // ��ֹ����(�����������)
		canComm.txTimeout =0; // ֹͣ���ͳ�ʱ��ʱ
		canComm.retryFlg =0;
		canComm.processFlg =2; // ��3�����ȴ����������·��Ǳ���Ĺ���Ĵ�����	
		// ��������
		canComm.rxCnt =0;
		canComm.rxTimeout =0;
    canComm.rxFlg =0;		
}


/**********************************************************************************************************
*	�� �� ��: CAN_WriteShareRegData
*	����˵��: �������ͷ�ͨ�Ŷ�����Ĺ���Ĵ�����
*	��    �Σ�_addr �豸��ַ 0 ��ʾ�㲥��
*			  _led_no �� LEDָʾ�����
*	�� �� ֵ: ��
* ��ע:
       ��� �����루1�ֽڣ�+ ����ʼ��ַ��2�ֽ�)��+ ���ֽ�����1�ֽ�)��+ [����]��N�ֽڣ�+ У�飨2�ֽڣ�
							 ������   0x03 ��  ����ַ0xFFFF��CAN�ӻ�����������Ĵ���������
											  0x10 д	
* ���ߣ� ���˼� �Ա���ַshop148504253.taobao.com
**********************************************************************************************************/
void CAN_WriteShareRegData(uint8_t _addr)
{		
	  uint8_t i=0;
		static uint8_t mod = 0;	
		static uint8_t bytes =0;
	  uint16_t shareRegStartIndex;
	
		if(canComm.retryFlg ==0) // ���ط�ʱ����
		{
			if(canComm.rxFlg == 5) // �������ݳɹ� 
			{
				 canComm.loop++;
				 if(_addr == canComm.loop) // _addr����Ĺ���Ĵ��������·�
					 canComm.loop +=1;
				 if( canComm.slaveNum < canComm.loop ) // ˵��һ����д����
				 {
						canComm.loop =0; // ���й���Ĵ������ݷ�����ɣ�				
						canComm.processFlg =0; // 3����������ȫ����ɣ����´�����1��ʼ							 
						canComm.txTimeout =0; // ��ֹ���ͳ�ʱ��ʱ
						canComm.txFlg =1; // �������� 					 
						return;							 
				 }
		  }			
	
			shareRegStartIndex =CAN_SHARED_REG_START_INDEX + CAN_UNIT_NUM * canComm.loop;			
			canComm.txBuf[0] = 0x10; // �����룺д��1���ֽڣ�		
			ACCESS_U16(canComm.txBuf[1]) = shareRegStartIndex; // ��ʼ��ַ��2���ֽڣ�
			canComm.txCnt = 7 + (canComm.shareRegNum[canComm.loop] <<1); // 6 = �����루1��+ ��ʼ��ַ��2�� + �ֽ�����1�� + CRC(2) + �������ݣ�1��			
			canComm.txBuf[3] = canComm.txCnt; // �ֽ�����1���ֽڣ�	
			// ����
			canComm.txBuf[4] = canComm.shareRegNum[canComm.loop] ; // ����ӻ������ݷ��ദ��   			
			memcpy((uint8_t *)&canComm.txBuf[5], (uint8_t *)&plc_16BitBuf[shareRegStartIndex], canComm.shareRegNum[canComm.loop] <<1);		
			ACCESS_U16(canComm.txBuf[canComm.txCnt - 2])= CRC16_Modbus(canComm.txBuf, canComm.txCnt - 2);		
			 
			mod = canComm.txCnt % 8;
			canComm.totalPacket = (mod)? (canComm.txCnt/8 +1) : (canComm.txCnt/8);
	  }
		
		while(i < canComm.totalPacket)
		{
				if(((i+1) == canComm.totalPacket) && (mod)) // ���һ�����Ҳ���8�ֽ�
					bytes = mod;
				else
					bytes =8;
				CAN_SendPacket(_addr,(uint8_t *)&canComm.txBuf[i << 3],bytes);
				i++;
				SimpleDelay(2);
		}		
		 
		canComm.txTimeout =1; // �������ͳ�ʱ����
		canComm.txFlg =0; // ��ֹ����
		canComm.retryFlg =0;
		
		// ��������
		canComm.rxCnt =0;
		canComm.rxTimeout =0;	
		canComm.rxFlg =0;
}


/**********************************************************************************************************
*	�� �� ��: CAN_Reply
*	����˵��: ���ӻ�Ӧ��
*	��    �Σ�_addr �豸��ַ 0 ��ʾ�㲥��
*	�� �� ֵ: ��
* ��ע��
				��� �����루1�ֽڣ�+ ����ʼ��ַ��2�ֽ�)��+ ���ֽ�����1�ֽ�)��+ �����ݡ���N�ֽڣ� + У�飨2�ֽڣ�
							 ������   0x03 ��  ����ַ0xFFFF��CAN�ӻ�����������Ĵ���������
											  0x10 д								
* ���ߣ� ���˼� �Ա���ַshop148504253.taobao.com				
**********************************************************************************************************/
void CAN_Reply(uint8_t _addr,uint8_t _cmd,uint16_t _startAddr,uint16_t _state)
{		
//	/* ��䷢�Ͳ����� Ҳ������ÿ�η��͵�ʱ���� */
//	g_tCanTxMsg.StdId = _addr;
//	g_tCanTxMsg.ExtId = 0x0;
//	g_tCanTxMsg.RTR = CAN_RTR_DATA;
//	g_tCanTxMsg.IDE = CAN_ID_STD;
//	
//	g_tCanTxMsg.DLC = 8; 						
//	g_tCanTxMsg.Data[0] = _cmd;
//	ACCESS_U16(g_tCanTxMsg.Data[1]) = _startAddr;
//	g_tCanTxMsg.Data[3] = g_tCanTxMsg.DLC;
//	ACCESS_U16(g_tCanTxMsg.Data[4]) = _state;
//	ACCESS_U16(g_tCanTxMsg.Data[6]) = CRC16_Modbus(g_tCanTxMsg.Data, g_tCanTxMsg.DLC - 2);
//		
//  CAN_Transmit(CAN1, &g_tCanTxMsg);	
//	
////	canComm.txTimeout =1; // �������ͳ�ʱ����
//	canComm.txFlg =0; // ��ֹ����
//	canComm.retryFlg =0;
//	
//	// ��ֹ���ճ�ʱ��ʱ
//	canComm.rxTimeout =0;
//	canComm.rxFlg =0;
}

/* �������ݴ��� */
void RevDataDeal(void)
{
		/* �ѽ������ݲ��ҵ��ν���ʱ�䵽 */
		if ((canComm.rxFlg ==1) && (canComm.setRxTimeoutValue < canComm.rxTimeout))
		{		
			  uint16_t crc;
			  canComm.rxTimeout =0; // ֹͣ���ճ�ʱ��ʱ
        canComm.txFlg =0; // ��ֹ����
			  canComm.rxFlg = 2;// ��Ǳ������ݽ�����ɣ����ڴ���������ݣ���ע���ڴ�������յ�������Ч  
			
				crc = CRC16_Modbus(canComm.rxBuf, canComm.rxCnt - 2);
				if( crc != ACCESS_U16(canComm.rxBuf[canComm.rxCnt - 2]) )
				{ // CRCУ�����
						canComm.devErr = crcErr;
						goto label;
				}	

				// ���ݳ���ƥ��
				if(canComm.rxCnt != canComm.rxBuf[3])
				{ // ������Ч				
						canComm.devErr = revLenErr;	
						goto label;
				}

				if(canComm.rxBuf[0] == 0x03) // ��
				{				
						// ��ʼ��ַƥ��
						if(ACCESS_U16(canComm.rxBuf[1]) == 0xFFFF) // ��ȡ��Ϣ������Ĵ���������
						{
								if(canComm.localDevAddr ==0) // ����
								{		
										canComm.shareRegNum[canComm.slaveCnt] = canComm.rxBuf[4]; // ����Ĵ�������		
										canComm.processFlg =1;	// ��ȡ���ݣ�����Ĵ�����
								}
								else 
								{// �ӻ�
										canComm.processFlg =0;	// ��ǽ���ظ���Ϣ������Ĵ���������						
								}
								canComm.rxFlg =3; // �������ݳɹ� 					
						}
						else
						{ // ��ȡ���ݣ�����Ĵ�����								
								uint16_t shareRegStartIndex = ACCESS_U16(canComm.rxBuf[1]);							
								if( ( shareRegStartIndex < CAN_SHARED_REG_START_INDEX) &&  ( CAN_SHARED_REG_END_INDEX < shareRegStartIndex)  ) // ����Ĵ��������ж�
								{ // ��Ч
										canComm.devErr = accessSharedRegErr;	
										goto label;
								}
								else
								{       
										if(canComm.localDevAddr ==0) // ����
										{											
												memcpy( (uint8_t *)&plc_16BitBuf[shareRegStartIndex],(uint8_t *)&canComm.rxBuf[5],canComm.rxBuf[4] << 1 ); // ����Ĵ�����ֵ
												canComm.processFlg =2; // �·�����	������Ĵ���)

												canComm.loop =0;									
										}
										else
										{ // �ӻ�
												// �ϴ�����Ĵ�������
												canComm.processFlg =1; // ��ǽ����ϴ�����Ĵ������� 											
										}
										canComm.rxFlg =4; // �������ݳɹ� 		
								}								
						}				
				}
				else if(canComm.rxBuf[0] == 0x10) // д
				{
						uint16_t shareRegStartIndex = ACCESS_U16(canComm.rxBuf[1]);							
						if( ( shareRegStartIndex < CAN_SHARED_REG_START_INDEX) &&  ( CAN_SHARED_REG_END_INDEX < shareRegStartIndex)  ) // ����Ĵ��������ж�
						{ // ��Ч
								canComm.devErr = accessSharedRegErr;	
						    goto label;
						}
						else
						{
								if(canComm.localDevAddr ==0) // ����
								{		
										if(ACCESS_U16(canComm.rxBuf[4])) // ����
												canComm.devErr =ackErr;										   
                    else 
											 canComm.rxFlg =5; // �������ݳɹ� 
								}
								else
								{ // �ӻ�                   									
										memcpy( (uint8_t *)&plc_16BitBuf[shareRegStartIndex],(uint8_t *)&canComm.rxBuf[5],canComm.rxBuf[4] << 1 ); // ����Ĵ�����ֵ
										canComm.processFlg =2; // ��ǽ���Ӧ������ �·�����	������Ĵ������ɹ�
									  canComm.rxFlg =5; // �������ݳɹ� 
								}
		
						}
				}
label: 
    		canComm.rxCnt =0;
        if(canComm.devErr ==0)
        {			  
            canComm.txTimeout =0;					
				}
        else
        { // ����
				  canComm.rxFlg =0;
				}					
				
		}
}

/**********************************************************************************************************
*	�� �� ��: CAN_Poll
*	����˵��: CAN���ܴ�����ڣ����������дӻ��Ĺ���Ĵ������๲��ÿվ���ɹ���32���Ĵ���
*	��    �Σ���
*	�� �� ֵ: ��
* ��ע��
				֡��ʽ�� �����루1�ֽڣ�+ ����ʼ��ַ��2�ֽ�)��+ ���ֽ�����1�ֽ�)��+ �����ݡ���N�ֽڣ�+ У�飨2�ֽڣ�
							   �����룺0x03����0x10д
* ���ߣ� ���˼� �Ա���ַshop148504253.taobao.com
**********************************************************************************************************/
void CAN_Poll(void)
{			
	  static uint8_t initFlg =0;	
	  if(PLC_BIT_TEST(CAN_EN_FLG)) // �ж�CAN�����Ƿ���
		{			
			if(initFlg ==0)
			{ // �����ʼ��
					initFlg =1;
					memset(&canComm, 0, sizeof(canComm)); // ���� 
				
					/* �豸ͨѶ��ַ */
					if(CAN_CH_MAX < CAN_ADDR)
					{ // ���õ�ͨ�ŵ�ַ��Ч
						CAN_COMM_ERR = slaveAddrErr;
						return;
					}	
					else
					{
						canComm.localDevAddr = CAN_ADDR;
					}
//			    canComm.localDevAddr =0; // test m
				
				  /* Ĭ��ֵ */
					if(canComm.localDevAddr ==0) // ��������
					{
						canComm.txFlg =1; 
						canComm.slaveNum =1;
					}				
					canComm.shareRegNum[canComm.localDevAddr] =8;
					canComm.setRxTimeoutValue = 10;	
          canComm.setTxTimeoutValue = 100;					
			}
			////////////////////////////////////////////////////////////////////////
			/* �ӻ�����,������ */
			if(canComm.localDevAddr ==0)
			{
				if(CAN_CH_MAX < CAN_SAVLE_NUM)
				{ // ���ôӻ�������Ч
					CAN_COMM_ERR = slaveNumErr;
					return;
				}	
				else
				{
					canComm.slaveNum = CAN_SAVLE_NUM;
				}			
			}
			
			/* ����Ĵ������� */
			if(CAN_UNIT_NUM < CAN_SHARE_REG_NUM)
			{
				CAN_COMM_ERR = shareRegNumErr;
        return;		
			}
			else
			{
			  canComm.shareRegNum[canComm.localDevAddr] =  CAN_SHARE_REG_NUM; // ��������Ĵ�������
			}			
			
			/* ͨѶ��ʱ */
			if(CAN_COMM_TIMEOUT_PARM < 100)
			{ // ���õ�ͨѶ��ʱ����������Ч��Χ��
				CAN_COMM_ERR = timeoutParmErr;
        return;				
			}	
			else
			{
				canComm.setTxTimeoutValue = CAN_COMM_TIMEOUT_PARM;
			}
	
			////////////////////////////////////////////////////////////////////////
			// �������ݴ���
			RevDataDeal(); 
			
			/* ���ͳ�ʱ���� */
			if( canComm.setTxTimeoutValue < canComm.txTimeout)
			{
				 canComm.txTimeout =0;
				 canComm.devErr = sendErr;
			}
			
			if(canComm.devErr) // ����
			{		
				  CAN_COMM_ERR = canComm.devErr;
					canComm.devErr =0;	
					if((++canComm.retryCnt) <6) // ����6��
					{
							canComm.retryFlg =1; // �������
					}
					else // �����ط�
					{
							canComm.retryCnt =0;
							canComm.retryFlg =0;
						
							canComm.processFlg =0;
						  canComm.txFlg =1;
					}					 
			}
			else
			{ // �޳���
					canComm.retryCnt =0;
					canComm.retryFlg =0;	
			}	
			
			/* �������ݳɹ����� ������������ ���� ��������*/
			if( ((0 < (canComm.rxFlg - 2)) || (canComm.txFlg == 1)) || (canComm.retryFlg == 1)) 
			{		
				if(canComm.localDevAddr ==0) // ����	
				{					
						// ����ͨѶ��ַ�ۼ� 
						if( (canComm.retryFlg ==0) && (canComm.processFlg ==0))
						{			 
							 if( canComm.slaveNum < (++canComm.slaveCnt))
									canComm.slaveCnt =1;  
						}
						 //////////////////////////////////////////////////////////////////////////////////
						 // �������͹�������
						 switch (canComm.processFlg)
						 {
								case 0: // 1����ȡ��Ϣ����¼��CAN�ӻ�����������Ĵ���������
								{
									 CAN_GetInfo(canComm.slaveCnt);										
									 break;
								}
								case 1: // 2����ȡ���ݣ�����Ĵ�����
								{
									 CAN_GetShareRegData(canComm.slaveCnt); 
									 break;
								}
								case 2: // 3���·�����	������Ĵ�����
								{
									 CAN_WriteShareRegData(canComm.slaveCnt);
									 break;
								}
						 }
				 }
				 else // �ӻ�
				 { 
						 switch (canComm.processFlg)
						 {
								case 0: // 0���ظ���Ϣ������Ĵ���������
								{
										CAN_Reply(canComm.localDevAddr, canComm.rxBuf[0],ACCESS_U16(canComm.rxBuf[1]),canComm.shareRegNum[canComm.localDevAddr]);
										break;
								}
								case 1: // 1���ظ����ݣ�����Ĵ�����
								{
										CAN_ReplyShareRegData(canComm.localDevAddr); // ������������
										break;
								}
								case 2: // 2��Ӧ������ �·�����	������Ĵ�����
								{
										CAN_Reply(canComm.localDevAddr, canComm.rxBuf[0],ACCESS_U16(canComm.rxBuf[1]),canComm.devErr);
										break;
								}
						 }
					}
			}
	 }
   else
   {
	    initFlg =0;
	 }		 
}
#endif /* #if CAN_FUNC */


/***************************** ���˼� �Ա���ַshop148504253.taobao.com (END OF FILE) *********************************/


