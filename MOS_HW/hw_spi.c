/**********************************************************************
	> File Name: hw_spi.c
	> Author: Rmoker
	> Mail: rmokerone@gmail.com 
	> Created Time: Wed 19 Feb 2014 04:06:28 PM CST
 *********************************************************************/

#include "../MOS_INC/common.h"
#include "hw_spi.h"

/*
 * MOS_SPI_Init
 * SPI初始化函数
 *
 * 参数：
 *    spi_init_structure--SPI初始化结构体，
 *                          具体定义见SPI_InitTypeDef
 *    spi_csn_structure --CSN端口初始话结构体
 *                          具体定义见SPI_CSN_TypeDef
 *
 * 输出：
 *    0 -- 配置错误
 *    1 -- 配置成功
 */
uint8 MOS_SPI_Init (SPI_InitTypeDef spi_init_structure, 
                    SPI_CSN_TypeDef spi_csn_structure)
{
    //SPI工作模式
    uint8 spi_mode = spi_init_structure.SPI_MODE_Select;

    //SPI片选引脚配置寄存器
    uint8 spi_csn_port = spi_csn_structure.SPI_CSN_PORT;
    //SPI片选引脚方向寄存器
    uint8 spi_csn_ddr = spi_csn_structure.SPI_CSN_DDR;
    //SPI片选端口
    uint8 spi_csn_pin = spi_csn_structure.SPI_CSN_PIN;

    //初始化输出端口
    DDRB |= (1<<MOSI) | (1<< SCK) | (1<<CSN);
    //初始化输入端口
    DDRB &= ~(1<<MISO);

    //选择为从机模式
    if (spi_mode == SPI_MODE_SLAVE)
    {
        SPCR &= ~(1<<MSTR);
        SPCR |=  (1<<SPE);

    }
    //选择为主机模式
    else
    {
        SPCR |= (1<<SPE) | (1<<MSTR);
        //CSN置为高电平
        PORTB |= (1<<CSN);
        //如果片选不为SS，根据定义进行修改
        if (~((spi_csn_ddr == NULL)||(spi_csn_pin == NULL)))
        {
            spi_csn_ddr |= (1<<spi_csn_pin);
            //csn置高电平
            spi_csn_port |= (1<<spi_csn_pin);
        }

    }
    return 1;
}

/*MOS_SPI_Master_WriteRead
 * AVR主机SPI向从机写入数据，并读取从机数据
 *
 * 参数：
 *    spi_csn_structure -- CSN端口初始化结构体
 *                          具体定义见SPI_CSN_TypeDef
 *    data --要发送的数据
 *          单位为一个字节，8位
 *    csn_state -- 一帧数据传送完成后的CS的状态
 *          SPI_CSN_ASSERTED - 保持片选有效，CSN保持低电平
 *          SPI_CSN_INACTIVE - 片选无效，CSN信号为高电平
 *输出：
 *    读取从机8位的数据
 */
 uint8 MOS_SPI_Master_WriteRead (SPI_CSN_TypeDef spi_csn_structure,
                               uint8 data, uint8 csn_state)
 {
     uint8 spi_csn_port = spi_csn_structure.SPI_CSN_PORT;
     uint8 spi_csn_pin = spi_csn_structure.SPI_CSN_PIN;
    //将CSN置为低电平
     if ((spi_csn_port == NULL)||(spi_csn_port == NULL))
     {
         PORTB &= ~(1<<CSN);
     }
     else
     {
         spi_csn_port &= ~(1<<spi_csn_pin);
     }
     //交换数据
     SPDR = data;
     while (!(SPSR & (1<SPIF)));
     if (csn_state == SPI_CSN_ASSERTED)
     {
        //不改变 
     }
     else 
     {
        if ((spi_csn_port == NULL)||(spi_csn_port == NULL))
        {
            PORTB |= (1<<CSN);
        }
        else
        {
             spi_csn_port |= (1<<spi_csn_pin);
        }
    
     }
     return SPDR;
 }

 /*MOS_SPI_Master_Read
  * AVR主机SPI从从机中读取数据
  *
  * 参数：
 *    spi_csn_structure -- CSN初始化结构体
 *                          具体定义见SPI_CSN_TypeDef
 *  输出：
 *   从从机中读取到的数据
 */
 uint8 MOS_SPI_Master_Read (SPI_CSN_TypeDef spi_csn_structure)
 {
     uint8 data;
     data = MOS_SPI_Master_WriteRead(spi_csn_structure,
                                     0x00,
                                     SPI_CSN_INACTIVE);
     return data;
 }

 /*MOS_SPI_Master_write
  * AVR主机SPI向从机中写入数据
  *
  * 参数：
  *    spi_csn_structure -- CSN初始化结构体
  *                          具体定义见SPI_CSN_TypeDef
  *    data:要向从机发送的数据
  *         单位为一个字节，8bits
  *
  * 输出：
  *     1 -- 成功
  */
  uint8 MOS_SPI_Master_Write (SPI_CSN_TypeDef spi_csn_structure
                            ,uint8 data)
  {
      MOS_SPI_Master_WriteRead(spi_csn_structure,
                              data,
                              SPI_CSN_INACTIVE);
      return 1;
  }
