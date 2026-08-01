# Hardware Setup 

## About the boards

### What is the ESP32-S3?

A development board with features useful for general development and creation of anything.
As a microcontroller, it acts as the ‘brain’ of your project. The code you upload will use its features to control the components it's connected to.
<img width="899" height="616" alt="Arial" src="https://github.com/user-attachments/assets/1df285eb-7f13-4d20-bc89-485e335144b2" />

**GPIO Pins**
Can be configured through code as (usually) either Inputs or Outputs. In the LED circuit above, GPIO 38 is an output that can be coded to HIGH, so it flows current to the LED.
>In this lab, will use numbers (0-255) instead of HIGH & LOW for LED brightness control

**TX and RX**
TX = Where ESP32-S3 sends its CAN Packets
RX = Where ESP32-S3 listens for CAN Packets (more accurate desc?)
- These are connected to the corresponding TX and RX pins on the receiving board.

**[ESP32-S3 setup with lights board here]**




<br><br>
### What are CAN Packets
They are the message containers (also called frames) that are sent across the CAN network. 
<img width="433" height="45" alt="CAN Frame" src="https://github.com/user-attachments/assets/e8b40d6e-b786-4343-b1b7-83bf5cf067ac" />

<sup><sub>From [CAN Protocol Overview](https://www.ni.com/en/shop/seamlessly-connect-to-third-party-devices-and-supervisory-system/controller-area-network--can--overview.html?srsltid=AfmBOorU1zvAJigLmHfHU1ybkgBWtry8Tv-Zwm5Jaf2WLQuyYqfSllEi)</sub><sup>


They have 12 parts shown in the image above. The three (highlighted) used in this lab are:
- **ID:** The identifier (name) of the CAN Packet
- **The data (0-8 bytes):** Also called **payload.** They're the content sent.
- **DLC:** The length of the data.

In this lab, you'll send a CAN Packet whose payload determines what the lights do. 

<br><br>

### Pulse Width Modulation (PWM)

You'll use built-in <i>PWM</i> to control <i>light brightness</i> according to what the payload says.

**What is PWM?**
It's a method that uses direct current (DC), which only outputs a HIGH (ON) or LOW (OFF) current, to output voltage values in between those two (similar to Analog current (AC), which automatically can output a range of those two values).

<i>How high is HIGH and how low is LOW?</i>
>Depends on the circuitry/microchips' preferences. The ESP32-S3's internal logic specifically recognizes a 5V or 3.3V as the maximum. (This and and any close values are HIGH). Same for 0V when it comes to LOW.

Specifically, it creates a **duty cycle** where, for a certain duration of that cycle, output is HIGH, and for the rest of the cycle, output is LOW. This duty cycle repeats and over time, outputs the average voltage. The longer that HIGH is the output, the higher the average voltage. This allows the average voltage to take a range of values.
>For example, if duty cycle is 50% HIGH and 50% low, the ultimate output is half of the maximum voltage, which would tell an LED to be half as bright.
<img width="412" height="74" alt="PWM wave" src="https://github.com/user-attachments/assets/f6b41997-1890-4135-91ee-de3773572dc9" />

<sup><sub>From [GeeksforGeeks](https://www.geeksforgeeks.org/electronics-engineering/pulse-width-modulation-pwm/)</sub><sup>

In the next part about code, you'll learn how to write the code that tells the ESP32-S3 when to output (or input, i.e. read) these voltage signals to other connected boards!










