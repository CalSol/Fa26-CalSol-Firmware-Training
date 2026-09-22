// --- INCLUDE HEADERS ---

// FREE RTOS
#include "freertos/FreeRTOS.h" // FreeRTOS.h to use FreeRTOS features
#include "freertos/task.h" // task.h enables you to create and manage tasks in FreeRTOS

// DEBUGGING
#include "esp_log.h" // esp_log.h provides logging functions
#include <stdio.h> // stdio.h lets me print into the console

// DRIVERS
#include "CAN.h" // CAN.h is custom header file for CAN driver functions and structures
#include "driver/gpio.h" // GPIO driver for ESP32 allows you to control the GPIO pins on the ESP32
#include "driver/i2c_master.h" // I2C driver for ESP32, allows you to communicate with I2C devices


// *TAG used for logging purposes, helps identify the source of log messages in the console
static const char *TAG = "Final_Project";

// --- DEFINITIONS ---
#define I2C_MASTER_SCL_IO       GPIO_NUM_14 // SCL pin from ESP32 schematic
#define I2C_MASTER_SDA_IO       GPIO_NUM_13 // SDA pin from ESP32 schematic
#define I2C_MASTER_NUM          I2C_NUM_0 // I2C port number, ESP32 has two I2C ports, 0 and 1
#define I2C_MASTER_FREQ_HZ      100000 // 100 kHz I2C clock frequency, standard speed for I2C communication
#define I2C_MASTER_TIMEOUT_MS   1000 // Timeout for I2C operations in milliseconds (will throw error if nothing received in time frame)
#define LTC4151_SENSOR_ADDR     0x69 // Chip address (ADR1 & ADR0 tied high) for LTC4151 power monitor sensor

// ---I2C Helper Functions ---

// Reads bytes from I2C device at specific register address
static esp_err_t ltc4151_register_read(i2c_master_dev_handle_t dev_handle, uint8_t reg_addr, uint8_t *data, size_t len) 
{
    return i2c_master_transmit_receive(dev_handle, &reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS); // Transmit the register address and receive the data from the device, with a timeout of 1000 milliseconds
}

// Initializes the I2C bus and adds the LTC4151 device to it
static void i2c_master_init(i2c_master_bus_handle_t *bus_handle, i2c_master_dev_handle_t *dev_handle) 
{
    i2c_master_bus_config_t bus_config = { // configs i2c bus with the parameters defined in the header file
        .i2c_port = I2C_MASTER_NUM, // I2C port number, ESP32 has two I2C ports, 0 and 1
        .sda_io_num = I2C_MASTER_SDA_IO, // SDA pin from ESP32 schematic
        .scl_io_num = I2C_MASTER_SCL_IO, // SCL pin from ESP32 schematic
        .clk_source = I2C_CLK_SRC_DEFAULT, // default clock source for I2C bus
        .glitch_ignore_cnt = 7, // filters out glitches on the line that are shorter than 7 clock cycles
        .flags.enable_internal_pullup = false, // disabled due to external pullups on the board
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, bus_handle)); // initializes i2c bus

    i2c_device_config_t dev_config = { // configs i2c device with the parameters defined in the header file
        .dev_addr_length = I2C_ADDR_BIT_LEN_7, // 7-bit address length for the LTC4151 sensor
        .device_address = LTC4151_SENSOR_ADDR, // I2C address of the LTC4151 sensor
        .scl_speed_hz = I2C_MASTER_FREQ_HZ, // I2C clock speed for communication with the sensor
    };
    ESP_ERROR_CHECK(i2c_master_bus_add_device(*bus_handle, &dev_config, dev_handle)); // adds the LTC4151 device to the I2C bus and initializes it
}

