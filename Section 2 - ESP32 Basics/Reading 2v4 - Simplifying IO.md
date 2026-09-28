# Simplifying IO

IO stands for **input/output**. The input/output discussed in this reading will be the physical connection between hardware and firmware. Earlier in this section, you learned how IO pins on the ESP32 work on an abstracted level. Now, we will learn smarter schemes of how to use them.

To motivate the use of our following techniques, let me pose a few non-trivial questions:
- How is data actually read?
- How do bits actually get written and read as packets?
- If my ESP is busy with another slow task, how can I ensure my ESP will "hear" the input
- How do we precisely time reading and writing?

## IO pins

TODO Write about how IO pins work on the most basic level

## Polling

A lot of the talk of hardware above, was to motivate this idea that for our IO pins bits are read serially (one at a time). Here we will discuss a naive way to read these bits.

### Analogy

TODO add picture

Imagine I am sitting in Supernode doing my homework while a meeting is happening. To gather input of what other people are working on, I can poll them! In other words, I can go up to them and ask what they are doing every so often. This allows me as lead to get input! This is polling.

### Common Implementation

An example implementation is a function that attempts to read from an IO every 10 millisecond (we will discuss how to implement this in a later section). We are polling the input at 100 Hz. 

From a hardware perspective, we are literally checking if the IO is seeing a high or low every 10 milliseconds. 

A simple use case is for a button. If we want to see if a button is pressed, we can poll and see if the voltage seen on the line is high or low from the button.

### Trade-Offs

The main benefit of polling is simplicity. It allows us to read data in a very straightforward way. However there are two main drawbacks:

1) Speed: You can imagine in our complex system, there are many things going on at once. If we are trying to get 10 inputs at once, polling each IO 100 times a second gets very CPU intensive.

2) Data Loss: You can imagine if we have a higher speed signal that is only active for a millisecond, and we poll every 10 milliseconds, there is a high chance we can miss the input.

## Interrupts

To solve our polling drawbacks, we introduce this idea of an interrupt!

### Analogy

TODO add picture

Now let's say I am sitting in Supernode and I need to get input from people again. Instead of standing up and asking them myself, I could have each member tap me on the shoulder when they are about to ask a question. They are interrupting my current task to deliver me input. We call this an interrupt!

### Common Implementations

We commonly see interrupts in ICs and communication protocols, but we can really use it for anything.

An example of how we would use an interrupt, is to sit idle and not poll on our "data IO pin" in our nominal state. However, when an interrupt is seen on our "interrupt IO pin" we now start reading data on the data IO pin at the exact frequency we expect to see!

### Trade-Offs

We can see that we have just solved our two problems!

1) Speed: we are no longer wasting time on polling when no data is coming. We are no longer wasting resources.

2) Data Loss: we can't miss data if we are notified exactly when the data is coming. Another important fun hardware note is that we must make sure in layout the timing of our interrupts are precise, as otherwise we will poll at the wrong time.

However, there are some new drawbacks. The main one being complexity. For interrupts to work, we need a synchronized and dedicated interrupt IO pin. We also need to know how to time the polling.

In summary, we should use interrupts when the data we need is very precise and known, while polling deals with more general cases.

### More details

TODO maybe write something about ISRs

Interrupt exact implementation we will leave to you guys to find out, but the main idea is that when an interrupt is triggered, it actually queries a function! Exact implementation we will let you discover in the exercise!

## Buffers

There is however one big lingering question. How do we go from bits to packets, and packets to a datastream!

### Analogy

TODO Image

Imagine I am trying to remember all the inputs the members are giving me, but because of my other work I don't really have time to deal with them now. Instead, I can write down all of their questions on a piece of paper to buffer them. When I have the time I can then work my way through the questions and come up with answers. To save my own time, I can then write down the answers on a piece of paper and then answer all my members questions at once. What I've described are input and output buffers!

### As an API

TODO explain buffers from the context of just reading and writing from it

## Conclusion

Here you have seen how to use polling, interrupts, and buffering to deal with IO pins in a smart way. To get practice, we recommend doing exercise 3v1 to practice implementing and using polling, buffers and interrupts
