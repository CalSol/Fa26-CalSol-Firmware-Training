# More on IO

## Hardware

Without confusing you with all the gritty details I will briefly give a conceptual idea of how Hardware actually does digital input/output. Hopefully, this will motivate the techniques you will learn.

### Input

We will define in much greater detail of what a bit or byte is, how bits are communicated on a wire, and exact protocols in sections 4 and 5, but the gist of how IO pins work is that we have low and high thresholds.

What do I mean? A signal is considered a 0, if the voltage it sees on the line is low, and it is a 1 if it sees a high. Intuitively, a low would be just 0 voltage and a high voltage would just be the voltage rail (the supply used by the IC). However, what if we have noise? Imagine a noise comes through on my 5V rail IO pin that is supposed to be low, and it spikes the voltage to 0.2V. Obviously, this isn't high, but it's also not zero.

In digital, we define high and low based off of the thresholds of our IO standards. For simplicity, just know that we can find the exact Vthreshold Low and Vthreshold High on our datasheets, referring to the threshold to be a low or a high signal respectively. We can see this easier in our image below:

![Digital Thresholds](./../images/SECTION3/DigitalThresholds.jpg)

There is obviously a lot more nuance, but for now this should give a good intuition.

### Output

Our outputs are similar, but instead of reading a threshold, we are pushing or pulling our rail to either the high or low state. You can also find output ranges on datasheets.

### Re-motivating Pull-ups and Pull-downs

Hopefully this re-motivated the idea of pull-ups from the hardware lab. If we really need our digital signal to be high or low, why risk it? If we are not high or low, we are called floating, and this can cause problems. Instead, we can set a "nominal" state of that line as high with a pull-up or low with a pull-down! 

## Buffer Implementations

### Firmware Buffers

Some buffers you will deal with are on the firmware side. Let's say we receive a bunch of packets, but like me in Supernode, the CPU doesn't have enough compute power to handle the input.

I can create a buffer as some data structure that can hold packets. **Writing** to the buffer is taking polled data and adding it to the data structure. **Reading** from a buffer is taking polled data and using it.

### Ring Buffers

TODO image

A common implementation of a firmware buffer is a ring buffer!

Going back to my example, you can imagine I try to write everything down on a piece of paper, but eventually after enough questions I will run out of paper!

A solution is to use a whiteboard! Imagine I write everything on the whiteboard in Supernode. Now when I run out of whiteboard space at the bottom, I can erase the top question of the board and use that space.

As you can imagine we get the positive of effectively infinite space, but with the possibility we might **overwrite** our data. In C we generally implement a ring buffer as an array where we wrap the index to the front when we get to the end of the array. 

To get a little more detailed on implementation, you would probably also need to store where you are in the buffer at any given moment, but this can easily be done by storing the index of the last read and last write.

### Common Schemes (Hardware)

We just saw dealing with multiple packets, but what about multiple bits. Luckily, the hardware does this for you! Each bit is put into a buffer the size of a packet or two, such that we can buffer a whole packet before we read it in!

Due to the complexity of the subject and the fact you won't be implementing these, I will leave this to you to learn more specifically how these are implemented. For those interested in working with FPGAs, this is pretty important.
