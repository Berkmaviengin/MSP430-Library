/*
 * ADC.c
 *
 *  Created on: 30 Mar 2020
 *      Author: Berk Maviengin
 */
#include "ADC.h"

int ADC_read_conv[100]; //Multi-Conv ADC read Array

/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void enable_pin_ADC(ADC_Handle Handle,int Pin)
{

    switch (Pin) {
        case A0:
            ADC10CTL1 =A0_REF+(Handle.Conversionmode); //REF pin + Conversation mode
            break;
        case A1:
            ADC10CTL1 =A1_REF+(Handle.Conversionmode); //REF pin + Conversation mode
            break;
        case A2:
            ADC10CTL1 =A2_REF+(Handle.Conversionmode); //REF pin + Conversation mode
            break;
        case A3:
            ADC10CTL1 =A3_REF+(Handle.Conversionmode); //REF pin + Conversation mode
            break;
        case A4:
            ADC10CTL1 =A4_REF+(Handle.Conversionmode); //REF pin + Conversation mode
            break;
        case A5:
            ADC10CTL1 =A5_REF+(Handle.Conversionmode); //REF pin + Conversation mode
            break;
        case A6:
            ADC10CTL1 =A6_REF+(Handle.Conversionmode); //REF pin + Conversation mode
            break;
        case A7:
            ADC10CTL1 =A7_REF+(Handle.Conversionmode); //REF pin + Conversation mode
            break;
        default:
            break;
    }
    ADC10AE0 |=Pin;
}

/*-----------------------------------------------------------------------
 *                               subfunction
 *----------------------------------------------------------------------*/
void conversation_value_ADC(ADC_Handle Handle)
{
    if(Handle.Conversionmode!=SINGLE_CONVERSION){ADC10DTC1=Handle.Conversionvalue;}
}



/* ----------------------------------------------------------------------------------------------
 *                                      ADC Read
 * ----------------------------------------------------------------------------------------------
 * This Needs MUltiple conversation
 *          parameters
 *        ---------------
 * Handle: This is Struct for ADC
 * Pin: Reading ADC pin => A0,A1,A2.....A7
 *
 *          Example Usage
 *        ----------------
 *  val=ADC_read(ADCParams,A4);
 *  This Example A4 pin (P1.4) read
 */
int ADC_read(ADC_Handle Handle,int Pin)
{
    int val=0;
    ADC10CTL0 &= ~ENC;
    enable_pin_ADC(Handle,Pin);
    switch (Handle.Conversionmode) {
        case SINGLE_CONVERSION:
            ADC10CTL0 |= ENC + ADC10SC;         // Sampling and conversion start
            while(ADC10CTL1 & BUSY);
            val = ADC10MEM;
            break;
        case MULTIPLE_CONVERSION:
            while (ADC10CTL1 & BUSY);       // Wait if ADC10 busy
            ADC10SA = (int)ADC_read_conv;
            val=ADC_read_conv[0];
            break;
        default:
            break;
    }
    return val;
}



/* ----------------------------------------------------------------------------------------------
 *                                      ADC Read Average
 * ----------------------------------------------------------------------------------------------
 * This Needs MUltiple conversation
 *          parameters
 *        ---------------
 * Handle: This is Struct for ADC
 * Pin: Reading ADC pin => A0,A1,A2.....A7
 *
 *          Example Usage
 *        ----------------
 *  val=ADC_read_average(ADCParams, A4);
 *  This Example A4 pin (P1.4) read average
 */
int ADC_read_average(ADC_Handle Handle,int Pin)
{
    int ADC_read_avg=0;
    int counter=0;
    ADC10CTL0 &= ~ENC;
    enable_pin_ADC(Handle,Pin);
    while (ADC10CTL1 & BUSY);       // Wait if ADC10 busy
    ADC10SA = (int)ADC_read_conv;
    ADC10CTL0 |= ENC + ADC10SC;     // Enable Conversion and conversion start
    for(counter=0;counter<Handle.Conversionvalue;counter++)
    {
        ADC_read_avg=ADC_read_avg+ADC_read_conv[counter];
    }
    ADC_read_avg=ADC_read_avg/Handle.Conversionvalue;
    return ADC_read_avg;
}



/* ----------------------------------------------------------------------------------------------
 *                                      ADC initialize function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * Handle: This is Struct for ADC initilation
 * |
 *  --> Conversionmode : SINGLE_CONVERSION,MULTIPLE_CONVERSION
 * |
 *  --> Conversionvalue : NULL,1,...100,...2000,...,32000
 * |
 *  --> Referencevoltage: VREF_AVCC_AVSS,VREF_VREF_AVSS
 * |
 *  --> Samplecycles: SAMPLE_CYCLES_4,SAMPLE_CYCLES_8,SAMPLE_CYCLES_16,SAMPLE_CYCLES_64
 *
 *          Example Usage
 *        ----------------
 *  ADC_Handle ADCParams;
 *  ADCParams.Conversionmode=SINGLE_CONVERSION;
 *  ADCParams.Conversionvalue=NULL;
 *  ADCParams.Referencevoltage=VREF_AVCC_AVSS;
 *  ADCParams.Samplecycles=SAMPLE_CYCLES_16;
 * This Example ADC sat Single conversation and Vref=AVCC and sample cycles=16
 */
void ADC_init(ADC_Handle Handle)
{
    int CTL0Registers=0;
    CTL0Registers=(Handle.Referencevoltage)+(Handle.Samplecycles);
    if(Handle.Conversionmode!=SINGLE_CONVERSION){CTL0Registers=CTL0Registers+MSC;}
    CTL0Registers=CTL0Registers+ADC10ON + ADC10IE;
    ADC10CTL0 =CTL0Registers;
    conversation_value_ADC(Handle);
    __enable_interrupt();
}



/* ----------------------------------------------------------------------------------------------
 *                                      Close function
 * ----------------------------------------------------------------------------------------------
 *
 *          Example Usage
 *        ----------------
 * ADC_Close(); =>ADC close
 */
void ADC_close()
{
    ADC10CTL0=0;
    ADC10CTL1=0;
    ADC10CTL0 &= ~ENC;
    ADC10AE0 |=0;
}



/*-----------------------------------------------------------------------
 *                          ADC Interrupt Pragma
 *----------------------------------------------------------------------*/
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{

}
