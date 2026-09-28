// Simulated CAN bus for Exercise 4v2 (you don't need to edit this file). See CAN.h.
//
// A pretend "dashboard" board is listening on the bus. It prints every message you send,
// and understands two IDs:
// 0x030  Motor RPM 2 bytes: [RPM high byte] [RPM low byte]
// 0x031  Status counter 1 byte: [count]

#include <stdio.h>
#include <string.h>
#include "CAN.h"

#define RPM_ID     0x030
#define STATUS_ID  0x031

static bool started = false;

esp_err_t CAN_init(void)
{
    if (started) return ESP_ERR_INVALID_STATE;
    started = true;
    return ESP_OK;
}

esp_err_t CAN_send(const CAN_message_t *frame, uint32_t timeout_ms)
{
    if (!started) {
        printf("[CAN] Error: call CAN_init() before CAN_send()\n");
        return ESP_ERR_INVALID_STATE;
    }

    printf("[CAN bus] ID 0x%03lX | DLC %d |", (unsigned long)frame->id, frame->dlc);
    for (int i = 0; i < frame->dlc && i < 8; i++) {
        printf(" %02X", frame->data[i]);
    }
    printf("\n");

    if (frame->id == RPM_ID) {
        if (frame->dlc != 2) {
            printf("[Dashboard] Motor RPM should have 2 data bytes, got %d\n", frame->dlc);
        } else {
            printf("[Dashboard] Motor RPM = %d\n", (frame->data[0] << 8) | frame->data[1]);
        }
    } else if (frame->id == STATUS_ID) {
        if (frame->dlc != 1) {
            printf("[Dashboard] Status should have 1 data byte, got %d\n", frame->dlc);
        } else {
            printf("[Dashboard] Status count = %d\n", frame->data[0]);
        }
    }
    return ESP_OK;
}

esp_err_t CAN_receive(CAN_message_t *frame, uint32_t timeout_ms)
{
    return ESP_ERR_TIMEOUT;   // nobody sends to you in this exercise
}

CAN_message_t build_packet_no_ext(uint32_t id, const uint8_t *data, uint8_t dlc)
{
    CAN_message_t msg = {0};
    msg.id = id;
    if (dlc == 0) dlc = 8;   
    if (dlc > 8)  dlc = 8;
    msg.dlc = dlc;
    if (data != NULL) {
        memcpy(msg.data, data, msg.dlc);
    }
    return msg;
}
