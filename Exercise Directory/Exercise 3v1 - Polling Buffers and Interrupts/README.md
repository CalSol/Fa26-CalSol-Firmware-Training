# Exercise 3v1 - Polling, Buffers, and Interrupts

In this exercise you'll detect presses of the final project's **startup button** three ways, and see for yourself the trade-offs from `Reading 2v4 - Simplifying IO`.

Complete the TODOs in `main/main.c` in order, then run with `idf.py qemu` (see `Exercise Directory/Exercise Instructions.md` for setup).

## The simulated button

QEMU can't press a real button, so `sim_button.c` pretends to be one. You don't need to edit it. It acts like the startup button on **GPIO 8**, which is **active low**:

| Reading | Meaning |
|---|---|
| `1` | Released |
| `0` | Pressed |

"Active low" means pressing the button pulls the pin to 0 V. The pin sits at `1` the rest of the time because of a pull-up resistor.

Each time you call `sim_button_start()`, the same 4 presses happen, measured from that moment: at **300 ms, 900 ms, 1623 ms and 2200 ms**. The press at 1623 ms is a very quick **0.3 ms tap**.

| Simulated function | What you'd use on a real ESP32 |
|---|---|
| `sim_button_read()` | `gpio_get_level(STARTUP_BUTTON_GPIO)` |
| `sim_button_attach_interrupt(handler)` | `gpio_install_isr_service()` + `gpio_isr_handler_add()` |

## Task 1: Polling

Polling means **checking** the button over and over. A press is a **change** from `1` to `0`. If you only checked for `0`, you'd count the same press several times while it's held down.

You'll poll every 50 ms. The 0.3 ms tap starts and ends between two checks, so polling will almost always miss it. This is the "data loss" drawback from the reading. (If you happen to see 4 presses, run it again: you got very lucky with the timing.)

## Task 2: Interrupts

With an interrupt, you don't check at all: you give the system a function (a **handler**), and it gets called **the moment** the button is pressed. Your code can wait or do other work in the meantime.

Rules for interrupt handlers:
- **Keep them short.** On real hardware, a handler pauses everything else. Do the minimum (count, set a flag, save a value) and do the slow work, like printing, somewhere else.
- **Mark shared variables `volatile`.** `press_count` is changed by the handler, not by the code that reads it. `volatile` tells the compiler to always read the latest value from memory.

The handler should catch all 4 presses, including the tap.

## Task 3: Buffers

The handler can't print, so how does your main code find out **when** each press happened? The handler writes the press time into a **buffer**, and your main code reads it out later.

You'll build a **ring buffer** from an array:

```
index:   0    1    2    3    4    5    6    7
        [300][900][1623][2200][ ][ ][ ][ ]
          ^tail                ^head
```

- `buffer_write()` stores at `buffer_head`, then moves `head` forward.
- `buffer_read()` takes from `buffer_tail`, then moves `tail` forward.
- When an index passes the end of the array, it wraps back to 0: `(index + 1) % BUFFER_SIZE`.
- `buffer_count` keeps track of how many values are waiting.

Values come out in the order they went in (**first in, first out**), you will learn more about this data structure in CS61B.

## Expected output

Your times will be slightly different:

```
Task 1:
780 ms Press detected
1381 ms Press detected
2680 ms Press detected
Polling saw 3 presses

Task 2:
Interrupt saw 4 presses

Task 3:
Press at 3798 ms
Press at 4399 ms
Press at 5121 ms
Press at 5699 ms

Done!
```

## Going further

For the final project, think about:

- If the buffer were only 3 values big, what would happen to the 4th press? Would you rather drop new values or overwrite old ones?
- A real button "bounces": one press can look like several quick `1 → 0` changes. How could you ignore those?
- FreeRTOS has a built-in buffer called a **queue** (`xQueueCreate`, `xQueueSendFromISR`). How is it like the ring buffer you wrote?
