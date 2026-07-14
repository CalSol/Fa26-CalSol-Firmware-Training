# Create a Custom Message to control Lights

## Write for the Grader ESP32

**General Idea**
You'll choose what to send <i>(CAN Packet)</i> from the grader ESP32, and also choose how the receiving board (the lights board) responds.

First, to turn the lights on, off, and give them certain brightness, have two distinct payloads (message content). Then fill in the blanks in the code below based on the given goal.
<br><br>
### Create the Project

Download the files of this training (on the left) and open them in your code editor (like VS Code) or (navigate to through a terminal?)

These files are set up using instructions from Section 0.

The "main" file is where you'll put the code below.

You'll build, flash, and monitor this file to the device you want to control (i.e. grader ESP32, lights board)

<br><br>

 



### Copy & Paste the below code into main.c file
Then fill in the blanks based on the following instructions:

<br><br>
<i>**Goal:**</i> Tell the lights board to turn on an LED with 50% brightness.

Payload: 0 for off, and any integer 1-255 for on with a certain brightness (0.4% to 100%).

**Requirements:**
- Define the Macro ON to equal the message payload (AKA the integer that represents brightness value, it doesn't have to be exactly 50%, just close).
- Send a CAN Packet with ID [Desired ID], and a payload to turn lights on half of full brightness.
- Use a TAG called "Control" for the grader ESP32.


**Hints:**
- 


**Code**
```
#include "esp_timer.h"
#include "CAN.h"
#include _________         // <--- FILL
#include "freertos/task.h"    

static const char *TAG = ________;       // <--- FILL

#define TX_ID  ____                    // <--- FILL
#define ON ____                       // <--- FILL
#define INTERVAL_MS 500


void ________(void)                // <--- FILL
{
    ESP_ERROR_CHECK(CAN_init());
    ESP_LOGI(TAG, "Initialized CAN. Preparing message...");

    while (1) {
        ;

        CAN_message_t lights_ON = build_packet_no_ext(____, ___, 1);          // <--- What are the macros for the ID and then the payload?

        esp_err_t ON_message_status = CAN_send(&______, 100);                  // <--- What's the CAN Packet called? (was created in the line above)
        if (err == ESP_OK) {
            ESP_LOGI(TAG, "__________");                                       // <--- Write anything you'd like to announce that the lights were turned on 50%.
        } else {
            ESP_LOGE(TAG, "Send failed: %s", esp_err_to_name(err));
        }

        vTaskDelay(pdMS_TO_TICKS(INTERVAL_MS));

    }
}
```

## Write for the Lights Board

```
#include "esp_log.h"
#include "esp_timer.h"
#include "_______"             
#include "freertos/task.h"

static const char *TAG = "________";

void _________(void)
{
    ESP_ERROR_CHECK(_________);
    ESP_LOGI(TAG, "Initialized CAN. Preparing to read incoming messages...");

while (1) {
        CAN_message_t incoming_message;
        if (_________(&incoming_message, portMAX_DELAY) == ESP_OK) {          // <-- What function extracts the received message?
            ESP_LOGI(TAG, "Received message. Desired brightness out of 255 is: %d", _______) <-- What variable stores this number?
            [Insert code to use integer from 0-255 for PWM pins on Light Board]

        } else {
            ESP_LOGI(TAG, "Did not receive message. Preparing to read incoming messages...");
        }
    }
}
```



<br><br>
## Test it out!
<br><br>
Go to Section 0 and follow the instructions to **Build, Flash, and Monitor.** Can be done from your terminal or using your code editor GUI for ESP-IDF. Through monitoring, you can see your ESP_LOGI announcement.

Once that works, try to turn the lights off!
