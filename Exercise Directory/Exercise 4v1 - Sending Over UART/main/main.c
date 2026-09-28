// Exercise 4v1 - Sending Over UART - Read "README.md" in this folder first

#include <stdio.h>
#include <string.h>
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define SERIAL_UART UART_NUM_0 // the UART connected to your computer (the serial monitor)
#define BAUD_RATE 115200
#define TX_BUFFER 1024 

// Pretend these are data/status from the Pedals ESP32 (in the final project this comes over CAN)
#define NUM_READINGS  5
const int pedal_positions[NUM_READINGS] = {0, 64, 128, 200, 255};  // 0 -> 255
const int power_x10[NUM_READINGS] = {120, 118, 115, 97, 121}; // volts * 10
const int hazards_on[NUM_READINGS] = {0, 0, 1, 1, 0};  // 1 = on


// Task 2: send text over the UART.
// Use uart_write_bytes(SERIAL_UART, text, <number of bytes>). strlen(text) gives the number of bytes.
void uart_send(const char *text)
{
    // TODO (Task 2)


    
}


void app_main(void)
{
    // Task 1: Set up the UART
    // Fill in uart_config: BAUD_RATE baud, 8 data bits, no parity, 1 stop bit, no flow control.
    // Look for the names in the README table (for example UART_DATA_8_BITS).
    uart_config_t uart_config = {
        // TODO (Task 1)

        .source_clk = UART_SCLK_DEFAULT,
    };
    // Then install the driver and apply the settings, feel free to just uncomment this:
    //   uart_driver_install(SERIAL_UART, 256, TX_BUFFER, 0, NULL, 0);
    //   uart_param_config(SERIAL_UART, &uart_config);
    // TODO (Task 1)

    printf("Task 1:\n");
    printf("UART ready at %d baud\n", BAUD_RATE);
    vTaskDelay(pdMS_TO_TICKS(100));

    // Task 2: finish uart_send(), then send "Hello from the Brakelights ESP32!\r\n".
    // Expected: Hello from the Brakelights ESP32!
    printf("\nTask 2:\n");
    vTaskDelay(pdMS_TO_TICKS(100));
    // TODO (Task 2)



    vTaskDelay(pdMS_TO_TICKS(100));

    // Task 3: Send a status line every 500 ms, like the final project's serial debugging.
    // For each reading i, build a line with snprintf() into line[], then send it with uart_send().
    // Power is stored as volts * 10 (to avoid decimals), so 118 means 11.8 V.
    // Hint: 118 / 10 = 11 and 118 % 10 = 8
    // Expected: Pedal: 64 | Power: 11.8 V | Hazards: OFF
    printf("\nTask 3:\n");
    vTaskDelay(pdMS_TO_TICKS(100));
    char line[64];
    for (int i = 0; i < NUM_READINGS; i++) {
        // TODO (Task 3)
        


        vTaskDelay(pdMS_TO_TICKS(500));
    }

    printf("\nDone!\n");
}
