# Other Comm Protocols

### JTAG (Joint Test Action Group) 
- Used to program to or read from MCU's
- Similar to SPI wiring (check MCU data sheet)

### RS485
- Differential signal (similar to CAN)

### USB D+/D-
- Differential signal (similar to CAN)
- From USB to your MCU
    - Typically used for flashing firmware

### I2S
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
