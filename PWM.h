/*
 * PWM.h
 *
 *  Created on: 20 Mar 2020
 *      Author: Berk Maviengin
 */

#ifndef PWM_H_
#define PWM_H_

#include "msp430.h"

/*-------------------------------- PWM PINS --------------------------------*/
enum _PWM_PIN
{
    P1_2,
    P1_6,
    P2_1,
    P2_2,
    P2_4,
    P2_5,
};
/*-------------------------------- PWM Handle -------------------------------*/
typedef struct _PWM_Handle
{
    int pin;
    int pwmPeriod;
    int startvalue;
}PWM_Handle;



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
void PWM_Write(PWM_Handle Handle,int Duty);



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
void PWM_init(PWM_Handle Handle);



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
void PWM_Close(PWM_Handle Handle);

#endif /* PWM_H_ */