// --- TASKS ---
void strobe_led_task(void *arg)
{
    // Configure GPIO pin for output
    gpio_num_t led_pin = (gpio_num_t)arg; // Cast the argument to gpio_num_t type
    gpio_reset_pin(led_pin); // Reset the GPIO pin to its default state
    gpio_set_direction(led_pin, GPIO_MODE_OUTPUT); // Set the GPIO pin as an output pin

    while (1) {
        // Toggle the GPIO pin state
        gpio_set_level(led_pin, 1); // Set GPIO pin high (on)
        ESP_LOGI(TAG, "LED ON"); // Log message indicating LED is on, uses Mutex so thread-safe
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 milliseconds
        gpio_set_level(led_pin, 0); // Set GPIO pin low (off)
        ESP_LOGI(TAG, "LED OFF"); // Log message indicating LED is off
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 milliseconds
    }
}

void power_monitor_task(void *arg)
{
    i2c_master_dev_handle_t ltc_handle = (i2c_master_dev_handle_t)arg;
    
    // Buffer to hold High Byte and Low Byte (from Vin)
    uint8_t data[2];

    while (1) {
        // Read 2 bytes starting from register 0x02 (VIN High Byte)
        esp_err_t ret = ltc4151_register_read(ltc_handle, 0x02, data, 2);

        if (ret == ESP_OK) {
            // The LTC4151 uses a 12-bit ADC. 
            // data[0] holds the top 8 bits. data[1] holds the bottom 4 bits in its upper half.
            uint16_t raw_adc = (data[0] << 4) | (data[1] >> 4);

            // The datasheet states that 1 LSB = 25mV (0.025V)
            float voltage = raw_adc * 0.025;

            ESP_LOGI(TAG, "Sensor Read SUCCESS! Voltage: %.2f V", voltage);

        } else {
            ESP_LOGE(TAG, "Failed to read sensor. Error: %s", esp_err_to_name(ret));
        }

        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }
}

// app_main is entry point, and basically starts all the tasks and initializes drivers 
void app_main(void)
{
    i2c_master_bus_handle_t bus_handle;
    i2c_master_dev_handle_t ltc_handle;

    i2c_master_init(&bus_handle, &ltc_handle);
    ESP_LOGI(TAG, "I2C initialized, starting tasks...");

    xTaskCreatePinnedToCore(
        strobe_led_task,        // Function that implements the task
        "strobe_led",           // Text name for debugging
        4096,                   // Stack size in bytes
        (void *)GPIO_NUM_42,    // Parameter passed into task, can use structs if more than one parameter is needed
        1,                      // Task priority (0 is lowest, configMAX_PRIORITIES-1 is highest, base is 0->24)
        NULL,                   // No task handle needed, can define a TaskHandle_t <name> = NULL; and use &<name> here if needed
        1                       // Hardcoded Core ID (1 = Core 1, 0 = Core 0, tskNO_AFFINITY = no preference)
    );

    xTaskCreatePinnedToCore(
        power_monitor_task,
        "power_monitor",
        4096,
        (void *)ltc_handle,
        2, // should be 0?
        NULL,               
        0
    );

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }

    // // Initialize the CAN hardware controller
    // ESP_ERROR_CHECK(CAN_init());
    // ESP_LOGI(TAG, "CAN initialized, starting RX loop...");

    // while (1) {
    //     CAN_message_t rx_msg;

    //     // Listen to the bus for up to 2000 milliseconds
    //     esp_err_t ret = CAN_receive(&rx_msg, 2000);
    
    //     if (ret == ESP_OK) {
    //         ESP_LOGI(TAG, "RECEIVED: ID=0x%03x, DLC=%d", rx_msg.id, rx_msg.dlc);
    //     } else if (ret == ESP_ERR_TIMEOUT) {
    //         ESP_LOGW(TAG, "TIMEOUT: No message received in last 2 seconds.");
    //     }

    //     // A tiny delay to keep FreeRTOS happy and prevent the loop from hogging the CPU
    //     vTaskDelay(pdMS_TO_TICKS(10));  
}