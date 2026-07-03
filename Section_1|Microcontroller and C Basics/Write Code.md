# Create a Custom Message to control Lights

## General Idea

You'll choose what to send <i>(CAN Packet)</i> through the grader esp, and also choose how the receiving board (the lights board) responds.

<br><br>
To turn the lights on, off, and give them certain brightness, have three distinct messages (CAN packets). Then write code so the lights board will recognize the purpose and respond accordingly. 

### Create the Project

Open/Create a new project using the set up instructions from Section 0.
Go to the main.c file (if it's named "main," rename and add the ".c")

<br><br>



### Fill the blanks in the below code for the grader esp

<br><br>
Goal: Tell the lights board to blink its lights with 1 second intervals.

**Requirements:**
- Send a CAN Packet with ID [Desired ID], payload [Message content]
- Use a TAG called [specific name] for the grader, and [other name] for the lights board to announce to the monitor
- Define Macros ON and OFF for their message payloads, which equal 1 and 0 respectively.

**Hints:**
- A Blink interval of 1 second separates the ON and OFF messages.


**Code**
```
#include "esp_timer.h"
#include "CAN.h"
#include _________   // <--- FILL
#include "freertos/task.h"    

static const char *TAG = ________;        // <--- FILL

#define TX_ID          ____               // <--- FILL
#define BLINK_INTERVAL_MS 1000
#define ______ 1
#define _____ 0

void ________(void)                        // <--- FILL
{
    ESP_ERROR_CHECK(CAN_init());
    ESP_LOGI(TAG, "Starting CAN transmit test...");

    while (1) {
        ;

        CAN_message_t lights_ON = build_packet_no_ext(TX_ID, ___, 1);        // <--- What's the payload?

        CAN_message_t lights_OFF = build_packet_no_ext(TX_ID, ___, 1);       // <--- What's the payload?

        esp_err_t ON_message_status = CAN_send(&______, 100);                 // <--- What's the CAN Packet called?
        if (err == ESP_OK) {
            ESP_LOGI(TAG, "Lights turned ON.");
        } else {
            ESP_LOGE(TAG, "Send failed: %s", esp_err_to_name(err));
        }

        vTaskDelay(pdMS_TO_TICKS(BLINK_INTERVAL_MS));

        esp_err_t OFF_message_status = CAN_send(&______, 100);
        if (OFF_message_status == ESP_OK) {
            ESP_LOGI(TAG, "Lights turned OFF.");
        } else {
            ESP_LOGE(TAG, "Send failed: %s", esp_err_to_name(err));
        }

        vTaskDelay(pdMS_TO_TICKS(BLINK_INTERVAL_MS));

    }
}
```



## Build, Flash, and Monitor

use info from Section 0?
