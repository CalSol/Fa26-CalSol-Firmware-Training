# Quick Reference of Comm Protocols

## Asynchronous Comm Protocols 

### UART (Universal Asynchronous Receiver Transmitter)
- Go to [Reading 4v2 - UART Overview](<../Section 4 - Asynchronous Comm Protocols/Reading 4v2 - UART Overview.md>)

### CAN (Controller Area Network) 
- Go to [Reading 4v3 - CAN Overview](<../Section 4 - Asynchronous Comm Protocols/Reading 4v3 - CAN Overview.md>)

### RS485 (Recommended Standard 485)
Important notes about RS485:
- **Physical layer only:** defines voltage levels, not a protocol. Usually carries UART frames (e.g., Modbus RTU)
- **Asynchronous** (when used with UART framing)
- **2 Wire (half-duplex)** **A** and **B** twisted pair, or **4 Wire (full-duplex)**
- **Multi-drop:** typically 32 nodes on one bus (up to 256 with modern low-load transceivers)
- **Needs a transceiver chip** (e.g., MAX485) between the UART and the bus
- **Termination:** 120 Ω resistors at both ends
- **Speed:** Up to 10 Mbps on short runs, ~100 kbps at 1200 m. *Comparable to CAN; much longer range than UART/SPI/I2C.*
- **Signaling:** Differential (A vs B)
- **Noise resistance:** Excellent. It is built for long cables in industrial environments.

### USB 2.0
Important notes about USB (D+/D-):
- Typically used for flashing firmware (From USB to MCU)
- **Asynchronous data lines:** the receiver recovers the clock from the data itself (NRZI encoding with bit stuffing)
- **4 Wire (USB 2.0):** **D+**, **D-**, **VBUS** (5 V power), and **GND**
- **Host-controlled:** one host polls many devices (through hubs); devices never talk unless asked
- **Half-duplex** on D+/D-
- **Plug-and-play:** enumeration and device classes are built in
- **Speed:** Low-speed 1.5 Mbps, Full-speed 12 Mbps, High-speed 480 Mbps. *Full-speed is already faster than UART/I2C/CAN; High-speed is on par with or faster than most SPI setups.*
- **Signaling:** Differential (D+ vs D-), with 90 Ω impedance-matched routing
- **Noise resistance:** Very good. Differential signaling, controlled impedance, and error detection (CRC, retries). Cable length is limited to ~5 m per segment.

### Ethernet
Important notes about Ethernet:
- **Asynchronous (self-clocked):** no separate clock line; the receiver recovers the clock from the encoded data (Manchester on 10BASE-T, MLT-3 on 100BASE-TX, PAM-5 on 1000BASE-T)
- **Twisted-pair cable:** 2 pairs (4 wires) for 10/100 Mbps, 4 pairs (8 wires) for 1 Gbps. Uses an RJ45 connector
- **Point-to-point links:** each cable connects 2 devices; **switches** connect many devices into a network
- **Full-duplex:** modern links transmit and receive simultaneously (older hub-based networks were half-duplex with collisions)
- **Addressing and framing:** every device has a unique 48-bit **MAC address**, and frames include a CRC32 to detect errors
- **Needs a MAC + PHY:** the MCU's MAC talks to an Ethernet PHY chip over **MII/RMII**, and the PHY connects to the cable through **magnetics** (transformers). Some parts, like the WIZnet W5500, put it all behind SPI. *The ESP32 has a built-in MAC but needs an external PHY (e.g., LAN8720).*
- **Galvanic isolation:** the magnetics isolate each side of the link, which helps with ground loops and safety
- **Speed:** 10 Mbps (10BASE-T), 100 Mbps (100BASE-TX), 1 Gbps (1000BASE-T), and 2.5/5/10 Gbps on newer standards. *Much faster than UART/I2C/CAN/RS485. Comparable to USB full-speed to high-speed, and to SPI at typical MCU rates.*
- **Range:** up to 100 m per segment on Cat5e/Cat6
- **Signaling:** Differential (each pair carries opposite voltages)
- **Noise resistance:** Excellent. Differential twisted pairs, transformer isolation, and CRC error detection make it reliable in noisy environments, and higher-layer protocols (like TCP) can retransmit lost data.

## Synchronous Comm Protocols 

