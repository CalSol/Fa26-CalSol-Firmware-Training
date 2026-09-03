# What is a Baud Rate?

A baud rate is the number of changes to a signal that happen per second.

The higher the baud rate, the **faster the data** is sent/received.

<br><br>

#### Visual Example:

Context: Imagine a signal as a wave pattern; usually modeled as a line that (the height of the line is the value of the signal, and the x-axis measures time). 
The significance of a signal being sent is so that the value (height) is communicated at a certain time.
- In a digital signal (like in this example) bits are the **data** sent through signal. The signal value (height) determines if the bit is 1 or 0.

<img width="472" height="343" alt="image" src="https://github.com/user-attachments/assets/794ee29f-0c8f-4b1a-a391-6731ee05dc61" />

Here, the red numbers denote each change, which counts toward the baud rate. 
- Additionally (this is optional to know), the two bits sent when the value of the signal is high are 1s, while the bit sent when the value of the signal is low is 0.
- The bit rate, which counts how many of these bits are sent per second, is <i>not</i> the baud rate.

The baud rate is 3 (changes per second) because 3 changes to the signal (its value/height) are made per second. The bit rate is also 3 because 3 bits (1, 0, and 1) are sent per second.

<br><br>

#### Example 2
<img width="402" height="293" alt="image" src="https://github.com/user-attachments/assets/a4c5fbd6-0c23-4894-abe1-2790bb8b0fbf" />

Here, 6 changes to the signal are made per second. The bit rate however, is still 3 (because per 2 signal changes, 1 bit was communicated).


Sources: https://www.geeksforgeeks.org/computer-networks/baud-rate-and-its-importance/
https://scienceinsights.org/what-is-the-baud-rate-and-why-does-it-matter/
