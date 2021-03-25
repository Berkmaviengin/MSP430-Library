/*
 * SPI.h
 *
 *  Created on: 18 Nis 2020
 *      Author: Berk Maviengin
 */

#ifndef SPI_H_
#define SPI_H_

#include <msp430.h>
#include <stdint.h>
typedef enum
{
    SPI_POL0_PHA0 = 0,    /*!< SPI mode Polarity 0 Phase 0 */
    SPI_POL0_PHA1 = 1,    /*!< SPI mode Polarity 0 Phase 1 */
    SPI_POL1_PHA0 = 2,    /*!< SPI mode Polarity 1 Phase 0 */
    SPI_POL1_PHA1 = 3,    /*!< SPI mode Polarity 1 Phase 1 */
}SPI_FrameFormat;

typedef enum
{
    SPI_LSB_FIRST = 0,  //MSB Read/Write First
    SPI_MSB_FIRST = 1,   //LSB Read/Write First
}SPI_Transaction_direction;

typedef enum
{
    SPI_3PIN = 0,
    SPI_4PIN_ACTIVE_HIGH = 1,
    SPI_4PIN_ACTIVE_LOW = 2,
}SPI_Mode;

typedef enum
{
    SPI_ASYNCHRON = 0,
    SPI_SYNCHRON= 1,
}SPI_SynchronMode;

typedef enum
{
    SPI_MASTER = 0,
    SPI_SLAVE= 1,
}SPI_Mastermode;
typedef enum
{
    SPI_CLOCK_SOURCE_ACLK = 0,
    SPI_CLOCK_SOURCE_SMCLK= 1,
}SPI_Clocksource;


/*-------------------------------- SPI Handle -------------------------------*/
typedef struct _SPI_Handle
{
    int Frameformat;
    int Speed; //SPI Clock Speed
    int Mode; //4-pin or 3-pin
    int Transactiondirection; //MSB or LSB
    int Mastermode; //Master or Slave
    int Synchronmode; // Synchron or Asynchron
    int Clocksource;

}SPI_Handle;



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
uint8_t SPI_transfer_8bit(uint8_t write_value);



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
uint16_t SPI_transfer_16bit(uint16_t write_value);



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
void SPI_writeBuffer(uint8_t *Buff, uint8_t Size);



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
void SPI_readBuffer(uint8_t *Buff, uint8_t Size);



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
void SPI_close();


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
void SPI_init(SPI_Handle Handle);
#endif /* SPI_H_ */
