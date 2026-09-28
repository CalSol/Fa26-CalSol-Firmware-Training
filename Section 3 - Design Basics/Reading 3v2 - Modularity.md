# Modularity

In the previous section, we discussed modularity, but here we will go deeper into how modularity is implemented into our firmware!

### Intro

An important thing to keep in your mind is that the code you will deal with are all modules! For example, all functions are modules! All files are modules! Even the main function loop we use is a module. With everything is a module, and modules helping us reduce complexity, let's try to see how modules work.

## Headers

At the top of all FW code you will have a header. The header is a great place to explain what the purpose of this code is for! More importantly, it is a place to make use of modular design. We can use the top area to import libraries, create useful macros, and define useful constants. Here I will go into detail of how to write and understand the headers of our code!

### Imports

In the header we can link in other modules (think library imports in higher level language like python/java). For example, let's say that there is a module out there that implements buffers (which we will see later in Reading 3v3). Instead of needing to re-implement a buffer, we can just use the buffer that comes with the imports! In other words, part of the headers job is to import in other modules.

In C, you can import these header files using the `#include` directive:

```c
#include "freertos/queue.h" // imports the queue module!
```

Utilizing our idea of abstraction, this lets us use really complex and useful tools by simply importing them in!

Another very important thing is header files which we write ourselves! Later I will talk about specifically how that works.

### Macros / Constants
Let's say that your code needs to turn on an LED connected to GPIO pin 4. In raw code without macros, you would use a "magic number" (a hardcoded number with no context):

```c
// What does the number 4 even mean?
// If I change the wiring, I have to find and replace every '4' in my entire file!
gpio_set_direction(4, GPIO_MODE_OUTPUT);
gpio_set_level(4, 1);
```

To fix this, we use the `#define` keyword. This lets us define a macro to abstract some number into a human-readable name.

```c
#define LED_PIN 4

gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
gpio_set_level(LED_PIN, 1);
```
By defining constants at the top of your file, if you ever change your hardware wiring, you only have to change the number in _one_ place, and the rest of  your module updates automatically.

## Modular Design

As mentioned in section 3v1, modular design is KEY to decreasing complexity! Here you will see how we would generally make our program more modular. Later you will even see how this will simplify some of the more complicated techniques like concurrent programming.

### Functional Programming 

Functional programming is the concept of abstracting sub-routines (sub-tasks) as a singular function call. For example, if I wanted to find the average of a list of numbers (which is more commonly used in firmware than you would think), I would need to loop through each number in the list and then divide by the size of the list. To do this each time we want an average, will bloat our code. Instead, we can create an average function that takes in a list and returns a single number as the output. In this way, we can abstract away how averages are calculated and allow it to be simply called.

In general, we want to keep our code simple, so making more complicated things functions are ideal. It also makes your code more readable and logical, as you can easily read that you are getting an average, instead of needing to focus on how the average was computed.

### Header Files

A header file is the `.h` files in our codebase. As mentioned before, imported files at the top of our code are linked and effectively printed at the top! We can use this to simplify our code with a `.h` file.

A header file tells the C compiler what functions, macros, and data structures exist in your project without cluttering the file with the actual implementation details (the code that does the work, which lives in `.c` files). In other words, the pinnacle of functional programming! We are using the header file to **interface** between the function and the implementation.

`.h` files is used both to decrease the complexity needed, while also providing documentation. PLEASE use these.

## Conclusion

<img height="200" alt="Modularity diagram" src="./../images/SECTION2/modularity.png" />

In all, we should strive in our code to use modularity. We can see this through how our header is setup with us importing modules and abstracting away hardware into things we can logically read. We then need to design modularly with functional programming!
