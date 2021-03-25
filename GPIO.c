#include "GPIO.h"
#include <stdio.h>
#include <math.h>


/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void write(GPIO_Handle Handle)
{

    switch (Handle.Port) {
        case Port1:
            if(Handle.Startvalue==GPIO_HIGH){ P1OUT |=Handle.Bit; }
            if(Handle.Startvalue==GPIO_LOW) { P1OUT &=~Handle.Bit;}
            break;
        case Port2:
            if(Handle.Startvalue==GPIO_HIGH){ P2OUT |=Handle.Bit; }
            if(Handle.Startvalue==GPIO_LOW) { P2OUT &=~Handle.Bit;}
            break;
        case Port3:
            if(Handle.Startvalue==GPIO_HIGH){ P3OUT |=Handle.Bit; }
            if(Handle.Startvalue==GPIO_LOW) { P3OUT &=~Handle.Bit;}
            break;
        default:
            break;
    }
}

/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void GPIO_set_output(GPIO_Handle Handle)
{
    switch (Handle.Port) {
        case Port1:
            P1DIR |=Handle.Bit;
            write(Handle);
            break;
        case Port2:
            P2DIR |=Handle.Bit;
            write(Handle);
            break;
        case Port3:
            P3DIR |=Handle.Bit;
            write(Handle);
            break;
        default:
            break;
    }

}
/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void GPIO_set_input(GPIO_Handle Handle)
{
    switch (Handle.Port) {
        case Port1:
            P1REN|=Handle.Bit;
            write(Handle);
            break;
        case Port2:
            P2REN |=Handle.Bit;
            write(Handle);
            break;
        case Port3:
            P3REN |=Handle.Bit;
            write(Handle);
            break;
        default:
            break;
    }

}



/* ----------------------------------------------------------------------------------------------
 *                                      Read function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Port Parameters: Port1, Port2,,Port3
 * Bit Paramaeters: BIT0,BIT1,...,BIT7
 * Result: GPIO read value => (GPIO_READ_LOW,GPIO_READ_HIGH,GPIO_READ_UNSUCCESFULL)
 *
 *          Example Usage
 *        ----------------
 * result=GPIO_read(Port1,BIT7); =>This example read Digital value of P1.7
 * if(result==GPIO_READ_HIGH){ ...Do Someting }
 */

int GPIO_read(int Port,int Bit)
{
    int Result;
    switch (Port) {
        case Port1:
            if ((P1IN & Bit) ==0 )
            {
                Result=GPIO_READ_LOW;
            }
            if ((P1IN & Bit) ==Bit )
            {
                Result=GPIO_READ_HIGH;
            }
            break;
        case Port2:
            if ((P2IN & Bit) ==0 )
            {
                Result=GPIO_READ_LOW;
            }
            if ((P2IN & Bit) ==Bit )
            {
                Result=GPIO_READ_HIGH;
            }
            break;
        case Port3:
            if ((P3IN & Bit) ==0 )
            {
                Result=GPIO_READ_LOW;
            }
            if ((P3IN & Bit) ==Bit )
            {
                Result=GPIO_READ_HIGH;
            }
            break;
        default:
            Result=GPIO_READ_UNSUCCESFULL;
            break;
    }
    return Result;
}



/* ----------------------------------------------------------------------------------------------
 *                                      Toggle function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Port Parameters: Port1, Port2,,Port3
 * Bit Paramaeters: BIT0,BIT1,...,BIT7
 *
 *          Example Usage
 *        ----------------
 * GPIO_Toggle(Port1,BIT0); =>This example Toggle P1.0
 */

void GPIO_Toggle(int Port,int Bit)
{
    switch (Port) {
        case Port1:
            P1OUT ^=Bit;
            break;
        case Port2:
            P2OUT ^=Bit;
            break;
        case Port3:
            P3OUT ^=Bit;
            break;
        default:
            break;
    }
}



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

void GPIO_write(int Port,int Bit,int HiLo)
{
    switch (Port) {
        case Port1:
            if(HiLo==GPIO_HIGH){ P1OUT |=Bit; }
            if(HiLo==GPIO_LOW) { P1OUT &=~Bit;}
            break;
        case Port2:
            if(HiLo==GPIO_HIGH){ P2OUT |=Bit; }
            if(HiLo==GPIO_LOW) { P2OUT &=~Bit;}
            break;
        case Port3:
            if(HiLo==GPIO_HIGH){ P3OUT |=Bit; }
            if(HiLo==GPIO_LOW) { P3OUT &=~Bit;}
            break;
        default:
            break;
    }
}



/* ----------------------------------------------------------------------------------------------
 *                                      PinMode function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Struct for PIN initilation
 * |
 *  --> Port : Port1,Port2,Port3
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

void GPIO_PinMode(GPIO_Handle Handle)
{
  //  int resultPort,resultPin,result;
    switch (Handle.Mode) {
        case GPIO_OUTPUT:
            GPIO_set_output(Handle);
            break;
        case GPIO_INPUT:
            GPIO_set_input(Handle);
            break;
        default:
            break;
    }
}



