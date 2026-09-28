// Exercise 3v1 - Polling, Buffers, and Interrupts - Read "README.md" in this folder first

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "sim_button.h"

#define RUN_MS 3000  // how long to watch the button in each task
#define POLL_MS 50  // Task 1: read the button every 50 ms
#define BUFFER_SIZE 8

static volatile int press_count = 0;   // look up volatile in ESP-IDF!


// Your fifo(first in first out) parameters
static int buffer[BUFFER_SIZE];
static int buffer_head = 0; // next index to write
static int buffer_tail = 0; // next index to read
static int buffer_count = 0; // how many values are stored


// Return how many milliseconds since the ESP32 started
static int now_ms(void)
{
    return esp_timer_get_time() / 1000;
}


// Task 3: add value to the buffer.
// If the buffer is full (buffer_count == BUFFER_SIZE), do nothing.
// Otherwise store it at buffer_head, move buffer_head forward, and add 1 to buffer_count.
// Hint: use % so buffer_head wraps back to 0 after the last index.
void buffer_write(int value)
{
    // TODO (Task 3)
    


}


// Task 3: remove and return the oldest value in the buffer and progress buffer_tail.
// Only call this when buffer_count > 0 (buffer is not empty).
int buffer_read(void)
{
    // TODO (Task 3)

    return 0;   // replace this with the value you read

}


// Task 2: the interrupt handler. It runs by itself every time the button is pressed.
// Add 1 to press_count. Keep handlers short: no printf and no delays in here!
// Task 3: also save the press time with buffer_write(now_ms()).
void on_button_press(void)
{
    // TODO (Task 2 and Task 3)
    

}


void app_main(void)
{
    // Task 1: Polling
    // Every POLL_MS, read the button with sim_button_read() (1 = released, 0 = pressed).
    // A new press is when the last reading was 1 and this reading is 0.
    // Print "<time> ms Press detected" for each new press, and stop after RUN_MS.
    // Expected: 3 presses or 4 if you are super lucky, run it again if that's the case
    printf("Task 1:\n");
    sim_button_start();
    int polled_presses = 0;
    int last_reading = 1;  // Remember only when reading changes from 1 -> 0 counts as 1 press           
    int start = now_ms();
    while (now_ms() - start < RUN_MS) {
        // TODO (Task 1)
        


    }


    printf("Polling saw %d presses\n", polled_presses);

    // Task 2: Interrupts
    // Finish on_button_press(), then attach it with sim_button_attach_interrupt(on_button_press).
    // Wait RUN_MS with vTaskDelay() while the "interrupt" counts presses for you.
    // Expected: 4 presses (the interrupt catches the quick tap too)
    printf("\nTask 2:\n");
    sim_button_start();
    // TODO (Task 2)



    printf("Interrupt saw %d presses\n", press_count);

    // Task 3: Buffers
    // Finish buffer_write() and buffer_read(), and save the press time in on_button_press().
    // Then read every value out of the buffer and print "Press at <time> ms".
    // Hint: Very intuitive for this one, just read out all buffer as long as it is not empty
    // Expected: 4 lines, one for each press in Task 2
    printf("\nTask 3:\n");
    // TODO (Task 3)



    printf("\nDone!\n");
}
