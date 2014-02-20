/**********************************************************************
	> File Name: main.c
	> Author: Rmoker
	> Mail: rmokerone@gmail.com 
	> Created Time: Wed 19 Feb 2014 09:56:02 PM CST
 *********************************************************************/

#include "hw_spi.h" 

int main (void)
{
    int8 data = 0;
    SPI_InitTypeDef spi_init_instruct;
    SPI_CSN_TypeDef spi_csn_instruct;
    spi_init_instruct.SPI_MODE_Select = SPI_MODE_MASTER; 
    MOS_SPI_Init(spi_init_instruct, spi_csn_instruct);
    data = MOS_SPI_Master_WriteRead(spi_csn_instruct,
                                    data, SPI_CSN_ASSERTED);
    data = MOS_SPI_Master_Write(spi_csn_instruct,
                                    data);
    data = MOS_SPI_Master_Read(spi_csn_instruct);
    return 0;
}

