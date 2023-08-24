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
*	Copyright (C), 2017-2020, 传人记 淘宝网址shop148504253.taobao.com
*
*********************************************************************************************************
*/

/*
	一、应用层协议:（自定义简单协议）	
	
       命令： 功能码（1字节）+ 【起始地址（2字节)】+ 【字节数（1字节)】+ [数据]（N字节）+ 校验（2字节）
							 功能码   0x03 读  （地址0xFFFF，CAN从机个数、共享寄存器个数）
											  0x10 写	
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

/* 定义全局变量 */
//CanTxMsg g_tCanTxMsg;	/* 用于发送 */
//CanRxMsg g_tCanRxMsg;	/* 用于接收 */
uint8_t g_ucLedNo = 0;	/* 点亮的LED灯序号，0-3 */


// can应用
sCanComm canComm;



/* 仅允许本文件内调用的函数声明 */
static void can_NVIC_Config(void);

/**********************************************************************************************************
*	函 数 名: can_Init
*	功能说明: 配置CAN硬件
*	形    参：无
*	返 回 值: 无
* 作者： 传人记 淘宝网址shop148504253.taobao.com
**********************************************************************************************************/
void can_Init(void)
{
	// GPIO_InitTypeDef GPIO_InitStructure;
	// CAN_InitTypeDef CAN_InitStructure;
	// CAN_FilterInitTypeDef CAN_FilterInitStructure;	
		
	// /* PB8，PB9口线设置为AFIO模式, 切换到CAN功能 */
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	// /* 使能GPIO时钟 */
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// /* 配置CAN信号接收引脚: RX */
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	/* GPIO配置为上拉输入模式 */
	// GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// /* 配置CAN信号发送引脚: TX */
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		/* 配置为复用推挽输出 */
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	/* 设置GPIO最大速度 */
	// GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// /* 原生的CAN引脚和USB引脚是相同的口线，安富莱开发板使用引脚的重映射功能将CAN引脚切换到PB8，PB9 */
	// GPIO_PinRemapConfig(GPIO_Remap1_CAN1 , ENABLE);	/* 使能CAN1的重映射 */
	
	// /* 使能CAN外设时钟 */
	// RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	// CAN_DeInit(CAN1);						/* 复位CAN寄存器 */
	// CAN_StructInit(&CAN_InitStructure);		/* 填充CAN参数结构体成员为缺省值 */
	
	// /*
	// 	TTCM = time triggered communication mode
	// 	ABOM = automatic bus-off management 
	// 	AWUM = automatic wake-up mode
	// 	NART = no automatic retransmission
	// 	RFLM = receive FIFO locked mode 
	// 	TXFP = transmit FIFO priority		
	// */
	// CAN_InitStructure.CAN_TTCM = DISABLE;			/* 禁止时间触发模式（不生成时间戳), T  */
	// CAN_InitStructure.CAN_ABOM = DISABLE;			/* 禁止自动总线关闭管理 */
	// CAN_InitStructure.CAN_AWUM = DISABLE;			/* 禁止自动唤醒模式 */
	// CAN_InitStructure.CAN_NART = DISABLE;			/* 禁止仲裁丢失或出错后的自动重传功能 */
	// CAN_InitStructure.CAN_RFLM = DISABLE;			/* 禁止接收FIFO加锁模式 */
	// CAN_InitStructure.CAN_TXFP = DISABLE;			/* 禁止传输FIFO优先级 */
	// CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;	/* 设置CAN为正常工作模式 */
	
	// /* 
	// 	CAN 波特率 = RCC_APB1Periph_CAN / Prescaler / (SJW + BS1 + BS2);
		
	// 	SJW = synchronisation_jump_width 
	// 	BS = bit_segment
		
	// 	本例中，设置CAN波特率为500Kbps		
	// 	CAN 波特率 = 360000000 / 6 / (1 + 6 + 5) / = 500kHz		
	// */
	
	// CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	// CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
	// CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
	// CAN_InitStructure.CAN_Prescaler = 6;
	// CAN_Init(CAN1, &CAN_InitStructure);
	
	// /* 设置CAN滤波器0 */
	// CAN_FilterInitStructure.CAN_FilterNumber = 0;		                  /* 滤波器序号，0-13，共14个滤波器 */
	// CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;		/* 滤波器模式，设置ID掩码模式 */
	// CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;	/* 32位滤波 */
	// CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;					      /* 要过滤的ID高16bit */
	// CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;					        /* 要过滤的ID低16bit */
	
	// /* 位为0意味着收到的数据帧中的相应位的ID不一定非要与设置的ID一样， */
	// CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;				    /* ID掩码值高16bit */
	// CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;				      /* ID掩码值低16bit */
	// CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;		  /* 滤波器绑定FIFO 0 */
	// CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;				    /* 使能滤波器 */
	// CAN_FilterInit(&CAN_FilterInitStructure);
	
	// /* 此处暂时不发送 */	

	// can_NVIC_Config();		/* 配置CAN中断 */	
  
  /********************HAL***********************/
  CANx_Init();
  /******************end HAL ********************/
}     

