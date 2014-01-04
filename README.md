# Microboard MCU Prototyping System

The Microboard form factor is a simple breakout board for various MCUs that
integrates with the [Clixx.IO](http://clixx.io) rapid prototyping system through
a set of external docks. It's goal is to allow the rapid development of
microcontroller based projects using Clixx.

The board design has a number of requirements:

* Each PCB is 40mm x 50mm
* The board (regardless of CPU) supports a serial bootloader. A 6 pin FTDI
  header is provided on the board to allow this to be done with a standard
  FTDI cable.
* The board provides a 2 pin header for power input and a 2 pin header for
  a RESET or PROGRAM button.
* Two 11 pin headers are provided to connect to
  [Clixx docking stations](http://thegaragelab.com/posts/modular-clixxio-docking-stations.html).
  One connector supports the SPI dock, the other the general dock.
* All headers are in a consistant location (and spaced at 0.1" pitch) to allow
  stacking of daughter boards if required.

Board designs can be found in the 'boards' directory. All schematics are in
[Fritzing](http://fritzing.org/home/) format. There is a template project
available in 'boards/template' that can be used to design a board for your
own MCU.
