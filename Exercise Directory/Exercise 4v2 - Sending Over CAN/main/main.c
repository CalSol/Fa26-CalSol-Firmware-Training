// Exercise 4v2 - Sending Over CAN - Read "README.md" in this folder first

#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "CAN.h"

#define RPM_ID     0x030   
#define STATUS_ID  0x031  


// Task 2: send the motor RPM (0 -> 65535) on RPM_ID.
// RPM doesn't fit in 1 byte, so split it into 2 bytes(This is your dlc), high byte first:
// data[0] = the top 8 bits (rpm >> 8)
// data[1] = the bottom 8 bits (rpm & 0xFF)
// Then build the message with build_packet_no_ext() and send it with CAN_send()
// set the timeout to 100 ms.
void send_rpm(int rpm)
{
    // TODO (Task 2)

    
}


void app_main(void)
{
    // Task 1: Send your first CAN message
    // Start CAN with CAN_init().
    // Make a data array of uint8_t with 2 bytes: 0xAA, 0xBB
    // Build the message: CAN_message_t msg = build_packet_no_ext(0x123, data, 2);
    // Send it with a 100 ms timeout: CAN_send(&msg, 100);
    printf("Task 1:\n");
    // TODO (Task 1)



    // Task 2: finish send_rpm(), then send 3000 RPM.
    printf("\nTask 2:\n");
    // TODO (Task 2)




    // Task 3: Send a status message every 250 ms, 4 times, on STATUS_ID.
    // The data is 1 byte: the count (1, 2, 3, 4).
    // Hint: If you decided to make a loop for this one, use uint8_t for your loop counter
    // As you can reuse it build_packet_no_ext which takes in uint_8
    printf("\nTask 3:\n");
    // TODO (Task 3)



    printf("\nDone!\n");
}
