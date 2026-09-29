// *Note: Here, 'Slave' is interchangeable with 'Peripheral' Forgive the wording...



// In this Exercise, we are now writing code for the Peripheral device that the Master controls


// --- INCLUDE HEADERS ---

// FREE RTOS
#include "freertos/FreeRTOS.h" 
#include "freertos/task.h"

// DEBUGGING
#include "esp_log.h" 
#include <stdio.h>

// DRIVERS
#include "driver/gpio.h"       
#include "driver/i2c_slave.h"  // Use the Slave (Peripheral) driver for peripheral devices












// --- DEFINITIONS ---
#define I2C_SLAVE_SCL_IO     GPIO_NUM_19 // SCL pin (different pins just for example)
#define I2C_SLAVE_SDA_IO     GPIO_NUM_18 // SDA pin
#define I2C_SLAVE_NUM        I2C_NUM_1   // Hardware I2C Port 1
#define I2C_SLAVE_TIMEOUT_MS 1000        // Block time for RTOS operations
#define MY_DEVICE_ADDR       0x69        // Our address on the bus (matches what the Master looks for)
#define BUFFER_SIZE          128         // Size of internal TX/RX queues
















static const char *TAG = "I2C_PERIPHERAL";






// --- 1. INITIALIZATION ---


// Defines a function that configures the physical I2C bus (for the peripheral) and registers a single peripheral device on that bus.
static void i2c_slave_init(i2c_slave_dev_handle_t *slave_handle) 
{


    // inside the function!

    // Configure the slave bus settings
    i2c_slave_config_t i2c_slv_config = {
        .i2c_port = I2C_SLAVE_NUM,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .scl_io_num = I2C_SLAVE_SCL_IO,
        .sda_io_num = I2C_SLAVE_SDA_IO,
        .slave_addr = MY_DEVICE_ADDR,      // The address we will respond to (like our name being called, and we respond)
        .send_buf_depth = BUFFER_SIZE,     // Size of the Transmit buffer (how big our container for data to transmit is)
        .receive_buf_depth = BUFFER_SIZE,  // Size of the Receive buffer (how big our container for data to receive is)
    };







    // Instantiate (Create and name) the I2C peripheral device (and its handle)
    ESP_ERROR_CHECK(i2c_new_slave_device(&i2c_slv_config, slave_handle));
}



    // Short initialization! this is because the Master decides all the settings (Clock frequency, etc.)









// --- 2. FREE RTOS TASK ---

// Create a Task... (A procedure we can call to specifically run its contents) 
// ...that loops the queuing of data for the master (to read upon request) and reading data from the master

void listen_to_master_task(void *arg)
{
    i2c_slave_dev_handle_t slave_handle = (i2c_slave_dev_handle_t)arg;

    uint8_t rx_data[BUFFER_SIZE] = {0}; // The container where we'll put data that we receive (in 'rx,' r is for recieve)
    uint8_t tx_data[2] = {0xAA, 0xBB}; // The data we WANT the master to read, that's why it's called tx (t for transmit)





    while (1) {
        // Queue data to Transmit
        // We are NOT forcing this onto the bus (because the peripheral has no control, only the master does). We are loading it into the send buffer.
        // It will sit here until the Master requests data from us.
        esp_err_t ret = i2c_slave_transmit(slave_handle, tx_data, sizeof(tx_data), pdMS_TO_TICKS(I2C_SLAVE_TIMEOUT_MS));
        if (ret == ESP_OK) {
            ESP_LOGI(TAG, "Data queued in TX buffer. Waiting for Master to read it...");
        }




        //  Wait to Receive data
        // This function blocks (waits) until the Master actually writes data to us, 
        // or until the timeout is reached.
        ret = i2c_slave_receive(slave_handle, rx_data, sizeof(rx_data), pdMS_TO_TICKS(I2C_SLAVE_TIMEOUT_MS));
        if (ret == ESP_OK) {
            ESP_LOGI(TAG, "Master wrote data to us! First byte: 0x%02X", rx_data[0]);
        } else if (ret == ESP_ERR_TIMEOUT) {
            ESP_LOGW(TAG, "No data received from Master within the timeout period.");
        }

        vTaskDelay(pdMS_TO_TICKS(10)); // Short delay to prevent task thrashing
    }
}

// Task has been created!










// Now to implement everything we've created (by running them in a loop):
// --- 3. MAIN ENTRY POINT ---
void app_main(void)
{

    // Create a container for the peripheral handle
    i2c_slave_dev_handle_t slave_handle = NULL;


    // Fill the handle using initialization
    ESP_LOGI(TAG, "Initializing I2C Peripheral (Slave)...");
    i2c_slave_init(&slave_handle);



    // Create the FreeRTOS task, passing in the configured peripheral handle
    xTaskCreate(listen_to_master_task, "i2c_slave_task", 4096, slave_handle, 5, NULL);
}

// This has completed the I2C Bus set up. We have...
// a Master that reads and writes data to/from a peripheral
// A Peripheral that will read and write data (UPON REQUEST) to the master
// The request part is why the Master is considered to manage all control