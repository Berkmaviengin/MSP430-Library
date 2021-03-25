/*
 * SPI.c
 *
 *  Created on: 18 Nis 2020
 *      Author: Berk Maviengin
 */

#include "SPI.h"

/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void spi_speed(SPI_Handle Handle)
{
    int value;
    switch (Handle.Clocksource) {
        case SPI_CLOCK_SOURCE_SMCLK:
            value=1000000/(Handle.Speed);
            break;
        case SPI_CLOCK_SOURCE_ACLK:
            value=32768/(Handle.Speed);
            break;
        default:
            break;
    }
    UCB0BR0 =value;
    UCB0BR1 = 0;
}


/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void spi_frame_format(SPI_Handle Handle)
{
    switch (Handle.Frameformat) {
        case SPI_POL0_PHA0:
            UCB0CTL0 |= UCCKPH;
            break;
        case SPI_POL0_PHA1:
            UCB0CTL0 &=~UCCKPH;
            break;
        case SPI_POL1_PHA0:
            UCB0CTL0 |=UCCKPL;
            UCB0CTL0 |= UCCKPH;
            break;
        case SPI_POL1_PHA1:
            UCB0CTL0 |= UCCKPL;
            UCB0CTL0 &=~UCCKPH;
            break;
        default:
            break;
    }
}


/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void spi_Transaction_direction_selection(SPI_Handle Handle)
{
    switch (Handle.Transactiondirection) {
        case SPI_MSB_FIRST:
            UCB0CTL0 |= UCMSB;
            break;
        case SPI_LSB_FIRST:
            UCB0CTL0 &=~ UCMSB;
            break;
        default:
            break;
    }
}


/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void spi_mastermode_selection(SPI_Handle Handle)
{
    switch (Handle.Mastermode) {
        case SPI_MASTER:
            UCB0CTL0 |= UCMST;
            break;
        case SPI_SLAVE:
            UCB0CTL0 &=~ UCMST;
            break;
        default:
            break;
    }
}


/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void spi_mode_selection(SPI_Handle Handle)
{
    switch (Handle.Mode) {
        case SPI_3PIN:
            UCB0CTL0 |= UCMODE_0;
            break;
        case SPI_4PIN_ACTIVE_HIGH:
            UCB0CTL0 |= UCMODE_1;
            break;
        case SPI_4PIN_ACTIVE_LOW:
            UCB0CTL0 |= UCMODE_2;
            break;
        default:
            break;
    }
}


/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void spi_Synchronmode_selection(SPI_Handle Handle)
{
    switch (Handle.Synchronmode) {
        case SPI_ASYNCHRON:
            UCB0CTL0 &=~UCSYNC;
            break;
        case SPI_SYNCHRON:
            UCB0CTL0 |=UCSYNC;
            break;
        default:
            break;
    }
}
void spi_select_clock_source(SPI_Handle Handle)
{
    switch (Handle.Clocksource) {
        case SPI_CLOCK_SOURCE_ACLK:
            UCB0CTL1 |=UCSSEL_1;
            break;
        case SPI_CLOCK_SOURCE_SMCLK:
            UCB0CTL1 |=UCSSEL_2;
            break;
        default:
            break;
    }
}


/* ----------------------------------------------------------------------------------------------
 *                                      SPI 8 Bit Transfer function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * write_value : 8 bit value (writing)
 *
 *          Example Usage
 *        ----------------
 * uint8_t Buffer;
 * uint8_t Buffer1=0xFF;
 * Buffer=SPI_transfer_8bit(Buffer1);
 */
uint8_t SPI_transfer_8bit(uint8_t write_value)
{
    UCB0TXBUF =write_value;
    while ( !(IFG2 & UCB0RXIFG) );  // Wait for RXIFG indicating remote byte received via SOMI
    return UCB0RXBUF;
}



/* ----------------------------------------------------------------------------------------------
 *                                      SPI 16 Bit Transfer function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * write_value : 16 bit value (writing)
 *
 *          Example Usage
 *        ----------------
 * uint16_t Buffer;
 * uint16_t Buffer1=0x15FF;
 * Buffer=SPI_transfer_16bit(Buffer1);
 */
