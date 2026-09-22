## Microcontroller (MCU) Overview

A microcontroller (MCU) is a chip that acts as a "brain" to control hardware it's directly connected to.
- Like a mini computer, but less powerful because it doesn't need to do such intense tasks.


### How?
<img width="450" height="511" alt="microcontroller-mcu fit_lim size_1050x" src="https://github.com/user-attachments/assets/98eae797-5a10-41df-bc72-2f76ec79bdcd" />


**The 3 things that make a MCU (or any computer!):**
- Input/Outputs: Peripherals and GPIO pins (General Purpose Input/Output Pins) can read **input** signals as from wires it's connect to, and also **output** signals to other devices through those same wires.
- Memory: Where code is frequently stored and erased to give the microcontroller logic to carry out actions.
- Processor: A CPU (Central Processing Unit) has the processing power to execute tasks efficiently.



How it uses these components: it interacts with the circuit it's apart of to control it.


### What is the ESP32-S3 Dev Board?

The ESP32-S3 is the development board model (a PCB with a microcontroller on it) that our subteam uses to write firmware to control parts/circuit boards in the car.
The code you flash to it will use its features to control the devices it's connected to.
<img width="899" height="616" alt="Arial" src="https://github.com/user-attachments/assets/1df285eb-7f13-4d20-bc89-485e335144b2" />

**GPIO Pins Example use:**
In the LED circuit above, GPIO 38 is an output that can be coded to HIGH, so it flows current to the LED.
