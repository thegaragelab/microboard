/*--------------------------------------------------------------------------*
* Microboard Interface Library
* Copyright (c) 2014, The Garage Lab (http://thegaragelab.com)
*---------------------------------------------------------------------------*
* 18-Jan-2014 ShaneG
*
* Initial version. Developed for the LPC1114 Microboard.
*--------------------------------------------------------------------------*/
#ifndef __MICROBOARD_H
#define __MICROBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

//--- Required definitions
#include <stdint.h>
#include <stdbool.h>

//---------------------------------------------------------------------------
// Common constants and definitions
//---------------------------------------------------------------------------

/** The available slots
 *
 * This defines the six available slots. There are three slots on the
 * general dock which can all be used as digital slots. SLOT0 on that port
 * can be configured for I2C operations and SLOT2 can be used as an analog
 * slot.
 *
 * The three slots on the SPI dock can only be used for SPI.
 */
typedef enum _SLOT {
  SLOT0 = 0, //! Slot 0 - can be digital or I2C
  SLOT1,     //! Slot 1 - always digital
  SLOT2,     //! Slot 2 - can be digital or analog
  SPI_SLOT0, //! SPI Slot 0
  SPI_SLOT1, //! SPI Slot 1
  SPI_SLOT2, //! SPI Slot 2
  } SLOT;

/** Pin definitions
 *
 * This defines the pins available on the various slots. Each of the general
 * slots has an INPUT pin (signal from CPU goes to the slot), an OUTPUT pin
 * (signal from the slot goes to the CPU) and an EXTRA pin (which can be used
 * in either direction.
 */
typedef enum _PIN {
  PIN_INPUT = 0, //! The input pin (relative to the Tab, is output from CPU)
  PIN_OUTPUT,    //! The output pin (relative to the Tab, is input to CPU)
  PIN_EXTRA,     //! The extra pin
  } PIN;

/** Pin direction
 *
 * Defines the direction of a single pin. Pin directions are defined from the
 * point of view of the slot so the OUTPUT direction means that data flows
 * from the slot to the CPU and the INPUT direction means that data flows from
 * the CPU to the slot.
 */
typedef enum _DIRECTION {
  OUTPUT = 0, //! The pin is an output
  INPUT,      //! The pin is an input
  } DIRECTION;

/** Bit order
 *
 * Defines the bit order for SPI transactions.
 */
typedef enum _BITORDER {
  LSBFIRST = 0, //! Send least significant bit first
  MSBFIRST,     //! Send most significant bit first
  } BITORDER;

/** Supported baud rates
 *
 * These constants define the supported baud rates. All implementations that
 * provide serial port access must at least support 9600 baud - higher data
 * rates are optional.
 */
typedef enum _BAUD {
  B9600 = 0, //! 9600 baud
  B19200,    //! 19200 baud
  B28800,    //! 28800 baud
  B56600,    //! 56600 baud
  B115200,   //! 115200 baud
  } BAUD;

//---------------------------------------------------------------------------
// Bring in implementation specific definitions
//---------------------------------------------------------------------------

#if defined(MICROBOARD_LPC1114)
#  include <microboard/lpc1114.h>
#elif defined(MICROBOARD_ATMEGA)
#  include <microboard/atmega.h>
#elif defined(MICROBOARD_PIC32)
#  include <microboard/pic32.h>
#elif defined(MICROBOARD_PIC16)
#  include <microboard/pic16.h>
#else
#  error "Unknown or unsupported board."
#endif

//---------------------------------------------------------------------------
// General purpose operations
//---------------------------------------------------------------------------

/** Board level initialisation
 *
 * This function does any system wide initialisation that is required. This
 * must be provided by all implementations but it may not do anything. It
 * must be the first function called by the user application.
 */
void mbInit(void);

