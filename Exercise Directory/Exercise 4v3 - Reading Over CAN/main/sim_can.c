// Simulated CAN bus for Exercise 4v3 (you don't need to edit this file). See CAN.h.


#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "esp_timer.h"
#include "CAN.h"

typedef struct {
    int at_ms;
    uint32_t id;
    uint8_t dlc;
    uint8_t data[8];
} scheduled_msg_t;

static const scheduled_msg_t schedule[] = {
    { 250, 0x050, 1, {0x00}},
    { 400, 0x030, 2, {0x05, 0xDC}},         // 1500 RPM
    { 500, 0x050, 1, {0x00}},
    { 650, 0x7FF, 3, {0x01, 0x02, 0x03}},
    { 750, 0x050, 1, {0x00}},
    { 900, 0x030, 2, {0x0C, 0x80}},         // 3200 RPM
    {1000, 0x050, 1, {0x00}},
    {1250, 0x050, 1, {0x00}},
    {1400, 0x030, 2, {0x11, 0x94}},         // 4500 RPM
    {1500, 0x050, 1, {0x00}},               // last heartbeat
};
#define NUM_SCHEDULED (sizeof(schedule) / sizeof(schedule[0]))

static QueueHandle_t rx_queue = NULL;
static esp_timer_handle_t bus_timer;
static int64_t start_us;
static int next_msg = 0;

static void bus_tick(void *arg)
{
    int elapsed_ms = (esp_timer_get_time() - start_us) / 1000;
    while (next_msg < NUM_SCHEDULED && schedule[next_msg].at_ms <= elapsed_ms) {
        CAN_message_t msg = build_packet_no_ext(schedule[next_msg].id,
                                                schedule[next_msg].data,
                                                schedule[next_msg].dlc);
        xQueueSend(rx_queue, &msg, 0);
        next_msg++;
    }
    if (next_msg >= NUM_SCHEDULED) {
        esp_timer_stop(bus_timer);
    }
}

esp_err_t CAN_init(void)
{
    if (rx_queue != NULL) return ESP_ERR_INVALID_STATE;
    rx_queue = xQueueCreate(16, sizeof(CAN_message_t));

    esp_timer_create_args_t args = { .callback = bus_tick, .name = "sim_can" };
    esp_timer_create(&args, &bus_timer);
    start_us = esp_timer_get_time();
    esp_timer_start_periodic(bus_timer, 10 * 1000);
    return ESP_OK;
}

esp_err_t CAN_send(const CAN_message_t *frame, uint32_t timeout_ms)
{
    if (rx_queue == NULL) return ESP_ERR_INVALID_STATE;
    return ESP_OK;   // nobody is listening in this exercise
}

esp_err_t CAN_receive(CAN_message_t *frame, uint32_t timeout_ms)
{
    if (rx_queue == NULL) {
        printf("[CAN] Error: call CAN_init() before CAN_receive()\n");
        vTaskDelay(pdMS_TO_TICKS(timeout_ms));
        return ESP_ERR_INVALID_STATE;
    }
    if (frame == NULL) return ESP_ERR_INVALID_ARG;
    return (xQueueReceive(rx_queue, frame, pdMS_TO_TICKS(timeout_ms)) == pdTRUE) ? ESP_OK
                                                                                 : ESP_ERR_TIMEOUT;
}

CAN_message_t build_packet_no_ext(uint32_t id, const uint8_t *data, uint8_t dlc)
{
    CAN_message_t msg = {0};
    msg.id = id;
    if (dlc == 0) dlc = 8;   // same as the real driver: 0 means 8
    if (dlc > 8)  dlc = 8;
    msg.dlc = dlc;
    if (data != NULL) {
        memcpy(msg.data, data, msg.dlc);
    }
    return msg;
}
