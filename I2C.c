/*
 * I2C.c
 *
 *  Created on: 27 Nis 2020
 *      Author: Berk Maviengin
 */
#include "I2C.h"



/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void i2c_select_master_mode(I2C_Handle Handle)
{
    switch (Handle.Mastermode) {
        case I2C_MASTER:
            UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;
            break;
        case I2C_SLAVE:
            UCB0CTL0 &= ~UCMST;
            UCB0CTL0 |= UCMODE_3+ UCSYNC;
            break;
        default:
            break;
    }
}



/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void i2c_set_slave_master_address(I2C_Handle Handle)
{
    switch (Handle.Mastermode) {
        case I2C_MASTER:
            UCB0I2CSA =Handle.Slaveaddress;
            break;
        case I2C_SLAVE:
            UCB0I2CSA = Handle.Masteraddress;
            break;
        default:
            break;
    }
    UCB0CTL1 &= ~UCSWRST;
}



/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void i2c_speed(I2C_Handle Handle){
    int value;
    switch (Handle.Clocksource) {
        case I2C_CLOCK_SOURCE_SMCLK:
            value=1000000/(Handle.Speed);
            break;
        case I2C_CLOCK_SOURCE_ACLK:
            value=32768/(Handle.Speed);
            break;
        default:
            break;
    }
    UCB0BR0 = value;
    UCB0BR1 = 0;
}



/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void i2c_select_clock_source(I2C_Handle Handle)
{
    switch (Handle.Clocksource) {
        case I2C_CLOCK_SOURCE_ACLK:
            UCB0CTL1 = UCSSEL_1 + UCSWRST;
            break;
        case I2C_CLOCK_SOURCE_SMCLK:
            UCB0CTL1 = UCSSEL_2 + UCSWRST;
            break;
        default:
            break;
    }
}


/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void I2C_write(uint8_t ByteCtr, uint8_t *TxData) {
    __disable_interrupt();

    IE2 &= ~UCB0RXIE;                              // Disable RX interrupt
    IE2 |= UCB0TXIE;                               // Enable TX interrupt
    //Pointer to where data is stored to be sent
    PTxData = (uint8_t *) TxData;                  // TX array start address
    TxByteCtr = ByteCtr;                           // Load TX byte counter
    //Send start condition
    UCB0CTL1 |= UCTR + UCTXSTT;                    // I2C TX, start condition
    __bis_SR_register(CPUOFF + GIE);               // Enter LPM0 w/ interrupts
    while (UCB0CTL1 & UCTXSTP);
}



/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void I2C_read(uint8_t ByteCtr, volatile uint8_t *RxData) {
    __disable_interrupt();
    //Interrupt management
    IE2 &= ~UCB0TXIE;                              // Disable TX interrupt
    UCB0CTL1 = UCSSEL_2 + UCSWRST;                 // Use SMCLK, keep SW reset
    UCB0CTL1 &= ~UCSWRST;                          // Clear SW reset, resume operation
    IE2 |= UCB0RXIE;                               // Enable RX interrupt

    //Pointer to where data will be stored
    PRxData = (uint8_t *) RxData;                  // Start of RX buffer
    RxByteCtr = ByteCtr;                           // Load RX byte counter
    //If only 1 byte will be read send stop signal as soon as it starts transmission
    if(RxByteCtr == 1){
        UCB0CTL1 |= UCTXSTT;                       // I2C start condition
        while (UCB0CTL1 & UCTXSTT);                // Start condition sent?
        UCB0CTL1 |= UCTXSTP;                       // I2C stop condition
        __enable_interrupt();
    } else {
        UCB0CTL1 |= UCTXSTT;                       // I2C start condition
    }

    __bis_SR_register(CPUOFF + GIE);               // Enter LPM0 w/ interrupts
    while (UCB0CTL1 & UCTXSTP);                    // Ensure stop condition got sent
}










/* -------------------------------------------------------------------------------------------------------------------
 *                                              I2C Write 8-bit function
 * -------------------------------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * WriteValue : Writing Value
 *          Example Usage
 *        ----------------
 * uint16_t temp=0xFF;
 * I2C_write8bit(&temp);
 *
 * This example I2C write value "0xFF"
 */
void I2C_write8bit(uint8_t *WriteValue)
{
    I2C_write(1, WriteValue);
}



/* -------------------------------------------------------------------------------------------------------------------
 *                                              I2C Write 16-bit function
 * -------------------------------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * WriteValue : Writing Value
 *          Example Usage
 *        ----------------
 * uint16_t temp=0x0FA1;
 * I2C_write16bit(&temp);
 *
 * This example I2C write value "0x0FA1"
 */
