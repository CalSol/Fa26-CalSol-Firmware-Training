# Timing and Synchronization

## Motivation

Up until now, we've talked about how to read and write data, but we haven't talked about how we determine _when_.

The ESP32's processor executes millions of instructions per second. If you write a line of code to turn an LED on, and the very next line it turns off, the LED will blink so fast that your eyes won't even register that it turned on. If you need a sensor to read data at exactly 100 Hz (100 times per second), you need a way to ensure your code waits that exact amount without locking up the entire system.

## Naive (Busy Waiting)
<img height="200" alt="Busy wait analogy" src="./../images/SECTION2/busy_wait.png" />

Imagine you are in Supernode waiting for a 3D print to finish, and you know it takes exactly 10 minutes. A "busy waiting" approach means you stand directly in front of the printer, staring intensely at the nozzle, doing absolutely nothing else for 10 straight minutes until it finishes.

The most intuitive way to delay an action is to just make the processor count to a really high number before moving on. We call this **busy waiting** or blocking.

### Common Implementation
In code, this usually looks like an empty `for` loop or a blocking delay function that hogs the CPU:

```c
// Busy waiting: the CPU is trapped in this loop doing nothing
for (int i = 0; i < 100000; i++) {
    // Just count up and waste time
}
```
_Note: while `vTaskDelay()` in ESP-iDF looks like a delay, it actually yields the processor to the OS, which is much smarter. But truly busy waiting is literally just stalling the CPU!_

### Trade-Offs
The only benefit to busy waiting is that it is trivially easy to write. However, it has huge drawbacks:
1. Total inefficiency: you are freezing the entire processor. It cannot read sensors, update displays, or communicate over Wi-Fi while it is busy staring at the clock.
2. Inaccuracy: if an interrupt fires while you are busy waiting, it throws off your timing, and now you can't guarantee exactly how the wait actually took.

## Timers and Tickers
<img height="200" alt="Timer analogy" src="./../images/SECTION2/timer.png" />

Okay now let's say I'm making cup noodles (for a long night in Cory Hall). Instead of staring at the noodles cooking, I set a 10-minute alarm on my phone and do my homework while I wait. I am completely productive until the exact moment my phone alarms (ticks), at which point I pause my homework, eat my noodles, and go back to work.

To fix the busy waiting problem, we use **Timers and Tickers**! A timer is essentially a dedicated hardware/software alarm clock. Instead of the CPU wasting time counting, a separate clock circuit handles the counting in the background and triggers an interrupt (or callback function) when the time is up!

_Note: Timers are the actual physical silicon peripheral (clock circuit) built into the chip and is completely independent of the main processor. Tickers are the software abstraction built on top of a hardware timer. For our purposes, they are functionally the same thing and we will call this concept timers in general._

### Timer Setup
In ESP-IDF, we can use the High-Resolution Timer (`esp_timer`) API (documentation [here](https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/system/esp_timer.html)) to set up recurring "ticks." To use a timer, you need three things:
1. Callback Function: the code that runs when the timer goes off
2. Timer Configuration: telling the timer which callback to use
3. Start Command: telling the timer how often to tick (in microseconds)

### Timer Implementation
In ESP-IDF, 

```c

```

## Scheduling

TODO just hint that in the next section we will learn a better way to do this