/**********************************************************************************************************
*	函 数 名: can_DeInit
*	功能说明: 退出CAN硬件硬质，恢复CPU相关的GPIO为缺省；关闭CAN中断
*	形    参：无
*	返 回 值: 无
* 作者： 传人记 淘宝网址shop148504253.taobao.com
**********************************************************************************************************/
void can_DeInit(void)
{
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, DISABLE);	/* 关闭CAN1时钟 */

//	{
//		NVIC_InitTypeDef  NVIC_InitStructure;
//		
//		NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
//		NVIC_Init(&NVIC_InitStructure);
//	
//		/* CAN FIFO0 消息接收中断使能 */ 
//		CAN_ITConfig(CAN1, CAN_IT_FMP0, DISABLE);	
//	}
}

/**********************************************************************************************************
*	函 数 名: can_NVIC_Config
*	功能说明: 配置CAN中断
*	形    参：无
*	返 回 值: 无
* 作者： 传人记 淘宝网址shop148504253.taobao.com
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
//	/* CAN FIFO0 消息接收中断使能 */ 
//	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);	
}

/**********************************************************************************************************
*	函 数 名: can_ISR
*	功能说明: CAN中断服务程序. 这个函数在 stm32f10x_it.c中被调用
*	形    参：无
*	返 回 值: 无
* 作者： 传人记 淘宝网址shop148504253.taobao.com
**********************************************************************************************************/ 
void can_ISR(void)
{
//	CAN_Receive(CAN1, CAN_FIFO0, &g_tCanRxMsg);
//	
//	if(canComm.localDevAddr ==0) // 主机
//		canComm.currDevAddr = canComm.slaveCnt;
//	else // 从机
//		canComm.currDevAddr =  canComm.localDevAddr;
//	
//	/* 无接收完成的数据处理并且地址、标准帧、长度都配对成功 */
//	if ( (canComm.rxFlg !=2)&&(g_tCanRxMsg.StdId == canComm.currDevAddr) && (g_tCanRxMsg.IDE == CAN_ID_STD) && (0 < g_tCanRxMsg.DLC))
//	{
//     memcpy((uint8_t *)&canComm.rxBuf[canComm.rxCnt], g_tCanRxMsg.Data, g_tCanRxMsg.DLC);
//		 canComm.rxCnt +=g_tCanRxMsg.DLC; // 接收数据长度累加
//		 if (CAN_BUF_LEN <= canComm.rxCnt) // 仿真
//       canComm.rxCnt = 0;
//		
//		 canComm.rxTimeout =1; // 重启等待
//		 canComm.rxFlg =1;     // 标记已接收到数据		 
//		 
//		 canComm.txTimeout =0; // 禁止发送超时计时
//		
//	} 
//	else
//	{
//	   CAN_FIFORelease(CAN1, CAN_FIFO0);	
//	}
}

/**********************************************************************************************************
*	函 数 名: USB_LP_CAN1_RX0_IRQHandler
*	功能说明: CAN中断服务程序. 这个函数在 stm32f10x_it.c中被调用
*	形    参：无
*	返 回 值: 无
* 作者： 传人记 淘宝网址shop148504253.taobao.com
**********************************************************************************************************/ 
#if 0		// 此函数放到 stm32f10x_it.c , USB中断和CAN共享
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	can_ISR();
}
#endif


