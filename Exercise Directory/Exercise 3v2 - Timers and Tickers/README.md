# Exercise 3v2 - Timers and Tickers

In this exercise you'll make the ESP32 run code **on a schedule**, without your main code having to wait for it. The final project will need this everywhere, such as heartbeats every 100 ms and a hazards blink every second.

Complete the TODOs in `main/main.c` in order, then run with `idf.py qemu` (see `Exercise Directory/Exercise Instructions.md` for setup).

## vTaskDelay() 

In 2v1 you blinked the LED with `vTaskDelay()`. While `vTaskDelay()` waits, your code is stuck: it can't do anything else. A **timer** fixes this. You tell it **what** function to run and **when**, and it calls that function for you while your code keeps going.

- A **one-shot timer** calls its function **once**, after a delay (like an alarm clock).
- A **periodic timer**, also called a **ticker**, calls its function **again and again** at a fixed interval (like a metronome).

## Functions you'll use

| Function | What it does |
|---|---|
| `esp_timer_create(&args, &timer)` | Creates a timer. `args` says which function to call. |
| `esp_timer_start_once(timer, us)` | Calls the function once, after `us` microseconds. |
| `esp_timer_start_periodic(timer, us)` | Calls the function every `us` microseconds. |
| `esp_timer_stop(timer)` | Stops the timer. |

> **esp_timer counts in microseconds.** 1 ms = 1000 µs, so 100 ms is `100 * 1000`. Forgetting this is the most common timer bug.

### `&`, but not the "and" you know

`esp_timer_create()` needs to know **where** to store the new timer, so you pass `&alarm_timer` ("the location of `alarm_timer`"). You'll learn more about this later or in CS61C (it's called a pointer). For now, copy the pattern from Task 1.

### Callbacks

The functions you give a timer (`on_alarm`, `on_heartbeat`, `on_blink`) are called **callbacks**: you don't call them yourself, the timer "calls you back". Like the interrupt handler in 3v1, keep callbacks short. Printing is fine here, but never put a long `vTaskDelay()` inside one.

## Expected output

Your times will be slightly different:

```
Task 1:
426 ms Timer started
1441 ms Alarm!

Task 2:
2036 ms Heartbeat 1
2135 ms Heartbeat 2
...
2835 ms Heartbeat 9

Task 3:
2935 ms Main loop 1
3436 ms LED ON
3531 ms Main loop 2
3936 ms LED OFF
4141 ms Main loop 3
4435 ms LED ON
...

Done!
```

In Task 2, seeing 9 or 10 heartbeats are both correct: the first one comes 100 ms after you start the timer, so the 10th lands right as you stop it.

In Task 3, notice that the `LED` lines and the `Main loop` lines are **mixed together**: the LED blinks on its own while the compiler "stuck" in the loop!!! Multitasking!!!

## Going further

For the final project, think about:

- What happens if a callback takes longer than its timer's period?
- ESP-IDF also has **hardware** timers (`gptimer`). How are they different from `esp_timer`, and when would you need one?
