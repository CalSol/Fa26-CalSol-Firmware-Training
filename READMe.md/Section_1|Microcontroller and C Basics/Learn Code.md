# Writing Code to Send and Receive Messages

## Summary

Through the contents of the project you build and flash, you can tell the ESP32 how and what to communicate over CAN, or listen for from others.
Specifically, you'll write code in a "main.c" file of your project to this.

**Basic description of Project file path structure & components folder?**

---

## Code to Send 
Here's a break down of each important chunk of code (language is C!), in order:

### Libraries
```
#include "esp_log.h"
#include "esp_timer.h"
#include "CAN.h"             
#include "freertos/task.h"
```
Allows us access to 'libraries' which contain functions, data types (and more) needed to write the rest of the code below. Explanations of how they work are in their API.

> Try it out! Ctrl+F in the following API references to search for descriptions of functions used in this code 
- [esp_log.h](https://my-esp-idf.readthedocs.io/en/stable/api-reference/system/log.html?__cf_chl_f_tk=ehK.DaQDboBsr7lyW1GqqgfX2ZOfX9Nyw5j.zoHBKzI-1782777579-1.0.1.1-e.O8t49iLQx_2nJFvmRg9GEf1oG3TqYHT0jCLhIn3Nc) 
- [esp_err_t (contained in esp.log.h)](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/esp_err.html)

### Macros & Set Up

```
static const char *TAG = "CAN_TX";

#define TX_ID          0x123
#define TX_INTERVAL_MS 500
```

<i>TAG</i>, <i>TX_ID</i>, and <i>TX_INTERVAL_MS</i> are macros. When the code runs, they will be replaced by their assigned values, ("CAN_TX," 0x123, and 500) respectively. 
>Why? Easier to access these values by a name that represents what they mean (meaning explained later). 

### Initialize CAN

```
void app_main(void)
{
    ESP_ERROR_CHECK(CAN_init());
    ESP_LOGI(TAG, "Initialized CAN. Preparing message...");
```

<i>Void</i> is the return type of the <i>app_main()</i> function, which runs all code inside of it once. (Void = returns nothing when done running). Every variable/function defined must have a return/data type declared before it.
<details>
<summary><i>Why?</i></summary>
That way, C knows... 
- how to prepare memory for it 
- what type of data to expect from it 
Examples in this code: int64_t, esp_err_t, CAN_message_t, etc.
</details>

<br><br>
<i>ESP_ERROR_CHECK(CAN_init())</i> accomplishes two things:
- CAN_init() initializes CAN. Necessary before any CAN actions.
- ESP_ERROR_CHECK() takes the value returned by CAN_init() (its output) and, based on that, decides if initialization worked or if something went wrong.
<br><br>
<i>ESP_LOGI(TAG...)</i> announces: "CAN_TX: Initialized CAN. Preparing message..."

### The Message

```
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
```

The first line means: while(this condition is true), loop what's inside the brackets {}. (1 is a true value).

What is <i>**now**?</i>
- A variable of the 64 bit integer (int64_t) data type. (A number that takes up 64 bits of memory)
- Container for the value of esp_timer_get_time() (which is a timestamp!)

What is <i>**payload**?</i>
- An array with 8 elements. uint8_t means 8 bits are allocated to each element.
- Container for all 64 bits in "now." Stored byte-by-byte through masking.

>(Extra:) What is <i>masking?</i>

<details> 
<summary><i>Explanation</i></summary>
>Not a concept used in this lab, but very important to know for packing data!
>
>**8 bits are eight 1s or 0s, (i.e. 11111111, 11011001, 00000000, etc.) These form numbers in binary! 1 byte = 8 bits.**
<br><br>
>**(now >> 8) shifts all bytes in "now" to the right by 1 byte. For example, (00001111 00000000) becomes --> (00000000 00001111)**
<br><br>
>**"&" masks these shifted bytes with 0xFF (a hexidecimal number that equals 11111111 in binary).**
<br><br>
>**Imagine each byte in "now" sits directly under the corresponding 0xFF bytes (in 64 bits).** 
<br><br>
>### <i>During Masking</i>

```
... 00000000 00000000 11111111 <-- This is OxFF
... xxxxxxxx xxxxxxxx XXXXXXXX <-- This is "now"
```


>**The output of masking these with each other is that any bits sitting under a 1 are kept, while any under a 0 are discarded.**
<br><br>
>### <i>Output</i>
```
... 00000000 00000000 XXXXXXXX <-- This is the result
```

>**As payload stores XXXXXXXX to one element, it then shifts "now" by another byte (8 bits) to store its next byte (xxxxxxxx).**
</details>
<br><br>


### Send & Confirmation

``` 
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

<i>tx</i> is a variable that stores freshly formatted packet (AKA, the message to send). 

The <i>**packet**</i> has...
- a CAN ID (TX_ID)
- The contents (payload)
- Data length Limit (8 bytes)

**CAN_send() sends the packet out of this device's TX pin**, and returns ESP_OK if successful.
- Specificaly, this packet is given a turn to be read by the receving device in a queue (known as the buffer)

The <i>**if/else**</i> control statements...
- Announce "CAN_TX: Sent ID: [TX_ID here], Time: [now here], Data [each of payload's stored bytes]"
- Announce "CAN_TX: Send failed [insert error name]"

## Code to Receive
```
#include "esp_log.h"
#include "esp_timer.h"
#include "CAN.h"             
#include "freertos/task.h"

static const char *TAG = "CAN_RX";

void app_main(void)
{
    ESP_ERROR_CHECK(CAN_init());
    ESP_LOGI(TAG, "Initialized CAN. Preparing to read incoming messages...");

while (1) {
        CAN_message_t incoming_message;
        if (CAN_recieve(&incoming_message, portMAX_DELAY) == ESP_OK) {
            ESP_LOGI(TAG, "Received message: Byte 1 = %d, Byte 2 = %d, Byte 3 = %d, Byte 4 = %d",
                    incoming_message.payload[0],                     // <--- or .data?
                    incoming_message.payload[1],
                    incoming_message.payload[2],
                    incoming_message.payload[3]);
        } else {
            ESP_LOGI(TAG, "Did not receive message. Preparing to read incoming messages...");
        }
    }
}
```
*Remember that this device's RX pin connects to the TX pin of the one it receives code from (through a transceiver of course)..

**Inside while loop**
- The variable <i>incoming_message</i> is created to later store the next received message. (its data type is <i>CAN_message_t</i>).
- CAN_receive() fills sent_info with the contents of the first message in the buffer (successful send and receive!).
- ESP_LOGI() announces the success and also the exact message received (each byte. There are 4 more, but only half written in ESP_LOGI() for simplicity).,
    - Each %d is replaced by a corresponding element in the payload array (where each element contains 1 byte)
 
<br><br>

After that, the message content can be used for anything.

## Your Turn
Remember key components, because now you will write code to send out a different CAN packet to control lights on the receiving board (next section!).












