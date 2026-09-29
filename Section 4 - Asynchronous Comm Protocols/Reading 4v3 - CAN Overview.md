# CAN (Controller Area Network) Overview

CAN is anoter protocol to implement serial communication, a method of communication between devices where bits are sent along some wire/line or even remotely (like a TV remove to a TV!). 
- Intuitively, CAN is a network (place where devices connect and share data) that lets the (electrical) controllers all around the car communicate with each other.
- Formally, the **CAN Bus** is the system that enables **communication between ECU's** (basically each circuit board in the car meant to control a specific part, i.e. pedals, lights).

## Important notes about CAN:
- **Asynchronous:** no dedicated clock line; nodes resync to bit edges in the data
- **2 Wire:** **CAN_H** and **CAN_L** twisted pair
- **Multi-master bus:** any node can transmit; many nodes share the same two wires
- **Message-based:** messages carry an ID (not a device address); the lowest ID wins arbitration, so higher-priority messages are never lost
- **Half-duplex:** one node transmits at a time
- **Built-in reliability:** CRC, ACK, and automatic retransmission on error
- **Termination:** 120 Ω resistors at both ends of the bus
- **Speed:** Up to 1 Mbps (classic CAN), up to ~5-8 Mbps (CAN FD). *Faster than UART/I2C standard mode, much slower than SPI/USB. Speed trades off against bus length (1 Mbps ≈ 40 m, 125 kbps ≈ 500 m).*
- **Signaling:** Differential (CAN_H vs CAN_L)
- **Noise resistance:** Excellent. Differential signaling rejects common-mode noise, which is why it is the standard in cars and other electrically noisy environments.

<img width="369" height="129" alt="image" src="https://github.com/user-attachments/assets/b96ba3cb-d4e3-4f53-aa17-6672f896a4c0" />




### How does CAN Bus Work?
It uses two **differential** wires (CAN HIGH and CAN LOW), and all ECU's each connect to both, and communicate (accept, send, or ignore messages)  along these wires.

What are differential signals?
  - Using two wires instead of one to send signals (communicate) by having one send positive signal values and the other send the negative equivalent. The signal received will be the difference (through subtraction) between these high and low signals. This is so outside noise (which will distort the signal) affects both wires and cancels itself out with this method.
  - This makes it very useful for long-distance communication since it is much more resistant to noise!

<img width="382" height="203" alt="image" src="https://github.com/user-attachments/assets/d5875e11-5f84-492a-8ee5-ce50925555a1" />

#### <i>ECU Requirements</i>
Each ECU (board that can communicate with other ECU's) must have...
- A **microcontroller (MCU)** to process messages and make decisions, like a brain, i.e. the ESP32.
- A **CAN Controller** to keep communication actions in line with CAN protocol (or the rules). Does the work behind MCU decisions. Sometimes built into the MCU.
- A **CAN Transceiver (Transmitter and Receiver at the same time!)** Connects to CAN Controller to send messages it encodes as signals to other ECU's (differential signals specifically).
<img width="299" height="280" alt="image" src="https://github.com/user-attachments/assets/eb50b49b-caf1-4933-94d8-602b3a147056" />


### What do ECU's send to each other? (CAN Frames)
These are the message containers (also called CAN Packets, or just frames) that are sent across the CAN network. 
<img width="697" height="170" alt="image" src="https://github.com/user-attachments/assets/82794d08-e40e-415e-b844-54e9cefa8abd" />


<sup><sub>From [CAN Bus Simple Intro](https://www.csselectronics.com/pages/can-bus-simple-intro-tutorial)</sub><sup>


They have 8 parts shown in the image above. The three (highlighted) used in this lab are:
- **ID:** The identifier (name) of the CAN frame. **Lower values have higher priority** for viewing.
- **The data (0-8 bytes):** Also called **payload.** They're the content sent that other devices should understand.
  - Each byte is 8 bits (eight 1s or 0s). 8 bytes = 64 bits.
  - <i>DLC:</i> The length of the data.
 The 6 other parts are well-explained in the sources below.

In this lab, you'll send a CAN Packet whose payload determines what information is sent to other devices. 



Source: https://www.csselectronics.com/pages/can-bus-simple-intro-tutorial, https://www.ni.com/en/shop/seamlessly-connect-to-third-party-devices-and-supervisory-system/controller-area-network--can--overview.html?srsltid=AfmBOorU1zvAJigLmHfHU1ybkgBWtry8Tv-Zwm5Jaf2WLQuyYqfSllEi
