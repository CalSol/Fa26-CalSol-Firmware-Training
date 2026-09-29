// Exercise 5v3 - SPI - Read "README.md" in this folder first

#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sim_spi.h"

#define DAC_READ_CMD  0x80


// Task 1: send one byte on MOSI and receive one byte from MISO at the same time.
// Remeber sent 8 bits from bit 7 (MSB) down to bit 0. For each bit, in this order:
// 1. Put the bit on MOSI:spi_mosi((out >> bit) & 1)
// 2. Rising edge: spi_sclk(1)
// 3. Read MISO and add it to the end of `in`: in = (in << 1) | spi_miso()
// 4. Falling edge: spi_sclk(0)
// Don't touch CS in here: the caller does that.
uint8_t spi_transfer_byte(uint8_t out)
{
    uint8_t in = 0;
    // TODO (Task 1)

    

    return in;
}


// Task 2: set the DAC output (0 -> 4095, where 4095 = 3.3 V).
// Send 2 bytes between spi_cs(0) and spi_cs(1):
// Hint: value >> 8 gives the top bits, value & 0xFF gives the bottom 8, and | combines bits.
void dac_set(int value)
{
    // TODO (Task 2) - Fill in byte1 and byte2, this is to practice your bits manipulation
    uint8_t byte1 = 0x00;  // settings bits + top 4 bits of value
    uint8_t byte2 = 0x00;  // bottom 8 bits of value

    spi_cs(0);
    spi_transfer_byte(byte1);
    spi_transfer_byte(byte2);
    spi_cs(1);
}


// Task 3: read back the DAC's current output.
// Between spi_cs(0) and spi_cs(1), send 3 bytes: DAC_READ_CMD, then 0x00, then 0x00.
// While you send the two 0x00 bytes, the DAC answers:
// first reply: top 8 bits of the value (D11 ... D4)
// second reply: bottom 4 bits, in the top half (D3 D2 D1 D0 0 0 0 0)
// So put them back together by (first << 4) | (second >> 4)
int dac_read(void)
{
    // TODO (Task 3)



    return 0;
}


void app_main(void)
{
    // Task 1: finish spi_transfer_byte(). This sends 0xA5 to the DAC.
    // Expected: [DAC] Received 1 byte(s): 0xA5
    printf("Task 1:\n");
    spi_cs(0);
    spi_transfer_byte(0xA5);
    spi_cs(1);

    // Task 2: finish dac_set(), then step the output up: 0, 1024, 2048, 3072, 4095.
    // Think of it as an LED getting brighter. Wait 200 ms between steps.
    // Expected: [DAC] Output set to 2048 (1.65 V) and so on
    printf("\nTask 2:\n");
    // TODO (Task 2)

    const int steps[] = {0, 1024, 2048, 3072, 4095};


    // Task 3: finish dac_read(), set the DAC to 2500, then read it back and print it.
    // Expected: Read back: 2500
    printf("\nTask 3:\n");
    // TODO (Task 3)



    printf("\nDone!\n");
}
