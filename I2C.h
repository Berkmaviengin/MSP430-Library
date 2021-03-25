/*
 * I2C.h
 *
 *  Created on: 27 Nis 2020
 *      Author: Berk Maviengin
 */

#ifndef I2C_H_
#define I2C_H_

#include<msp430.h>
#include <stdint.h>

typedef enum
{
    I2C_MASTER = 0,
    I2C_SLAVE= 1,
}I2C_Mastermode;
typedef enum
{
    I2C_CLOCK_SOURCE_ACLK = 0,
    I2C_CLOCK_SOURCE_SMCLK= 1,
}I2C_Clocksource;

/*------------------------------ I2C HANDLE --------------------------------*/
typedef struct _I2C_Handle
{
    int Mastermode;                 //Master or Slave
    int Clocksource;                //Clock Source
    long Speed;                     //I2C Clock Speed
    uint8_t Slaveaddress;           //Slave Address
    uint8_t Masteraddress;          //Master Address
}I2C_Handle;



/*-----------------------------------------------------------------------
 *                               subvalue
 *----------------------------------------------------------------------*/
uint8_t *PTxData;                     // Pointer to TX data
uint8_t *PRxData;                     // Pointer to RX data
/*-----------------------------------------------------------------------
 *                               subvalue
 *----------------------------------------------------------------------*/
uint8_t TxByteCtr;
uint8_t RxByteCtr;



/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void I2C_write(uint8_t ByteCtr, uint8_t *TxData);



/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void I2C_read(uint8_t ByteCtr, volatile uint8_t *RxData);



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
void I2C_write8bit(uint8_t *WriteValue);



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
void I2C_write16bit(uint16_t *WriteValue);


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
void I2C_read16bit(uint16_t *ReadValue);



/* -------------------------------------------------------------------------------------------------------------------
 *                                              I2C read 8-bit function
 * -------------------------------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 *  ReadValue : Reading Value
 *          Example Usage
 *        ----------------
 *  uint8_t * RXBuffer;
 *  I2C_read8bit(&RXBuffer);
 *
 * This example read 8 bit and set reading value "RXBuffer"
 */
void I2C_read8bit(uint8_t *ReadValue);



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
void I2C_close();



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
void I2C_init(I2C_Handle Handle);


#endif /* I2C_H_ */
