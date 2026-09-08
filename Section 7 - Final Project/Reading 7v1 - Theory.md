# Brake Lights

In this project, you will write the firmware for an ESP32 Devboard to drive a model "brake light" system.

## Project Specs

- Power Monitor: using I2C, you will measure the current <DOUBLE CHECK WHAT THIS IS> draw from the ESP32
- Brake Lights: you will program LEDS to turn on based on different input methods
    - PWM: drive an LED with varying brightness using PWM
    - DAC: drive an LED with varying brightness using a DAC that communicates using SPI
    - On/Off Monitor: drive an LED (binary brightness) that blinks when hazards are triggered
- CAN Communication: you will design CAN infrastructure to communicate with an external ESP32
    - Send: your ESP32 will send a heartbeat, along with live current <DOUBLE CHECK WHAT IT IS> data
    - Receive: your ESP32 will receive hazard status (on/off) and pedal position data (potentiometer) to inform how you drive your LEDs
- Serial Debugging: your ESP32 should send status information through UART, which can be monitored by a computer over USB