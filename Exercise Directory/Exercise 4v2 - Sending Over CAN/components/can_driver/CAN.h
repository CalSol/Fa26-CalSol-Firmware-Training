/* ========================= CAN.h =========================
    JonathanSHJ, Jan 23 2026

    *Please Read*
    This project is meant to establish all functions needed for the CANBUS 2.0 assuming 
    that the HW is ESP32-S3 with TCAN322 transciever or any micro controller (with
    TWAI controller interface) and ISO 11898-2 compaitable transciever. 
*/

/* 
    *Enviorment Debugging*
    go to the "esp/esp-idf" directory and run ". ./export.sh"
    then go to project directory and run "idf.py fullclean" then "idf.py build"
    If that doesn't work make sure the CMakeLists.txt contains all needed directories/files.
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "esp_err.h"
#include "esp_twai_types.h"
#include "esp_twai.h"
#include "esp_twai_onchip.h"

#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/portmacro.h"

/* ESP -> TCAN322 connection on ESP32 Dev */
#define CAN_TX GPIO_NUM_17 //17
#define CAN_RX GPIO_NUM_18 //18

typedef struct {
    uint32_t id;
    uint8_t  dlc;
    uint8_t  data[8];
    bool     extended;
    bool     rtr;
} CAN_message_t;

/**
 * @brief initalizes the TWAI controller within S3 SoC
 * Deafults to 1M bit rate
 */
esp_err_t CAN_init(void);

/**
 * @brief deactivates the TWAI controller within S3 SoC
 */
esp_err_t CAN_deinit(void);

/**
 * @brief sends a CAN message onto the BUS
 */
esp_err_t CAN_send(const CAN_message_t *frame, uint32_t timeout_ms);

/**
 * @brief receives a CAN message from the BUS
 */
esp_err_t CAN_receive(CAN_message_t *frame, uint32_t timeout_ms);


/**
 * @brief Pass in id, data to build a packet with dlc deafult to 8
 */
CAN_message_t build_packet_no_ext(uint32_t id, const uint8_t *data, uint8_t dlc);

twai_node_handle_t CAN_get_node_handle(void);