void I2C_write16bit(uint16_t *WriteValue)
{
    uint8_t TxBuffer[2];
    TxBuffer[0] = *WriteValue >> 8; // high byte (0x12)
    TxBuffer[1] = *WriteValue & 0x00FF; // low byte (0x34)
    I2C_write(2, TxBuffer);
}



/* -------------------------------------------------------------------------------------------------------------------
 *                                              I2C Read 16-bit Function
 * -------------------------------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 *  ReadValue : Reading Value
 *          Example Usage
 *        ----------------
 * uint16_t temp;
 * I2C_read16bit(&temp);
 *
 * This example read 16 bit and set reading value "temp"
 */
void I2C_read16bit(uint16_t *ReadValue)
{
    uint8_t RxBuffer[2];
    I2C_read(2, RxBuffer);
    *ReadValue=(((unsigned int)RxBuffer[0] <<8 | RxBuffer[1]));

}




/* -------------------------------------------------------------------------------------------------------------------
 *                                              I2C Read 8-bit Function
 * -------------------------------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 *  ReadValue : Reading Value
 *          Example Usage
 *        ----------------
 *  uint8_t RXBuffer;
 *  I2C_read8bit(&RXBuffer);
 *
 * This example read 8 bit and set reading value "RXBuffer"
 */
void I2C_read8bit(uint8_t *ReadValue)
{
    uint8_t RxBuffer;
    I2C_read(1, &RxBuffer);
    *ReadValue=RxBuffer;
}



/* ----------------------------------------------------------------------------------------------
 *                                      I2C Close function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * None
 *
 *          Example Usage
 *        ----------------
 * I2C_close();
 */
void I2C_close()
{
    UCB0CTL1 |= UCSWRST;
}



/* -------------------------------------------------------------------------------------------------------------------
 *                                              I2C initialize function
 * -------------------------------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Struct for I2C initilation
 * |
 *  --> Mastermode    : I2C_MASTER , I2C_SLAVE
 * |
 *  --> Clocksource   : I2C_CLOCK_SOURCE_ACLK , I2C_CLOCK_SOURCE_SMCLK
 * |
 *  --> Speed         : 0, ... , 100 , ... , 1000 , ... (Hz)
 * |
 *  --> Slaveaddress  : Adress for Slave
 * |
 *  --> Masteraddress : Adress for Master
 *          Example Usage
 *        ----------------
 *  I2CParams.Mastermode=I2C_MASTER;
 *  I2CParams.Clocksource=I2C_CLOCK_SOURCE_SMCLK;
 *  I2CParams.Speed=100000;
 *  I2CParams.Slaveaddress=0x40;
 *  I2C_init(I2CParams);
 *
 * Start Master mode and 100khz speed,and slave adress 0x40 set
 */
void I2C_init(I2C_Handle Handle)
{
    // Port Configuration
    P1SEL  |=BIT6+BIT7;
    P1SEL2 |=BIT6+BIT7;

    // Enable SW reset
    UCB0CTL1 |= UCSWRST;
    //Master or  Slave mode Select
    i2c_select_master_mode(Handle);

    //Clock Sourece Select SMCLK or ACLK
    i2c_select_clock_source(Handle);

    //I2C speed Set (0,..10,...1000,.....)
    i2c_speed(Handle);

    //Set Slave or Master Adress
    i2c_set_slave_master_address(Handle);

}




/*-----------------------------------------------------------------------
 *                          I2C Interrupt Pragma
 *----------------------------------------------------------------------*/
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0TX_VECTOR))) USCIAB0TX_ISR (void)
#else
#error Compiler not supported!
#endif
{
  if(IFG2 & UCB0RXIFG){                              // Receive In
  if (RxByteCtr == 1)
  {
     *PRxData = UCB0RXBUF;   // Move final RX data to PRxData
     __bic_SR_register_on_exit(CPUOFF); // Exit LPM0
  }
  else
  {
      *PRxData++ = UCB0RXBUF;// Move RX data to address PRxData
      if (RxByteCtr == 2)  // Check whether byte is second to last to be read to send stop condition
      UCB0CTL1 |= UCTXSTP;
      __no_operation();
  }
  RxByteCtr--; // Decrement RX byte counter
  }

  else{   // Master Transmit
      if (TxByteCtr) // Check TX byte counter
  {
    UCB0TXBUF = *PTxData; // Load TX buffer
    PTxData++;
    TxByteCtr--; // Decrement TX byte counter
  }
  else
  {
    UCB0CTL1 |= UCTXSTP;                             // I2C stop condition
    IFG2 &= ~UCB0TXIFG;                              // Clear USCI_B0 TX int flag
    __bic_SR_register_on_exit(CPUOFF);               // Exit LPM0
  }
 }
}



