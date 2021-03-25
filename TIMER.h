/*
 * TIMER.h
 *
 *  Created on: 3 Nis 2020
 *      Author: Berk Maviengin
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <msp430.h>

/*-------------------------------------------- TIMER Clock Source Select -------------------------------------------*/
#define TIMER_CLOCK_SOURCE_SMCLK              TASSEL_2          //Select Normally
#define TIMER_CLOCK_SOURCE_ACLK               TASSEL_1          //Select Low-Power Mode Only Second Unit supports

/*----------------------------------------------- TIMER Mode Select ------------------------------------------------*/
#define TIMER_MODE_STOP                       MC_0  //Counter Stop
#define TIMER_MODE_UP                         MC_1  //Counter Up mode (Time*1 )
#define TIMER_MODE_CONTINOUS_UP               MC_2  //Counter continous up mode (Always decrement)
#define TIMER_MODE_UP_DOWN                    MC_3  //Counter Up and Down mode (Time*2)

/*--------------------------------------------- TIMER Time Unit Select ----------------------------------------------*/
#define TIME_UNIT_MILISECOND                  2     //Time unit select milisecond (Only support SMCLK)
#define TIME_UNIT_SECOND                      3     //Time unit select second
#define TIME_UNIT_MINUTE                      4     //Time unit select minute
#define TIME_UNIT_HOUR                        5     //Time unit select hour

/*------------------------------------------------ TIMER Hande ------------------------------------------------------*/
typedef struct _TIMER_Handle
{
    int Clocksource;
    int Mode;
    int Timeunit;
    int Time;
}TIMER_Handle;

/*--------------------------------------------- Callback Function Handle ---------------------------------------------*/
typedef struct _callback_function_Handle
{
    int (*Int_Function)(void);

}callback_function_Handle;




/* ---------------------------------------------------------------------------------------------------------------------
 *                                            TIMER Set Callback function
 * ---------------------------------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Struct for Timer
 * Callback: Callback Function for Timer
 *
 *          Example Usage
 *        ----------------
 *  int TimerCallBack()
 *  {
 *      ...
 *      ...
 *      return EXIT_INTERRUPT_FUNCTION;
 *  }
 *
 *  int main(void){
 *      ...
 *      ...
 *      GPIO_Interrupt_setCallback(&InterruptParams, TimerCallBack);
 *      ...
 *      ...
 *  }
 *
 */
void TIMER_setCallback(TIMER_Handle Handle,int Callback(void));



/* -------------------------------------------------------------------------------------------------------------------
 *                                              TIMER Close function
 * -------------------------------------------------------------------------------------------------------------------
 *
 * For initiated Timer Start Command.
 *
 *          Example Usage
 *        ----------------
 *  TIMER_close();
 */
void TIMER_close();



/* -------------------------------------------------------------------------------------------------------------------
 *                                              TIMER Open function
 * -------------------------------------------------------------------------------------------------------------------
 *
 * For opened Timer close Command.
 *
 *          Example Usage
 *        ----------------
 *  TIMER_open();
 */
void TIMER_open();




/* -------------------------------------------------------------------------------------------------------------------
 *                                              TIMER initialize function
 * -------------------------------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Struct for Timer initilation
 * |
 *  --> Clocksource : TIMER_CLOCK_SOURCE_SMCLK , TIMER_CLOCK_SOURCE_ACLK
 * |
 *  --> Mode        : TIMER_MODE_STOP , TIMER_MODE_UP , TIMER_MODE_CONTINOUS_UP , TIMER_MODE_UP_DOWN
 * |
 *  --> Timeunit    : TIME_UNIT_MILISECOND , TIME_UNIT_SECOND , TIME_UNIT_MINUTE , TIME_UNIT_HOUR
 * |
 *  --> Time        : 0, ... , 100 , ... , 1000 , ...
 *
 *          Example Usage
 *        ----------------
 *  TimerParams.Clocksource=TIMER_CLOCK_SOURCE_SMCLK;
 *  TimerParams.Mode=TIMER_MODE_UP;
 *  TimerParams.Timeunit=TIME_UNIT_SECOND;
 *  TimerParams.Time=2;
 *
 * This Example initiation TIMER for 2 seconds
 */
void TIMER_init(TIMER_Handle Handle);

#endif /* TIMER_H_ */
