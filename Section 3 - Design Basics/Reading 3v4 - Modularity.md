# Modularity

In the previous section, we discussed modularity, but here we will go deeper into how modularity is implemented into our firmware!

### Intro

An important thing to keep in your mind is that the code you will deal with are all modules! For example, all functions are modules! All files are modules! Even the main function loop we use is a module.

## Headers

At the top of all FW code you will have a header. The header is a great place to explain what the purpose of this code is for! More importantly, it is a place to make use of modular design. We can use the top area to import libraries, create useful macros, and define useful constants. Here I will go into detail of how to write and understand the headers of our code!

### Imports

In the header we can link in other modules (think library imports in higher level language like python/java). For example, let's say that there is a module out there that implements buffers (which we will see later in Reading 3v3). Instead of needing to re-implement a buffer, we can just use the buffer that comes with the imports! In other words, part of the headers job is to import in other modules.

Utilizing our idea of abstraction, this lets us use really complex and useful tools by simply importing them in!

Another very important thing is header files which we write ourselves! Later I will talk about specifically how that works.

### Macros / Constants

Let's say that part of our code is accessing a very specific value (like an IO pin) over and over. In the code it might look like
```
TODO
```

The # define keyword lets us define a macro to abstract some number to it's meaning.

## Modular Design

As mentioned in section 1, modular design is KEY to decreasing complexity! Here you will see how we would generally make our program more modular. Later you will even see how this will simplify some of the more complicated techniques like concurrent programming.

### Functional Programming 

We will formalize this more in a later section on planning, but you want to imagine your code as being made up of two parts.

1) The main control loop: the logic of the code that determines what is happening and when
2) The functions to be executed: the individual tasks that interact firmware with hardware or other firmware 

In this section, we will be focusing on the individual tasks! The way we want to functionally program, is writing a function to do a specific task. It's easiest to explain with an example!

Let's take the simple example of blinking an LED when a button signal is received after 5 consecutive polls. How would I naively implement this without functional programming? The pseudo-code is below
```
#include "esp_timer.h"

...

bool button_pressed

...

#define BLINK_GPIO GPIO_NUM_2

...

// Main Control Loop
main() {

  ...
  // poll the button input into a buffer

  // parse the buffer
  button_pressed = true
  for (size_t i = 0; i < size; i++) {
    if (data in buffer isn't expected) { button_pressed = false; }
  }

  // if button is pressed, 
  if (button_pressed == true) {
    // Use the timer API inside the loop to know if we need to switch states
    // Potentially toggle IO states
  }
}
```

### Header Files
