// Exercise 3v2 - Timers and Tickers - Read "README.md" in this folder first

#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"

#define HAZARDS_LED_GPIO  42 // Hazards LED pin from the final project spec
#define HEARTBEAT_MS      100 // the final project sends a CAN heartbeat every 100 ms
#define BLINK_MS          500

static int led_is_on = 0;
static int heartbeat_count = 0;


// Return how many milliseconds since the ESP32 started
static long long now_ms(void)
{
    return esp_timer_get_time() / 1000;
}


// Provided (you wrote this in 2v1.... Hopefully you did): turn the Hazards LED on or off and print it
static void set_led(int on)
{
    gpio_set_level(HAZARDS_LED_GPIO, on);
    led_is_on = on;
    // The fancy {condition} ? {true result} : {false result} is just an inline if/else statement (ternary)
    // if {condition} is true, return {true result}, else {false result} 
    printf("%lld ms LED %s\n", now_ms(), on ? "ON" : "OFF");
}


// Note: none of these functions need to use the parameters, the void *args is just
// required format for all "callback" functions

// Task 1: runs once when the one-shot timer goes off.
// Simply make it print "<time> ms Alarm!"
static void on_alarm(void *arg)
{
    // TODO (Task 1)
    

}


// Task 2: Call back function for Task 2, runs every HEARTBEAT_MS.
// Add 1 to heartbeat_count and print "<time> ms Heartbeat <count>"
static void on_heartbeat(void *arg)
{
    // TODO (Task 2)


}


// Task 3: Call back function for task 3. Toggle the LED with set_led().
// Hint: use set_led() with !led_is_on to toggle the led each time
static void on_blink(void *arg)
{
    // TODO (Task 3)


}


void app_main(void)
{
    gpio_reset_pin(HAZARDS_LED_GPIO);
    gpio_set_direction(HAZARDS_LED_GPIO, GPIO_MODE_OUTPUT);

    // Task 1: One-shot timer
    // This creates a timer that will call on_alarm(). Copy this pattern for Tasks 2 and 3.
    esp_timer_handle_t alarm_timer;
    esp_timer_create_args_t alarm_args = { .callback = on_alarm, .name = "alarm" };
    esp_timer_create(&alarm_args, &alarm_timer);

    // Start it once with esp_timer_start_once(alarm_timer, <microseconds>) to go off after 1 second.
    // Careful: esp_timer counts in MICROseconds (1 ms = 1000 us).
    // Then wait 1500 ms with vTaskDelay() so the alarm has time to go off.
    // Expected: "Alarm!" printed about 1000 ms after "Timer started"
    printf("Task 1:\n");
    printf("%lld ms Timer started\n", now_ms());
    // TODO (Task 1)




    // Task 2: Periodic timer (a "ticker")
    // Create a timer that calls on_heartbeat(), start it with esp_timer_start_periodic()
    // every HEARTBEAT_MS, wait 1000 ms, then stop it with esp_timer_stop().
    // Expected: 9 or 10 heartbeats, about 100 ms apart
    printf("\nTask 2:\n");
    // TODO (Task 2)
    // Reuse how timer are set up in Task 1
    // but use on_heartbeat() as your call back function this time!




    // Task 3: Blink with a ticker
    // Create a timer that calls on_blink() every BLINK_MS and start it.
    // The main loop below is already written: it keeps counting while your timer blinks the LED.
    // After the loop, stop the timer.
    // Expected: LED ON/OFF lines about 500 ms apart, mixed in with "Main loop" lines
    printf("\nTask 3:\n");
    // TODO (Task 3): create and start the blink timer, use on_blink as your call back this time!
    // Hint: This should be very similar to task 2




    // Don't change this
    for (int i = 1; i <= 5; i++) {
        printf("%lld ms Main loop %d\n", now_ms(), i);
        vTaskDelay(pdMS_TO_TICKS(600));
    }

    // TODO (Task 3): stop the blink timer



    printf("\nDone!\n");
}
