/*---------------------------------------------------------------------------*
* Main program template.
*---------------------------------------------------------------------------*/
#include <microboard.h>

/** Initialisation
 *
 * Use this function to do any one time initialisation. The main Microboard
 * will already have been called so you only need to initialise the slots and
 * features you intend to use in your program.
 */
static void init(void) {
  // TODO: Initialise any required slots
  // TODO: Set up any peripherials used
  }

/** Main program loop
 *
 * This function is called for every iteration of the main program loop.
 */
static void loop(void) {
  // TODO: Implement this
  }

/** Program entry point
 *
 * Initialise the Microboard and any needed peripherals and then go into the
 * main processing loop.
 */
int main(void) {
  mbInit();
  // Program specific initialisation
  init();
  // Main loop
  while(1)
    loop();
  // Should never get here
  return 0;
  }
