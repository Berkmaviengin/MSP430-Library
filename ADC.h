/*
 * ADC.h
 *
 *  Created on: 30 Mar 2020
 *      Author: Berk Maviengin
 */

#ifndef ADC_H_
#define ADC_H_
#include <msp430.h>

/*------------------------------ Analog Pins ------------------------------*/
#define A0_REF                                         INCH_0
#define A1_REF                                         INCH_1
#define A2_REF                                         INCH_2
#define A3_REF                                         INCH_3
#define A4_REF                                         INCH_4
#define A5_REF                                         INCH_5
#define A6_REF                                         INCH_6
#define A7_REF                                         INCH_7

#define A0                                             BIT0
#define A1                                             BIT1
#define A2                                             BIT2
#define A3                                             BIT3
#define A4                                             BIT4
#define A5                                             BIT5
#define A6                                             BIT6
#define A7                                             BIT7

/*----------------------------- Conversion Mode -----------------------------*/
#define SINGLE_CONVERSION                              CONSEQ_0
#define MULTIPLE_CONVERSION                            CONSEQ_2

/*---------------------------- Reference Voltage ----------------------------*/
#define VREF_AVCC_AVSS                                 SREF_0
#define VREF_VREF_AVSS                                 SREF_1

/*----------------------------- Sample  Cycles ------------------------------*/
#define SAMPLE_CYCLES_4                                ADC10SHT_0
#define SAMPLE_CYCLES_8                                ADC10SHT_1
#define SAMPLE_CYCLES_16                               ADC10SHT_2
#define SAMPLE_CYCLES_64                               ADC10SHT_3

#define NULL                                           0

/*------------------------------ ADC HANDLE --------------------------------*/
typedef struct _ADC_Handle
{
    int Conversionmode;
    int Conversionvalue;
    int Referencevoltage;
    int Samplecycles;



}ADC_Handle;




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
int ADC_read(ADC_Handle Handle,int Pin);



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
int ADC_read_average(ADC_Handle Handle,int Pin);



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
void ADC_init(ADC_Handle Handle);



/* ----------------------------------------------------------------------------------------------
 *                                      Close function
 * ----------------------------------------------------------------------------------------------
 *
 *          Example Usage
 *        ----------------
 * ADC_Close(); =>ADC close
 */
void ADC_close();
#endif /* ADC_H_ */
