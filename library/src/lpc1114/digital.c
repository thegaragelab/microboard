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
  // INPUT                           OUTPUT                          EXTRA                           ENABLE
  { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, // SLOT0
  { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, // SLOT1
  { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, // SLOT2
  { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, // SPI0
  { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, // SPI1
  { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, { 1, 1, 0, 0, &IOCON_PIO1_4 }, // SPI2
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
  // Check the parameters
  if((slot>SLOT_MAX)||(pin>PIN_MAX))
    return; // Bad slot or pin
  const PINDEF *pindef = &g_pindefs[(slot * PIN_MAX) + pin];
  if(!pindef->m_used)
    return; // Unused slot/pin combination
  // Get the direction register
  volatile uint32_t *gpiodir = &GPIO_GPIO0DIR;
  switch(pindef->m_port) {
    case 0:
      gpiodir = &GPIO_GPIO0DIR;
      break;
    case 1:
      gpiodir = &GPIO_GPIO1DIR;
      break;
    case 2:
      gpiodir = &GPIO_GPIO2DIR;
      break;
    case 3:
      gpiodir = &GPIO_GPIO3DIR;
      break;
    default:
      return; // Bad port number
    }
  // TODO: Set the direction and disable the pull up resistor
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

