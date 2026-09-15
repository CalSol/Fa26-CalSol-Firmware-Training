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
# Arithmetic

C can perform normal mathematical operations.

```c
int a = 10;
int b = 5;

int addition = a + b;
int subtraction = a - b;
int multiplication = a * b;
int division = a / b;
```

The main arithmetic operators are:

| Operator | Meaning |
|---|---|
| `+` | Addition |
| `-` | Subtraction |
| `*` | Multiplication |
| `/` | Division |
| `%` | Remainder |

For example:

```c
int value = 10 % 3;
```

The result is:

```text
1
```

because:

```text
10 / 3 = 3 remainder 1
```

---

# Comparison Operators

Comparison operators allow us to compare values.

| Operator | Meaning |
|---|---|
| `==` | Equal to |
| `!=` | Not equal to |
| `>` | Greater than |
| `<` | Less than |
| `>=` | Greater than or equal to |
| `<=` | Less than or equal to |

For example:

```c
speed > 50
```

checks whether `speed` is greater than `50`.

Be careful with:

```c
=
```

and:

```c
==
```

They mean different things.

`=` assigns a value:

```c
speed = 50;
```

`==` compares two values:

```c
speed == 50
```

---

# If Statements

An `if` statement allows the program to make decisions.

```c
int temperature = 100;

if (temperature > 90)
{
    printf("Temperature is high!\n");
}
```

The code inside the `{ }` only runs if the condition is true.

---

## `if` and `else`

We can also provide another action if the condition is false.

```c
int temperature = 70;

if (temperature > 90)
{
    printf("Temperature is high!\n");
}
else
{
    printf("Temperature is normal.\n");
}
```

---

## `else if`

We can check multiple conditions:

```c
int temperature = 85;

if (temperature > 100)
{
    printf("Temperature is too high!\n");
}
else if (temperature > 80)
{
    printf("Temperature is warm.\n");
}
else
{
    printf("Temperature is normal.\n");
}
```

---

# Logical Operators

Sometimes we want to check multiple conditions at once.

The most common logical operators are:

| Operator | Meaning |
|---|---|
| `&&` | AND |
| `||` | OR |
| `!` | NOT |

For example:

```c
if (temperature > 80 && temperature < 100)
{
    printf("Temperature is within range.\n");
}
```

Both conditions must be true because we used:

```c
&&
```

---

# Loops

Loops allow us to repeat code.

Two important loops in C are:

- `for`
- `while`

---

## `for` Loop

A `for` loop repeats code a specific number of times.

```c
for (int i = 0; i < 5; i++)
{
    printf("%d\n", i);
}
```

Output:

```text
0
1
2
3
4
```

The variable `i` increases by one after every loop.

This:

```c
i++;
```

is equivalent to:

```c
i = i + 1;
```

---

## `while` Loop

A `while` loop continues running while a condition is true.

```c
int count = 0;

while (count < 5)
{
    printf("%d\n", count);

    count++;
}
```

Output:

```text
0
1
2
3
4
```

---

# Infinite Loops

Embedded systems commonly use infinite loops.

For example:

```c
while (1)
{
    printf("Running...\n");
}
```

Because `1` represents true, this loop runs forever.

You will see this pattern often in embedded programming.

Conceptually, a microcontroller might do:

```c
while (1)
{
    read_sensor();

    process_data();

    control_motor();
}
```

The microcontroller continuously performs its tasks until power is removed or the system is reset.

---

# Functions

Functions allow us to organize and reuse code.

Instead of writing the same code repeatedly, we can put it inside a function.

Example:

```c
#include <stdio.h>

void say_hello(void)
{
    printf("Hello!\n");
}

int main(void)
{
    say_hello();

    say_hello();

    return 0;
}
```

Output:

```text
Hello!
Hello!
```

---

# Function Parameters

Functions can also receive information.

```c
void print_speed(int speed)
{
    printf("Speed: %d\n", speed);
}
```

We can call it using:

```c
print_speed(50);
```

Output:

```text
Speed: 50
```

---

# Functions That Return Values

Functions can also calculate and return a value.

```c
int add(int a, int b)
{
    return a + b;
}
```

We can use the function like this:

```c
int result = add(5, 10);

printf("%d\n", result);
```

Output:

```text
15
```

---

# Arrays

Arrays allow us to store multiple values of the same type.

For example:

```c
int temperatures[5] = {70, 72, 75, 78, 80};
```

Each value has an **index**.

```text
Index:       0   1   2   3   4
Value:      70  72  75  78  80
```

Notice that array indexing begins at:

```text
0
```

To access the first value:

```c
temperatures[0]
```

To access the third value:

```c
temperatures[2]
```

Example:

```c
printf("%d\n", temperatures[2]);
```

Output:

```text
75
```

# Comments

Comments allow us to leave notes inside our code.

A single-line comment uses:

```c
// This is a comment
```

For example:

```c
int speed = 50; // Motor speed
```

A multi-line comment uses:

```c
/*
 * This is a
 * multi-line comment.
 */
```

Comments are ignored by the compiler.

# Example Program

Let's combine some of the concepts we just learned.

```c
#include <stdio.h>

void check_temperature(int temperature)
{
    if (temperature > 100)
    {
        printf("WARNING: Temperature is too high!\n");
    }
    else if (temperature > 80)
    {
        printf("Temperature is warm.\n");
    }
    else
    {
        printf("Temperature is normal.\n");
    }
}

int main(void)
{
    int temperatures[5] = {70, 85, 95, 105, 75};

    for (int i = 0; i < 5; i++)
    {
        printf("Temperature: %d\n", temperatures[i]);

        check_temperature(temperatures[i]);
    }

    return 0;
}
```

This example uses:

- Variables
- Arrays
- Functions
- `for` loops
- `if` statements
- Comparisons
- `printf()`

These concepts will appear frequently throughout the rest of the firmware training.


## Exercise 1v1 - C Basics
[https://www.onlinegdb.com/online_c_compiler](https://www.onlinegdb.com/online_c_compiler)

Will have to download the C/C++ extension in VSCode.
