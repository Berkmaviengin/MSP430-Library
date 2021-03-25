/*
 * PWM.c
 *
 *  Created on: 20 Mar 2020
 *      Author: Berk Maviengin
 */
#include "PWM.h"
#include <stdio.h>
#include <string.h>

/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void PWM_Pin_init(PWM_Handle Handle)
{
    switch (Handle.pin) {
        case P1_2: //TA0
            P1DIR |= BIT2;
            P1SEL |= BIT2;
            break;
        case P1_6:
            P1DIR |= BIT6;
            P1SEL |= BIT6;
            break;
        case P2_1:
            P2DIR |= BIT1;
            P2SEL |= BIT1;
            break;
        case P2_2:
            P2DIR |= BIT2;
            P2SEL |= BIT2;
            break;
        case P2_4:
            P2DIR |= BIT4;
            P2SEL |= BIT4;
            break;
        case P2_5:
            P2DIR |= BIT5;
            P2SEL |= BIT5;
            break;
        default:
            break;
    }
}

/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void PWM_outmod_init(PWM_Handle Handle)
{
    if((Handle.pin==P1_2)||(Handle.pin==P1_6)){
        TA0CCTL1 = OUTMOD_7;        // CCR1 reset/set
        TA0CTL = TASSEL_2 + MC_1;   // Chooses SMCLK and Up Mode
    }
    if((Handle.pin==P2_1)||(Handle.pin==P2_2)){
        TA1CCTL1 = OUTMOD_7;        // CCR1 reset/set
        TA1CTL = TASSEL_2 + MC_1;   // Chooses SMCLK and Up Mode
    }
    if((Handle.pin==P2_4)||(Handle.pin==P2_5)){
        TA1CCTL2 = OUTMOD_7;        // CCR1 reset/set
        TA1CTL = TASSEL_2 + MC_1;   // Chooses SMCLK and Up Mode
    }
}

/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void Timer_time_init(PWM_Handle Handle)
{
    if((Handle.pin==P1_2)||(Handle.pin==P1_6)){
        TA0CCR0 = Handle.pwmPeriod-1;     //1MHZ
    }
    if((Handle.pin==P2_1)||(Handle.pin==P2_2)||(Handle.pin==P2_4)||(Handle.pin==P2_5)){
        TA1CCR0 = Handle.pwmPeriod-1;     //1MHZ
    }
}




/* ----------------------------------------------------------------------------------------------
 *                                      Write function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Struct for PWM
 * Duty: 0,1,...100,...2000,...,pwmPeriod
 *
 *          Example Usage
 *        ----------------
 * PWM_Write(Handle,1000); =>PWM pin set Duty cycle 1000
 */
void PWM_Write(PWM_Handle Handle,int Duty)
{
    if((Handle.pin==P1_2)||(Handle.pin==P1_6)){
        TA0CCR1 = Duty;
    }
    if((Handle.pin==P2_1)||(Handle.pin==P2_2)){
        TA1CCR1 = Duty;
    }
    if((Handle.pin==P2_4)||(Handle.pin==P2_5)){
        TA1CCR2 = Duty;
    }
}



/* ----------------------------------------------------------------------------------------------
 *                                      PWM initialize function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Struct for PWM initilation
 * |
 *  --> pin : P1_2,P1_6,P2_1,P2_2,P2_4,P2_5
 * |
 *  --> pwmPeriod : 0,1,...100,...2000,...,32000
 * |
 *  --> startvalue: 0,1,2,3.........,pwmPeriod
 *
 *          Example Usage
 *        ----------------
 *  PWM_Handle PWMParams;
 *  PWMParams.pin=P2_4;
 *  PWMParams.pwmPeriod=5000;
 *  PWMParams.startvalue=0;
 *  PWM_init(PWMParams);
 *  PWM_Write(PWMParams,1000);
 * This Example P2.4 pins activeted PWM and PWM_ duty cycle set %20
 */
void PWM_init(PWM_Handle Handle)
{
    PWM_Pin_init(Handle);
    Timer_time_init(Handle);
    PWM_outmod_init(Handle);
    PWM_Write(Handle, Handle.startvalue);

}



/* ----------------------------------------------------------------------------------------------
 *                                      Close function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Struct for PWM
 *
 *          Example Usage
 *        ----------------
 * PWM_Close(Handle); =>PWM close
 */
void PWM_Close(PWM_Handle Handle)
{
    if((Handle.pin==P1_2)||(Handle.pin==P1_6)){
        TA0CTL &=~(TASSEL_2 + MC_1);   // Chooses SMCLK and Up Mode
    }
    if((Handle.pin==P2_1)||(Handle.pin==P2_2)||(Handle.pin==P2_4)||(Handle.pin==P2_5)){
        TA1CTL &=~(TASSEL_2 + MC_1);   // Chooses SMCLK and Up Mode
    }

}

