/*
 * FLASH.h
 *
 *  Created on: 7 Nis 2020
 *      Author: Berk Maviengin
 */



/*
  static const unsigned char flash[3*512] = {0};

  Flash segments:     |...SEGMENT-0...|...SEGMENT-1...|...SEGMENT-2...|...SEGMENT-3...|...SEGMENT-4...|...SEGMENT-5...|
  Program output:     |Program code.......|flash[3*512***********************************]|Other data.................|
  Available segments: |-------------------------------|+++++++++++++++|+++++++++++++++|-------------------------------|


*/

#ifndef FLASH_H_
#define FLASH_H_

#include <msp430.h>

#define SEGMENT_SIZE 512 // main segment size (smallest flasheable area)
#define INFO_SIZE 64 // information flah sizes (SEG_A to SEG_D)


/*------------------------------ Writable and Readable Flash Segment ------------------------------*/
#define SEGMENT_D ((unsigned char*)0x1000)
#define SEGMENT_C ((unsigned char*)0x1000+64)
#define SEGMENT_B ((unsigned char*)0x1000+128)



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
void FLASH_erase(unsigned char *flash);


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
void FLASH_read(unsigned char *flash, unsigned char *data, int size);



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
void FLASH_write(unsigned char *flash, unsigned char *data, int size);



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
void FLASH_init();
#endif /* FLASH_H_ */
