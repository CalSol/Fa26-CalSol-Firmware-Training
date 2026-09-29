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

### USB D+/D- 
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

## Synchronous Comm Protocols 

### I2C (Inter-Integrated Circuit)
- Go to [Reading 5v2 - I2C Overview](<../Section 5 - Synchronous Comm Protocols/Reading 5v2 - I2C Overview.md>)

### SPI (Serial Peripheral Interface)
- Go to [Reading 5v3 - SPI & IsoSPI Overview](<../Section 5 - Synchronous Comm Protocols/Reading 5v3 - SPI & IsoSPI Overview.md>)

### IsoSPI (Isolated SPI)
- Go to [Reading 5v3 - SPI & IsoSPI Overview](<../Section 5 - Synchronous Comm Protocols/Reading 5v3 - SPI & IsoSPI Overview.md>)

### JTAG (Joint Test Action Group) 
Important notes about JTAG:
- Used to program to or read from MCU's
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