### I2C (Inter-Integrated Circuit)
- Go to [Reading 5v2 - I2C Overview](<../Section 5 - Synchronous Comm Protocols/Reading 5v2 - I2C Overview.md>)

### SPI (Serial Peripheral Interface)
- Go to [Reading 5v3 - SPI & IsoSPI Overview](<../Section 5 - Synchronous Comm Protocols/Reading 5v3 - SPI & IsoSPI Overview.md>)

### IsoSPI (Isolated SPI)
- Go to [Reading 5v3 - SPI & IsoSPI Overview](<../Section 5 - Synchronous Comm Protocols/Reading 5v3 - SPI & IsoSPI Overview.md>)

### JTAG (Joint Test Action Group) 
Important notes about JTAG:
- Used to program to or read from MCU's (has wiring that is similar to SPI, but check MCU datasheet)
- **Synchronous:** clocked by the debug probe
- **4 Wire (+1 optional):** **TCK** (clock), **TMS** (mode select), **TDI** (data in), **TDO** (data out), plus optional **TRST** (reset)
- **Purpose:** debugging, flash programming, and boundary scan (not a general data bus)
- **Daisy-chainable:** multiple devices share one chain, with TDO of one feeding TDI of the next
- **Shift-register based:** data is shifted through a state machine controlled by TMS
- **Speed:** Typically 1-50 MHz depending on probe and target. *Similar to SPI, much faster than UART/I2C.*
- **Signaling:** Single-ended
- **Noise resistance:** Poor to fair. It is fast and single-ended, so keep wires short. Long or noisy debug cables commonly cause flaky connections and failed flashes.

### I2S (Inter-IC Sound)
Important notes about I2S:
- Used for audio (like your headphone jack!)
- **Synchronous:** dedicated clock lines
- **3-4 Wires:** **SCK/BCLK** (bit clock), **WS/LRCLK** (word select, left/right channel), and 1-2 **SD** lines (serial data) (more info below)
- **Audio only:** designed for digital audio (PCM) between ICs such as MCU, codec, DAC, ADC, or MEMS mic
- **Unidirectional per data line:** one line for TX or RX; use two data lines for both directions
- **One transmitter to one receiver** (typically), with one side generating the clocks
- **Speed:** Bit clock = sample rate × bit depth × channels, e.g. 44.1 kHz × 16-bit × 2 ch ≈ 1.4 MHz. *In the same range as fast I2C/CAN up to low-MHz SPI.*
- **Signaling:** Single-ended
- **Noise resistance:** Fair to poor. Clock jitter directly degrades audio quality, so keep traces short and use ground plane and clean clock routing.

Wires:
- SCK/BCLK: Bit Clock
- WS/LRCLK: Word Select
    - 0 -> Audio goes into left channel
    - 1 -> Audio goes into right channel
- SD: Serial Data (Ex: From MCU)
    - SD wires(s) can be:
        - SDATA (Recieve Only)
        - SDIN and SDOUT
        - DACDAT and ASCDAT

## Quick comparison

| Protocol | Wires | Clock | Duplex | Signaling | Typical Speed | Noise Resistance |
|---|---|---|---|---|---|---|
| UART | 2 | Async | Full | Single-ended | 9.6k-115.2k baud (up to ~Mbaud) | Moderate |
| CAN | 2 | Async | Half | Differential | up to 1 Mbps (FD: 5-8) | Excellent |
| RS485 | 2 or 4 | Async | Half (2-wire) / Full (4-wire) | Differential | up to 10 Mbps | Excellent |
| USB 2.0 | 2 data (+power) | Async (recovered) | Half | Differential | 1.5M / 12M / 480M | Very good |
| Ethernet | 4 or 8 (2 or 4 pairs) | Async (self-clocked) | Full | Differential | 10M / 100M / 1G+ | Excellent |
| I2C | 2 | Sync | Half | Single-ended | 100k-3.4M | Fair/Poor |
| SPI | 4+ | Sync | Full | Single-ended | 1-50+ MHz | Poor |
| isoSPI | 2 | Async (pulses) | Half | Differential | 100k-1M | Excellent |
| JTAG | 4-5 | Sync | Full (shift) | Single-ended | 1-50 MHz | Poor/Fair |
| I2S | 3-4 | Sync | Simplex per line | Single-ended | ~1-12 MHz (audio dependent) | Fair/Poor |
