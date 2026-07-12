# Hardware Setup 

## About the boards

### What is the ESP32-S3?

A development board with features useful for general development and creation of anything.
As a microcontroller, it acts as the ‘brain’ of your project. The code you upload will control its features.

<img width="751" height="497" alt="Screenshot 2026-07-11 133643" src="https://github.com/user-attachments/assets/3349b08a-6612-4e39-976a-40b2e2dbbefc" />


**GPIO Pins**
Can be configured through code as (usually) either Inputs or Outputs. In the LED circuit above, GPIO 38 is an output that can be coded to HIGH, so it flows current to the LED.
>In this lab, will use numbers (0-255) instead of HIGH & LOW for LED brightness control

**TX and RX**
TX = Where ESP32-S3 sends its CAN Packets
RX = Where ESP32-S3 listens for CAN Packets (more accurate desc?)
- These are connected to the corresponding TX and RX pins on the receiving board.

**[ESP32-S3 setup with lights board here]**


### Pulse Width Modulation

### What are CAN Packets
 Message Containers
 (add more)









