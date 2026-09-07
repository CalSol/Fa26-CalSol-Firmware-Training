# Reading 3.2 - Modularity

In the previous section, we discussed modularity, but here we will go deeper into how modularity is implemented into our firmware!

### Intro

An important thing to keep in your mind is that the code you will deal with are all modules! For example, all functions are modules! All files are modules! Even the main function loop we use is a module.

## Headers

At the top of all FW code you will have a header. The header is a great place to explain what the purpose of this code is for! More importantly, it is a place to make use of modular design. We can use the top area to import libraries, create useful macros, and define useful constants. Here I will go into detail of how to write and understand the headers of our code!

### Imports

In the header we can link in other modules (think library imports in higher level language like python/java). For example, let's say that there is a module out there that implements buffers (which we will see later in Reading 3v3). Instead of needing to re-implement a buffer, we can just use the buffer that comes with the imports! In other words, part of the headers job is to import in other modules.

Utilizing our idea of abstraction, this lets us use really complex and useful tools by simply importing them in!

We won't go into this in detail, but we also import files with the .h keyword. This is a header file. Basically, a simplified version of a library that only gives the functions and how to interact with them. Another example of abstraction making our life easier!!!

### Macros / Constants

Let's say that part of our code is accessing a very specific value (like an IO pin) over and over. In the code it might look like
```
TODO
```

The # define keyword lets us define a macro.

## Modular Design

### Multiple Functions 

### Multiple Files
