# Modularity

In the previous section, we discussed modularity, but here we will go deeper into how modularity is implemented into our firmware!

### Intro

An important thing to keep in your mind is that the code you will deal with are all modules! For example, all functions are modules! All files are modules! Even the main function loop we use is a module.

TODO talk about this as a motivation for abstraction

## Headers

At the top of all FW code you will have a header. The header is a great place to explain what the purpose of this code is for! More importantly, it is a place to make use of modular design. We can use the top area to import libraries, create useful macros, and define useful constants. Here I will go into detail of how to write and understand the headers of our code!

### Imports

In the header we can link in other modules (think library imports in higher level language like python/java). For example, let's say that there is a module out there that implements buffers (which we will see later in Reading 3v3). Instead of needing to re-implement a buffer, we can just use the buffer that comes with the imports! In other words, part of the headers job is to import in other modules.

Utilizing our idea of abstraction, this lets us use really complex and useful tools by simply importing them in!

Another very important thing is header files which we write ourselves! Later I will talk about specifically how that works.

### Header Files

A header file is the .h files in our codebase. As mentioned before, imported files at the top of our code are linked and effectively printed at the top! We can use this to simplify our code with a .h file.

A header file tells the C compiler what functions, macros, and data structures exist in your project without cluttering the file with the actual implementation details (the code that does the work, which lives in .c files).

.h files is used both to decrease the complexity needed, while also providing documentation. PLEASE use these

### Macros / Constants

Let's say that part of our code is accessing a very specific value (like an IO pin) over and over. In the code it might look like
```
TODO
```

The # define keyword lets us define a macro to abstract some number to it's meaning.

## Modular Design

As mentioned in section 3v1, modular design is KEY to decreasing complexity! Here you will see how we would generally make our program more modular. Later you will even see how this will simplify some of the more complicated techniques like concurrent programming.

### Functional Programming 

Functional programming is the concept of abstracting sub-routines (sub-tasks) as a singular function call. For example, if I wanted to find the average of a list of numbers (which is more commonly used in firmware than you would think), I would need to loop through each number in the list and then divide by the size of the list. To do this each time we want an average, will bloat our code. Instead, we can create an average function that takes in a list and returns a single number as the output. In this way, we can abstract away how averages are calculated and allow it to be simply called.

In general, we want to keep our code simple, so making more complicated things functions are ideal. It also makes your code more readable and logical, as you can easily read that you are getting an average, instead of needing to focus on how the average was computed.
