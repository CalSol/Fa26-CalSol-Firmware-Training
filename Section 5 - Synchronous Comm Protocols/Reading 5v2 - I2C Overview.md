# I2C (Inter-Integrated Circuit) Overview

I2C is anoter protocol to implement serial communication, a method of communication between devices where bits are sent along some wire/line or even remotely (like a TV remove to a TV!).

Important notes about I2C:
- **Synchronous:** uses a shared clock line
- **2 Wire:** **SDA** (data) and **SCL** (clock), plus GND (more info later)
- **Multi-device:** one bus supports many peripherals, each with a 7-bit (or 10-bit) address; supports multiple controllers
- **Half-duplex:** SDA is bidirectional, so only one direction at a time
- **Open-drain:** needs **pull-up resistors** on SDA and SCL (typically 2.2k-10k)
- **Speed:** 100 kHz (standard), 400 kHz (fast), 1 MHz (fast-plus), 3.4 MHz (high-speed). *Similar to UART, slower than SPI.*
- **Signaling:** Single-ended
- **Noise resistance:** Fair to poor. Slower than SPI, but it is open-drain with weak pull-ups and a bus capacitance limit (~400 pF), so it is meant for short, on-board distances.
- *Requires Pull Up Resistors (more info later)*

### Master <--> Slave / Controller <--> Peripheral Communication

<img width="800" height="392" alt="image" src="https://github.com/user-attachments/assets/cf68fc32-088a-4398-8754-1c13d49d5b06" />

* I2C uses 2 lines: Serial Data Line (SDA) and Serial Clock Line (SCL) to communicate between the microcontroller (master) and peripherals (slaves)

SCL:
* Hardware: must be pulled up to 3.3V or 5V with a pull up resistor
* Controller device sets a clock pulse (usually on the order of 100-500 kbits/second) to synchronize devices
* For each pulse, 1 bit of data is send over the data (SDA) line.
  

SDA (Bidirectional): 
* Hardware: the SDA line must be pulled up to 3.3V or 5V with a pull up resistor so the idle state is high. Devices on the line will pull the voltage down to indicate logic low.
* Addressing: Each peripheral device has a 7 bit address, and listens to the data line at all times. Once it hears its address come from the microcontroller + an 8th bit (which indicates if the controller wants to read or write data from the peripheral), it pulls the SDA line low. This address is sometimes hardwired by connecting certain pins on the device to a given voltage rail.

<img width="1280" height="720" alt="image" src="https://github.com/user-attachments/assets/b7541661-5b60-4676-964a-764bd783726d" />

The microcontroller calls out the peripheral it wants to talk to, tells it if it wants to read or write data (with the R/W bit), transmits/receives data, and finally sends an acknowledgement (ACK) and stop command.

Implementation: most microcontrollers will have a built in library for I2C, which can be used with any I2C compatible device.



###  What if the microcontroller wants to talk to multiple devices at the same time?

Because all devices are on a shared *bus* on the same data line, only one peripheral device can communicate with the MCU at a time. However, this data is sent at a very fast rate (100 kBits/sec, around 100 kHz), so the MCU can speak to all these devices sequentially. 


### Pull Up Resistors

- I2C needs pull up resistors so that SDA/SCL are not floating (so it can switch from either HIGH or LOW)
- Larger pull up -> slower but more power efficient
  - 4.7kΩ is usually fine for CalSol purposes
