/**********************************************************************
	> File Name: hw_uart.c
	> Author: Rmoker
	> Mail: rmokerone@gmail.com 
	> Created Time: Thu 20 Feb 2014 12:50:26 PM CST
 *********************************************************************/

#include "hw_uart.h"

/*
 *MOS_UART_Init
 *UART初始化函数
 *
 * 参数：
 *    uart_init_strcuture -- UART初始话结构体
 *                      具体定义见UART_InitTypeDef
 * 输出：
 *    0 -- 配置成功
 *    1 -- 配置错误
 */ 
uint8 MOS_UART_Init (UART_InitTypeDef uart_init_structure)
{
    uint32 uart_baud = uart_init_structure.UART_BAUD;
    uint32 uart_baud_setting = (uint32)((uint32)CRYSTAL/
                            (16*(uint32)uart_baud)-1);
    DDRD |= (1<<PD1);
    PORTD |= (1<<PD0)|(1<<PD1);
    
    UBRR0H = (uint8)(uart_baud_setting>>8);
    UBRR0L = (uint8)(uart_baud_setting);
    UCSR0A = 0x00;
    //8位数据位 1位停止位 无奇偶校验位
    UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
    //接收结束中断使能
    //接收使能
    //发送使能
    UCSR0B = (1<<RXCIE0)|
             (1<<RXEN0)|
             (1<<TXEN0);
    //开启全局中断
    sei();
    //成功返回
    return 0;
}

/*
 *MOS_UART_Write
 * UART发送数据函数
 *
 * 参数:
 *    data -- UART要发送的数据
 *              单位为一个字节，8bits
 *    stream -- UART数据流
 *              用来进行stdio接口输出
 * 输出：
 *    0 -- 写入成功
 *    1 -- 写入错误
 */
int MOS_UART_Write (char data, FILE * stream)
{
    if (data == '\n')
    MOS_UART_Write ('\r', stream);
    loop_until_bit_is_set (UCSR0A, UDRE0);
    UDR0 = data;
    //写入成功
    return 0;
}

/*MOS_UART_Read
 * UART接收数据函数
 *
 * 参数：
 *     无
 * 
 * 返回值：
 *     接收到的数据
 *     单位为一个字节
 */
uint8 MOS_UART_Read (void)
{
    uint8 data;
    data = UART_RX_BUFF;
    return data;
}

//UART数据接收接受触发中断
ISR (USART_RX_vect)
{
    uint8 status;
    status = UCSR0A;
    if ((status &((1<<DOR0)|(1<<FE0)))==0)
    {
       UART_RX_BUFF = UDR0;
    }
} 
