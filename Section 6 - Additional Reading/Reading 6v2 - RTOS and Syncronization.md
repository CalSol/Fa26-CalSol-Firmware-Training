# RTOS and Syncronization

WARNING: this is a more conceptually difficult concept to understand. Understanding this is important, but generally a lower priority as the project can be completed without it. If you need help understanding, please come up to us at a meeting and ask. 

An RTOS is a Real Time Operating System. We use an RTOS to allow for parallel and concurrent programming. This allows for us to write considerably more powerful programs, but comes at the cost of complexity. In this section, we will show you how an RTOS works, the problems that arise, and how to fix them.

## Parallel vs Concurrency

To explain parallel vs concurrency I will use an analogy. Let's say I am helping many people with their projects outside of Supernode. You can imagine I can get multiple requests from multiple people, and I can concurrently deal with them one by one. This doesn't mean sequentially, I could help student A, explain something to student B, then go back and continue helping student A. I am concurrently doing two things at once, but not really at the same time.

Now let's say I called over another lead and had them help me. Now while I am helping student A, my friend is helping out student B. Now we are literally dealing with both problems in parallel! The difference at first will seem a little subtle, but try your best to conceptualize the difference.

### Threads

Threads are the methods at which we do things concurrently. When we run our firmware, our main control loop has actually been running on a thread. So far in the lab, we've only talked about **single-threaded** programs, where all logic and functions are happening in one thread.

Now let's say, I want to concurrently poll for data, while still running my main control loop. I can now create a second thread to run concurrently. Now, I have two **tasks** running concurrently (not parallel)! I now have a **multi-threaded** program that is running my main task and polling task concurrently. 

Threads you can think of as different tasks the CPU is switching between. From my example, I have a thread of helping student A and a thread of helping student B. I am then switching between the two of them to help them!

### Dual Cores

The ESP32 is a powerful piece of hardware due to it being **multi-core**. A core is effectively (for our purposes) a CPU that can run threads. 

Going back to our example, a second core is effectively me having a friend to help me out. Now I can take the multiple threads and assign them to a specific core to work with. Our ESP32 now can handle parallelism!

## Hazards

However, concurrent and parallel programming can cause problems and create complexity. Below I will go into some common problems.

### Switching

Before we talk about it, I will discuss a quirk without multiple threads. When two threads are running, you might be wondering, when does the RTOS know to swap between the two threads. Well, sometimes it's not up to you. In other words, the RTOS can swap between your processes at really awkward times.

For the problems below, assume we have one task/thread in the main control loop, and two tasks/threads polling into a generic input buffer.

### Data Races

Let's say that my two polling tasks/threads, Thread A and Thread B, are attempting to write to the buffer at the same time. 

Worst case, let's say the way we implement our ring buffer is that we can call a function buffer_write(), it checks the index of where in the buffer we are writing to and it writes to that index. Thread A currently has the CPU and calls populate_buffer and saves the index, let's say 5, it needs to write to.

Oh no! The RTOS decided to switch, and now Thread B is running. Thread B now grabs the same index as Thread A, 5, and writes to the buffer. Now when we switch back, Thread A writes to index 5 as well, but ends up overwriting Thread B's data.

Whoops! We just lost data because of a **data race**. In general, anytime two threads are accessing the same shared data (like a buffer), we need to fear for data races! We can imagine that this holds true for multiple writers, but also when reading and writing are happening concurrently.

Note: this is a challenging topic both conceptually, but also hard to catch. The subtlety of why this is a problem is hard to catch, which makes it that much harder to debug.

### Deadlock

Now let's say we add a flag whenever someone starts trying to write to this buffer (we will formalize this later), that makes it so only one person can access it at once. But let's say to deal with data races from readers, we also have a flag for whenever a buffer is getting read. Imagine the pseudo-code below:

```
buffer_write() {
    // if writer flag -> wait for flag to turn off
    // else -> turn flag to true and advance
    // if reader flag is on -> wait for flag to turn off
    // else -> start writing
}

buffer_read() {
    // if reader flag -> wait for flag to turn off
    // else -> turn flag to true and advance
    // if writer flag is on -> wait for flag to turn off
    // else -> start reading
}
```

This implementation has a big problem! Imagine a writer thread enters buffer_write and grabs the writer flag, but a switch happens immediately after. Now the reader thread enters buffer_read and grabs the reader flag. The reader thread is forced to wait because the writer flag has been taken. When we switch back to the writer thread, it is also forced to wait because the reader flag has been taken. We have reached **deadlock** where both threads are effectively stuck and the software freezes.

I don't need to elaborate on why deadlock for our solar car is potentially problematic.

## Hazard Solutions

As you can see, everytime we have shared data, we need to beware of hazards. Here we can see some protection.

### Smart Programming

The obvious solution is to not limit the amount of shared data between threads. In other words, isolate the data of threads as much as possible! If you can't you will need mutual exclusion!

### Mutual Exclusion

As mentioned before, it is in shared memory we need to beware for hazards. Here I will discuss the main tool we will use to protect our memory.

The idea of the reader and writer flag in the deadlock example is implemented with something called a **lock**. A lock you can imagine is an object a thread can hold to get sole access to an area of code. Those who try to access the area without the lock need to wait for the thread with the lock to relinquish it.

We also have other implementations of locks using semaphores and monitors. If you have any interest in this stuff, feel free to look it up, but this is way out of scope of this learning.
