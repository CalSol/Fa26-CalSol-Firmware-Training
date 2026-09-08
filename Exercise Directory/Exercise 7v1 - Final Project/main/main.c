#include "CAN.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "Final_Project";

void app_main(void)
{
    // Initialize the CAN hardware controller
    ESP_ERROR_CHECK(CAN_init());
    ESP_LOGI(TAG, "CAN initialized, starting RX loop...");

    while (1) {
        CAN_message_t rx_msg;

        // Listen to the bus for up to 2000 milliseconds
        esp_err_t ret = CAN_receive(&rx_msg, 2000);
    
        if (ret == ESP_OK) {
            ESP_LOGI(TAG, "RECEIVED: ID=0x%03x, DLC=%d", rx_msg.id, rx_msg.dlc);
        } else if (ret == ESP_ERR_TIMEOUT) {
            ESP_LOGW(TAG, "TIMEOUT: No message received in last 2 seconds.");
        }

        // A tiny delay to keep FreeRTOS happy and prevent the loop from hogging the CPU
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}