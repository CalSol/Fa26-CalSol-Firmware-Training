# SPI (Serial Peripheral Interface) Overview

SPI is anoter protocol to implement serial communication, a method of communication between devices where bits are sent along some wire/line or even remotely (like a TV remove to a TV!).

Important notes about SPI:
- **Synchronous:** controller generates the clock
- **4+ Wires:** **SCLK** (clock), **MOSI** (controller out), **MISO** (controller in), **CS/SS** (chip select, one per peripheral)
- **One controller, many peripherals:** each extra peripheral needs another CS line
- **Full-duplex:** data goes out on MOSI and in on MISO simultaneously
- **No addressing or error checking:** simple and fast, but the protocol does not detect errors
- **Speed:** Typically 1-50 MHz, up to 100+ MHz on some parts. *One of the fastest simple serial buses: roughly 10-100x faster than I2C/UART.*
- **Signaling:** Single-ended
- **Noise resistance:** Poor. It runs faster than UART/I2C with sharp edges over single-ended lines, so it is more prone to noise, crosstalk, and ringing. Keep traces short and add series resistors or ground shielding if needed.


<img width="1144" height="1172" alt="image" src="https://github.com/user-attachments/assets/ab6845a6-1f14-405d-889a-b21bb7f73e7f" />
Similarly to I2C, SPI uses the Master/Slave naming convention.

### SPI Lines:
* MOSI (Master out, Slave in):
  * Carries data from the master to the slave.
* MISO (Master in, Slave out):
  * Carries data from the slave back to the master.
* SCLK (Serial Clock):
  * Works similarly to the I2C SCL line, creating a square wave to synchronize data.
  * On the rising edge of the SCLK line, the slave reads what is coming in from the MOSI line. On the falling edge, the MCU reads the MISO line.
* CS (Chip Select):
   * Each peripheral device has a separate Chip Select line connecting it to the microcontroller, which is pulled high (logic level 1). When the microcontroller wants to talk to that chip/device, it pulls the specific CS line down, waking the device up.
     * **IMPORTANT:** Only **one** CS line should be low at a time!!!
   * These CS lines are usually connected to the MCU via GPIO (General Purpose Input/Output) pins.

# IsoSPI (Isolated SPI) Overview
A variation of the SPI communication protocol that is more suitable for longer-distance communication (e.g. between boards), due to being differential and its resistance electromagnetic interference and ground loops. 

Important notes about isoSPI:
- **Isolated SPI:** Analog Devices' (Linear Tech) transformer-isolated variant of SPI, commonly used in battery management ICs (e.g., LTC681x)
- **2 Wire per link:** a twisted pair carrying differential pulses through an isolation transformer
- **Daisy-chainable:** devices are chained in series, so only the first device connects back to the controller (via a bridge such as the LTC6820)
- **Half-duplex:** one direction at a time on the pair
- **Galvanic isolation:** handles the large voltage differences between stacked battery modules
- **Speed:** 100 kbps to 1 Mbps. *Much slower than SPI, similar to CAN.*
- **Signaling:** Differential (pulse-coded through a transformer)
- **Noise resistance:** Excellent. Differential plus transformer isolation rejects common-mode noise, and cable runs of up to ~100 m are supported.

What are differential signals?
  - Using two wires instead of one to send signals (communicate) by having one send positive signal values and the other send the negative equivalent. The signal received will be the difference (through subtraction) between these high and low signals. This is so outside noise (which will distort the signal) affects both wires and cancels itself out with this method.
  - This makes it very useful for long-distance communication since it is much more resistant to noise!

<img width="425" height="470" alt="image" src="https://github.com/user-attachments/assets/b9a37463-286c-48af-8c89-5aeb6324c34a" />

Master Transceiver:
* A chip that encodes the 4 SPI lines into differential pulses, so the SPI code does not need to be changed at all
* Slave transceiver on the other side decodes these pulses into the conventional 4-line SPI protocol.