/** Delay for a specified number of milliseconds
 *
 * This function blocks execution (interrupts will still be processed) for
 * the specified number of milliseconds. The delay period is specified as
 * an unsigned 16 bit integer allowing for a maximum delay of approximately
 * 16.5 seconds.
 *
 * Most implementations of this function will be expected to use a timer to
 * determine the delay period and should be reasonably accurate for periods
 * >= 10ms.
 *
 * @param period the number of millseconds to delay for.
 */
void mbDelay(uint16_t period);

//---------------------------------------------------------------------------
// Digital operations
//
// These operations are provided by all implementations.
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
void mbInitDigital(SLOT slot, PIN pin, DIRECTION direction);

/** Initialise a slot for digital operations.
 *
 * This initialises the specified slot for digital IO. This is a shortcut
 * function that sets the 'standard' operations of each of the pins on the
 * slot. By default the EXTRA pin is configured to be an OUTPUT (from the
 * point of view of the peripheral).
 *
 * @param slot the slot to initialise. This may be any of the generic slots.
 */
void mbInitSlot(SLOT slot);

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
void mbDigitalSet(SLOT slot, PIN pin, bool value);

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
bool mbDigitalGet(SLOT slot, PIN pin);

/** Shift an 8 bit value out a pair of pins
 *
 * This function provides a 'poor mans SPI' by shifting an 8 bit value out
 * using a data pin (configured as INPUT relative to the peripheral) and
 * a clock pin (configured as INPUT relative to the peripheral).
 *
 * This is useful for controlling a shift register or a write only SPI
 * device (like an LCD screen).
 *
 * @param slot the slot to use. This may be any generic slot (SLOT0 to SLOT2)
 *             that has been configured as a binary slot.
 * @param data the pin to use as the data pin. Typically this will be
 *             PIN_INPUT.
 * @param clock the pin to use as the clock pin. Typicall this will be
 *              PIN_EXTRA.
 * @param order the bit order to use - either LSBFIRST or MSBFIRST.
 * @param value the 8 bit value to shift out.
 */
void mbDigitalShift(SLOT slot, PIN data, PIN clock, BITORDER order, uint8_t value);

/** Shift a 16 bit value out a pair of pins
 *
 * This function provides a 'poor mans SPI' by shifting a 16 bit value out
 * using a data pin (configured as INPUT relative to the peripheral) and
 * a clock pin (configured as INPUT relative to the peripheral).
 *
 * This is useful for controlling a shift register or a write only SPI
 * device (like an LCD screen).
 *
 * @param slot the slot to use. This may be any generic slot (SLOT0 to SLOT2)
 *             that has been configured as a binary slot.
 * @param data the pin to use as the data pin. Typically this will be
 *             PIN_INPUT.
 * @param clock the pin to use as the clock pin. Typicall this will be
 *              PIN_EXTRA.
 * @param order the bit order to use - either LSBFIRST or MSBFIRST.
 * @param value the 16 bit value to shift out.
 */
void mbDigitalShift16(SLOT slot, PIN data, PIN clock, BITORDER order, uint16_t value);

//---------------------------------------------------------------------------
// SPI Operations
//---------------------------------------------------------------------------

/** Initialise the SPI interface
 *
 * Sets up the SPI dock for operation. In most implementations this will use
 * the hardware SPI module of the CPU if available, if the board does not
 * support hardware SPI it will be simulated in software.
 *
 * This function configures the EXTRA pin of all three SPI ports as an
 * OUTPUT pin (data flow from peripheral to CPU). You can modify this by
 * calling the 'mbDigitalInit()' function after SPI initialisation.
 */
void mbInitSPI(void);

