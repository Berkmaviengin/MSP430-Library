/*
 * TIMER.c
 *
 *  Created on: 3 Nis 2020
 *      Author: Berk Maviengin
 */
#include "TIMER.h"

callback_function_Handle TIMERFUNC;

int counter=0;
int Timerval=0;


/*-------------------------------------------------------------------------------------------------------
 *                                              subfunction
 *------------------------------------------------------------------------------------------------------*/
void _time_init(TIMER_Handle Handle)
{
    switch (Handle.Clocksource) {
        case TIMER_CLOCK_SOURCE_ACLK:
            CCR0=32768-1;
            if(Handle.Timeunit==TIME_UNIT_SECOND)     { Timerval=Handle.Time;        }
            if(Handle.Timeunit==TIME_UNIT_MINUTE)     { Timerval=(Handle.Time*600);  }
            if(Handle.Timeunit==TIME_UNIT_HOUR)       { Timerval=(Handle.Time*36000);}
            break;
        case TIMER_CLOCK_SOURCE_SMCLK:
            if(Handle.Timeunit==TIME_UNIT_MILISECOND) { CCR0=125-1;   Timerval=Handle.Time;        }
            if(Handle.Timeunit==TIME_UNIT_SECOND)     { CCR0=12500-1; Timerval=(Handle.Time*10);   }
            if(Handle.Timeunit==TIME_UNIT_MINUTE)     { CCR0=12500-1; Timerval=(Handle.Time*600);  }
            if(Handle.Timeunit==TIME_UNIT_HOUR)       { CCR0=12500-1; Timerval=(Handle.Time*36000);}
            break;

        default:
            break;
    }
}



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
void TIMER_setCallback(TIMER_Handle Handle,int Callback(void))
{
    TIMERFUNC.Int_Function=Callback;
}



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
void TIMER_close()
{
    CCTL0 &= ~CCIE; //Timer Close
}



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
void TIMER_open()
{
    CCTL0 = CCIE;       //Start Timer
}



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
void TIMER_init(TIMER_Handle Handle)
{
    __enable_interrupt();
    TACTL |=Handle.Clocksource+Handle.Mode+ID_3 +TACLR;
    _time_init(Handle);

}


/*-------------------------------------------------------------------------------------------------------
 *                                         Interrupt Pragma Void
 *------------------------------------------------------------------------------------------------------*/
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
    counter++;
    if(counter==Timerval)
    {
        TIMERFUNC.Int_Function();
        counter=0;
    }

}
