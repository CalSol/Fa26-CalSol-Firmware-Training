# Quick Reference of Comm Protocols

## Asynchronous Comm Protocols 

### UART (Universal Asynchronous Receiver Transmitter)
- Go to [Reading 4v2 - UART Overview](<../Section 4 - Asynchronous Comm Protocols/Reading 4v2 - UART Overview.md>)

### CAN (Controller Area Network) 
- Go to [Reading 4v3 - CAN Overview](<../Section 4 - Asynchronous Comm Protocols/Reading 4v3 - CAN Overview.md>)

### RS485 (Recommended Standard 485)
- Differential signal (similar to CAN)

### USB D+/D- 
- Differential signal (similar to CAN)
- From USB to your MCU
    - Typically used for flashing firmware

## Synchronous Comm Protocols 

### I2C (Inter-Integrated Circuit)
- Go to Reading 5v2 - I2C Overview

### SPI (Serial Peripheral Interface)
- Go to Reading 5v3 - SPI & IsoSPI Overview

### IsoSPI (Isolated SPI)
- Go to Reading 5v3 - SPI & IsoSPI Overview

### JTAG (Joint Test Action Group) 
- Used to program to or read from MCU's
- Similar to SPI wiring (check MCU data sheet)

### I2S (Inter-IC Sound)
- Used for audio (like your headphone jack!)
- Wires:
    - SCK/BCLK: Bit Clock
    - WS: Word Select
        - 0 -> Audio goes into left channel
        - 1 -> Audio goes into right channel
    - SD: Serial Data (Ex: From MCU)
        - SD wires(s) can be:
            - SDATA (Recieve Only)
            - SDIN and SDOUT
            - DACDAT and ASCDAT
