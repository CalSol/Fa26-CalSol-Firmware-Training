# Reading 1v1 - C Basics

## Installing C
We actually don't need to have C installed on your local system due to ESP-IDF having its own specialized C compiler in the background.

Thus the only setup for C that we have to do is to add the extension on VSCode which you can do by searching up C/C++ in the extensions tab.

![Install Picture](./../images/VSCode_C_extensions.png)

<div style="padding: 2px 16px; background-color: #705337; border-radius: 6px;">
<h3>🎯 <b>TASK:</b> Download the C/C++ VSCode extension.</h3> 
</div>

# What is C?

C is a programming language commonly used for **embedded systems** and **microcontrollers**.
Unlike higher-level programming languages, C allows us to work closely with the hardware.

For example, C can be used to:
- Read sensors
- Control GPIO pins
- Communicate using CAN
- Control motors
- Generate PWM signals
- Configure hardware timers
- Communicate using I2C, SPI, and UART
- Control an ESP32
Throughout this training, we will use C to write firmware for our microcontrollers.

# Hello World

A basic C program looks like this:

```c
#include <stdio.h>

int main(void)
{
    printf("Hello World!\n");

    return 0;
}
```

When this program runs, it prints:

```text
Hello World!
```

Let's break down what each part means.

---

## `#include`

```c
#include <stdio.h>
```

`#include` allows us to use code from another library.

`stdio.h` stands for:

```text
Standard Input / Output
```

It gives us access to functions such as:

```c
printf();
```

which allows us to print information to the terminal.

---

## The `main()` Function

```c
int main(void)
{
    
}
```

`main()` is where a normal C program begins executing.

Everything inside the `{ }` belongs to the function.

For example:

```c
int main(void)
{
    printf("Hello!\n");

    return 0;
}
```

The computer executes the program starting from the first statement inside `main()`.

# Variables

Variables allow us to store information.

For example:

```c
int speed = 50;
```

This creates a variable named:

```text
speed
```

and gives it the value:

```text
50
```

We can later change it:

```c
speed = 75;
```

---

# Basic Data Types

C requires us to specify what type of information a variable stores.

Some common types are:

| Type | Description | Example |
|---|---|---|
| `int` | Whole number | `25` |
| `float` | Decimal number | `3.14` |
| `double` | Higher precision decimal | `3.141592` |
| `char` | Single character | `'A'` |
| `bool` | True or false | `true` |

Examples:

```c
int speed = 50;

float voltage = 12.5;

char letter = 'A';
```

To use `bool`, include:

```c
#include <stdbool.h>
```

Then we can write:

```c
bool motor_running = true;
```

# Printing Variables

We can use `printf()` to print variables.

For an integer:

```c
#include <stdio.h>

int main(void)
{
    int speed = 50;

    printf("Speed: %d\n", speed);

    return 0;
}
```

Output:

```text
Speed: 50
```

`%d` tells `printf()` that we want to print an integer.

Some common formatting symbols are:

| Symbol | Type |
|---|---|
| `%d` | Integer |
| `%f` | Float |
| `%c` | Character |
| `%s` | String |

Example:

```c
int temperature = 85;

printf("Temperature: %d\n", temperature);
```

---


## Exercise 1v1 - C Basics
[https://www.onlinegdb.com/online_c_compiler](https://www.onlinegdb.com/online_c_compiler)

Will have to download the C/C++ extension in VSCode.
