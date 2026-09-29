# Exercise 2v1 - GPIO (Blink)

In this exercise you'll blink the **Hazards LED** from the final project. It's the "hello world" of firmware: if you can blink an LED, you can control any pin on the ESP32.

Complete the TODOs in `main/main.c` in order, then run with `idf.py qemu` (see `Exercise Directory/Exercise Instructions.md` for setup).

## What is GPIO?

**GPIO** (General Purpose Input/Output) pins are the ESP32's connections to the outside world. Each pin has a number (for example, GPIO 42) and can be set up as:

- **Output:** the ESP32 drives the pin **HIGH** (3.3 V, `1`) or **LOW** (0 V, `0`). An LED connected to an output pin turns on when the pin is HIGH.
- **Input:** the ESP32 reads whether something else is driving the pin HIGH or LOW, like a button. You'll use inputs in later exercises.

In the final project, the Hazards LED is on **GPIO 42** and should blink once per second when hazards are on.

## Functions you'll use

| Function | What it does |
|---|---|
| `gpio_reset_pin(pin)` | Puts the pin back into a clean default state. Call it first. |
| `gpio_set_direction(pin, GPIO_MODE_OUTPUT)` | Makes the pin an output. |
| `gpio_set_level(pin, level)` | Drives the pin HIGH (`1`) or LOW (`0`). |
| `vTaskDelay(pdMS_TO_TICKS(ms))` | Pauses your code for `ms` milliseconds. |

`pdMS_TO_TICKS()` is needed because `vTaskDelay()` counts in FreeRTOS "ticks", not milliseconds. It converts for you. (You'll learn more about FreeRTOS in Section 3.)

## Note on set_led()

QEMU emulates the ESP32's processor, but not its pins: `gpio_set_level()` runs without errors, but there's no LED to light up. So `set_led()` does two things:

1. Calls `gpio_set_level()`: this is the line that lights the LED on a real board.
2. Prints the LED state with a timestamp: this is how **you** see it in QEMU.

The timestamps let you check your timing. For a 500 ms blink, each line should be about 500 ms after the one before.

## Expected output

Your timestamps will be slightly different:

```
Task 1:
Hazards LED ready on GPIO 42

Task 2:
481 ms LED ON
1478 ms LED OFF

Task 3:
1492 ms LED ON
1987 ms LED OFF
2488 ms LED ON
...
6017 ms LED OFF

Done!
```

## Going further

Once you've finished, think about how you'd handle these in the final project. There's no code to hand in, but try them out if you want:

- Real firmware blinks **forever**. What changes if you use `while (1)` instead of a fixed number of blinks?
- Look up `gpio_config()`. How is it different from `gpio_reset_pin()` + `gpio_set_direction()`?
- While `vTaskDelay()` is waiting, your code can't do anything else. How could the ESP32 blink an LED **and** watch for a button press at the same time?
