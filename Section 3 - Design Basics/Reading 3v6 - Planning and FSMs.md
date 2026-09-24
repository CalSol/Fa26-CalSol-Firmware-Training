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

Whether you like it or not, we have basically derived how a finite state machines work!

An FSM is a state transition diagram. In other words, it is a bunch of states accompanied with which events in firmware move the system to a different state.

### ENUM / Flags

## Implementation Tips

## Summary


