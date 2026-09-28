# Exercise 4v1 - Sending Over UART

In this exercise you'll set up a **UART** and use it to send status messages to your computer, like the final project's serial debugging ("display pedal position over serial").

Complete the TODOs in `main/main.c` in order, then run with `idf.py qemu` (see `Exercise Directory/Exercise Instructions.md` for setup).

## You have been doing "UART"

Every `printf()` you've written so far already went over a UART! The ESP32's **UART0** is connected to your computer (over USB on a real board, and to your terminal in QEMU). In this exercise you'll skip `printf()` and use the UART driver directly, so you can see what's underneath.

## Task 1: Configure the UART

As `Reading 4v2 - UART Overview` says, both sides must agree on the settings before any data is sent. These are the settings you'll use (the most common ones, often written **115200 8N1**):

| Setting      | Value  | `uart_config_t` field and name          |
| ------------ | ------ | --------------------------------------- |
| Baud rate    | 115200 | `.baud_rate = BAUD_RATE`                |
| Data bits    | 8      | `.data_bits = UART_DATA_8_BITS`         |
| Parity       | None   | `.parity = UART_PARITY_DISABLE`         |
| Stop bits    | 1      | `.stop_bits = UART_STOP_BITS_1`         |
| Flow control | None   | `.flow_ctrl = UART_HW_FLOWCTRL_DISABLE` |

Then two function calls make it happen:

| Function                                       | What it does                                                           |
| ---------------------------------------------- | ---------------------------------------------------------------------- |
| `uart_driver_install(...)`                     | Sets up the driver and its buffers (the code is given in the comment). |
| `uart_param_config(SERIAL_UART, &uart_config)` | Applies your settings to the UART hardware.                            |

## Task 2: Send bytes

Review or Preview for CS61C!

`uart_write_bytes(uart, text, length)` sends `length` bytes of `text`. In C, text is an array of characters, and `strlen(text)` counts them for you.

End your messages with `\r\n` (carriage return + new line) so the next message starts on a new line in the serial monitor.

## Task 3: Send a status line

`snprintf()` works like `printf()`, but instead of printing, it writes the text into an array:

```c
char line[64];
snprintf(line, sizeof(line), "Pedal: %d\r\n", 64);   // line now holds "Pedal: 64\r\n"
```

`sizeof(line)` stops it from writing past the end of the array.

The final project stores voltages as **volts × 10** (`118` means `11.8 V`) so it never needs decimals. To print it, split it with `/` and `%`:

- `118 / 10` = `11` (whole volts)
- `118 % 10` = `8` (tenths)

## Expected output

```
Task 1:
UART ready at 115200 baud

Task 2:
Hello from the Brakelights ESP32!

Task 3:
Pedal: 0 | Power: 12.0 V | Hazards: OFF
Pedal: 64 | Power: 11.8 V | Hazards: OFF
Pedal: 128 | Power: 11.5 V | Hazards: ON
Pedal: 200 | Power: 9.7 V | Hazards: ON
Pedal: 255 | Power: 12.1 V | Hazards: OFF

Done!
```

## What QEMU can't show you

On a real board, the baud rate really matters: if the ESP32 sends at 115200 but your serial monitor listens at 9600, you'll see garbage characters instead of text. QEMU sends text straight to your terminal, so it ignores the baud rate.

## Going further

For the final project, think about:

.....I think this is enough for your final project so I'll save you for this one haha, check out the CAN part though!
