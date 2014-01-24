/*---------------------------------------------------------------------------*
* Digital slot initialisation.
*----------------------------------------------------------------------------*
* 24-Jan-2014 ShaneG
*
*  Handles initialisation of all pins on a digital slot.
*--------------------------------------------------------------------------*/
#include <microboard.h>
#include "lpc111x.h"

/** Initialise a slot for digital operations.
 *
 * This initialises the specified slot for digital IO. This is a shortcut
 * function that sets the 'standard' operations of each of the pins on the
 * slot. By default the EXTRA pin is configured to be an OUTPUT (from the
 * point of view of the peripheral).
 *
 * @param slot the slot to initialise. This may be any of the generic slots.
 */
void mbInitSlot(SLOT slot) {
  if((slot<SLOT0)||(slot>SLOT2))
    return; // Unsupported slot, just ignore it
  // Initialise the pins
  mbInitDigital(slot, PIN_INPUT, INPUT);
  mbInitDigital(slot, PIN_OUTPUT, OUTPUT);
  mbInitDigital(slot, PIN_EXTRA, OUTPUT);
  }

