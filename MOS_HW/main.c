/**********************************************************************
	> File Name: main.c
	> Author: Rmoker
	> Mail: rmokerone@gmail.com 
	> Created Time: Wed 19 Feb 2014 09:56:02 PM CST
 *********************************************************************/

#include "hw_uart.h"

static FILE mystdout = FDEV_SETUP_STREAM (MOS_UART_Write, NULL, _FDEV_SETUP_WRITE);

int main (void)
{
    uint8 data;
    //测试UART
    UART_InitTypeDef uart_init_instruct;
    uart_init_instruct.UART_BAUD = 9600;
    MOS_UART_Init (uart_init_instruct);

    //转化为标准输出
    stdout = &mystdout;

    while (1)
    {
        data = MOS_UART_Read();
        printf ("data = %x\n", data);
        printf ("hi i'm jack!\n");
        _delay_ms (500);
    }
    return 0;
}