/**********************************************************************************************************
*	函 数 名: can_SendPacket
*	功能说明: 发送一包数据
*	形    参：_DataBuf 数据缓冲区
*			  _Len 数据长度, 0-8字节
*	返 回 值: 无
* 作者： 传人记 淘宝网址shop148504253.taobao.com
**********************************************************************************************************/
void CAN_SendPacket(uint8_t _addr,uint8_t *_DataBuf, uint8_t _Len)
{		
		/* 填充发送参数， 也可以再每次发送的时候填 */
//		g_tCanTxMsg.StdId = _addr;      // 标准帧ID,如果要发送扩展帧，可以不管它
//		g_tCanTxMsg.ExtId = 0x0;        // 扩展帧ID,如果要发送标准帧，可以不管它
//		g_tCanTxMsg.RTR = CAN_RTR_DATA; // 数据帧、远程帧
//		g_tCanTxMsg.IDE = CAN_ID_STD;   // 标准帧、扩展帧
//		g_tCanTxMsg.DLC = _Len;
//						
//    memcpy(g_tCanTxMsg.Data, _DataBuf, _Len);
//    CAN_Transmit(CAN1, &g_tCanTxMsg);	
}

/**********************************************************************************************************
*	函 数 名: CAN_GetInfo
*	功能说明: 获取信息并记录（CAN从机个数、共享寄存器个数）
*	形    参：_addr 设备地址 0 表示广播的
*	返 回 值: 无
* 备注：
				命令： 功能码（1字节）+ 【起始地址（2字节)】+ 【字节数（1字节)】+ 【数据】（N字节） + 校验（2字节）
							 功能码   0x03 读  （地址0xFFFF，CAN从机个数、共享寄存器个数）
											  0x10 写								
* 作者： 传人记 淘宝网址shop148504253.taobao.com				
**********************************************************************************************************/
void CAN_GetInfo(uint8_t _addr)
{		
//	/* 填充发送参数， 也可以再每次发送的时候填 */
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
//	canComm.txTimeout =1; // 启动发送超时计数
//	canComm.txFlg =0; // 禁止发送
//	canComm.retryFlg =0;
//	
//	// 接收清零
//	canComm.rxCnt =0;
//	canComm.rxTimeout =0;
//	canComm.rxFlg =0;
}

/**********************************************************************************************************
*	函 数 名: CAN_GetShareRegData
*	功能说明: 获取数据（共享寄存器）
*	形    参：_addr 设备地址 0 表示广播的；
*	返 回 值: 无
* 备注：
				命令： 功能码（1字节）+ 【起始地址（2字节)】+ 【字节数（1字节)】+ 【数据】（N字节） + 校验（2字节）
							 功能码   0x03 读  （地址0xFFFF，CAN从机个数、共享寄存器个数）
											  0x10 写		
* 作者： 传人记 淘宝网址shop148504253.taobao.com
**********************************************************************************************************/
void CAN_GetShareRegData(uint8_t _addr)
{		
//	/* 填充发送参数， 也可以再每次发送的时候填 */
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
//	canComm.txTimeout =1; // 启动发送超时计数
//	canComm.txFlg =0; // 禁止发送
//	canComm.retryFlg =0; 
//	
//	// 接收清零
//	canComm.rxCnt =0;
//	canComm.rxTimeout =0;
//	canComm.rxFlg =0;	
}

/* 延时 */
void SimpleDelay(uint16_t value)
{
  uint16_t i,j;
	for(i=0;i < value;i++)
	  for(j=0;j <1000; j++);
}

