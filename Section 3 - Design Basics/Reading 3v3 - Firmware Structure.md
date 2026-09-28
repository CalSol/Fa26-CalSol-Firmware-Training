# Firmware Structure

The most important thing to manage our complexity is to understand the structure of firmware itself! Here is the structure below, don't worry we will discuss this in great depths.

TODO IMAGE

## Structure

You want to imagine your code as being made up of two parts:

1) The main control loop: the logic of the code that determines what is happening and when
2) The tasks to be executed: the individual tasks that interact firmware with hardware

### Logic (Main Control Loop, Section 3v4)

The **main control loop** you can imagine as the **brain** of of your code. The main control loop shouldn't be interacting with hardware, it should be purely dealing with data it already has. In other words, it is the logic of the code, not the actual tasks itself.

In our ESP-IDF code, we can implement our main control loop as a large looping block of code. We then have if statements determining what the ESP will do! You will see in section 3v4 how we develop this main control loop to be simple.

### IO Actions (Tasks, Section 3v5)

The **Tasks** you can imagine as the **body** of your code. The tasks should be interacting with hardware closely. It will be the blocks of code that are actually writing out of IO pins and reading from IO pins!

In our ESP-IDF code, you will see in section 3v5, that we will implement tasks with a real time operating system that allows for concurrent/parallel running of tasks!

## Functions

As discussed in the modularity section, we want to use modular design in our code. In other words, we want to do as little computation as possible within the main functions for the **main control loop** and **tasks**.

Remember, life gets much simpler when we abstract away actions as reusable functions. Functional programming therefore isn't a part of our Logic vs Actions structure, but it must be used by both parts to manage complexity

### Conclusion

Here we introduced you to the **main control loop** and **task** structure of our firmware. The **main control loop** is the brain that decides what happens logically. The **tasks** are the body that involves hardware and software. We then implement all of our structure with functional programming to reduce complexity!
