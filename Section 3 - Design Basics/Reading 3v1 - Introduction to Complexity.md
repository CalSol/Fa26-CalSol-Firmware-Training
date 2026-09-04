# Section 3.1 - Introduction to Complexity

Firmware and code in general will seem complicated at first. However, with some techniques and tool, we can tackle firmware together! 

![XKCD on Complexity](./../images/SECTION3/XKCD_COMPLEXITY.png)

*Taken from XKCD*

## Dependencies and Information Overload

Let's say I'm trying to create code that turns on the physical brake lights when the brake pedal is pressed.
This begs a few questions. 
- How does the car know the brake pedal is being pressed?
- How does the car know how to time keeping the lights on?
- How does it keep time?
- How do the pedals on the bottom shell talk to the brake lights on the top shell?
- How do the brake lights vary in intensity?

There are a lot of questions that need to be answered and to be honest, it seems intimidating. To even understand
one simple part of the car, it seems as if you would need to understand a bunch of other things.

Another example (which some of you may recognize and others will see in the future) is the RISC-V CPU. For anyone seeing this for the first time, this is an incredibly daunting piece of computing. However, those who have taken it will know that we can handle the complexity of this in a very simple way.

![CS61C RISCV PIPELINE](./../images/SECTION3/CS61C_RISCV_PIPELINE.png)

*Taken from CS61C Reference Card*

### Abstraction

Our solution (and one you will see EVERYWHERE in EE and CS) is Abstraction!!!

Abstraction is simplifying a system through omitting unimportant details. For example, to understand how to drive a car, you don't need to know exactly how the hardware of the car actually drives the motor. Instead, all you need to know is that when you press the pedal, the car accelerates, which is much more useful than how the whole cars system works. As you can see, we can convert complex systems into simple abstractions that are more useful for us to use.

### Modularity

Abstraction is often implemented with modularity. A module in code can be a function where we abstract away the exact details of how it works, and instead just focus on how the function can be used. Throughout this lab we will go through a lot of important abstractions, but here I will give a general overview of how to read libraries and common firmware abstractions.

Take here, me hovering over the ___ function.

Modularity also matters in how YOU program! Later, we will discuss ways to make the whole code for a system modular, but for now we will discuss on a more micro level. Here are a few rules for this:
- If you are doing something multiple times, create a function for it! This will make code shorter and more readable. It will also save a lot of time
- If you are directly interfacing with hardware (you will see a lot more about what this means later), make a function to do so. This will keep the firmware code a lot more focused on the logic and less on the specifics of how we deal with firmware.
- Make modules work in isolation from the rest of the code and be robust to be used in many situations. If a module is supposed to handle inputted data, make sure it can handle all types of data and returns the data in a way that is easily usable by any other program.

## Obscurities and Syntax

### Planning

### Documented Code

## What Tools Will We Use?

Throughout this section, you will see a lot of techniques that programmers everywhere use to write non-complex code. You will soon learn, that all of the seemingly difficult techniques you will see are actually clever ways to manage complexity and make code easier to read and write. This lab is only the tip of the iceberg (and you learn much more in EVERY hardware and software class at Berkeley about this), but we hope this is a good start.