/**********************************************************************************************************
*	函 数 名: CAN_WriteShareRegData
*	功能说明: 发送通信对象本身的共享寄存数据
*	形    参：_addr 设备地址 0 表示广播的
*			  _led_no ： LED指示灯序号
*	返 回 值: 无
* 备注:
       命令： 功能码（1字节）+ 【起始地址（2字节)】+ 【字节数（1字节)】+ [数据]（N字节）+ 校验（2字节）
							 功能码   0x03 读  （地址0xFFFF，CAN从机个数、共享寄存器个数）
											  0x10 写		
* 作者： 传人记 淘宝网址shop148504253.taobao.com
**********************************************************************************************************/
void CAN_ReplyShareRegData(uint8_t _addr)
{		
		static uint8_t mod =0;	
		uint8_t bytes =0;
		uint8_t i=0;
	 	if(canComm.retryFlg ==0) // 无重发时进入
		{		
				uint16_t shareRegStartIndex =CAN_SHARED_REG_START_INDEX + CAN_UNIT_NUM * _addr;	
			
				canComm.txBuf[0] = 0x03; // 功能码：写（1个字节）		
				ACCESS_U16(canComm.txBuf[1]) = shareRegStartIndex; // 起始地址（2个字节）
				canComm.txCnt = 7 + (canComm.shareRegNum[_addr] <<1); // 6 = 功能码（1）+ 起始地址（2） + 字节数（1） + CRC(2) + 特殊数据（1）			
				canComm.txBuf[3] = canComm.txCnt; // 字节数（1个字节）	
				// 数据
				canComm.txBuf[4] = canComm.shareRegNum[_addr]; // 方便从机把数据分类处理   			
				memcpy((uint8_t *)&canComm.txBuf[5], (uint8_t *)&plc_16BitBuf[shareRegStartIndex], canComm.shareRegNum[_addr] <<1);		
				ACCESS_U16(canComm.txBuf[canComm.txCnt - 2])= CRC16_Modbus(canComm.txBuf, canComm.txCnt - 2);		
				 
				mod = canComm.txCnt % 8;
				canComm.totalPacket = (mod)? (canComm.txCnt/8 +1) : (canComm.txCnt/8);		
	  }	
		
		while(i < canComm.totalPacket)
		{
				if(((i+1) == canComm.totalPacket) && (mod)) // 最后一包并且不足8字节
					bytes = mod;
				else
					bytes =8;
				CAN_SendPacket(_addr,(uint8_t *)&canComm.txBuf[i << 3],bytes);
				i++;				
				SimpleDelay(2);
		}			
							
		canComm.txFlg =0; // 禁止发送(整包发送完成)
		canComm.txTimeout =0; // 停止发送超时计时
		canComm.retryFlg =0;
		canComm.processFlg =2; // 第3步，等待接收主机下发非本身的共享寄存数据	
		// 接收清零
		canComm.rxCnt =0;
		canComm.rxTimeout =0;
    canComm.rxFlg =0;		
}


