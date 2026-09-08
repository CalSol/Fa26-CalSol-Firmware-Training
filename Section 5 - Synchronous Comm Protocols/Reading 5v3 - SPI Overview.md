# Serial Peripheral Interface (SPI) Overview

Four-Wire serial communication protocol for quick and short-distance communication between a microcontroller and peripheral ICs.

<img width="1144" height="1172" alt="image" src="https://github.com/user-attachments/assets/ab6845a6-1f14-405d-889a-b21bb7f73e7f" />
Similarly to I2C, SPI uses the Master/Slave naming convention.

## SPI Lines:
* MOSI (Master out, Slave in):
  * Carries data from the master to the slave.
* MISO (Master in, Slave out):
  * Carries data from the slave back to the master.
* SCLK (Serial Clock):
  * Works similarly to the I2C SCL line, creating a square wave to synchronize data.
  * On the rising edge of the SCLK line, the slave reads what is coming in from the MOSI line. On the falling edge, the MCU reads the MISO line.
* CS (Chip Select):
   * Each peripheral device has a separate Chip Select line connecting it to the microcontroller, which is pulled high (logic level 1). When the microcontroller wants to talk to that chip/device, it pulls the specific CS line down, waking the device up.
   * These CS lines are usually connected to the MCU via GPIO (General Purpose Input/Output) pins.

## Isolated SPI (IsoSPI)
A variation of the SPI communication protocol that is more suitable for longer-distance communication (e.g. between boards), due to resistance electromagnetic interference and ground loops. 

<img width="425" height="470" alt="image" src="https://github.com/user-attachments/assets/b9a37463-286c-48af-8c89-5aeb6324c34a" />

Master Transceiver:
* A chip that encodes the 4 SPI lines into differential pulses, so the SPI code does not need to be changed at all
* Detour: what is a **differential line**?
  * The twisted pair architecture (similar to what you saw in CAN) allows us to eliminate electromagnetic interference. Pulses are sent as mirror images of each other (through the HIGH and LOW lines that are twisted together) so that electromagnetic interference impacts both lines in exactly the same way.
  * Noise can be subtracted from the signal like this: (HIGH - LOW)/2, which doubles the signal and cancels out the noise
* Slave transceiver on the other side decodes these pulses into the conventional 4-line SPI protocol.