/** Transfer a single byte through an SPI slot
 *
 * This function will simultaneously send and receive a single byte through
 * the specified SPI slot. The ENABLE pin of the specified port will be
 * pulled low and a single bit will be sent on MOSI and read on MISO with
 * each transition of the CLK pin. After all 8 bits have been transferred
 * the ENABLE pin will be pulled high again.
 *
 * @param slot the slot to use for the transfer. This must be one of the SPI
 *             slots (SPI_SLOT0, SPI_SLOT1 & SPI_SLOT2).
 * @param order the bit order to use for transfer.
 * @param data an 8 bit value to send to the SPI device.
 *
 * @return the 8 bit value received from the SPI device.
 */
uint8_t mbSPITransferByte(SLOT slot, BITORDER order, uint8_t data);

/** Transfer a block of data through an SPI slot
 *
 * This function will simultaneously send and receive a block of data through
 * the specified SPI slot. The ENABLE pin of the specified port will be
 * pulled low and a single bit will be sent on MOSI and read on MISO with
 * each transition of the CLK pin. After all bytes have been transferred
 * the ENABLE pin will be pulled high again.
 *
 * @param slot the slot to use for the transfer. This must be one of the SPI
 *             slots (SPI_SLOT0, SPI_SLOT1 & SPI_SLOT2).
 * @param order the bit order to use for transfer.
 * @param pDataOut a pointer to an array containing the data to be sent. If
 *                 this value is NULL then the value zero will be used
 *                 instead.
 * @param pDataIn a pointer to an array to hold the data received. If this
 *                value is NULL then received data will be discarded.
 * @param size the number of bytes to process. If either pDataOut or pDataIn
 *             are not NULL they must be at least this many bytes in size.
 *
 * @return the number of bytes processed.
 *
 */
uint16_t mbSPITransfer(SLOT slot, BITORDER order, uint8_t *pDataOut, uint8_t *pDataIn, uint16_t size);

//---------------------------------------------------------------------------
// Analog operations
//
// These operations are optional and can be tested for by the MB_OPT_ANALOG
// define. If an implementation sets MB_OPT_ANALOG it must also set the
// following defines:
//
//  MB_ANALOG_MAX_GET - the maximum value returned by 'mbAnalogGet()'
//  MB_ANALOG_MAX_SET - the maximum value accepted by 'mbAnalogSet()'
//
// The implementation may also set the following:
//
//  MB_ANALOG_SET - if defined then analog values can be set with the function
//                  'mbAnalogSet()'.
//---------------------------------------------------------------------------

#ifdef MB_OPT_ANALOG

/** Configure an analog pin on SLOT2
 *
 * This function is used to configure analog operations on a pin on SLOT2.
 * If the direction is set to OUTPUT the ADC attached to the pin will be
 * configured appropriately. If the direction is set to INPUT the pin will
 * configured to use a DAC (if available) or PWM to be able to generate an
 * analog value.
 *
 * The behaviour of the analog port is very dependent on the target device,
 * please refer to the specific documentation for the device you are using
 * for more details.
 *
 * @param pin the pin to modify. This may be any of the three available pins
 *            on SLOT2.
 * @param direction the direction of the pin (relative to the peripheral).
 */
void mbInitAnalog(PIN pin, DIRECTION direction);

/** Get the value of an analog pin on SLOT2
 *
 * Gets the current value being sampled by the pin on SLOT2. The behaviour
 * of this function (and the range of returned values) is implementation
 * specific.
 *
 * @param pin the pin the get the value for. This pin must have been defined
 *            as an OUTPUT pin with the 'mbInitAnalog()' function prior to
 *            calling this function.
 *
 * @return a 16 bit value indicating what is currently being presented to
 *         the pin. The range of this value is implementation specific.
 */
uint16_t mbAnalogGet(PIN pin);

#ifdef MB_ANALOG_SET
/** Set the value of an analog pin on SLOT2
 *
 * Sets the current analog value on a pin on SLOT2. The behaviour of this
 * operation (and the range of allowable values) is implementation specific.
 * In many cases the analog value is simulated using PWM - you will have to
 * take this into account in your circuit.
 *
 * This function may not be supported by all implementations in which case
 * it will silently fail.
 *
 * @param pin the pin to set the value for. This pin must have been defined
 *            as an INPUT pin with the 'mbInitAnalog()' function prior to
 *            calling this function.
 * @param value a 16 bit value determining the value of the signal.
 */
