/*--------------------------------------------------------------------------*
* Microboard Interface Library
* Copyright (c) 2014, The Garage Lab (http://thegaragelab.com)
*---------------------------------------------------------------------------*
* 22-Jan-2014 ShaneG
*
* Initial version. Developed for the LPC1114 Microboard.
*--------------------------------------------------------------------------*/
#ifndef __MICROBOARD_LPC1114_H
#define __MICROBOARD_LPC1114_H

/* Check inclusion order */
#ifndef __MICROBOARD_H
#  error "Do not include this file directly. Include <microboard.h> instead."
#endif

//---------------------------------------------------------------------------
// LPC1114 specific definitions.
//---------------------------------------------------------------------------

#define FREQ_CRYSTAL 12000000  // Crystal frequency
#define FREQ_CPU     50000000  // Core frequency

//---------------------------------------------------------------------------
// Configure optional implementation details
//---------------------------------------------------------------------------

// If defined then analog operations are supported by the board
//#define MB_OPT_ANALOG

// If defined then I2C operations are supported by the board
//#define MB_OPT_I2C

// If defined then serial operations are supported by the board
//#define MB_OPT_SERIAL

//---------------------------------------------------------------------------
// Analog configuration
//---------------------------------------------------------------------------

// The maximum value returned by 'mbAnalogGet()' (in this case 10 bits)
#define MB_ANALOG_MAX_GET ((1<<10)-1)

// The maximum value accepted by 'mbAnalogSet()' (in this case 10 bits)
#define MB_ANALOG_MAX_SET ((1<<10)-1)

// If defined then analog values can be set with the function 'mbAnalogSet()'.
//#define MB_ANALOG_SET

#endif /* __MICROBOARD_LPC1114_H */

