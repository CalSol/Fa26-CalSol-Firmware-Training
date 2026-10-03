# Quick Reference of Comm Protocols

## Asynchronous Comm Protocols 

### UART (Universal Asynchronous Receiver Transmitter)
Go to [Reading 4v2 - UART Overview](<../Section 4 - Asynchronous Comm Protocols/Reading 4v2 - UART Overview.md>) for more info

Important notes about UART:
- **Universal:** usable on <i>any</i> transmitting/receiving device
- **Asynchronous:** does not follow any shared clock, simply sends/receives when it has data (but both sides must agree on baud rate)
- **2 Wire:** **Transmit (TX)** and **Receive (RX)** (plus a common GND). TX of one device connects to RX of the other
- **One-to-One communication:** UART only communicates between 2 devices
- **Full-duplex:** TX and RX are separate lines, so both devices can talk at the same time
- **Speed:** Usually 9600 baud (bits per second), commonly up to 115200 baud. *Slow-to-moderate compared to SPI/USB; similar to I2C standard mode.*
- **Signaling:** Single-ended
- **Noise resistance:** Moderate. It is slow, which helps, but it is single-ended with no shielding or error correction (only an optional parity bit)


### CAN (Controller Area Network) 
Go to [Reading 4v3 - CAN Overview](<../Section 4 - Asynchronous Comm Protocols/Reading 4v3 - CAN Overview.md>) for more info

Important notes about CAN:
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
Important notes about USB 2.0:
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
Go to [Reading 5v2 - I2C Overview](<../Section 5 - Synchronous Comm Protocols/Reading 5v2 - I2C Overview.md>) for more info

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


### SPI (Serial Peripheral Interface)
Go to [Reading 5v3 - SPI & IsoSPI Overview](<../Section 5 - Synchronous Comm Protocols/Reading 5v3 - SPI & IsoSPI Overview.md>) for more info

Important notes about SPI:
- **Synchronous:** controller generates the clock
- **4+ Wires:** **SCLK** (clock), **MOSI** (controller out), **MISO** (controller in), **CS/SS** (chip select, one per peripheral)
- **One controller, many peripherals:** each extra peripheral needs another CS line
- **Full-duplex:** data goes out on MOSI and in on MISO simultaneously
- **No addressing or error checking:** simple and fast, but the protocol does not detect errors
- **Speed:** Typically 1-50 MHz, up to 100+ MHz on some parts. *One of the fastest simple serial buses: roughly 10-100x faster than I2C/UART.*
- **Signaling:** Single-ended
- **Noise resistance:** Poor. It runs faster than UART/I2C with sharp edges over single-ended lines, so it is more prone to noise, crosstalk, and ringing. Keep traces short and add series resistors or ground shielding if needed.


### IsoSPI (Isolated SPI)
Go to [Reading 5v3 - SPI & IsoSPI Overview](<../Section 5 - Synchronous Comm Protocols/Reading 5v3 - SPI & IsoSPI Overview.md>) for more info

Important notes about isoSPI:
- **Isolated SPI:** Analog Devices' (Linear Tech) transformer-isolated variant of SPI, commonly used in battery management ICs (e.g., LTC681x)
- **2 Wire per link:** a twisted pair carrying differential pulses through an isolation transformer
- **Daisy-chainable:** devices are chained in series, so only the first device connects back to the controller (via a bridge such as the LTC6820)
- **Half-duplex:** one direction at a time on the pair
- **Galvanic isolation:** handles the large voltage differences between stacked battery modules
- **Speed:** 100 kbps to 1 Mbps. *Much slower than SPI, similar to CAN.*
- **Signaling:** Differential (pulse-coded through a transformer)
- **Noise resistance:** Excellent. Differential plus transformer isolation rejects common-mode noise, and cable runs of up to ~100 m are supported.


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