void mbAnalogSet(PIN pin, uint16_t value);
#endif /* MB_ANALOG_SET */

#endif /* MB_OPT_ANALOG */

//---------------------------------------------------------------------------
// I2C Operations
//
// These operations are optional and can be tested for by the MB_OPT_I2C
// define.
//---------------------------------------------------------------------------

#ifdef MB_OPT_I2C
/** I2C Initialisation
 *
 * This function enables I2C functionality on SLOT0 of the general dock. If
 * available the CPU's hardware I2C support will be used.  The
 * INPUT and OUTPUT pins of SLOT0 will become SCL and SDA and the EXTRA pin
 * will be configured as an OUTPUT pin. The configuration of the EXTRA pin
 * may be changed at any time by calling 'mbDigitalInit()', reconfiguring
 * PIN_INPUT or PIN_OUTPUT for SLOT0 after I2C initialisation will break the
 * I2C functionality.
 */
void mbInitI2C();

/** Write a single register on the target I2C address
 *
 * This function writes a single value to the specified register on the device
 * at the given address.
 *
 * @param address the address of the I2C slave to write to.
 * @param reg the number of the register to write to.
 * @param data the value to write to the specified register.
 */
void mbI2CWriteRegister(uint8_t address, uint8_t reg, uint8_t data);

/** Write multiple registers on the target I2C address
 *
 * This function writes to multiple contiguous registers on slave devices that
 * support the operation.
 *
 * @param address the address of the I2C slave to write to.
 * @param reg the number of the first register to write to.
 * @param pData a pointer to an array of bytes to write.
 * @param size the number of registers to set.
 *
 * @return the number of registers written in this operation
 */
uint8_t mbI2CWriteBlock(uint8_t address, uint8_t reg, uint8_t *pData, uint8_t size);

/** Read a single register from the I2C slave device
 *
 * This function reads the value of a single register on the specified I2C
 * slave.
 *
 * @param address the address of the I2C slave to communicate with
 * @param reg the number of the register to read.
 *
 * @return the value read from the register.
 */
uint8_t mbI2CReadRegister(uint8_t address, uint8_t reg);

/** Read multiple registers from the target I2C address
 *
 * This function reads from multiple contiguous registers on slave devices
 * that support the operation.
 *
 * @param address the address of the I2C slave to read from.
 * @param reg the number of the first register to read from.
 * @param pData a pointer to an array of bytes to read. This must point to
 *              an area of memory capable of holding the requested number
 *              of bytes.
 * @param size the number of registers to read.
 *
 * @return the number of registers read in this operation
 */
uint8_t mbI2CReadBlock(uint8_t address, uint8_t reg, uint8_t *pData, uint8_t size);

#endif /* MB_OPT_I2C */

//---------------------------------------------------------------------------
// Serial Operations
//
// These operations are optional and can be tested for by the MB_OPT_SERIAL
// define.
//---------------------------------------------------------------------------

#ifdef MB_OPT_SERIAL
/** Initialise the serial port
 *
 * This function will set up the serial port on the CPU with the specified
 * baud rate at 8N1 (8 data bits, no parity and 1 stop bit). If available
 * this function is guaranteed to allow at least 9600 baud over the port,
 * higher speeds may be available in different implementations.
 *
 * @param baud the baud rate to use on the port.
 *
 * @return true if the initialisation succeeded, false otherwise.
 */
bool mbInitSerial(BAUD baud);

/** Write a single byte to the serial port
 *
 * This function sends a single 8 bit value to the serial port. It is a
 * non blocking function and will return immediately if the data cannot be
 * sent (or if the serial port has not been initialised).
 *
 * @param data the byte to send
 *
 * @return true if the byte was queued for transmission, false if the output
 *              queue is full or if the serial port has not been initialised.
 */
