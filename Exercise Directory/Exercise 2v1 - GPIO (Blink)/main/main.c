// Exercise 2v1 - GPIO (Blink) - Read "README.md" in this folder first
// Follow the Exercise Instruction.md on how to compile and run the code

#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"

#define HAZARDS_LED_GPIO 42    // Hazards LED pin from the final project spec
#define BLINK_MS 500   // on 500 ms + off 500 ms = one blink per second
#define NUM_BLINKS 5

static int led_is_on = 0;  // LED state (0 off, 1 on)

// Return how many milliseconds since the ESP32 started
// Use it to check your timing
static long long now_ms(void)
{
    return esp_timer_get_time() / 1000;
}

// Task 2: turn the LED on (1) or off (0)
// 1. Set the pin level with gpio_set_level()
// 2. Save the new state in led_is_on
// 3. Print "<time> ms LED ON" or "<time> ms LED OFF" using now_ms()
void set_led(int on)
{
    // TODO (Task 2)
    // Hint: use %lld to print "long long int" in your print statement

}


void app_main(void)
{
    // Task 1: set up HAZARDS_LED_GPIO as an output.
    // Use gpio_reset_pin(), then gpio_set_direction() with GPIO_MODE_OUTPUT.
    printf("Task 1:\n");
    // TODO (Task 1)



    printf("Hazards LED ready on GPIO %d\n", HAZARDS_LED_GPIO);

    // Task 2: finish set_led(). Turn the LED on, wait 1 second, then turn it off.
    // Wait with vTaskDelay(pdMS_TO_TICKS(<milliseconds>)).
    // Expected: LED ON, then LED OFF about 1000 ms later
    printf("\nTask 2:\n");
    // TODO (Task 2)




    // Task 3: blink the LED NUM_BLINKS times: on for BLINK_MS, off for BLINK_MS.
    // Try toggling with set_led(!led_is_on).

    // Hint: Suppose I want to repeat something multiple times in C, what would I need?
    // Try not to just copy past task 2 ten times!

    // Expected: 10 lines (ON/OFF alternating), about 500 ms apart
    printf("\nTask 3:\n");
    // TODO (Task 3)



    printf("\nDone!\n");
}
