/*
 * UART.c
 *
 *  Created on: 25 Mar 2020
 *      Author: Berk Maviengin
 */
#include "msp430g2553.h"
#include "UART.h"


int timeoutflag=0;


/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void UART_timeout(UART_Handle Handle,int length)
{
    long Tmeout=0;
    while (rx_flag == 0)
    {
        Tmeout=Tmeout+1;
        if(Tmeout==((Handle.Timeout*150)/length)){timeoutflag=1; break;}

    }
    rx_flag = 0;
}
/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void UART_Read_Finish(char* Array, int strt,int stp)
{
    timeoutflag=0;
    for( ; strt < stp ; strt++)        //fill the rest of the string with \0 nul
    {
        Array[strt] = '\0';
    }
}
/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
unsigned char UART_readchar(UART_Handle Handle,int length)
{
    if(Handle.Timeout==0){
        while (rx_flag == 0);
        rx_flag = 0;
    }
    if(Handle.Timeout > UART_READ_TIMEOUT_NONE){
        UART_timeout(Handle, length);
    }
    return rx_char;
}







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
void UART_Read(UART_Handle Handle ,char* Array, int length)
{
    unsigned int i = 0;
    switch (Handle.Readreturnmode) {
        case UART_RETURN_FULL:
            while((i < length))                 //Grab data till the array fills
            {
                Array[i] = UART_readchar(Handle,length);
                i++;
                if(timeoutflag==1)
                {
                    UART_Read_Finish(Array, i, length);
                    break;
                }
            }
            break;
        case UART_RETURN_NEWLINE:
            while((i < length))                 //Grab data till the array fills
            {
                Array[i] = UART_readchar(Handle,length);
                if(timeoutflag==1)
                {
                    UART_Read_Finish(Array, i, length);
                    break;
                }
                if(Array[i] == '\r')                //If we receive a \r the master wants to end
                {
                    UART_Read_Finish(Array, i, length);
                    break;
                }
                i++;
            }
            break;
        default:
            break;
    }
    if(Handle.Readecho==UART_READ_ECHO_ON){UART_Write(Handle, Array);}
}




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
void UART_Write(UART_Handle Handle,char *str)
{
     while(*str)
     {
         while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
             UCA0TXBUF = *str; //Write the character at the location specified py the pointer
             str++; //Increment the TxString pointer to point to the next character

     }
     IFG2 &= ~UCA0TXIFG;
     return;
}



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
void UART_Close()
{
    P1SEL &=~RXD + TXD;
    P1SEL2 &=~ RXD + TXD;
}



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
void UART_init(UART_Handle Handle)
{
    P1SEL = RXD + TXD;
    P1SEL2 = RXD + TXD;

    UCA0CTL1 |= UCSSEL_2;
    int Baud=(1000000/Handle.Baudrate);
    UCA0BR0 = Baud;
    UCA0BR1 = 0;
    UCA0MCTL = UCBRS_1;
    UCA0CTL1 &= ~UCSWRST;
    IE2 |= UCA0RXIE;

    rx_flag = 0;
    tx_flag = 0;
    __enable_interrupt();
    return;
}



/*
#pragma vector = USCIAB0TX_VECTOR       //UART TX USCI Interrupt
__interrupt void USCI0TX_ISR(void)
{
    UCA0TXBUF = tx_char;                //Copy char to the TX Buffer
    tx_flag = 0;                        //ACK the tx_flag
    IE2 &= ~UCA0TXIE;                   //Turn off the interrupt to save CPU
}
*/
#pragma vector = USCIAB0RX_VECTOR       //UART RX USCI Interrupt. This triggers when the USCI receives a char.
__interrupt void USCI0RX_ISR(void)
{
    rx_char = UCA0RXBUF;                //Copy from RX buffer, in doing so we ACK the interrupt as well
    rx_flag = 1;                        //Set the rx_flag to 1

}
