/*
 * FLASH.c
 *
 *  Created on: 7 Nis 2020
 *      Author: Berk Maviengin
 */
#include "FLASH.h"



/* ----------------------------------------------------------------------------------------------
 *                                      FLASH Erase Function
 * ----------------------------------------------------------------------------------------------
 * This Needs MUltiple conversation
 *          parameters
 *        ---------------
 * flash: Erase Segment
 *
 *          Example Usage
 *        ----------------
 *  #define flash SEGMENT_D
 *  FLASH_erase(flash);
 *
 *  This example erase D SEGMENT
 */
void FLASH_erase(unsigned char *flash)
{
  FCTL1 = FWKEY+ERASE;
  FCTL3 = FWKEY;
  *flash = 0;
  FCTL3 = FWKEY+LOCK;

}



/* ----------------------------------------------------------------------------------------------
 *                                      FLASH Read Function
 * ----------------------------------------------------------------------------------------------
 * This Needs MUltiple conversation
 *          parameters
 *        ---------------
 * flash: Readable Segment
 * data : Data to be Read
 * size : Data to be Read size
 *
 *          Example Usage
 *        ----------------
 *  #define flash SEGMENT_D
 *  unsigned char flash_read;
 *  FLASH_read(flash, &flash_read, 1);
 *
 *  This example read D SEGMENT 1 character and write flash_read variable
 */
void FLASH_read(unsigned char *flash, unsigned char *data, int size)
{
  while(size--){
   *(data++) = *(flash++);
  __delay_cycles(10000);
  }
}



/* ----------------------------------------------------------------------------------------------
 *                                      FLASH Write Function
 * ----------------------------------------------------------------------------------------------
 * This Needs MUltiple conversation
 *          parameters
 *        ---------------
 * flash: Writable Segment
 * data : Data to be written
 * size : Data to be written size
 *
 *          Example Usage
 *        ----------------
 *  #define flash SEGMENT_D
 *  FLASH_write(flash, (unsigned char*) "Tutorial" ,8);
 *
 *  This example "Tutorial" write D SEGMENT
 */
void FLASH_write(unsigned char *flash, unsigned char *data, int size)
{
    FCTL3 = FWKEY;            // Clear LOCK
    FCTL1 = FWKEY+WRT;        // Enable write
    __delay_cycles(10000);
    while(size--)
    {
        *(flash++) = *(data++);
        __delay_cycles(10000);
    }
    FCTL1 = FWKEY;
    FCTL3 = FWKEY+LOCK;       // Set LOCK
}



/* ----------------------------------------------------------------------------------------------
 *                                      ADC initialize function
 * ----------------------------------------------------------------------------------------------
 *          parameters
 *        ---------------
 * [NONE]
 *
 *          Example Usage
 *        ----------------
 * FLASH_init();
 */
void FLASH_init()
{
    FCTL2 = FWKEY + FSSEL0 + FN1;
}




