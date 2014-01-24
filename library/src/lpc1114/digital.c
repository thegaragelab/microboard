/*--------------------------------------------------------------------------*
* Digital pin management and IO
*---------------------------------------------------------------------------*
* 24-Jan-2014 ShaneG
*
*  Implements the set of digital pin functions for configuration and IO.
*--------------------------------------------------------------------------*/
#include <microboard.h>
#include "lpc111x.h"
#include "hardware.h"

const PINDEF g_pindefs[] = {
  // INPUT            OUTPUT           EXTRA           ENABLE
  { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, // SLOT0
  { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, // SLOT1
  { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, // SLOT2
  { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, // SPI0
  { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, // SPI1
  { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, // SPI2
  };

//---------------------------------------------------------------------------
// Public API
//---------------------------------------------------------------------------

/** Initialise a single digital pin on a slot
 *
 * Configure a single pin on a specified general slot as a digital pin.
 * This function is generally used the configure the EXTRA pin but can also
 * be used to override the standard behaviour of one of the other pins.
 *
 * Errors and invalid parameters are quietly ignored.
 *
 * @param slot the slot to modify. This may be any available slot.
 * @param pin the pin to modify. For a general slot (SLOT0, SLOT1 & SLOT2)
 *            this can be any of the three pins. For an SPI slot only the
 *            EXTRA pin can be modified.
 * @param direction set the desired pin direction. Note that the direction
 *                  is defined relative to the peripheral (@see DIRECTION)
 */
void mbInitDigital(SLOT slot, PIN pin, DIRECTION direction) {
  }

/** Write a digital value to a pin
 *
 * Set the value of a digital pin. The pin must have been defined as an
 * INPUT pin (relative to the peripheral).
 *
 * @param slot the slot to use. This can be any slot.
 * @param pin the pin to set the value for. For a generic dock (SLOT0, SLOT1
 *            & SLOT2) this may be any pin. For an SPI slot only the EXTRA
 *            pin can have it's value changed.
 * @param value the value to set (true is HIGH, false is LOW).
 */
void mbDigitalSet(SLOT slot, PIN pin, bool value) {
  }

/** Read a digital value from a pin
 *
 * Get the value of a digital pin. The pin must have been defined as an
 * OUTPUT pin (relative to the peripheral).
 *
 * @param slot the slot to use. This can be any slot.
 * @param pin the pin to set the value for. For a generic dock (SLOT0, SLOT1
 *            & SLOT2) this may be any pin. For an SPI slot only the EXTRA
 *            pin can have it's value read.
 * @param value the value to set (true is HIGH, false is LOW).
 */
bool mbDigitalGet(SLOT slot, PIN pin) {
  return false;
  }

