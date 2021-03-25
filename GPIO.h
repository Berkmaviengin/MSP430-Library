/*
 * IO_library.h
 *
 *  Created on: 18 Mar 2020
 *      Author: Berk Maviengin
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "msp430.h"



/*------------------------------ PinMode In/OUT ----------------------------*/
enum _Pin_Mode
{
    GPIO_OUTPUT,
    GPIO_INPUT,
};
/*----------------------------- Port Parameters -----------------------------*/
enum _Port
{
    Port1,
    Port2,
    Port3,
};
/*----------------------------- GPIO Write Hi/Lo -----------------------------*/
enum _GPIO_Out
{
    GPIO_HIGH,
    GPIO_LOW,
};
/*----------------------------- GPIO Read Result ------------------------------*/
enum _GPIO_Read
{
    GPIO_READ_HIGH,
    GPIO_READ_LOW,
    GPIO_READ_UNSUCCESFULL,
};
/*----------------------- GPIO Handle For PinMode ------------------------------*/
typedef struct _GPIO_Handle
{
    int Port;               //Port of pin
    int Bit;                //Bit of Pin
    int Mode;               //input,output
    int Startvalue;         //Start-High or Start-low

}GPIO_Handle;

/* ---------------------------------------------------------------------------------------------------------------------------------------
 * ------------------------------------------------|   FUNCTIONS   |----------------------------------------------------------------------
 * ---------------------------------------------------------------------------------------------------------------------------------------*/



/* ----------------------------------------------------------------------------------------------
 *                                      PinMode function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Struct for PIN initilation
 * |
 *  --> Port : Port1,Port2,,Port3
 * |
 *  --> Bit : BIT0,BIT1,...BIT7
 * |
 *  --> mode: GPIO_OUTPUT , GPIO_INPUT
 * |
 *  --> startValue: GPIO_LOW , GPIO_HIGH
 *
 *          Example Usage
 *        ----------------
 * GPIO_Handle PinParams;
 * PinParams.Port = Port1;
 * PinParams.Bit = BIT6+BIT0;
 * PinParams.mode = GPIO_OUTPUT;
 * PinParams.startValue = GPIO_LOW;
 * GPIO_PinMode(PinParams);
 *
 * This Example P1.0 and P1.6 pins initilaze OUPUT and write LOW
 */
void GPIO_PinMode(GPIO_Handle Handle);



/* ----------------------------------------------------------------------------------------------
 *                                      Write function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Port Parameters: Port1,Port2,,Port3
 * Bit Paramaeters: BIT0,BIT1,...,BIT7
 * HiLo Parameters: Pin write High or Low
 *
 *          Example Usage
 *        ----------------
 * GPIO_write(Port1,BIT0,GPIO_HIGH); => P1.0 write HIGH
 * GPIO_write(Port1,BIT1,GPIO_HIGH); => P1.1 write LOW
 */
void GPIO_write(int Port,int Bit,int HiLo);



/* ----------------------------------------------------------------------------------------------
 *                                      Toggle function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Port Parameters: Port1,Port2,,Port3
 * Bit Paramaeters: BIT0,BIT1,...,BIT7
 *
 *          Example Usage
 *        ----------------
 * GPIO_Toggle(Port1,BIT0); =>This example Toggle P1.0
 */
void GPIO_Toggle(int Port,int Bit);



/* ----------------------------------------------------------------------------------------------
 *                                      Read function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Port Parameters: Port1,Port2,Port3
 * Bit Paramaeters: BIT0,BIT1,...,BIT7
 * Result: GPIO read value => (GPIO_READ_LOW,GPIO_READ_HIGH,GPIO_READ_UNSUCCESFULL)
 *
 *          Example Usage
 *        ----------------
 * result=GPIO_read(Port1,BIT7); =>This example read Digital value of P1.7
 * if(result==GPIO_READ_HIGH){ ...Do Someting }
 */
int GPIO_read(int Port,int Bit);



#endif /* GPIO_H_ */
