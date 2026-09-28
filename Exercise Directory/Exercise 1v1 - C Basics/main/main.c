// Exercise 1v1 - C Basics  (Check out "Reading 1v1 - C Basics.md")
//
// Complete each TODO in order
// How to run: see "Exercise Directory/Exercise Instructions.md" (board: idf.py flash monitor, no board: idf.py qemu).
// On the ESP32, the program starts at app_main() instead of main().

// There is no testbench for these exercises, but you should run the code and confirm your answer
// All works in exercise will not be checked but purely for exercise to aid your understanding 
// in completing the final project!

#include <stdio.h>


// Task 4: print "Current Temperature: <temperature>"
void print_temperature(int temperature)
{
    // TODO (Task 4)
}


// Bonus 5: print one message.
//  if > 100:  "WARNING: Temperature is too high!"
//  if > 80:  "Temperature is warm."
//  else  "Temperature is normal."
void check_temperature(int temperature)
{
    // TODO (Bonus 5): use if / else if / else (order matters!)
}


// Bonus 6: return Fahrenheit (F = C * 9 / 5 + 32). Don't print here but return the value.
int celsius_to_fahrenheit(int celsius)
{
    // TODO (Bonus 6)
    return 0;
}


void app_main(void)
{
    // Task 1: change temperature to 100.
    // Expected: Temperature: 100
    printf("Task 1:\n");
    int temperature = 75;
    printf("Temperature: %d\n", temperature);

    // Task 2: if temperature > 90, print "WARNING: Temperature is too high!"
    // Expected: the warning prints for 100, and not for 75.
    printf("\nTask 2:\n");
    // TODO (Task 2)

    // Task 3: use a for loop to print 0 through 9, one per line.
    printf("\nTask 3:\n");
    // TODO (Task 3)

    // Task 4: finish print_temperature(), then call it with 75.
    // Expected: Current Temperature: 75
    printf("\nTask 4:\n");
    // TODO (Task 4)

    // Bonus 5: finish check_temperature(). Loop over temperatures and call
    // print_temperature() and check_temperature() on each value.
    // Expected: 70 normal, 85 warm, 95 warm, 105 WARNING, 75 normal
    printf("\nBonus Task 5:\n");
    int temperatures[5] = {70, 85, 95, 105, 75};
    // TODO (Bonus 5)

    // Bonus 6: finish celsius_to_fahrenheit(). Use a while loop to print
    // 0 to 100 C in steps of 20, as "<C> C = <F> F".
    // Expected: 0 C = 32 F, 20 C = 68 F, ... 100 C = 212 F
    printf("\nBonus Task 6:\n");
    int celsius = 0;
    // TODO (Bonus 6)

    printf("\nDone!\n");
}
