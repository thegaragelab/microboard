# Currently Available Microboard Systems

This directory contains the hardware design files (and supporting software) for
the currently available Microboard format systems. You can use the project file
in the 'template' directory to create your own board that matches the
Microboard footprint.

The currently available boards include:

## ATmega

This board design supports the 28 pin DIP ATmega series of CPUs. The board uses
an Arduino compatible boot loader and can be used with the Arduino IDE and
libraries.

## LPC1114

This board is based around the [NXP LPC1114FN28](http://www.nxp.com/products/microcontrollers/cortex_m0_m0/LPC1114FN28.html)
ARM Cortex-M0 chip in 28 pin DIP format. This chip has it's own built in
bootloader and a collection of supporting functions in the onboard ROM.

## PIC32MX

This board can be used with the 28 pin DIP versions of the [PIC32MX](http://www.microchip.com/ParamChartSearch/chart.aspx?branchID=211&mid=10&lang=en&pageId=74)
family of processors from Microchip. The board avoids using the USB specific
pins so it can be used with both the PIC32MX1xx and PIC32MX2xx variants.

## PIC16F1827

A board for the [PIC16F1827](http://www.microchip.com/wwwproducts/Devices.aspx?dDocName=en538963)
CPU in 18 pin DIP format.