# Exercise 5v3 - SPI

In this exercise you'll talk to a **DAC** (Digital to Analog Converter) over **SPI**, by driving the SPI wires yourself, one bit at a time. A DAC turns a number into a voltage, for example to set how bright an LED is.

Complete the TODOs in `main/main.c` in order, then run with `idf.py qemu` (see `Exercise Directory/Exercise Instructions.md` for setup).

## The simulated wires

QEMU can't run the ESP32's real SPI hardware (the real driver freezes), so `sim_spi.c` pretends to be the 4 SPI wires from `Reading 5v3 - SPI Overview`, with a 12-bit DAC on the other end. You don't need to edit it.

| Function | Wire | What it does |
|---|---|---|
| `spi_cs(level)` | CS (Chip Select) | `0` starts talking to the DAC, `1` ends it. CS is **active low**. |
| `spi_sclk(level)` | SCLK (Serial Clock) | You make the clock: `1` then `0` is one clock pulse. |
| `spi_mosi(bit)` | MOSI (Master Out, Slave In) | The bit you're sending. |
| `spi_miso()` | MISO (Master In, Slave Out) | The bit the DAC is sending back. |

You are the **master**: you control CS and the clock. The DAC prints `[DAC] ...` lines so you can see what it received.

## Task 1: One byte, both directions

SPI is **full duplex**: on every clock pulse, one bit goes out on MOSI **and** one bit comes back on MISO. So sending a byte and receiving a byte is the same 8-step loop.

Bits are sent **MSB first** (most significant bit, bit 7, first). To get bit number `b` of a byte:

```c
(out >> b) & 1      // shift bit b down to position 0, then keep only that bit
```

To build up the received byte, shift what you have left and add the new bit at the end:

```c
in = (in << 1) | spi_miso();
```

For example, receiving 1, 0, 1: `in` goes `1` → `10` → `101` (in binary).

## Task 2: Set the DAC output

The DAC is **12-bit**: its output is a number from `0` to `4095` (`4095` = 3.3 V). That doesn't fit in one byte, so a command is 2 bytes (16 bits):

```
byte 1:  0  0  1  1  D11 D10 D9 D8      top 4 bits: settings (0011 = normal output)
byte 2:  D7 D6 D5 D4 D3  D2  D1 D0      the rest of the value
```

This is the same format as the real **MCP4921** DAC. To build the bytes:

| Operation | Example with value = 2048 (binary `1000 0000 0000`) |
|---|---|
| `value >> 8` (top 4 bits) | `1000` = `0x8` |
| `0x30 \| (value >> 8)` (add the settings) | `0x38` |
| `value & 0xFF` (bottom 8 bits) | `0x00` |

## Task 3: Read the DAC

To read, send the read command `0x80`, then two "dummy" bytes (`0x00`). You don't care what you send: the dummy bytes only exist to make clock pulses, so the DAC can send its answer back on MISO. This is how reading works on almost every SPI device.

The DAC answers in a common "left-aligned" format, and you need to put the 12 bits back together:

```
first reply:   D11 D10 D9 D8 D7 D6 D5 D4      → shift left by 4
second reply:  D3  D2  D1 D0 0  0  0  0       → shift right by 4
value = (first << 4) | (second >> 4)
```

The final project's power monitor (LTC4151, over I2C) sends its voltage in exactly this format, so this is good practice!

## Expected output

```
Task 1:
[DAC] Received 1 byte(s): 0xA5

Task 2:
[DAC] Output set to 0 (0.00 V)
[DAC] Output set to 1024 (0.82 V)
[DAC] Output set to 2048 (1.65 V)
[DAC] Output set to 3072 (2.47 V)
[DAC] Output set to 4095 (3.30 V)

Task 3:
[DAC] Output set to 2500 (2.01 V)
[DAC] Read request: sent back 2500
Read back: 2500

Done!
```

## On a real ESP32

Moving wires one bit at a time in code is called **bit-banging**. Real firmware usually lets the SPI hardware do it instead. With the ESP-IDF SPI driver, Task 2 looks like this:

```c
uint8_t tx[2] = { 0x30 | (value >> 8), value & 0xFF };
spi_transaction_t t = { .length = 16, .tx_buffer = tx };   // length is in bits
spi_device_transmit(dac, &t);                              // handles CS, clock and bits for you
```

The bytes you build are exactly the same. Only the "sending" part changes.