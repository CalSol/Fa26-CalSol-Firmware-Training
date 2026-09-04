
# What is UART?
UART is a Universal Asynchronous Receiver Transmitter protocol that is used for serial communication.
- What kind of protocol?
  - **Universal:** usable on <i>any</i> transmitting/receiving device.
  - **Asynchronous:** does not follow any clock/time, simply sends receives when it does.
  - **Receiver/Transmitter**: This protocol is for devices that transmit and receive data.
- Serial communication is the method of communication between devices where bits are sent along some wire/line or even remotely (like a TV remove to a TV!).

#### This communication happens via two wires.
- TX (transmission)
- RX (receive)
  - On your microcontroller, you'll choose which pins on it will connect to these wires.
 
### How to use UART?

Both the receiving and transmitting device should be configured to use UART before any data is sent. You must also configure...
- The **baud rate** (speed of data transmission)
- The length of the data sent/received (fixed amount)
The above configurations must be the same for both devices involved. More configurations also exist.


Sources: https://www.geeksforgeeks.org/computer-networks/universal-asynchronous-receiver-transmitter-uart-protocol/

