/**********************************************************************
	> File Name: hw_spi.h
	> Author: Rmoker
	> Mail: rmokerone@gmail.com 
	> Created Time: Tue 18 Feb 2014 08:47:36 PM CST
 *********************************************************************/

#ifndef _HW_SPI_H_
#define _HW_SPI_H_

#include "../MOS_INC/common.h"
//定义SPI工作模式
#define SPI_MODE_MASTER  (0)
#define SPI_MODE_SLAVE   (1)

typedef struct 
{
    /*
     * 描述：
     *   选择SPI工作模式
     * 取值：
     *    SPI_MODE_MASTER - SPI主机工作模式
     *    SPI_MODE_SLAVE  - SPI从机工作模式
     * 初始化：
     *    不必须初始化，默认主机工作模式
     */
    uint8 SPI_MODE_Select;

    /*
     * 描述：
     *    选择SPI的片选引脚配置寄存器（仅主机模式）
     * 取值：
     *    PORTA，PORTB，PORTC，PORTD
     * 初始化：
     *    不必须初始化，默认使用SS（PORTB）
     */
    uint8 SPI_CSN_PORT;
    
    /*
     * 描述：
     *    选择SPI的片选引脚方向寄存器(仅主机模式)
     * 取值：
     *     DDRA，DDRB，DDRC,DDRD
     * 初始化：
     *    不必须初始化，默认使用SS(DDRB)
     */
    uint8 SPI_CSN_DDR;
    
    /*
     * 描述：
     *    选择SPI的片选端口(仅主机模式)
     * 取值：
     *    PIN0 ~ PIN7
     * 初始化：
     *    不必须初始化，默认使用SS(PIN2)
     */
    uint8 SPI_CSN_PIN;
}SPI_InitTypeDef;

//一帧完成后CSN的状态
#define SPI_CSN_ASSERTED  (1)
#define SPI_CSN_INACTIVE  (0)

//SPI初始化函数
uint8 MOS_SPI_Init (SPI_InitTypeDef);
//SPI反初始化函数
uint8 MOS_SPI_Deinit (SPI_InitTypeDef);
//SPI使能串行传输结束中断
uint8 MOS_SPI_EnableIrq (SPI_InitTypeDef);
//SPI禁止串行传输结束中断
uint8 MOS_SPI_DisableIrq (SPI_InitTypeDef);
//SPI主机读写函数
uint8 MOS_SPI_Master_WriteRead (SPI_InitTypeDef, uint8, uint8);
//SPI主机读函数
uint8 MOS_SPI_Master_Read(SPI_InitTypeDef);
//SPI主机写函数
uint8 MOS_SPI_Master_Write (SPI_InitTypeDef, uint8);

//定义默认端口
#define CSN   PB2
#define MOSI PB3
#define MISO PB4
#define SCK  PB5

#endif