/**********************************************************************************************************
*	函 数 名: CAN_WriteShareRegData
*	功能说明: 主机发送非通信对象本身的共享寄存数据
*	形    参：_addr 设备地址 0 表示广播的
*			  _led_no ： LED指示灯序号
*	返 回 值: 无
* 备注:
       命令： 功能码（1字节）+ 【起始地址（2字节)】+ 【字节数（1字节)】+ [数据]（N字节）+ 校验（2字节）
							 功能码   0x03 读  （地址0xFFFF，CAN从机个数、共享寄存器个数）
											  0x10 写	
* 作者： 传人记 淘宝网址shop148504253.taobao.com
**********************************************************************************************************/
void CAN_WriteShareRegData(uint8_t _addr)
{		
	  uint8_t i=0;
		static uint8_t mod = 0;	
		static uint8_t bytes =0;
	  uint16_t shareRegStartIndex;
	
		if(canComm.retryFlg ==0) // 无重发时进入
		{
			if(canComm.rxFlg == 5) // 接收数据成功 
			{
				 canComm.loop++;
				 if(_addr == canComm.loop) // _addr本身的共享寄存器不用下发
					 canComm.loop +=1;
				 if( canComm.slaveNum < canComm.loop ) // 说明一轮已写结束
				 {
						canComm.loop =0; // 所有共享寄存器数据发送完成，				
						canComm.processFlg =0; // 3个工作流程全部完成，重新从流程1开始							 
						canComm.txTimeout =0; // 禁止发送超时计时
						canComm.txFlg =1; // 启动发送 					 
						return;							 
				 }
		  }			
	
			shareRegStartIndex =CAN_SHARED_REG_START_INDEX + CAN_UNIT_NUM * canComm.loop;			
			canComm.txBuf[0] = 0x10; // 功能码：写（1个字节）		
			ACCESS_U16(canComm.txBuf[1]) = shareRegStartIndex; // 起始地址（2个字节）
			canComm.txCnt = 7 + (canComm.shareRegNum[canComm.loop] <<1); // 6 = 功能码（1）+ 起始地址（2） + 字节数（1） + CRC(2) + 特殊数据（1）			
			canComm.txBuf[3] = canComm.txCnt; // 字节数（1个字节）	
			// 数据
			canComm.txBuf[4] = canComm.shareRegNum[canComm.loop] ; // 方便从机把数据分类处理   			
			memcpy((uint8_t *)&canComm.txBuf[5], (uint8_t *)&plc_16BitBuf[shareRegStartIndex], canComm.shareRegNum[canComm.loop] <<1);		
			ACCESS_U16(canComm.txBuf[canComm.txCnt - 2])= CRC16_Modbus(canComm.txBuf, canComm.txCnt - 2);		
			 
			mod = canComm.txCnt % 8;
			canComm.totalPacket = (mod)? (canComm.txCnt/8 +1) : (canComm.txCnt/8);
	  }
		
		while(i < canComm.totalPacket)
		{
				if(((i+1) == canComm.totalPacket) && (mod)) // 最后一包并且不足8字节
					bytes = mod;
				else
					bytes =8;
				CAN_SendPacket(_addr,(uint8_t *)&canComm.txBuf[i << 3],bytes);
				i++;
				SimpleDelay(2);
		}		
		 
		canComm.txTimeout =1; // 启动发送超时计数
		canComm.txFlg =0; // 禁止发送
		canComm.retryFlg =0;
		
		// 接收清零
		canComm.rxCnt =0;
		canComm.rxTimeout =0;	
		canComm.rxFlg =0;
}


/**********************************************************************************************************
*	函 数 名: CAN_Reply
*	功能说明: 主从机应答
*	形    参：_addr 设备地址 0 表示广播的
*	返 回 值: 无
* 备注：
				命令： 功能码（1字节）+ 【起始地址（2字节)】+ 【字节数（1字节)】+ 【数据】（N字节） + 校验（2字节）
							 功能码   0x03 读  （地址0xFFFF，CAN从机个数、共享寄存器个数）
											  0x10 写								
* 作者： 传人记 淘宝网址shop148504253.taobao.com				
**********************************************************************************************************/
void CAN_Reply(uint8_t _addr,uint8_t _cmd,uint16_t _startAddr,uint16_t _state)
{		
//	/* 填充发送参数， 也可以再每次发送的时候填 */
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
////	canComm.txTimeout =1; // 启动发送超时计数
//	canComm.txFlg =0; // 禁止发送
//	canComm.retryFlg =0;
//	
//	// 禁止接收超时计时
//	canComm.rxTimeout =0;
//	canComm.rxFlg =0;
}

