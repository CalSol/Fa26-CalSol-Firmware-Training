// Simulated SPI wires and DAC (you don't need to edit this file)
//
// QEMU can't run the real SPI driver, so these functions pretend to be the 4 SPI wires.
// A simulated 12-bit DAC (Digital to Analog Converter, 0 -> 3.3 V) is connected on the other end.
// It prints what it receives, so you can see if your code is right.
//
// You are the master. Drive the wires in this order:
//   spi_cs(0)                   start talking to the DAC
//   for each bit (MSB first):
//       spi_mosi(bit)           put your bit on MOSI
//       spi_sclk(1)             rising edge: the DAC reads MOSI
//       spi_miso()              read the DAC's bit from MISO
//       spi_sclk(0)             falling edge: the DAC gets its next bit ready
//   spi_cs(1)                   done talking


#pragma once

void spi_cs(int level); // Chip Select (active low)
void spi_sclk(int level); // Serial Clock
void spi_mosi(int level); // Master Out, Slave In
int  spi_miso(void); // Master In, Slave Out
