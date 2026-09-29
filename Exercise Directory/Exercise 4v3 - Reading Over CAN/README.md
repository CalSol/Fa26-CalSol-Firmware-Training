# Exercise 4v3 - Reading Over CAN

In this exercise you'll **receive** CAN messages, pick out the ones you care about, and notice when another board stops talking. 

Complete the TODOs in `main/main.c` in order, then run with `idf.py qemu` (see `Exercise Directory/Exercise Instructions.md` for setup).

## The simulated CAN bus

QEMU can't run the ESP32's real CAN hardware, so `sim_can.c` pretends to be a CAN bus with a "motor controller" board sending messages. You don't need to edit it. Timed from `CAN_init()`, it sends:

| ID | Message | Data | When |
|---|---|---|---|
| `0x050` | Heartbeat | 1 byte: `00` | Every 250 ms from 250 ms to 1500 ms, **then it stops** |
| `0x030` | Motor RPM | 2 bytes, high byte first | 400 ms, 900 ms, 1400 ms |
| `0x7FF` | Something you don't care about | 3 bytes | 650 ms |

Like in 4v2, the functions in `CAN.h` work exactly like the team's real CAN driver.

## The receive loop

Real firmware reads CAN in a loop: wait a little for a message, handle it, repeat. That's already written for you in `app_main()`:

```c
if (CAN_receive(&msg, 50) == ESP_OK) {
    // a message arrived: handle it
}
// no message in 50 ms: carry on
```

`CAN_receive()` waits **at most** 50 ms, so the loop keeps running even when nobody is talking. Task 3 depends on that.

## Task 1: Print every message

`print_message()` gets a **pointer** to the message (`const CAN_message_t *msg`), so use `->` instead of `.` to get its fields: `msg->id`, `msg->dlc`, `msg->data[i]`.

Every board on the bus sees every message, including the `0x7FF` one nobody asked for....Who asked?

## Task 2: Filter by ID

Most messages aren't for you. Check `msg.id`, and only decode the ones you care about. The RPM arrives as 2 bytes, high byte first (the reverse of 4v2):

```
data = 0x05, 0xDC
rpm  = (0x05 << 8) | 0xDC = 0x05DC = 1500
```

## Task 3: Heartbeat timeout

A **heartbeat** is a message a board sends regularly just to say "I'm still here". If it stops arriving, you can't trust that board anymore. To detect that:

1. Every time a heartbeat arrives, save the time.
2. Every time around the loop, check how long it's been. If it's more than the timeout, the board is gone.

## Expected output

Your times will be slightly different:

```
Listening for 2500 ms...
ID 0x050 | DLC 1 | 00
ID 0x030 | DLC 2 | 05 DC
  -> Motor RPM = 1500
ID 0x050 | DLC 1 | 00
ID 0x7FF | DLC 3 | 01 02 03
ID 0x050 | DLC 1 | 00
ID 0x030 | DLC 2 | 0C 80
  -> Motor RPM = 3200
ID 0x050 | DLC 1 | 00
ID 0x050 | DLC 1 | 00
ID 0x030 | DLC 2 | 11 94
  -> Motor RPM = 4500
ID 0x050 | DLC 1 | 00
2491 ms Heartbeat lost!

Done!
```

