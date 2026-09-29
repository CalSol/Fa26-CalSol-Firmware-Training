
// In this file, we are writing code for the Master Device in the I2C Bus.


// --- INCLUDE HEADERS ---

// FREE RTOS
#include "freertos/FreeRTOS.h" // FreeRTOS.h to use FreeRTOS features
#include "freertos/task.h" // task.h enables you to create and manage tasks in FreeRTOS

// DEBUGGING
#include "esp_log.h" // esp_log.h provides logging functions
#include <stdio.h> // stdio.h lets me print into the console

// DRIVERS
#include "driver/gpio.h" // GPIO driver for ESP32 allows you to control the GPIO pins on the ESP32
#include "driver/i2c_master.h" // I2C driver for ESP32, allows you to communicate with I2C devices (as the master device)













// --- DEFINITIONS ---
#define I2C_MASTER_SCL_IO       GPIO_NUM_14 // SCL pin from ESP32 schematic
#define I2C_MASTER_SDA_IO       GPIO_NUM_13 // SDA pin from ESP32 schematic
#define I2C_MASTER_NUM          I2C_NUM_0 // I2C port number, ESP32 has two I2C ports, 0 and 1
#define I2C_MASTER_FREQ_HZ      100000 // 100 kHz I2C clock frequency, standard speed for I2C communication
#define I2C_MASTER_TIMEOUT_MS   1000 // Timeout for I2C operations in milliseconds (will throw error if nothing received in time frame)
#define PERIPHERAL_DEVICE_ADDR     0x69 // Chip address for Peripheral device (this represents the location of the device, referenceable by the master)








static const char *TAG = "I2C_MASTER";





// --- 1. INITIALIZATION ---


// Defines a function that configures the physical I2C bus and registers a single peripheral device on that bus.
static void i2c_master_init(i2c_master_bus_handle_t *bus_handle, i2c_master_dev_handle_t *dev_handle) 
{

    // inside the function!

    // Configure the overall I2C bus hardware settings 
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_MASTER_NUM,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = false, // Set to true if external pull-up resistors are missing
    };




    // Instantiate (Create and name) the I2C master bus (and its handle)
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, bus_handle));


    // Configure the communication settings for the specific peripheral device
    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7, //  The length of the peripheral's address/location 'value.' Length = 7 bits.
        .device_address = PERIPHERAL_DEV_ADDR, // The acutal value of the address/location of your peripheral device on the bus.
        .scl_speed_hz = I2C_MASTER_FREQ_HZ, //The clock speed, set to the value of one of the 'DEFINITIONS' above!
    };

    // Attach the (peripheral) device handle to the bus
    ESP_ERROR_CHECK(i2c_master_bus_add_device(*bus_handle, &dev_config, dev_handle));
}



// --- 2. BASIC I2C OPERATIONS ---

// The following static functions are custom-created (you can do this too!) with names
// to represent their purpose, and the actual contents inside are functions from the i2c_master.h header file.



// SEND (Write): Transmits data bytes out to the peripheral
static esp_err_t peripheral_write(i2c_master_dev_handle_t dev_handle, const uint8_t *data, size_t len) 
{
    return i2c_master_transmit(dev_handle, data, len, I2C_MASTER_TIMEOUT_MS);
}

// RECEIVE (Read): Requests and receives data bytes directly from the peripheral
static esp_err_t peripheral_read(i2c_master_dev_handle_t dev_handle, uint8_t *data, size_t len) 
{
    return i2c_master_receive(dev_handle, data, len, I2C_MASTER_TIMEOUT_MS);
}

// READ REGISTER (Write + Read): Sends target register address first, then reads returned bytes
static esp_err_t peripheral_register_read(i2c_master_dev_handle_t dev_handle, uint8_t reg_addr, uint8_t *data, size_t len) 
{
    return i2c_master_transmit_receive(dev_handle, &reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS);
}




// This is the end of our initialization.
// RECAP: We Initialied our I2C Bus, Master Device, and Peripheral Device that the master controls
// RECAP: We defined the following functions:
// i2c_master_init(), peripheral_write(), peripheral_read(), peripheral_register_read().
// We will later call these functions to actually do what we wrote inside of them.



// Now to the main action below:



// --- 3. FREE RTOS TASK ---
// Create a Task... (A procedure we can call to specifically run its contents) 
// ...that loops the transmitting and receiving of messages
void speak_to_peripheral_task(void *arg)
{
    i2c_master_dev_handle_t dev_handle = (i2c_master_dev_handle_t)arg;

    // Buffers for transmission and reception.
    // Creating containers that will 'send out' what we fill it with (transmission)...
    // ...OR 'catch' any received data (reception)
    uint8_t tx_data[2] = {0x00, 0xFF}; // Sample message payload (message content) to send
    uint8_t rx_data[2] = {0};           // Buffer for received data (This will be filled with data received from transmission)



    // Never ending loop of what is inside (below).
    while (1) {
        // A Simple Transmission (Send message)


        // esp_err_t goes behind any variable/function that returns the value 'ESP_OK' if its procedure went well, or an error value if not.
        // Look for it in the code written up until this point, see the pattern

        esp_err_t ret = peripheral_write(dev_handle, tx_data, sizeof(tx_data));

        // Notice how ret's value (either ESP_OK or not) tells us if peripheral_write() was succesful or not.
        if (ret == ESP_OK) {
            ESP_LOGI(TAG, "Successfully sent data to peripheral.");
        } else {
            ESP_LOGE(TAG, "Failed to send data: %s", esp_err_to_name(ret));
        }

        // A Simple Reception (Receive message/response after receive)
        ret = peripheral_read(dev_handle, rx_data, sizeof(rx_data));
        if (ret == ESP_OK) {
            ESP_LOGI(TAG, "Successfully received data: 0x%02X 0x%02X", rx_data[0], rx_data[1]);
        } else {
            ESP_LOGE(TAG, "Failed to receive data: %s", esp_err_to_name(ret));
        }

    
        vTaskDelay(pdMS_TO_TICKS(1000)); // Run transaction every 1 second
    }


    // Basically, this task called 'speak_to_peripheral_task' will do the above that we just wrote...
    // ...Wherever and whenever we call it.
}








// All the code up until now was to define the tools (functions, values) that we will now use in the app_main loop.
// This is where things actually happen.

// --- 4. MAIN ENTRY POINT ---
void app_main(void)
{


    // Create variables that will contian our bus and dev(ice) handles
    i2c_master_bus_handle_t bus_handle = NULL;
    i2c_master_dev_handle_t dev_handle = NULL;


    // Initialization will fill those handles by running i2c_master_init
    ESP_LOGI(TAG, "Initializing I2C Master Bus...");
    i2c_master_init(&bus_handle, &dev_handle);



    // Create the FreeRTOS task, passing in the configured device handle
    xTaskCreate(speak_to_peripheral_task, "i2c_task", 3072, dev_handle, 5, NULL);
}

// Done!