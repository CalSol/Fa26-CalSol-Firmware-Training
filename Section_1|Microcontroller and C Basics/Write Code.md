# Create a Custom Message to control Lights

## Create the Project

Open/Create a new project using the set up instructions from Section 0.
Go to the main.c file (if it's named "main," rename and add the ".c")


```
#include "esp_timer.h"
#include "CAN.h"
#include _________   // <--- FILL
#include "freertos/task.h"    

static const char *TAG = ________;        // <--- FILL

#define TX_ID          ____               // <--- FILL
#define TX_INTERVAL_MS 500

void ________(void)                        // <--- FILL
{
    ESP_ERROR_CHECK(CAN_init());
    ESP_LOGI(TAG, "Starting CAN transmit test...");

    while (1) {
        int64_t now = esp_timer_get_time();

        uint8_t payload[8];
        payload[0] = (now >> 0)  & 0xFF;
        payload[1] = (now >> 8)  & 0xFF;
        payload[2] = (now >> 16) & 0xFF;
        payload[3] = (now >> 24) & 0xFF;
        payload[4] = (now >> 32) & 0xFF;
        payload[5] = (now >> 40) & 0xFF;
        payload[6] = (now >> 48) & 0xFF;
        payload[7] = (now >> 56) & 0xFF;

        CAN_message_t tx = build_packet_no_ext(TX_ID, payload, 8);

        esp_err_t err = CAN_send(&tx, 100);
        if (err == ESP_OK) {
            ESP_LOGI(TAG, "Sent ID: 0x%03X  Time: %lld us  Data: %02X %02X %02X %02X %02X %02X %02X %02X",
                TX_ID, now,
                payload[0], payload[1], payload[2], payload[3],
                payload[4], payload[5], payload[6], payload[7]
            );
        } else {
            ESP_LOGE(TAG, "Send failed: %s", esp_err_to_name(err));
        }

        vTaskDelay(pdMS_TO_TICKS(TX_INTERVAL_MS));
    }
}
```



## Build, Flash, and Monitor

use info from Section 0?
