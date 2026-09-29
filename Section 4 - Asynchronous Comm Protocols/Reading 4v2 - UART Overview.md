
# UART (Universal Asynchronous Receiver Transmitter) Overview

UART is one protocol to implement serial communication, a method of communication between devices where bits are sent along some wire/line or even remotely (like a TV remove to a TV!).

Important notes about UART:
- **Universal:** usable on <i>any</i> transmitting/receiving device
- **Asynchronous:** does not follow any shared clock, simply sends/receives when it has data (but both sides must agree on baud rate)
- **2 Wire:** **Transmit (TX)** and **Receive (RX)** (plus a common GND). TX of one device connects to RX of the other
- **One-to-One communication:** UART only communicates between 2 devices
- **Full-duplex:** TX and RX are separate lines, so both devices can talk at the same time
- **Speed:** Usually 9600 baud (bits per second), commonly up to 115200 baud. *Slow-to-moderate compared to SPI/USB; similar to I2C standard mode.*
- **Signaling:** Single-ended (logic-level voltage relative to GND)
- **Noise resistance:** Moderate. It is slow, which helps, but it is single-ended with no shielding or error correction (only an optional parity bit)


### Serial communication happens via two wires.
<img width="377" height="239" alt="image" src="https://github.com/user-attachments/assets/29e9b9bc-96e0-4354-941e-b4836159fae9" />

- <i>TX (transmission):</i>
  - the UART creates the data packets and sends them on this wire at a rate according to baud rate
- <i>RX (receive):</i>
  - the same UART circuitry also samples sent data from this wire at rate according to baud rate
- **These wires are the <i>Serial Bus</i>.** On your microcontroller, you'll choose which pins on it will connect to these wires.
  - In general, a bus refers to a set of data lines (wires) of transmission/receiving.
    - (Data is sent through signals along these wires, as described in previous reading) 

<i>Note:</i> Serial communication happens in almost any protocol (i.e. CAN, I2C), just conveniently introduced through UART here.

### How to use UART?

Both the receiving and transmitting device should be configured to use UART before any data is sent. You must also configure...
- The **baud rate** (speed of data transmission)
- The length of the data sent/received (fixed amount)
The above configurations must be the same for both devices involved. More configurations also exist.

**<i>More on how to configure this in another section!</i>**

## UART Bits Breakdown (Optional but useful read)

Each transmitted message in UART follows a structured format to ensure reliable communication between devices. Here’s a breakdown of each component:
- Start Bit (1 bit):
  - The start bit is always low (0), meaning the signal line transitions from idle (high) to active (low).
  - This alerts the receiver that a new data frame is starting and helps it synchronize with the transmitter’s timing.
  - Since UART is asynchronous (no shared clock), this synchronization is crucial for correct data interpretation.

- Data Frame (5 to 9 bits):
  - This is the actual payload of the transmission—the information being sent.
  - Most UART systems use an 8-bit data frame since it aligns well with standard byte-based systems. However, some systems may use 5, 6, 7, or even 9 bits depending on the application.
  - The least significant bit (LSB) is sent first, meaning the data is transmitted in little-endian order by default.

- Parity Bit (Optional, 0 to 1 bit):
  - This is an optional error-checking mechanism used to detect single-bit errors during transmission.
  - There are three common parity modes:
      - Even parity: Ensures the total number of 1s in the data frame is even. If necessary, the parity bit is set to 1 to maintain even parity.
      - Odd parity: Ensures the total number of 1s is odd by adjusting the parity bit accordingly.
      - No parity: The parity bit is omitted (common in high-speed or low-power applications).
  - While parity checking helps with error detection, it doesn’t correct errors, and more robust error-checking methods like CRC are used in critical systems.

- Stop Bits (1 to 2 bits):
  - The stop bit(s) are always high (1), signaling the end of the transmission.
  - 1 stop bit is the standard, but some systems use 2 stop bits for increased reliability, allowing the receiver more time to process the received data.
  - A longer stop bit duration can also help when communicating with slower devices that need more processing time between transmissions.

Together, these components ensure synchronized, reliable, and structured communication between UART devices, making it a widely used serial communication standard.



Sources: https://learn.sparkfun.com/tutorials/serial-communication/all (<--- This is a good read), https://www.geeksforgeeks.org/computer-networks/universal-asynchronous-receiver-transmitter-uart-protocol/

