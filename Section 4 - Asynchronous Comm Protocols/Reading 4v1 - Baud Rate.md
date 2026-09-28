# What is a Baud Rate?
At its core, baud rate is the speed at which microcontrollers talk to each other. It measures the number of signal values (units of data) that are processed per second on a communication line. The higher the baud rate, the faster the hardware changes the voltage on the wire, meaning information is sent and received more quickly.

- A new signal value meaning: (the next one, regardless of whether the actual value is different from the previous).

The higher the baud rate, the **faster the data** is sent/received.
- In the sense that, the information is read faster because each new signal value is received sooner.

## Importance
Microcontrollers communicating with each other must agree upon a baud rate so that they communicate at the same speed. The baud rate is fixed from the start.

### Visual Example:

Context: Imagine a signal as a wave pattern; usually modeled as a line that (the height of the line is the value of the signal, and the x-axis measures time). 
The significance of a signal being sent is so that the value (height) is communicated at a certain time.
- In a digital signal (like in this example) bits are the **data** sent through signal. The signal value (height) determines if the bit is 1 or 0.

<img width="472" height="343" alt="image" src="https://github.com/user-attachments/assets/794ee29f-0c8f-4b1a-a391-6731ee05dc61" />

Here, the red numbers denote each new signal value, which counts toward the baud rate. 
- Additionally (this is optional to know), the two bits sent when the value of the signal is high are 1s, while the bit sent when the value of the signal is low is 0.
- The bit rate, which counts how many of these bits are sent per second, is <i>not</i> the baud rate.

The baud rate is 3 because 3 different signal values are occur per second. The bit rate is also 3 because 3 bits (1, 0, and 1) are sent per second.

#### Example 2
<img width="402" height="293" alt="image" src="https://github.com/user-attachments/assets/a4c5fbd6-0c23-4894-abe1-2790bb8b0fbf" />

Here, 6 different signal values occur per second. The bit rate however, is still 3 (because per 2 signal values, 1 bit was communicated).

### Data Signals
**IMPORANT:** In general, data signals are customizable to send certain combinations of bits in differently sized chunks (i.e. could send "11011010", which is 8 bits of info. You could send 16 if you want). Certain combinations can represent specific letters, numbers, etc.
-  The signal value changes to communicate this specific combination, which is how data signals send specific information.

Sources: https://www.geeksforgeeks.org/computer-networks/baud-rate-and-its-importance/
https://scienceinsights.org/what-is-the-baud-rate-and-why-does-it-matter/
