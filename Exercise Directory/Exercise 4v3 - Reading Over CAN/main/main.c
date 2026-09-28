// Exercise 4v3 - Reading Over CAN - Read "README.md" in this folder first

#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "CAN.h"

#define RPM_ID 0x030   // Motor RPM: 2 data bytes, high byte first
#define HEARTBEAT_ID 0x050   // Heartbeat: sent every 250 ms while the motor controller is on
#define HEARTBEAT_TIMEOUT_MS 600   // no heartbeat for this long = the motor controller is gone
#define RUN_MS 2500  // how long to listen


// Return how many milliseconds since the ESP32 started
static int now_ms(void)
{
    return esp_timer_get_time() / 1000;
}


// Task 1: print one message like this: ID 0x030 | DLC 2 | 05 DC
// Use %03lX for the ID (it's a uint32_t) and %02X for each data byte, %d for dlc.
void print_message(const CAN_message_t *msg)
{
    // TODO (Task 1)


    
}


void app_main(void)
{
    CAN_init();

    int start = now_ms();
    int last_heartbeat = now_ms(); // Task 3: when the last heartbeat arrived
    int heartbeat_lost = 0; // Task 3: 1 once you've reported it

    printf("Listening for %d ms...\n", RUN_MS);

    // This is the "receive loop". Real firmware has one just like it.
    while (now_ms() - start < RUN_MS) {
        CAN_message_t msg;

        // Wait up to 50 ms for a message
        if (CAN_receive(&msg, 50) == ESP_OK) {
            // Task 1: print every message with print_message(&msg)
            // TODO (Task 1)




            // Task 2: if the message is a Motor RPM message, rebuild the RPM from its 2 bytes
            // Check if id == RPM_ID
            // and print "  -> Motor RPM = <rpm>". Ignore every other ID.
            // Hint: this is 4v2's send_rpm() in reverse: (data[0] << 8) | data[1]
            // TODO (Task 2)




            // Task 3 (part 1): if the message is a heartbeat, save the time in last_heartbeat.
            // Check if id == HEARTBEAT_ID
            // TODO (Task 3)

        }

        // Task 3 (part 2): if no heartbeat has arrived for HEARTBEAT_TIMEOUT_MS,
        // print "<time> ms Heartbeat lost!" and set teh state heartbeat_lost to 1 (So you don't repeatly trigger it)
        // TODO (Task 3)


    }

    printf("\nDone!\n");
}
