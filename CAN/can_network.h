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
*	Copyright (C), 2017-2020, ���˼� shop148504253.taobao.com
*
*********************************************************************************************************
*/

#ifndef _CAN_NETWORK_H
#define _CAN_NETWORK_H

#include "plc_conf.h"

#if CAN_FUNC

/*�궨��----------------------------------------*/
#define ACCESS_U16(x)              (*(u16*)&x) 
#define CAN_BUF_LEN                 128

/* �Ĵ�����̵���˵�� */
// �ݲ�ʵ��
// M8149 ͨѶ��ʱ��־��CAN ����ͨѶ���ϻ�ʱ��־���ñ�־ ON ����Ҫ�ڳ������ֶ� OFF��  ��ע��ʹ��D8063���
// D8153-ͨѶ�����ʣ�20K~1000K��Ĭ�� 250K��
// D8196-ͨѶ���ϵĴӻ���1~16�� 
// D8197-ͨѶ���ϵĴӻ��� 17~32 ��
// D8198-ͨѶ���ϵĴӻ����ܣ�1~16�� 
// D8199-ͨѶ���ϵĴӻ����ܣ� 17~32 ��
// D8200-��ӻ�ͨѶ�ɹ�һ�ε����ʱ�䣨1=1ms��


#define CAN_EN_FLG	            M8150  // CAN ������

#define CAN_COMM_TIMEOUT_PARM	  D8149  // ͨѶ��ʱ������1=1ms��Ĭ�� 100ms�� 
#define CAN_ADDR	              D8150  // �������ߴӻ���ַ���ã�0������1~32�ӻ���
#define CAN_SAVLE_NUM	          D8151  // �ӻ�������1~32������ʱ֧��CAN_CH_MAX��
#define CAN_SHARE_REG_NUM	      D8152  // ����ļĴ���������1~32��Ĭ�� 8��

#define CAN_COMM_ERR	          D8063  // ��Ŵ������

/* ��/�ӻ����๲��ļĴ����б�(�ݶ�9����Ԫ) */
#define CAN_REG_D_START_ADDR 		         4096   // D�Ĵ�����ʼ��ַ
#define CAN_REG_D_END_ADDR 		           12096  // D�Ĵ���������ַ

#define CAN_CH_MAX                        8  // ֧�ִӻ�������
#define CAN_UNIT_NUM	                    32  // ����Ĵ������������
#define CAN_SHARED_REG_START_INDEX	      (CAN_REG_D_START_ADDR + 1000)                             // ��������Ĵ�����ʼ
#define CAN_SHARED_REG_END_INDEX	        (CAN_SHARED_REG_START_INDEX + CAN_UNIT_NUM * CAN_CH_MAX)  // ��������Ĵ�������


/*��������--------------------------------------*/
typedef enum 
{
    normal = 0000,     // ���쳣
    initFailed = 6361, // CAN ��ʼ�����ɹ�
    fillErr =6362,     // CAN λ����
    formatErr =6363,   // CAN ��ʽ��
    ackErr = 6364,     // CAN ȷ�ϣ�ACK���� 
    hiddenErr = 6365,  // CAN ����λ��
    dominantErr = 6366,// CAN ����λ��
	  crcErr = 6367,     // CAN �� CRC ��
	  revIncompleteErr = 6368, // CAN �������ݲ�����
	  idErr = 6369,            // CAN ������ȡ��ID�뷵��ID��һ��
	  revLenErr = 6370,        // CAN �������ݳ��ȳ���
	
	  sendErr = 6371,          // CAN ���ͳ���
	
	  revErr = 6372,           // CAN ���ճ���
	  hostAddrRepeat = 6373,   // CAN ������ַ���ظ�
	  slaveAddrRepeat = 6374,  // CAN �ӻ���ַ���ظ�
	  slaveAddrErr =6375,      // CAN ���õĴӻ���ַ������Ч��Χ��
	  timeoutParmErr =6376,    // CAN ���õĳ�ʱ����ֵ������Ч��Χ��
	  accessSharedRegErr =6377,  // CAN ���ʹ���Ĵ���������Ч��Χ��
	
	  slaveNumErr =6378,      // CAN ���õĴӻ�����������Ч��Χ��
		shareRegNumErr =6379,   // CAN ���õĹ���Ĵ�������������Ч��Χ��
	
}eCanErr;

// CANͨѶ����
typedef struct
{
	 uint8_t txBuf[CAN_BUF_LEN]; // ���ͻ���
	 uint16_t txCnt;             // ���ͼ���
	 uint8_t txFlg;              // ���ͱ�־
	 uint16_t txTimeout;         // ���ͳ�ʱ

	 uint8_t retryFlg;           // �ط���־
	 uint8_t retryCnt;           // �ط�����
	
	 uint16_t setTxTimeoutValue; // ���÷��ͳ�ʱֵ
   ////////////////////////////////////////////////
	 uint8_t rxBuf[CAN_BUF_LEN];  // ���ջ���
	 uint16_t rxCnt;              // ���ռ���
	 uint8_t rxFlg;               // �ѽ��յ����ݱ�־ 
	 uint16_t rxTimeout;          // ���ճ�ʱ
	
	 uint16_t setRxTimeoutValue;  // ���ý��ճ�ʱֵ
	 ////////////////////////////////////////
	 uint8_t localDevAddr;   // �����豸ͨѶ��ַ
	 uint8_t currDevAddr;    // ��ǰ���ڴ�����豸ͨѶ��ַ
	
	 uint16_t devErr;        // �豸����
	 uint8_t processFlg;     // 1Ϊ����Ϣ������2Ϊ������Ĵ���������3Ϊд�Ǳ�����Ĵ�������	
	 uint8_t slaveCnt;       // �ӻ����ۼ�
	 uint8_t slaveNum;       // �ӻ�����
	 uint8_t shareRegNum[CAN_CH_MAX]; // ����Ĵ�������
	
	 uint16_t totalPacket; // �ܰ���
   uint8_t loop;
	 
} sCanComm;
extern sCanComm canComm;

/*��������--------------------------------------*/
extern void can_Init(void);
void can_DeInit(void);

/* Ӧ�ò�Э�� */
extern void CAN_Poll(void);


//extern CanTxMsg g_tCanTxMsg;	/* ���ڷ��� */
//extern CanRxMsg g_tCanRxMsg;	/* ���ڽ��� */
#endif /* #if CAN_FUNC */

#endif


