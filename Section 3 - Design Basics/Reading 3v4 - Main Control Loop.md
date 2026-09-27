# Planning and FSMs

The Main Control Loop is the logic base of your firmware. In this section, I will go less into how the firmware of the control loop is implemented, but more how the system itself works. This section will teach you how to plan out your main control loop to be simple!

## Naive - Flow Chart

Let's say I want to make an elevator. I can draw a flow chart out like this:

TODO IMAGE OF ELEVATOR BLOCK DIAGRAM

### What is a block?

A block is a thing your **system** is doing, or in other words the state your system is in. For example, with our elevator we have a block representing the elevator door being opened. In this state, you are opening the door to the elevator.

### What is an arrow?

An arrow in our flow chart represents the reasons we move from one block to another block. An example is the block of the doors being closed to the elevator moving. For each arrow, we also want to define all the ways we can change these states.

In this example, we change our states by pressing a floor button.

We can think of these arrows as **conditions** that when true cause the state of our system to change.

## Finite State Machines (FSM)

We have basically derived how a **finite state machines** work!

An FSM is a **state** transition diagram. In other words, it is a bunch of states accompanied with events, which in firmware move the system to a different state.

In CS61C, you will learn the more formal FSM, where certain read bits send you from what state to another, but it works here as well!

### ENUM

To define our states more formally, we use an **enum** (an enumeration relating variable names to numbers)!

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

<i> Note that k prefix refers to the fact that these variables are integers, with the kStartup being enumerated to 0, kClosedWaiting to 1, etc. </i>

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

Another useful tool for book keeping is using **flags**. A flag is a boolean variable (true or false) that keeps track if something has happened or not. 

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

The way we should design our main code loop block is as follows:

1) Define the goals of the project. What actually needs to happen in the firmware?
2) Write out what functions and states you will need to accomplish these goals
3) Draw the FSM out!
4) Implement the logic in the main loop based off of the FSM using enum and flags!

## Implementation Tips

When implementing your FSMs, you want to think of your enums as your states, and then your main loop logic as the arrows getting you between the states.

We recommend the actions being done in specific state be caused by an if statement checking if you are within the state.

The reason why, is it allows for cleaner code, where certain function calls and logic can be re-used in multiple states trivially.

## Summary

In this section we talked about how we want to imagine our firmware as a system with **states** and **conditions** to move between the states. We found we can formalize this in a **FSM** and implement it using **enum** and **flags**

In the next section, we will talk about the different tasks the Main Control Loop will call.