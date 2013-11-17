# PIC16F1827 Microboard

This board contains the PIC16F1827 CPU at the core, one of the mid-range
controllers from Microchip. In this design both I2C and Serial communications
are provided by the onboard hardware. SPI is simulated over GPIO chips (this
is due to pin assignment conflicts which do not allow all 3 UARTS to be used
simultaneously).

Due to the low pin count a number of the *extra* pins on various docks are not
implemented. Slot 1 and Slot 2 on the general dock can be used as either
digital or analog slots. The *input* pin (to the TwinTab) is driver by a PWM
output (for Slot 1) or the onboard DAC (for Slot 2).

