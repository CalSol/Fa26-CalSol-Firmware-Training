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

## ESP Master Board

This is the board that will be taking in potentiometer data through an ADC (ESP32 GPIO), and then sending that data over CAN

### Requirements/Todos

- Setup breadboard hardware
    - ESP32
    - Potentiometer (for pedal position)
    - Button (for hazards)
    - Indicator LED (receiving power)
    - Indicator LED (receiving heartbeat)
    - Connect up to CAN
- Pedal position
    - Read ADC data from an ESP32 GPIO
        - Take ADC data
        - Store it in a buffer or somewhere
    - Queue to send out through CAN
- Hazards
    - Read digital data from an ESP32 GPIO
        - Take button
        - Control logic to only toggle once per press
    - Queue to send out through CAN
- CAN architecture
    - Set up CAN driver
    - Sending CAN
        - Prepare and send packet with pedal position
        - Prepare and send packet with hazard state
    - Receiving CAN
        - Receive packets that contain heartbeat
        - Receive packets that contain power monitor reading
- Indicator LEDs
    - Binary on/off when receiving heartbeats periodically
    - Binary on/off when receiving power data periodically

## ESP Slave Board

### Requirements/Todos
- Setup breadboard hardware
    - ESP32
    - PWM resistor + LED
    - SPI DAC + resistor + LED
    - On/off monitor resistor + LED
    - Connect up to CAN
- Send serial status over UART
    - Grab pedal position data, hazard data, and power monitor data and put it on terminal
        - Should read default value until CAN is implemented
- Read power monitor
    - Set up I2C and read data
    - Save in buffer and send moving average
- CAN communication
    - Set up driver and stuff
    - Sending CAN:
        - Prepare and send heartbeat packet
        - Prepare and send power monitor data packet
    - Receiving CAN 
        - Grab and save pedal position data (get moving average)
        - Grab and save hazard status data
- On/Off LED
    - Make the LED blink at a set interval
    - Have it start/stop the blinking based off of listening to the CAN packet
- PWM LED
    - Make the LED turn on
    - Vary the brightness using CAN data (pedal position)
- DAC LED
    - Set up the SPI
    - Make the LED turn on
    - Vary the brightness using CAN data (pedal position)