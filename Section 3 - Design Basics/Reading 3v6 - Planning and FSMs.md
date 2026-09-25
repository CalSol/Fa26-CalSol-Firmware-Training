# Planning and FSMs

All of these techniques are good and all, but the biggest way to mitigate complexity is through good planning! Here, I will go less into how firmware and hardware work, but more how systems work. You will learn in this project, understanding systems and firmware are the same skill.

## Naive - Flow Chart

Let's say I want to make an elevator. I can draw a flow chart out like this:

TODO IMAGE OF ELEVATOR BLOCK DIAGRAM

### What is a block?

A block is a thing your system is doing, or in other words the state your system is in. For example, with our elevator we have a block representing the elevator door being opened. In this state, you are opening the door to the elevator.

### What is an arrow?

An arrow in our flow chart represents the ways we can move from one block to another block. An example is the block of the doors being closed to the elevator moving. For each arrow, we also want to define all the ways we can change these states.

In this example, we change our states by pressing a floor button.

## Finite State Machines (FSM)

We have basically derived how a finite state machines work!

An FSM is a state transition diagram. In other words, it is a bunch of states accompanied with events, which in firmware move the system to a different state.

In CS61C, you will learn the more formal FSM, where certain read bits send you from what state to another, but it works here as well!

### ENUM

To define our states more formally, we use an enum!

```
enum ElevatorState {
  kStartup,
  kClosedWaiting,
  kClosedMoving,
  kOpening,
  kClosing,
  kOpen,
  kShutdown
};
```

<i> Note that k prefix refers to the fact that these enums are implemented as integers </i>

Here you can see for our elevator we defined our states above. The enum tells the code to enumerate (assign numbers) to each of the values. The data type of our enum is **ElevatorState**. You can see some examples as follows:

```
// Used at start to put the state into startup
ElevatorState elevator_state = kStartup;

/** When the door is in opening state, run the motor to open the door. After enough time switch the state to the door being open **/
if (elevator_state == kOpening) {
    // Drive motor to open elevator door
    if ( //Timer is finished running ) {
        elevator_state = kOpen;
    }
}
```

As you can see, we can in our code abstract away a lot of book keeping into a single state variable that we can check to see where we are at. We can then off certain conditions swap the state!

### Flags

Another useful tool for book keeping is using flags. A flag is a boolean variable (true or false) that keeps track if something has happened or not. 

An example is let's say for our elevator we would like a flag for whether when the door is closing someone clicks the open button again. You can see a mock implementation below:

```
// flag true if object sensed in door
boolean door_sense = false;

// flag true if the open_door button was pressed
boolean open_door_pressed = false; 

// Check to see if object in door
if ( // object in door ) { door_sense = true; }

...

// Check to see if door open button was pressed
if ( // button pressed ) { open_door_pressed = true; }

...

// Closing code
if ((elevator_state == kClosing) && (!door_sense) && (!open_door_pressed)){
    // Drive motor to close elevator door
    if ( //Timer is finished running ) {
        elevator_state = kOpen;
    }
}
```

There is obviously a bit more nuance to this example, but I hope you got the point that flags can be useful as additional conditionals to know to switch states.

### Workflow

The way we should design code is as follows:

1) Define the goals of the project. What actually needs to happen in the firmware?
2) Write out what functions and states you will need to accomplish these goals
3) Draw the FSM out!
4) Implement the logic in the main loop based off of the FSM

## Implementation Tips

When implementing your FSMs, you want to think of your enums as your states, and then your main loop logic as the arrows getting you between the states.

We recommend the actions being done in specific state be caused by an if statement checking if you are within the state.

The reason why, is it allows for cleaner code, where certain function calls and logic can be re-used in multiple states trivially.

## Summary

In all, section 6 should've taught you a lot about how to manage complexity! 

Section 6 hopefully showed you how to structure your main loop logic, with the timing and synchronization section being of aid.

Section 4 hopefully showed you how to use functions that spur off of the main logic, with the IO techniques and the RTOS showing you how to utilize the ESP32 hardware to do more powerful firmware.

In the next few sections, we will go more in depth with IO and show some of the communication protocols on the ESP32!