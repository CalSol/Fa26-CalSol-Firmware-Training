
# What is UART?
UART is a block of circuitry that implements serial communication through its Universal Asynchronous Receiver Transmitter protocol.
- What kind of protocol?
  - **Universal:** usable on <i>any</i> transmitting/receiving device.
  - **Asynchronous:** does not follow any clock/time, simply sends receives when it does.
  - **Receiver/Transmitter**: This protocol is for devices that transmit and receive data.
- Serial communication is the method of communication between devices where bits are sent along some wire/line or even remotely (like a TV remove to a TV!).
- UART exists in most microcontrollers, including our ESP32.

### Serial communication happens via two wires.
<img width="377" height="239" alt="image" src="https://github.com/user-attachments/assets/29e9b9bc-96e0-4354-941e-b4836159fae9" />

- <i>TX (transmission):</i>
  - the UART creates the data packets and sends them on this wire at a rate according to baud rate
- <i>RX (receive):</i>
  - the same UART circuitry also samples sent data from this wire at rate according to baud rate
- **These wires are the <i>Serial Bus</i>.** On your microcontroller, you'll choose which pins on it will connect to these wires.
  - In general, a bus refers to a set of data lines (wires) of transmission/receiving.
<br><br>
<i>Note:</i> Serial communication happens in almost any protocol (i.e. CAN, I2C), just conveniently introduced through UART here.
<br><br>
### How to use UART?

Both the receiving and transmitting device should be configured to use UART before any data is sent. You must also configure...
- The **baud rate** (speed of data transmission)
- The length of the data sent/received (fixed amount)
The above configurations must be the same for both devices involved. More configurations also exist.

**<i>More on how to configure this in another section!</i>**


Sources: https://learn.sparkfun.com/tutorials/serial-communication/all (<--- This is a good read), https://www.geeksforgeeks.org/computer-networks/universal-asynchronous-receiver-transmitter-uart-protocol/

