/*
 * interrupt.c
 *
 *  Created on: 22 Mar 2020
 *      Author: Berk Maviengin
 */
#include "INTERRUPT.h"
#include "GPIO.h"


callback_func_Handle FUNCTIONPORT1;
callback_func_Handle FUNCTIONPORT2;

Intterupt_Handle Handle;




/* ----------------------------------------------------------------------------------------------
 *                               Interrupt Enable function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Struct for interrupt
 *
 *          Example Usage
 *        ----------------
 * GPIO_Interrupt_Enable(InterruptParams);
 *
 */
void GPIO_Interrupt_Enable(Intterupt_Handle Handle)
{
    switch (Handle.Port) {
        case Port1:
            P1IE |=Handle.Pin; //Register Enable
            break;
        case Port2:
            P2IE |=Handle.Pin;  //Register Enable
            break;
        default:
            break;
    }
    __enable_interrupt();
}



/* ----------------------------------------------------------------------------------------------
 *                               Interrupt Set Callback function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Struct for interrupt
 * Callback: Callback Function for interrupt
 *
 *          Example Usage
 *        ----------------
 *  int InterruptCallBack()
 *  {
 *      ...
 *      ...
 *      return EXIT_INTERRUPT_FUNCTION;
 *  }
 *
 *  int main(void){
 *      ...
 *      ...
 *      GPIO_Interrupt_setCallback(InterruptParams, &InterruptCallBackFunc);
 *      ...
 *      ...
 *  }
 *
 */
void GPIO_Interrupt_setCallback(Intterupt_Handle Handle,int Callback(void))
{
    Handle.Int_Func=Callback;
    if(Handle.Port==Port1){
        switch (Handle.Pin) {
            case BIT0:
                FUNCTIONPORT1.Int_Function0=Handle.Int_Func;
                break;
            case BIT1:
                FUNCTIONPORT1.Int_Function1=Handle.Int_Func;
                break;
            case BIT2:
                FUNCTIONPORT1.Int_Function2=Handle.Int_Func;
                break;
            case BIT3:
                FUNCTIONPORT1.Int_Function3=Handle.Int_Func;
                break;
            case BIT4:
                FUNCTIONPORT1.Int_Function4=Handle.Int_Func;
                break;
            case BIT5:
                FUNCTIONPORT1.Int_Function5=Handle.Int_Func;
                break;
            case BIT6:
                FUNCTIONPORT1.Int_Function6=Handle.Int_Func;
                break;
            case BIT7:
                FUNCTIONPORT1.Int_Function7=Handle.Int_Func;
                break;
            default:
                break;
        }
    }
    if(Handle.Port==Port2){
        switch (Handle.Pin) {
            case BIT0:
                FUNCTIONPORT2.Int_Function0=Handle.Int_Func;
                break;
            case BIT1:
                FUNCTIONPORT2.Int_Function1=Handle.Int_Func;
                break;
            case BIT2:
                FUNCTIONPORT2.Int_Function2=Handle.Int_Func;
                break;
            case BIT3:
                FUNCTIONPORT2.Int_Function3=Handle.Int_Func;
                break;
            case BIT4:
                FUNCTIONPORT2.Int_Function4=Handle.Int_Func;
                break;
            case BIT5:
                FUNCTIONPORT2.Int_Function5=Handle.Int_Func;
                break;
            case BIT6:
                FUNCTIONPORT2.Int_Function6=Handle.Int_Func;
                break;
            case BIT7:
                FUNCTIONPORT2.Int_Function7=Handle.Int_Func;
                break;
            default:
                break;
        }
    }
    __enable_interrupt();
}



/* ----------------------------------------------------------------------------------------------
 *                               Interrupt initialize function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Struct for Interrupt initilation
 * |
 *  --> Port : Port1,Port2
 * |
 *  --> Pin : BIT0,BIT1,...BIT7
 * |
 *  --> Selectedge: INTERRUPT_RISING_EDGE , INTERRUPT_FALLING_EDGE
 *
 *          Example Usage
 *        ----------------
 * Intterupt_Handle InterruptParams;
 * InterruptParams.port=Port1;
 * InterruptParams.pin=BIT3;
 * InterruptParams.selectedge=INTERRUPT_FALLING_EDGE;
 * GPIO_interrupt_init(InterruptParams);
 *
 * This Example P1.3 pin initilation interrupt for Falling edge
 */
void GPIO_interrupt_init(Intterupt_Handle Handle)
{

    switch (Handle.Port) {
        case Port1:
            P1REN |=Handle.Pin; //Register Enable
            if(Handle.Selectedge==INTERRUPT_RISING_EDGE){P1IES&=~Handle.Pin;}
            if(Handle.Selectedge==INTERRUPT_FALLING_EDGE){P1IES|=Handle.Pin;}
            break;
        case Port2:
            P2REN |=Handle.Pin;  //Register Enable
            if(Handle.Selectedge==INTERRUPT_RISING_EDGE){P2IES&=~Handle.Pin;}
            if(Handle.Selectedge==INTERRUPT_FALLING_EDGE){P2IES|=Handle.Pin;}
            break;
        default:
            break;
    }
}




/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
int Trigger_Interrupt(int pin)
{
    int PinTrigger;
    if(pin) { PinTrigger=Trigger_True; }
    else    { PinTrigger=Trigger_False; }
    return (PinTrigger);
}

/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if(Trigger_Interrupt(intP1_0)==Trigger_True){ FUNCTIONPORT1.Int_Function0(); }
    if(Trigger_Interrupt(intP1_1)==Trigger_True){ FUNCTIONPORT1.Int_Function1(); }
    if(Trigger_Interrupt(intP1_2)==Trigger_True){ FUNCTIONPORT1.Int_Function2(); }
    if(Trigger_Interrupt(intP1_3)==Trigger_True){ FUNCTIONPORT1.Int_Function3(); }
    if(Trigger_Interrupt(intP1_4)==Trigger_True){ FUNCTIONPORT1.Int_Function4(); }
    if(Trigger_Interrupt(intP1_5)==Trigger_True){ FUNCTIONPORT1.Int_Function5(); }
    if(Trigger_Interrupt(intP1_6)==Trigger_True){ FUNCTIONPORT1.Int_Function6(); }
    if(Trigger_Interrupt(intP1_7)==Trigger_True){ FUNCTIONPORT1.Int_Function7(); }
    P1IFG=0x00;

}
/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    if(Trigger_Interrupt(intP2_0)==Trigger_True){ FUNCTIONPORT2.Int_Function0(); }
    if(Trigger_Interrupt(intP2_1)==Trigger_True){ FUNCTIONPORT2.Int_Function1(); }
    if(Trigger_Interrupt(intP2_2)==Trigger_True){ FUNCTIONPORT2.Int_Function2(); }
    if(Trigger_Interrupt(intP2_3)==Trigger_True){ FUNCTIONPORT2.Int_Function3(); }
    if(Trigger_Interrupt(intP2_4)==Trigger_True){ FUNCTIONPORT2.Int_Function4(); }
    if(Trigger_Interrupt(intP2_5)==Trigger_True){ FUNCTIONPORT2.Int_Function5(); }
    if(Trigger_Interrupt(intP2_6)==Trigger_True){ FUNCTIONPORT2.Int_Function6(); }
    if(Trigger_Interrupt(intP2_7)==Trigger_True){ FUNCTIONPORT2.Int_Function7(); }
    P2IFG=0x00;

}







