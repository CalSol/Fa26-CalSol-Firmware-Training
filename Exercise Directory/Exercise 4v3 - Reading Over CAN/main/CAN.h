// Simulated CAN driver (you don't need to edit this file)

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

typedef struct {
    uint32_t id; // who the message is from / what it is about
    uint8_t  dlc; // how many data bytes (0 -> 8)
    uint8_t  data[8]; // the payload
    bool     extended; // false for normal (11-bit) IDs
    bool     rtr; // false for normal data messages
} CAN_message_t;

// Start the CAN controller. Call this once before sending or receiving.
esp_err_t CAN_init(void);

// Send a message. Returns ESP_OK if it was sent.
esp_err_t CAN_send(const CAN_message_t *frame, uint32_t timeout_ms);

// Wait up to timeout_ms for a message. Returns ESP_OK if one arrived, ESP_ERR_TIMEOUT if not.
esp_err_t CAN_receive(CAN_message_t *frame, uint32_t timeout_ms);

// Build a message with a normal ID from an array of dlc data bytes.
CAN_message_t build_packet_no_ext(uint32_t id, const uint8_t *data, uint8_t dlc);
