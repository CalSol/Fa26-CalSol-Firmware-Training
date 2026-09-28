# C Example

## What is PWM?
**PWM (Pulse Width Modulation)** is a technique used by microcontrollers to control the average power delivered to a device by rapidly switching a digital output **ON** and **OFF**. You should have used this in the [hardware lab](https://github.com/CalSol/CalSol-Electrical-Onboarding), but we will review it again!

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
![Install Picture](./../images/SECTION1/Arduino-PWM.jpg)

As we can see in the image above:
+ **0% duty cycle**, the signal never goes HIGH.
+ **25% duty cycle** spends less time HIGH.
+ **50% duty cycle** means that the signal is HIGH for half of the period and LOW for the other half.
+ **75% duty cycle** spends more time HIGH.

### Frequency

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

## C Example

The following program demonstrates the basic idea behind PWM using software. You may not understand a lot of the functions used, and we will try our best to break it down. We are hoping to just get you exposed to what C code and firmware might look like.

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
## Breaking Down the Code

### 1. Setting the PWM Frequency

The PWM frequency is defined here:

```c
#define PWM_FREQUENCY_HZ 1000
```

This means the PWM signal operates at:

```text
1000 Hz = 1 kHz
```

### 2. Calculating the PWM Period

The period is calculated using:

```c
#define PWM_PERIOD_US (1000000U / PWM_FREQUENCY_HZ)
```

There are `1,000,000` microseconds in one second.

Therefore:

```text
PWM_PERIOD_US = 1,000,000 / 1000
              = 1000 us
```

Each complete PWM cycle lasts `1000 us`.

### 3. Calculating HIGH Time

The amount of time the signal remains HIGH depends on the duty cycle.

```c
uint32_t high_time_us =
    (PWM_PERIOD_US * duty_percent) / 100;
```

For a **50% duty cycle**:

```text
HIGH Time = 1000 us × 50 / 100

HIGH Time = 500 us
```

### 4. Calculating LOW Time

The remaining part of the PWM period is LOW.

```c
uint32_t low_time_us =
    PWM_PERIOD_US - high_time_us;
```

For a 50% duty cycle:

```text
LOW Time = 1000 us - 500 us

LOW Time = 500 us
```

This pattern repeats continuously.

---

## Changing the Duty Cycle

To generate a **25% duty cycle**:

```c
pwm_write(PWM_PIN, 25);
```

To generate a **50% duty cycle**:

```c
pwm_write(PWM_PIN, 50);
```

To generate a **75% duty cycle**:

```c
pwm_write(PWM_PIN, 75);
```

To completely turn the output OFF:

```c
pwm_write(PWM_PIN, 0);
```

To keep the output completely ON:

```c
pwm_write(PWM_PIN, 100);
```

---

## Example: Controlling LED Brightness

PWM can be used to control the apparent brightness of an LED.

For example:

```c
pwm_write(PWM_PIN, 10);   // Dim
pwm_write(PWM_PIN, 50);   // Medium brightness
pwm_write(PWM_PIN, 90);   // Bright
```

The microcontroller is **not changing the HIGH voltage**.

Instead, the GPIO pin is rapidly switching between:

```text
0V and VCC (or in the image's case, 5V)
```

Increasing the duty cycle causes the LED to receive power for a greater percentage of each PWM period.

Because this switching happens very quickly, the LED appears brighter or dimmer to the human eye.
