# Simplifying IO

IO stands for **input/output**. The input/output discussed in this reading will be the physical connection between hardware and firmware. Let's first explore how IO pins on the ESP32 work on an abstracted level, then learn smarter schemes of how to use them.

## Using IO in ESP-IDF
To use a standard IO pin in ESP-IDF (documentation [here](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/gpio.html)), you first have to include the GPIO driver so that your system knows to import the relevant functionality:

```
#include "driver/gpio.h" // GPIO driver for ESP32 allows you to control the GPIO pins on the ESP32
```
For each GPIO pin, you then have to configure it for either input or output. Below is a sample implementation of how to configure for output:

```
// Configure GPIO pin for output
gpio_num_t peripheral_pin = (gpio_num_t)arg; // Cast the argument to gpio_num_t type
gpio_reset_pin(perhiperal_pin); // Reset the GPIO pin to its default state
gpio_set_direction(peripheral_pin, GPIO_MODE_OUTPUT); // Set the GPIO pin as an output pin
```

To set the output of a GPIO:

```
gpio_set_level(peripheral_pin, 1); // Set GPIO pin high (on)
gpio_set_level(peripheral_pin, 0); // Set GPIO pin low (off)
```

To read the input into a GPIO:

```
gpio_get_level(peripheral_pin);
```

_Note: for GPIO input, we typically use external pullup/pulldown resistors, so you can set the internal pullup/pulldown using `gpio_set_pull_mode(peripheral_pin, GPIO_FLOATING);`_

## So What?
Okay so it's pretty simple to implement IO, but what is really happening under the hood? To motivate the use of our following techniques, let me pose a few non-trivial questions:
- How is data actually read?
- How do bits actually get written and read as packets?
- If my ESP is busy with another slow task, how can I ensure my ESP will "hear" the input
- How do we precisely time reading and writing?

### IO pins
At their most basic level, IO pins are the physical metal legs (or pads) on the outside of the ESP32 chip. They bridge the microcontroller's digital brain to the physical world.

#### Voltage as Data
To understand IO, we must first understand the concept of digital vs analog.
- Digital: binary 1s and 0s, what most MCUs understand
- Analog: the physical world, (π, 5.5, 14)

The ESP32 only understands binary (1s and 0s), but the physical world speaks in analog. IO pins translate between the two using voltage. 

For the ESP32, its standard operating voltage is 3.3 Volts (V). Therefore, digital IO pins recognize exactly two distinct states:

- HIGH (1): voltage is at or near 3.3V
- LOW (0): Voltage is at or near 0V (GND)

Any time we called `gpio_set_level()` or `gpio_get_level()` earlier, we were directly manipulating or reading the electrical voltage on that specific metal pin.

#### Input vs Output
IO pins must have their direction configured. This is because in either the input/output state, it acts in different ways:
- When configured as output: the ESP32 acts like a switch connected to a power supply. If you tell it to output HIGH, internal transistors connect the pin to the 3.3V rail, pushing power out into your circuit (like turning on an LED). If you output LOW, it connects the pin to GND.
- When configured as input: the ESP32 acts like a tiny voltmeter. It passively listens to the wire connected to it, and if an external sensor applies 3.3V to the pin, the ESP32's internal circuitry detects it and registers a `1` in software.

If you think about it, the IO pin only will know what the voltage is at the exact fraction of a millisecond that you check it since it has no memory...so how can we solve this issue?

### Polling

A lot of the talk of hardware above, was to motivate this idea that for our IO pins bits are read serially (one at a time). Here we will discuss a naive way to read these bits.

#### Analogy

TODO add picture

Imagine I am sitting in Supernode doing my homework while a meeting is happening. To gather input of what other people are working on, I can poll them! In other words, I can go up to them and ask what they are doing every so often. This allows me as lead to get input! This is polling.

#### Common Implementation

An example implementation is a function that attempts to read from an IO every 10 millisecond (we will discuss how to implement this in a later section). We are polling the input at 100 Hz. 

From a hardware perspective, we are literally checking if the IO is seeing a high or low every 10 milliseconds. 

A simple use case is for a button. If we want to see if a button is pressed, we can poll and see if the voltage seen on the line is high or low from the button.

#### Trade-Offs

The main benefit of polling is simplicity. It allows us to read data in a very straightforward way. However there are two main drawbacks:

1) Speed: You can imagine in our complex system, there are many things going on at once. If we are trying to get 10 inputs at once, polling each IO 100 times a second gets very CPU intensive.

2) Data Loss: You can imagine if we have a higher speed signal that is only active for a millisecond, and we poll every 10 milliseconds, there is a high chance we can miss the input.

### Interrupts

To solve our polling drawbacks, we introduce this idea of an interrupt!

#### Analogy

TODO add picture

Now let's say I am sitting in Supernode and I need to get input from people again. Instead of standing up and asking them myself, I could have each member tap me on the shoulder when they are about to ask a question. They are interrupting my current task to deliver me input. We call this an interrupt!

#### Common Implementations

We commonly see interrupts in ICs and communication protocols, but we can really use it for anything.

An example of how we would use an interrupt, is to sit idle and not poll on our "data IO pin" in our nominal state. However, when an interrupt is seen on our "interrupt IO pin" we now start reading data on the data IO pin at the exact frequency we expect to see!

#### Trade-Offs

We can see that we have just solved our two problems!

1) Speed: we are no longer wasting time on polling when no data is coming. We are no longer wasting resources.

2) Data Loss: we can't miss data if we are notified exactly when the data is coming. Another important fun hardware note is that we must make sure in layout the timing of our interrupts are precise, as otherwise we will poll at the wrong time.

However, there are some new drawbacks. The main one being complexity. For interrupts to work, we need a synchronized and dedicated interrupt IO pin. We also need to know how to time the polling.

In summary, we should use interrupts when the data we need is very precise and known, while polling deals with more general cases.

#### More details

TODO maybe write something about ISRs

Interrupt exact implementation we will leave to you guys to find out, but the main idea is that when an interrupt is triggered, it actually queries a function! Exact implementation we will let you discover in the exercise!

### Buffers

There is however one big lingering question. How do we go from bits to packets, and packets to a datastream!

#### Analogy

TODO Image

Imagine I am trying to remember all the inputs the members are giving me, but because of my other work I don't really have time to deal with them now. Instead, I can write down all of their questions on a piece of paper to buffer them. When I have the time I can then work my way through the questions and come up with answers. To save my own time, I can then write down the answers on a piece of paper and then answer all my members questions at once. What I've described are input and output buffers!

#### As an API

TODO explain buffers from the context of just reading and writing from it

### Conclusion

Here you have seen how to use polling, interrupts, and buffering to deal with IO pins in a smart way. To get practice, we recommend doing exercise 3v1 to practice implementing and using polling, buffers and interrupts
