# Microcontroller (MCU) Overview

A microcontroller (MCU) is a chip that acts as a "brain" to control hardware it's directly connected to.
- Like a mini computer, but less powerful because it doesn't need to do such intense tasks.

When we write firmware, we upload the logic to the MCU, which will handle all of the code during operation.

## How?
<div>
  <img height="275" alt="microcontroller-mcu fit_lim size_1050x" src="https://github.com/user-attachments/assets/98eae797-5a10-41df-bc72-2f76ec79bdcd" />
  <img height="275" alt="mcu diagram" src="./../images/SECTION2/mcu_diagram.png" />
</div>

<br>

**The 3 things that make a MCU (or any computer!):**
- Input/Outputs: Peripherals and GPIO pins (General Purpose Input/Output Pins) can read **input** signals as from wires it's connect to, and also **output** signals to other devices through those same wires. A standard IO pin will read 0/1, but specific IO pins have additional functionalities such as ADC (see 6v1)!
- Memory: Where code is frequently stored and erased to give the microcontroller logic to carry out actions.
- Processor: A CPU (Central Processing Unit) has the processing power to execute tasks efficiently. Some CPUs have more than one core, which means that they can process things in parallel.

## What is the ESP32-S3 Dev Board?

A development board is a PCB with a microcontroller (MCU) on it! Our team uses a custom [ESP32-S3](https://documentation.espressif.com/esp32-s3-wroom-1_wroom-1u_datasheet_en.pdf) development board to write firmware to control parts/circuit boards in the car. This enables us to have standardized CAN transceivers, an I2C power monitor, and other debugging capabilities. The ESP32 itself has 2 cores and ability for RTOS (you'll learn more about all these things in later sections! The code you flash to it will use its features to control the peripherals it's connected to.

<img height="275" alt="ESP32" src="https://github.com/user-attachments/assets/1df285eb-7f13-4d20-bc89-485e335144b2" />

**GPIO Pins Example use:**
In the LED circuit above, GPIO 38 is an output that can be coded to HIGH, so it flows current to the LED.
