# What is a Clock Signal?






(Imagine how a clock tower rings every hour, or a metronome seen below).

<img width="320" height="320" alt="8721049" src="https://github.com/user-attachments/assets/3183ba06-6701-4036-9d71-472be2df7022" />



<br><br>
<br><br>

### The clock signal is the consistent, periodic pulse of alternating HIGH and LOW signal values (voltage changes).


<img width="572" height="162.5" alt="image" src="https://github.com/user-attachments/assets/bd79c765-6949-4b4f-989f-9cdf4ee89f72" />



<img width="164.7" height="109.2" alt="images" src="https://github.com/user-attachments/assets/4b109464-7531-48af-8915-df22e3d77647" />

- Each period (written in green) is like one pulse.
- The higher the frequency the faster (<i>more frequent</i>) the signal pulses per a certain time period.
  - Hertz (Hz) measures frequency. 1 Hz = one cycle per second.

<i>*Note: The image on the right is only a reference for frequency, not meant to represent a clock signal like the blue graph. 
Sharp edges are important for timing accuracy! </i>

<br><br>


## How the Clock Signal helps Data reading
**This is different from the data signal (shown in Baud Rate reading), whose changes from HIGH to LOW represent the changes in the data (the bits sent).**
- From just a data signal, devices wouldn't know where specific information starts and ends (the data signal is continuous).

**Here, the clock simply defines a timing a reference so transmitting/receiving devices know when a certain bit (sent through the data signal) is the beginning of some sequence of bits that makes up a message, for instance.**
- The data signal and clock signal are being transmitted simultaneously. 

<br><br>

## Rising and Falling Edge
<img width="598" height="222" alt="image" src="https://github.com/user-attachments/assets/9a824c7d-bb9e-4414-86b7-64c9d52b6b5a" />


- **Rising Edge:** Transition (rise) of clock signal from LOW to HIGH
- **Falling Edge:** Transition (fall) of clock signal from HIGH to LOW


Communication protocols like UART, CAN, I2C, and SPI define which edge devices will use as a trigger to send data, and which one will trigger to read (sample) data.

That way, all devices in a Serial communication Bus recognize the same shifts in data along the data lines (wires) in the Bus. 
- Each edge cycle is like one push of data forward. (Rates could vary depending on protocol).

<br><br>

## Relation to Synchronous Communication
This signal provides precise timing, where microcontrollers can choose specifically when (during which signal pulse/tick) to do certain communication actions.
- Devices can synchronize so that specific tasks are done one after the other.



<br><br>


Sources: https://www.think-embedded.com/communication-protocols/clock-signal-basics.html, https://engineerfix.com/what-is-a-clock-signal-and-how-does-it-work/, https://www.think-embedded.com/communication-protocols/timing-basics.html
