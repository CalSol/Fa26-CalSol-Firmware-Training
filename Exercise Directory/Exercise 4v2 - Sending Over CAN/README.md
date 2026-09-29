# Exercise 4v2 - Sending Over CAN

In this exercise you'll build and send **CAN messages**, the way boards in the car talk to each other. 

Complete the TODOs in `main/main.c` in order, then run with `idf.py qemu` (see `Exercise Directory/Exercise Instructions.md` for setup).

## The simulated CAN bus

QEMU can't run the ESP32's real CAN hardware, so `sim_can.c` pretends to be a CAN bus with a "dashboard" board listening on it. You don't need to edit it. The dashboard prints every message it sees (`[CAN bus] ...`), and decodes the two IDs it knows (`[Dashboard] ...`).

The functions in `CAN.h` work exactly like the **team's real CAN driver**, which you'll use in the final project. Code you write here will work on a real ESP32.

## A CAN message

From `Reading 4v3 - CAN Overview`, the parts you need are:

| Field | What it is | Example |
|---|---|---|
| `id` | What the message is about. Lower IDs have higher priority. | `0x030` = Motor RPM |
| `dlc` | How many data bytes (0 to 8) | `2` |
| `data[]` | The payload: up to 8 bytes | `0x0B, 0xB8` |

`build_packet_no_ext(id, data, dlc)` fills in a `CAN_message_t` for you ("no_ext" means a normal 11-bit ID).

## Functions you'll use

| Function | What it does |
|---|---|
| `CAN_init()` | Starts CAN. Call it once, before anything else. |
| `build_packet_no_ext(id, data, dlc)` | Builds a message from an ID and an array of `dlc` bytes. |
| `CAN_send(&msg, timeout_ms)` | Sends the message. The `&` passes where `msg` is stored, like in 3v2. |

## Task 2: Values bigger than a byte

Each data byte holds 0 to 255, but RPM can be 3000. So we split it into 2 bytes, **high byte first**:

```
3000 = 0x0BB8
data[0] = 3000 >> 8   = 0x0B   (top 8 bits)
data[1] = 3000 & 0xFF = 0xB8   (bottom 8 bits)
```

Both boards must agree on the order. If the dashboard expected the low byte first, it would read `0xB80B` = 47115 RPM!

## Expected output

```
Task 1:
[CAN bus] ID 0x123 | DLC 2 | AA BB

Task 2:
[CAN bus] ID 0x030 | DLC 2 | 0B B8
[Dashboard] Motor RPM = 3000

Task 3:
[CAN bus] ID 0x031 | DLC 1 | 01
[Dashboard] Status count = 1
[CAN bus] ID 0x031 | DLC 1 | 02
[Dashboard] Status count = 2
...
[Dashboard] Status count = 4

Done!
```
