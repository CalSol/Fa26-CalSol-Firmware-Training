#include "CAN.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "CAN_Sender";

void app_main(void)
{
    // Initialize the CAN hardware controller
    ESP_ERROR_CHECK(CAN_init());
    ESP_LOGI(TAG, "CAN initialized, starting TX loop...");

    uint8_t payload[8] = {0xAA, 0xBB, 0xCC, 0xDD, 0x11, 0x22, 0x33, 0x44};

    while (1) {
        // Package the ID and payload
        CAN_message_t tx_msg = build_packet_no_ext(0x123, payload, 0);

        // Send the message with a 100ms timeout
        esp_err_t ret = CAN_send(&tx_msg, 100);

        if (ret == ESP_OK) {
            ESP_LOGI(TAG, "SUCCESS: TX send id=0x123");
        } else {
            ESP_LOGE(TAG, "FAILED: TX error: %s", esp_err_to_name(ret));
        }

        // Pause for 1 second before sending the next message
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}