/**********************************************************************
	> File Name: hw_uart.h
	> Author: Rmoker
	> Mail: rmokerone@gmail.com 
	> Created Time: Thu 20 Feb 2014 12:50:18 PM CST
 *********************************************************************/

#ifndef _HW_UART_H_
#define _HW_UART_H_

#include "../MOS_INC/common.h"

//中断触发接收数据缓存
static vuint8 UART_RX_BUFF;

typedef struct
{
    /* 描述：
     *  UART波特率
     * 取值：
     *    0~115200
     * 初始化：
     *    不必须初始化，默认为9600
     */
    uint32 UART_BAUD;
}UART_InitTypeDef;

//UART初始化函数
uint8 MOS_UART_Init (UART_InitTypeDef);
//UART反初始化函数
uint8 MOS_UART_Deninit (UART_InitTypeDef);
//UART接收数据函数
uint8 MOS_UART_Read (void);
//UART发送数据函数
int MOS_UART_Write (char,FILE *);
#endif
