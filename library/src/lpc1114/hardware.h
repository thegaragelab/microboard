/*--------------------------------------------------------------------------*
* Hardware mapping definitions
*---------------------------------------------------------------------------*
* 24-Jan-2014 ShaneG
*
*  Initial version
*--------------------------------------------------------------------------*/
#ifndef __HARDWARE_H
#define __HARDWARE_H

// Make sure structures are packed as tightly as possible
#pragma pack(push, 1)

/** Defines a single pin on a slot
 *
 * This maps a Clixx slot and pin to one of the GPIO pins on the LPC1114.
 * For each pin we store the GPIO port, the pin number on that port and a
 * pointer to the IO configuration register for the pin.
 */
typedef struct _PINDEF {
  uint8_t             m_port;     //! The GPIO port (0 - 3)
  uint8_t             m_pin;      //! The GPIO pin (0 - 31)
  uint8_t             m_used;     //! If 0 this pin is not used
  uint8_t             m_reserved; //! Space this structure to a 32 bit value
  volatile uint32_t *m_iocon;    //! IO control register for this pin
  } PINDEF;

// Restore previous packing
#pragma pack(pop)

/** Pin definition table.
 *
 * This table contains the definitions for each of the four possible user
 * configurable pins on each of the 6 slots (24 entries). The table will be
 * stored in flash so it won't use any RAM.
 */
extern const PINDEF g_pindefs[];

#endif /* __HARDWARE_H */

