/*---------------------------------------------------------------------------*
* Board initialisation and common data
*----------------------------------------------------------------------------*
* 23-Jan-2014 ShaneG
*
*  Implements the 'mbInit()' function as well as defining the static arrays
*  needed throughout the library.
*--------------------------------------------------------------------------*/
#include <microboard.h>
#include "lpc111x.h"
#include "syscon.h"

//! System tick count
static volatile uint16_t g_systicks;

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
  SCB_SYSOSCCTRL = 0;                      // "lower speed" crystals
  SCB_PDRUNCFG &= ~PDRUNCFG_SYSOSC_PD;     // power-up main oscillator

  SCB_PLLCLKSEL = SYSPLLCLKSEL_SEL_IRC; // select main oscillator as the input clock for PLL
  SCB_PLLCLKUEN = 0;                    // confirm the change of PLL input clock by toggling the...
  SCB_PLLCLKUEN = SYSPLLUEN_ENA;        // ...ENA bit in SCB_SYSPLLCLKUEN register

  // calculate PLL parameters
  m = FREQ_CPU / FREQ_CRYSTAL;  // M is the PLL multiplier
  frequency = FREQ_CRYSTAL * m; // Calculate the 'actual' core frequency
  fcco = frequency * 2;         // FCCO is the internal PLL frequency
  while(fcco < 156000000) {
    fcco *= 2;
    p++;  // find P which gives FCCO in the allowed range (over 156MHz)
    }

  // Configure the PLL and power it up
  SCB_PLLCTRL = ((m - 1) << SYSPLLCTRL_MSEL_bit) | (p << SYSPLLCTRL_PSEL_bit);
  SCB_PDRUNCFG &= ~PDRUNCFG_SYSPLL_PD;

  // Wait for the PLL to lock
  while (!(SCB_PLLSTAT & SYSPLLSTAT_LOCK));

  // Switch to PLL output as the main clock
  SCB_MAINCLKSEL = MAINCLKSEL_SEL_PLLOUT; // select PLL output as the main clock
  SCB_MAINCLKUEN = 0;                     // confirm the change of main clock by toggling the...
  SCB_MAINCLKUEN = MAINCLKUEN_ENA;        // ...ENA bit in LPC_SYSCON->MAINCLKUEN register
  SCB_SYSAHBCLKDIV = 1;                   // set AHB clock divider to 1
  }

/** System tick handler
 *
 * This function is invoked by the SysTick interrupt. It simply updates a 16
 * bit counter (ignoring overflow).
 */
void SysTick_Handler (void) {
  g_systicks++;
  }

//---------------------------------------------------------------------------
// Public API
//---------------------------------------------------------------------------

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
  SCB_SYSAHBCLKCTRL |= SYSAHBCLKCTRL_IOCON;
  // Configure the SYSTICK timer for 1ms operation
  SYSTICK_STRELOAD  = ((FREQ_CPU / 1000) & SYSTICK_STRELOAD_MASK) - 1;
  SYSTICK_STCURR = 0;
  SYSTICK_STCTRL = SYSTICK_STCTRL_CLKSOURCE | SYSTICK_STCTRL_TICKINT;
  }

/** Delay for a specified number of milliseconds
 *
 * This function blocks execution (interrupts will still be processed) for
 * the specified number of milliseconds. The delay period is specified as
 * an unsigned 16 bit integer allowing for a maximum delay of approximately
 * 65 seconds.
 *
 * Most implementations of this function will be expected to use a timer to
 * determine the delay period and should be reasonably accurate for periods
 * >= 10ms.
 *
 * @param period the number of millseconds to delay for.
 */
void mbDelay(uint16_t period) {
  // No delay, return immediately
  if(period==0)
    return;
  // Reset counter
  g_systicks = 0;
  // Enable the SYSTICK interrupt
  SYSTICK_STCTRL |= SYSTICK_STCTRL_ENABLE;
  // Wait for the time to expire
  while(g_systicks<period);
  // Disable the interrupt
  SYSTICK_STCTRL &= ~SYSTICK_STCTRL_ENABLE;
  }

