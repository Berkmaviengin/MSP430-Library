/*
 * UART.h
 *
 *  Created on: 25 Mar 2020
 *      Author: Berk Maviengin
 */

#ifndef UART_H_
#define UART_H_

#include <msp430.h>

#define RXD BIT1  //RX BIT
#define TXD BIT2  //TX BIT

#define UART_READ_TIMEOUT_NONE      0 //Read Time Out Disable

/*-------------------------------- Read Echo Config --------------------------------*/
enum _ReadEcho
{
    UART_READ_ECHO_ON,   //Receive String Send
    UART_READ_ECHO_OFF,  //Receive String Not Send
};
/*------------------------------- Return Mode Config -------------------------------*/
enum _ReadReturnMode
{
    UART_RETURN_FULL,     /*! Unblock/callback when buffer is full. */
    UART_RETURN_NEWLINE,  /*! Unblock/callback when newline character is received. */
};
/*--------------------------------- UART Handle ----------------------------------*/
typedef struct _UART_Handle
{
    int Baudrate; //2400,4800,9600,....
    int Readreturnmode; //UART_RETURN_FULL,UART_RETURN_NEWLINE
    int Readecho;       //UART_READ_ECHO_ON,UART_READ_ECHO_OFF
    long Timeout;       //UART_READ_TIMEOUT_NONE,0.......10000....

}UART_Handle;


/*-----------------------------------------------------------------------
 *                               subParameters
 *----------------------------------------------------------------------*/
volatile unsigned int tx_flag;          //Mailbox Flag for the tx_char.
volatile unsigned char tx_char;         //This char is the most current char to go into the UART

volatile unsigned int rx_flag;          //Mailbox Flag for the rx_char.
volatile unsigned char rx_char;         //This char is the most current char to come out of the UART






/* ----------------------------------------------------------------------------------------------
 *                                     UART Receive function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Uart Handle
 * Array : Receiving string
 * length: string size
 *
 *          Example Usage
 *        ----------------
 * UART_Read(UartParams, receive, 50);
 *
 * This Example UART receive String,size=50
 */
void UART_Read(UART_Handle Handle ,char* Array, int length);



/* ----------------------------------------------------------------------------------------------
 *                                     UART Send function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Uart Handle
 * str : Sending string
 *
 *          Example Usage
 *        ----------------
 * UART_Write(UartParams,"Test123");
 *
 * This Example UART send String
 */
void UART_Write(UART_Handle Handle,char *str);


/* ----------------------------------------------------------------------------------------------
 *                                     UART Close function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 *  NONE
 *
 *          Example Usage
 *        ----------------
 *
 * UART_Close();
 *
 * This Example UART closing.
 */
void UART_Close();



/* ----------------------------------------------------------------------------------------------
 *                                     UART initialize function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Struct for UART initilation
 * |
 *  --> Baudrate :2400,4800,9600....
 * |
 *  --> Readreturnmode :UART_RETURN_FULL,UART_RETURN_NEWLINE
 * |
 *  --> Readecho: UART_READ_ECHO_ON,UART_READ_ECHO_OFF
 * |
 *  --> Timeout: UART_READ_TIMEOUT_NONE,0,..100...1000..(msn),
 *
 *          Example Usage
 *        ----------------
 *
 *  UART_Handle UartParams;
 *  UartParams.Baudrate=9600;
 *  UartParams.Readecho=UART_READ_ECHO_ON;
 *  UartParams.Readreturnmode=UART_RETURN_NEWLINE;
 *  UartParams.Timeout=10000; //MS
 *  UART_init(UartParams);
 *
 * This Example UART init for 9600 baudrate ,Read echo,adn 10s time out
 */
void UART_init(UART_Handle Handle);
#endif /* UART_H_ */
