/*---------------------------------------------------------------------------*
* Board initialisation and common data
*----------------------------------------------------------------------------*
* 23-Jan-2014 ShaneG
*
*  Implements the 'mbInit()' function as well as defining the static arrays
*  needed throughout the library.
*--------------------------------------------------------------------------*/
#include <microboard.h>
#include "cmsis/LPC11xx.h"
#include "syscon.h"

/** Initialise the system clock
 *
 * Configures and enables the PLL to achieve FREQ_CPU with the internal RC
 * resonator. Before the speed change flash access time is tuned to allow
 * faster core speeds. The PLL is configured, started and selected as the
 * main clock. AHB clock divider is set to 1.
 */
static void initSystemClock(void) {
  uint32_t frequency, m, p = 0, fcco;

  // Adjust the flash access time to support higher core frequencies
  frequency = FLASHCFG;
  frequency &= ~(FLASHCFG_FLASHTIM_mask << FLASHCFG_FLASHTIM_bit);
  frequency |= FLASHCFG_FLASHTIM_3CLK << FLASHCFG_FLASHTIM_bit;
  FLASHCFG = frequency;
  // Set up clock control
  LPC_SYSCON->SYSOSCCTRL = 0;                      // "lower speed" crystals
  LPC_SYSCON->PDRUNCFG &= ~PDRUNCFG_SYSOSC_PD;     // power-up main oscillator

  LPC_SYSCON->SYSPLLCLKSEL = SYSPLLCLKSEL_SEL_IRC; // select main oscillator as the input clock for PLL
  LPC_SYSCON->SYSPLLCLKUEN = 0;                    // confirm the change of PLL input clock by toggling the...
  LPC_SYSCON->SYSPLLCLKUEN = SYSPLLUEN_ENA;        // ...ENA bit in LPC_SYSCON->SYSPLLCLKUEN register

  // calculate PLL parameters
  m = FREQ_CPU / FREQ_CRYSTAL;  // M is the PLL multiplier
  frequency = FREQ_CRYSTAL * m; // Calculate the 'actual' core frequency
  fcco = frequency * 2;         // FCCO is the internal PLL frequency
  while(fcco < 156000000) {
    fcco *= 2;
    p++;  // find P which gives FCCO in the allowed range (over 156MHz)
    }

  // Configure the PLL and power it up
  LPC_SYSCON->SYSPLLCTRL = ((m - 1) << SYSPLLCTRL_MSEL_bit) | (p << SYSPLLCTRL_PSEL_bit);
  LPC_SYSCON->PDRUNCFG &= ~PDRUNCFG_SYSPLL_PD;

  // Wait for the PLL to lock
  while (!(LPC_SYSCON->SYSPLLSTAT & SYSPLLSTAT_LOCK));

  // Switch to PLL output as the main clock
  LPC_SYSCON->MAINCLKSEL = MAINCLKSEL_SEL_PLLOUT; // select PLL output as the main clock
  LPC_SYSCON->MAINCLKUEN = 0;                     // confirm the change of main clock by toggling the...
  LPC_SYSCON->MAINCLKUEN = MAINCLKUEN_ENA;        // ...ENA bit in LPC_SYSCON->MAINCLKUEN register
  LPC_SYSCON->SYSAHBCLKDIV = 1;                   // set AHB clock divider to 1
  }

/** Board level initialisation
 *
 * This function does any system wide initialisation that is required. This
 * must be provided by all implementations but it may not do anything. It
 * must be the first function called by the user application.
 */
void mbInit(void) {
  // Initialise the system clock
  initSystemClock();
  // Enable clock for the IO configuration block
  LPC_SYSCON->SYSAHBCLKCTRL |= SYSAHBCLKCTRL_IOCON;
  }