/* 接收数据处理 */
void RevDataDeal(void)
{
		/* 已接收数据并且单次接收时间到 */
		if ((canComm.rxFlg ==1) && (canComm.setRxTimeoutValue < canComm.rxTimeout))
		{		
			  uint16_t crc;
			  canComm.rxTimeout =0; // 停止接收超时计时
        canComm.txFlg =0; // 禁止发送
			  canComm.rxFlg = 2;// 标记本次数据接收完成，正在处理接收数据，备注：在此区间接收的数据无效  
			
				crc = CRC16_Modbus(canComm.rxBuf, canComm.rxCnt - 2);
				if( crc != ACCESS_U16(canComm.rxBuf[canComm.rxCnt - 2]) )
				{ // CRC校验出错
						canComm.devErr = crcErr;
						goto label;
				}	

				// 数据长度匹配
				if(canComm.rxCnt != canComm.rxBuf[3])
				{ // 长度无效				
						canComm.devErr = revLenErr;	
						goto label;
				}

				if(canComm.rxBuf[0] == 0x03) // 读
				{				
						// 起始地址匹配
						if(ACCESS_U16(canComm.rxBuf[1]) == 0xFFFF) // 获取信息（共享寄存器个数）
						{
								if(canComm.localDevAddr ==0) // 主机
								{		
										canComm.shareRegNum[canComm.slaveCnt] = canComm.rxBuf[4]; // 共享寄存器个数		
										canComm.processFlg =1;	// 获取数据（共享寄存器）
								}
								else 
								{// 从机
										canComm.processFlg =0;	// 标记进入回复信息（共享寄存器个数）						
								}
								canComm.rxFlg =3; // 接收数据成功 					
						}
						else
						{ // 获取数据（共享寄存器）								
								uint16_t shareRegStartIndex = ACCESS_U16(canComm.rxBuf[1]);							
								if( ( shareRegStartIndex < CAN_SHARED_REG_START_INDEX) &&  ( CAN_SHARED_REG_END_INDEX < shareRegStartIndex)  ) // 共享寄存器区间判断
								{ // 无效
										canComm.devErr = accessSharedRegErr;	
										goto label;
								}
								else
								{       
										if(canComm.localDevAddr ==0) // 主机
										{											
												memcpy( (uint8_t *)&plc_16BitBuf[shareRegStartIndex],(uint8_t *)&canComm.rxBuf[5],canComm.rxBuf[4] << 1 ); // 共享寄存器赋值
												canComm.processFlg =2; // 下发数据	（共享寄存器)

												canComm.loop =0;									
										}
										else
										{ // 从机
												// 上传共享寄存器数据
												canComm.processFlg =1; // 标记进入上传共享寄存器数据 											
										}
										canComm.rxFlg =4; // 接收数据成功 		
								}								
						}				
				}
				else if(canComm.rxBuf[0] == 0x10) // 写
				{
						uint16_t shareRegStartIndex = ACCESS_U16(canComm.rxBuf[1]);							
						if( ( shareRegStartIndex < CAN_SHARED_REG_START_INDEX) &&  ( CAN_SHARED_REG_END_INDEX < shareRegStartIndex)  ) // 共享寄存器区间判断
						{ // 无效
								canComm.devErr = accessSharedRegErr;	
						    goto label;
						}
						else
						{
								if(canComm.localDevAddr ==0) // 主机
								{		
										if(ACCESS_U16(canComm.rxBuf[4])) // 出错
												canComm.devErr =ackErr;										   
                    else 
											 canComm.rxFlg =5; // 接收数据成功 
								}
								else
								{ // 从机                   									
										memcpy( (uint8_t *)&plc_16BitBuf[shareRegStartIndex],(uint8_t *)&canComm.rxBuf[5],canComm.rxBuf[4] << 1 ); // 共享寄存器赋值
										canComm.processFlg =2; // 标记进入应答主机 下发数据	（共享寄存器）成功
									  canComm.rxFlg =5; // 接收数据成功 
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
        { // 出错
				  canComm.rxFlg =0;
				}					
				
		}
}

/**********************************************************************************************************
*	函 数 名: CAN_Poll
*	功能说明: CAN功能处理入口，主机与所有从机的共享寄存器互相共享，每站最大可共享32个寄存器
*	形    参：无
*	返 回 值: 无
* 备注：
				帧格式： 功能码（1字节）+ 【起始地址（2字节)】+ 【字节数（1字节)】+ 【数据】（N字节）+ 校验（2字节）
							   功能码：0x03读，0x10写
* 作者： 传人记 淘宝网址shop148504253.taobao.com
**********************************************************************************************************/
void CAN_Poll(void)
{			
	  static uint8_t initFlg =0;	
	  if(PLC_BIT_TEST(CAN_EN_FLG)) // 判断CAN功能是否开启
		{			
			if(initFlg ==0)
			{ // 进入初始化
					initFlg =1;
					memset(&canComm, 0, sizeof(canComm)); // 清零 
				
					/* 设备通讯地址 */
					if(CAN_CH_MAX < CAN_ADDR)
					{ // 设置的通信地址无效
						CAN_COMM_ERR = slaveAddrErr;
						return;
					}	
					else
					{
						canComm.localDevAddr = CAN_ADDR;
					}
//			    canComm.localDevAddr =0; // test m
				
				  /* 默认值 */
					if(canComm.localDevAddr ==0) // 仅主机有
					{
						canComm.txFlg =1; 
						canComm.slaveNum =1;
					}				
					canComm.shareRegNum[canComm.localDevAddr] =8;
					canComm.setRxTimeoutValue = 10;	
          canComm.setTxTimeoutValue = 100;					
			}
			////////////////////////////////////////////////////////////////////////
			/* 从机个数,仅主机 */
			if(canComm.localDevAddr ==0)
			{
				if(CAN_CH_MAX < CAN_SAVLE_NUM)
				{ // 设置从机个数无效
					CAN_COMM_ERR = slaveNumErr;
					return;
				}	
				else
				{
					canComm.slaveNum = CAN_SAVLE_NUM;
				}			
			}
			
			/* 共享寄存器个数 */
			if(CAN_UNIT_NUM < CAN_SHARE_REG_NUM)
			{
				CAN_COMM_ERR = shareRegNumErr;
        return;		
			}
			else
			{
			  canComm.shareRegNum[canComm.localDevAddr] =  CAN_SHARE_REG_NUM; // 本机共享寄存器个数
			}			
			
			/* 通讯超时 */
			if(CAN_COMM_TIMEOUT_PARM < 100)
			{ // 设置的通讯超时参数不在有效范围内
				CAN_COMM_ERR = timeoutParmErr;
        return;				
			}	
			else
			{
				canComm.setTxTimeoutValue = CAN_COMM_TIMEOUT_PARM;
			}
	
			////////////////////////////////////////////////////////////////////////
			// 接收数据处理
			RevDataDeal(); 
			
			/* 发送超时处理 */
			if( canComm.setTxTimeoutValue < canComm.txTimeout)
			{
				 canComm.txTimeout =0;
				 canComm.devErr = sendErr;
			}
			
			if(canComm.devErr) // 重试
			{		
				  CAN_COMM_ERR = canComm.devErr;
					canComm.devErr =0;	
					if((++canComm.retryCnt) <6) // 重试6次
					{
							canComm.retryFlg =1; // 标记重试
					}
					else // 放弃重发
					{
							canComm.retryCnt =0;
							canComm.retryFlg =0;
						
							canComm.processFlg =0;
						  canComm.txFlg =1;
					}					 
			}
			else
			{ // 无出错
					canComm.retryCnt =0;
					canComm.retryFlg =0;	
			}	
			
			/* 接收数据成功或者 发送数据允许 或者 发送重试*/
			if( ((0 < (canComm.rxFlg - 2)) || (canComm.txFlg == 1)) || (canComm.retryFlg == 1)) 
			{		
				if(canComm.localDevAddr ==0) // 主机	
				{					
						// 允许通讯地址累加 
						if( (canComm.retryFlg ==0) && (canComm.processFlg ==0))
						{			 
							 if( canComm.slaveNum < (++canComm.slaveCnt))
									canComm.slaveCnt =1;  
						}
						 //////////////////////////////////////////////////////////////////////////////////
						 // 主机发送工作流程
						 switch (canComm.processFlg)
						 {
								case 0: // 1、获取信息并记录（CAN从机个数、共享寄存器个数）
								{
									 CAN_GetInfo(canComm.slaveCnt);										
									 break;
								}
								case 1: // 2、获取数据（共享寄存器）
								{
									 CAN_GetShareRegData(canComm.slaveCnt); 
									 break;
								}
								case 2: // 3、下发数据	（共享寄存器）
								{
									 CAN_WriteShareRegData(canComm.slaveCnt);
									 break;
								}
						 }
				 }
				 else // 从机
				 { 
						 switch (canComm.processFlg)
						 {
								case 0: // 0、回复信息（共享寄存器个数）
								{
										CAN_Reply(canComm.localDevAddr, canComm.rxBuf[0],ACCESS_U16(canComm.rxBuf[1]),canComm.shareRegNum[canComm.localDevAddr]);
										break;
								}
								case 1: // 1、回复数据（共享寄存器）
								{
										CAN_ReplyShareRegData(canComm.localDevAddr); // 本机共享数据
										break;
								}
								case 2: // 2、应答主机 下发数据	（共享寄存器）
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


/***************************** 传人记 淘宝网址shop148504253.taobao.com (END OF FILE) *********************************/


