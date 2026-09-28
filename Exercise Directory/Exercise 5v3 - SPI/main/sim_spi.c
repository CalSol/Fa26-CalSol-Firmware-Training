// Simulated SPI wires and DAC (you don't need to edit this file). See sim_spi.h.

#include <stdio.h>
#include <stdint.h>
#include "sim_spi.h"

#define MAX_FRAME   8
#define READ_CMD    0x80

static int cs = 1, sclk = 0, mosi = 0;
static int bit_index;                
static uint8_t rx_byte; 
static uint8_t tx_byte;              
static uint8_t frame[MAX_FRAME];      
static int frame_len;
static int dac_value = 0;            

static void print_voltage(int value)
{
    int mv = value * 3300 / 4095;
    printf("%d.%02d V", mv / 1000, (mv % 1000) / 10);
}

static void finish_frame(void)
{
    if (frame_len == 2 && (frame[0] & 0xF0) == 0x30) {
        dac_value = ((frame[0] & 0x0F) << 8) | frame[1];
        printf("[DAC] Output set to %d (", dac_value);
        print_voltage(dac_value);
        printf(")\n");
    } else if (frame_len >= 1 && frame[0] == READ_CMD) {
        printf("[DAC] Read request: sent back %d\n", dac_value);
    } else {
        printf("[DAC] Received %d byte(s):", frame_len);
        for (int i = 0; i < frame_len; i++) {
            printf(" 0x%02X", frame[i]);
        }
        printf("\n");
    }
}

static uint8_t next_tx_byte(int index)
{
    if (frame_len >= 1 && frame[0] == READ_CMD) {
        if (index == 1) return (dac_value >> 4) & 0xFF;    
        if (index == 2) return (dac_value & 0x0F) << 4;    
    }
    return 0x00;
}

void spi_cs(int level)
{
    if (cs == 1 && level == 0) {          
        frame_len = 0;
        bit_index = 0;
        rx_byte = 0;
        tx_byte = next_tx_byte(0);
    } else if (cs == 0 && level == 1) {   
        finish_frame();
    }
    cs = level;
}

void spi_mosi(int level)
{
    mosi = level ? 1 : 0;
}

void spi_sclk(int level)
{
    if (cs == 0 && sclk == 0 && level == 1) {          
        rx_byte = (rx_byte << 1) | mosi;
    } else if (cs == 0 && sclk == 1 && level == 0) {   
        bit_index++;
        if (bit_index == 8) {
            if (frame_len < MAX_FRAME) {
                frame[frame_len++] = rx_byte;
            }
            bit_index = 0;
            rx_byte = 0;
            tx_byte = next_tx_byte(frame_len);
        }
    }
    sclk = level;
}

int spi_miso(void)
{
    if (cs == 1) {
        return 0;
    }
    return (tx_byte >> (7 - bit_index)) & 1;
}
