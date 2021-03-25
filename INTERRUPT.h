/*
 * interrupt.h
 *
 *  Created on: 22 Mar 2020
 *      Author: Berk Maviengin
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <msp430.h>



/*-------------------------------- Trigger Detect Pins -------------------------------*/
#define intP1_0         P1IFG&BIT0
#define intP1_1         P1IFG&BIT1
#define intP1_2         P1IFG&BIT2
#define intP1_3         P1IFG&BIT3
#define intP1_4         P1IFG&BIT4
#define intP1_5         P1IFG&BIT5
#define intP1_6         P1IFG&BIT6
#define intP1_7         P1IFG&BIT7

#define intP2_0         P2IFG&BIT0
#define intP2_1         P2IFG&BIT1
#define intP2_2         P2IFG&BIT2
#define intP2_3         P2IFG&BIT3
#define intP2_4         P2IFG&BIT4
#define intP2_5         P2IFG&BIT5
#define intP2_6         P2IFG&BIT6
#define intP2_7         P2IFG&BIT7





/*------------------- Interrupt Select Edge & CallBack Return Value ------------------*/
enum _Interrupt
{
    INTERRUPT_RISING_EDGE,
    INTERRUPT_FALLING_EDGE,
    EXIT_INTERRUPT_FUNCTION,
};


/*----------------------------------- Trigger Answer ---------------------------------*/
enum{
    Trigger_True=1,
    Trigger_False=0,
};


/*----------------------------------- Interrupt Hande --------------------------------*/
typedef struct _Intterupt_Handle
{
    int Port;
    int Pin;
    int Selectedge;
    int (*Int_Func)(void);

}Intterupt_Handle;


/*------------------------------ Callback Function Handle ------------------------------*/
typedef struct _callback_func_Handle
{
    int (*Int_Function0)(void);
    int (*Int_Function1)(void);
    int (*Int_Function2)(void);
    int (*Int_Function3)(void);
    int (*Int_Function4)(void);
    int (*Int_Function5)(void);
    int (*Int_Function6)(void);
    int (*Int_Function7)(void);
}callback_func_Handle;



/* ----------------------------------------------------------------------------------------------
 *                               Interrupt Enable function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Struct for interrupt
 *
 *          Example Usage
 *        ----------------
 * GPIO_Interrupt_Enable(&InterruptParams);
 *
 */
void GPIO_Interrupt_Enable(Intterupt_Handle Handle);



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
 *      GPIO_Interrupt_setCallback(&InterruptParams, &InterruptCallBackFunc);
 *      ...
 *      ...
 *  }
 *
 */
void GPIO_Interrupt_setCallback(Intterupt_Handle Handle,int Callback(void));



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
 * GPIO_interrupt_init(&InterruptParams);
 *
 * This Example P1.3 pin initilation interrupt for Falling edge
 */
void GPIO_interrupt_init(Intterupt_Handle Handle);
#endif /* INTERRUPT_H_ */