uint16_t SPI_transfer_16bit(uint16_t write_value)
{
    uint16_t Ret_write;
    uint8_t *Retwrite_8 = (uint8_t *)&Ret_write, *Write_8 = (uint8_t *)&write_value;

    UCB0TXBUF = Write_8[1];
    while (!(IFG2 & UCB0RXIFG));
    Retwrite_8[1] = UCB0RXBUF;

    UCB0TXBUF = Write_8[0];
    while (!(IFG2 & UCB0RXIFG));
    Retwrite_8[0] = UCB0RXBUF;

    return Ret_write;
}




/* ----------------------------------------------------------------------------------------------
 *                                      SPI Write Buffer function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Buff : Writing Buffer
 * Size : Writeng Buffer size
 *
 *          Example Usage
 *        ----------------
 * uint8_t Buffer[15];
 * SPI_writeBuffer(Buffer,15);
 */
void SPI_writeBuffer(uint8_t *Buff, uint8_t Size)
{
    uint_fast8_t i=0;
    for(i=0; i<Size; i++)
    {
        SPI_transfer_8bit(Buff[i]);
    }
}


/* ----------------------------------------------------------------------------------------------
 *                                      SPI Read Buffer function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Buff : reading Buffer
 * Size : reading Buffer size
 *
 *          Example Usage
 *        ----------------
 * uint8_t Buffer[15];
 * SPI_readBuffer(Buffer,15);
 */
void SPI_readBuffer(uint8_t *Buff, uint8_t Size)
{
    uint_fast8_t i;
    for(i=0; i<Size; i++){
        Buff[i] = SPI_transfer_8bit(0);
    }

}



/* ----------------------------------------------------------------------------------------------
 *                                      SPI Close function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * None
 *
 *          Example Usage
 *        ----------------
 * SPI_close();
 */
void SPI_close()
{
    UCB0CTL1 |= UCSWRST;
}



/* ----------------------------------------------------------------------------------------------
 *                                      SPI initialize function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Struct for SPI initilation
 * |
 *  --> Frameformat           : SPI_POL0_PHA0 , SPI_POL0_PHA1 , SPI_POL1_PHA0 , SPI_POL1_PHA1
 * |
 *  --> Speed                 : 0,1,...100,...2000,...,32000
 * |
 *  --> Mode                  : SPI_3PIN , SPI_4PIN_ACTIVE_HIGH , SPI_4PIN_ACTIVE_LOW
 * |
 *  --> Transactiondirection  : SPI_LSB_FIRST , SPI_MSB_FIRST
 * |
 *  --> Mastermode            : SPI_MASTER , SPI_SLAVE
 * |
 *  --> Synchronmode          : SPI_ASYNCHRON , SPI_SYNCHRON
 * |
 *  --> Clocksource           : SPI_CLOCK_SOURCE_ACLK , SPI_CLOCK_SOURCE_SMCLK
 *          Example Usage
 *        ----------------
 *  SPI_Handle SPIParams;
 *  SPIParams.Frameformat=SPI_POL0_PHA1;
 *  SPIParams.Speed=5000; //5khz
 *  SPIParams.Mode=SPI_3PIN;
 *  SPIParams.Transactiondirection=SPI_MSB_FIRST;
 *  SPIParams.Mastermode=SPI_MASTER;
 *  SPIParams.Synchronmode=SPI_SYNCHRON;
 *  SPIParams.Clocksource=SPI_CLOCK_SOURCE_SMCLK;
 *  SPI_init(SPIParams);
 */
void SPI_init(SPI_Handle Handle)
{
    P1SEL |= BIT5 | BIT6 | BIT7;
    P1SEL2 |= BIT5 | BIT6 | BIT7;

    UCB0CTL1 |= UCSWRST;
    spi_frame_format(Handle);
    spi_Transaction_direction_selection(Handle);
    spi_mastermode_selection(Handle);
    spi_mode_selection(Handle);
    spi_Synchronmode_selection(Handle);
    spi_select_clock_source(Handle);
    spi_speed(Handle);

}
