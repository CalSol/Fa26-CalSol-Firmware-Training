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

# C Example

The following program demonstrates the basic idea behind PWM using software.

This example assumes that the microcontroller provides functions similar to:

```c
gpio_init_output();
gpio_write();
delay_us();
```

The exact GPIO functions will depend on the microcontroller being used.

```c
#include <stdint.h>

#define PWM_PIN 5
#define PWM_FREQUENCY_HZ 1000

#define PWM_PERIOD_US (1000000U / PWM_FREQUENCY_HZ)

/*
 * These functions represent hardware-specific GPIO functions.
 * The actual implementation depends on the microcontroller.
 */
void gpio_init_output(uint8_t pin);
void gpio_write(uint8_t pin, uint8_t value);
void delay_us(uint32_t microseconds);


/*
 * Generate one PWM period.
 *
 * pin          - GPIO pin used for PWM
 * duty_percent - duty cycle from 0 to 100
 */
void pwm_write(uint8_t pin, uint8_t duty_percent)
{
    /*
     * Prevent duty cycles greater than 100%.
     */
    if (duty_percent > 100)
    {
        duty_percent = 100;
    }

    /*
     * Calculate how long the signal should stay HIGH.
     */
    uint32_t high_time_us =
        (PWM_PERIOD_US * duty_percent) / 100;

    /*
     * Calculate how long the signal should stay LOW.
     */
    uint32_t low_time_us =
        PWM_PERIOD_US - high_time_us;

    /*
     * 0% duty cycle means the output is always LOW.
     */
    if (duty_percent == 0)
    {
        gpio_write(pin, 0);
        delay_us(PWM_PERIOD_US);
        return;
    }

    /*
     * 100% duty cycle means the output is always HIGH.
     */
    if (duty_percent == 100)
    {
        gpio_write(pin, 1);
        delay_us(PWM_PERIOD_US);
        return;
    }

    /*
     * HIGH portion of the PWM signal.
     */
    gpio_write(pin, 1);
    delay_us(high_time_us);

    /*
     * LOW portion of the PWM signal.
     */
    gpio_write(pin, 0);
    delay_us(low_time_us);
}


int main(void)
{
    /*
     * Configure the PWM pin as an output.
     */
    gpio_init_output(PWM_PIN);

    while (1)
    {
        /*
         * Generate a 1 kHz PWM signal
         * with a 50% duty cycle.
         */
        pwm_write(PWM_PIN, 50);
    }

    return 0;
}
```
