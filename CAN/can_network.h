/*
*********************************************************************************************************
*	                                  
*	模块名称 : CAN网络通信程序
*	文件名称 : can_network.c
*	版    本 : V1.0.1
*	说    明 : 实现多个CAN节点（节点的程序相同）之间的通信。
*	修改记录 :
*		版本号       日期       作者    说明
*		V1.0.1   2017-11-02    传人记  ST固件库V3.5.0版本。
*
*	Copyright (C), 2017-2020, 传人记 shop148504253.taobao.com
*
*********************************************************************************************************
*/

#ifndef _CAN_NETWORK_H
#define _CAN_NETWORK_H

#include "plc_conf.h"

#if CAN_FUNC

/*宏定义----------------------------------------*/
#define ACCESS_U16(x)              (*(u16*)&x) 
#define CAN_BUF_LEN                 128

/* 寄存器与继电器说明 */
// 暂不实现
// M8149 通讯超时标志（CAN 出现通讯不上或超时标志，该标志 ON 后，需要在程序里手动 OFF）  备注：使用D8063替代
// D8153-通讯波特率（20K~1000K，默认 250K）
// D8196-通讯不上的从机（1~16） 
// D8197-通讯不上的从机（ 17~32 ）
// D8198-通讯不上的从机汇总（1~16） 
// D8199-通讯不上的从机汇总（ 17~32 ）
// D8200-与从机通讯成功一次的最大时间（1=1ms）


#define CAN_EN_FLG	            M8150  // CAN 允许工作

#define CAN_COMM_TIMEOUT_PARM	  D8149  // 通讯超时参数（1=1ms，默认 100ms） 
#define CAN_ADDR	              D8150  // 主机或者从机地址设置（0主机，1~32从机）
#define CAN_SAVLE_NUM	          D8151  // 从机个数（1~32），暂时支持CAN_CH_MAX个
#define CAN_SHARE_REG_NUM	      D8152  // 共享的寄存器个数（1~32，默认 8）

#define CAN_COMM_ERR	          D8063  // 存放错误代码

/* 主/从机互相共享的寄存器列表(暂定9个单元) */
#define CAN_REG_D_START_ADDR 		         4096   // D寄存器起始地址
#define CAN_REG_D_END_ADDR 		           12096  // D寄存器结束地址

#define CAN_CH_MAX                        8  // 支持从机最大个数
#define CAN_UNIT_NUM	                    32  // 共享寄存器单组最大数
#define CAN_SHARED_REG_START_INDEX	      (CAN_REG_D_START_ADDR + 1000)                             // 主机共享寄存器起始
#define CAN_SHARED_REG_END_INDEX	        (CAN_SHARED_REG_START_INDEX + CAN_UNIT_NUM * CAN_CH_MAX)  // 主机共享寄存器结束


/*变量定义--------------------------------------*/
typedef enum 
{
    normal = 0000,     // 无异常
    initFailed = 6361, // CAN 初始化不成功
    fillErr =6362,     // CAN 位填充错
    formatErr =6363,   // CAN 格式错
    ackErr = 6364,     // CAN 确认（ACK）错 
    hiddenErr = 6365,  // CAN 隐性位错
    dominantErr = 6366,// CAN 显性位错
	  crcErr = 6367,     // CAN 的 CRC 错
	  revIncompleteErr = 6368, // CAN 接收数据不完整
	  idErr = 6369,            // CAN 主机读取的ID与返回ID不一致
	  revLenErr = 6370,        // CAN 接收数据长度出错
	
	  sendErr = 6371,          // CAN 发送出错
	
	  revErr = 6372,           // CAN 接收出错
	  hostAddrRepeat = 6373,   // CAN 主机地址有重复
	  slaveAddrRepeat = 6374,  // CAN 从机地址有重复
	  slaveAddrErr =6375,      // CAN 设置的从机地址不在有效范围内
	  timeoutParmErr =6376,    // CAN 设置的超时参数值不在有效范围内
	  accessSharedRegErr =6377,  // CAN 访问共享寄存器不在有效范围内
	
	  slaveNumErr =6378,      // CAN 设置的从机个数不在有效范围内
		shareRegNumErr =6379,   // CAN 设置的共享寄存器个数不在有效范围内
	
}eCanErr;

// CAN通讯处理
typedef struct
{
	 uint8_t txBuf[CAN_BUF_LEN]; // 发送缓存
	 uint16_t txCnt;             // 发送计数
	 uint8_t txFlg;              // 发送标志
	 uint16_t txTimeout;         // 发送超时

	 uint8_t retryFlg;           // 重发标志
	 uint8_t retryCnt;           // 重发次数
	
	 uint16_t setTxTimeoutValue; // 设置发送超时值
   ////////////////////////////////////////////////
	 uint8_t rxBuf[CAN_BUF_LEN];  // 接收缓存
	 uint16_t rxCnt;              // 接收计数
	 uint8_t rxFlg;               // 已接收到数据标志 
	 uint16_t rxTimeout;          // 接收超时
	
	 uint16_t setRxTimeoutValue;  // 设置接收超时值
	 ////////////////////////////////////////
	 uint8_t localDevAddr;   // 本机设备通讯地址
	 uint8_t currDevAddr;    // 当前正在处理的设备通讯地址
	
	 uint16_t devErr;        // 设备错误
	 uint8_t processFlg;     // 1为读信息结束，2为读共享寄存器结束，3为写非本身共享寄存器结束	
	 uint8_t slaveCnt;       // 从机数累计
	 uint8_t slaveNum;       // 从机个数
	 uint8_t shareRegNum[CAN_CH_MAX]; // 共享寄存器个数
	
	 uint16_t totalPacket; // 总包数
   uint8_t loop;
	 
} sCanComm;
extern sCanComm canComm;

/*函数声明--------------------------------------*/
extern void can_Init(void);
void can_DeInit(void);

/* 应用层协议 */
extern void CAN_Poll(void);


//extern CanTxMsg g_tCanTxMsg;	/* 用于发送 */
//extern CanRxMsg g_tCanRxMsg;	/* 用于接收 */
#endif /* #if CAN_FUNC */

#endif