bool mbSerialWrite(uint8_t data);

/** Write a block of data to the serial port
 *
 * This function will write a sequence of bytes to the serial port. It is
 * a non-blocking function and will return when no more bytes can be queued
 * for output or if the serial port has not been initialised.
 *
 * @param pData a pointer to the block of data to be sent.
 * @param offset the offset into pData to start sending from.
 * @param size the number of bytes that should be sent.
 *
 * @return the number of bytes that were actually sent.
 */
uint16_t mbSerialWriteData(uint8_t *pData, uint16_t offset, uint16_t size);

/** Write a string to the serial port
 *
 * This function writes a zero terminated string to the serial port. It is
 * a blocking function and will not return until the entire string has been
 * sent.
 *
 * @param cszString the string to write to the serial port.
 *
 * @return the number of characters actually written to the port.
 */
uint16_t mbSerialWriteString(const char *cszString);

/** Write an integer to the serial port
 *
 * This is a helper function to write the value of an unsigned 32 bit
 * integer in base 10 to the serial port. This is a blocking operation
 * and will not return until the entire string has been sent.
 *
 * @param value the unsigned 32 bit value to display in base 10.
 *
 * @return the number of bytes that were actually written.
 */
uint16_t mbSerialWriteInt(uint32_t value);

/** Write a hex value to the serial port
 *
 * This is a helper function to write the value of an unsigned 32 bit
 * integer in base 16 to the serial port. This is a blocking operation
 * and will not return until the entire string has been sent.
 *
 * @param value the unsigned 32 bit value to display in base 16.
 * @param digits the minimum number of digits to display. If the value
 *               requires less than this number of digits it will be
 *               padded to the left with zeros.
 */
uint16_t mbSerialWriteHex(uint32_t value, uint16_t digits);

/** Determine if data is available for reading
 *
 * This function checks if data is available on the serial port for
 * immediate reading.
 *
 * @return true if attempting to read from the serial port will return at
 *         least one byte.
 */
bool mbSerialReady();

/** Read a single byte from the serial port
 *
 * This function will read a single 8 bit value from the serial port. This
 * is a non-blocking function and will return immediately if there is no
 * data available.
 *
 * @param pData a pointer to the location to store the byte read.
 *
 * @return true if a byte was read, false if no data is available.
 */
bool mbSerialRead(uint8_t *pData);

/** Read a block of data from the serial port
 *
 * This function will read a block of data from the serial port. It is a
 * non-blocking function and will return if there is no more data available
 * to read.
 *
 * @param pData pointer to a buffer to hold the read data.
 * @param offset offset into pData to start writing the read data.
 * @param size the maximum number of bytes to read in this call.
 *
 * @return the actual number of bytes read in this call.
 *
 */
uint16_t mbSerialReadData(uint8_t *pData, uint16_t offset, uint16_t size);

/** Read a string from the serial port
 *
 * This is a helper function to read a string (terminated by a CR/LF pair).
 * This is a blocking function, it will not return until a string (with
 * terminator) has been read or until the buffer is full.
 *
 * The terminating character sequence is not placed in the input buffer,
 * it will be trimmed.
 *
 * @param szString the buffer to contain the (zero terminated) result.
 * @param size the size of the buffer pointed to by szString. This must
 *             be greater than or equal to 2 (to allow for the terminating
 *             characters to be stored and recognised).
 *
 * @return the number of characters (excluding the zero terminator) placed
 *         in szString. The maximum return value will be two less than
 *         'size'. If the return value is zero then szString may not
 *         represent a null terminated string.
 */
uint16_t mbSerialReadString(char *szString, uint16_t size);

#endif /* MB_OPT_SERIAL */

#ifdef __cplusplus
}
#endif

#endif /* __MICROBOARD_H */
