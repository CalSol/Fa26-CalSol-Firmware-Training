## What is PWM?

**PWM (Pulse Width Modulation)** is a technique used by microcontrollers to control the average power delivered to a device by rapidly switching a digital output **ON** and **OFF**.

PWM is commonly used for:
- Controlling LED brightness
- Controlling DC motor speed
- Controlling fans
- Servo motors
- Power electronics

## How PWM Works

A normal digital GPIO pin has two possible states:

```text
HIGH = ON
LOW  = OFF
```
PWM switches rapidly between these two states. Below are some of the basic duty cycles:
![Install Picture](./../images/Arduino-PWM.jpg)

As we can see in the image above:
+ **0% duty cycle**, the signal never goes HIGH.
+ **25% duty cycle** spends less time HIGH.
+ **50% duty cycle** means that the signal is HIGH for half of the period and LOW for the other half.
+ **75% duty cycle** spends more time HIGH.

## Frequency

The **frequency** tells us how many PWM cycles occur every second.

Frequency is measured in **Hertz (Hz)**.

For example:

```text
1000 Hz = 1000 PWM cycles per second
```

Frequency and period are related by:

```text
Period = 1 / Frequency
```

If the PWM frequency is `1000 Hz`:

```text
Period = 1 / 1000
       = 0.001 seconds
       = 1 ms
       = 1000 microseconds
```
