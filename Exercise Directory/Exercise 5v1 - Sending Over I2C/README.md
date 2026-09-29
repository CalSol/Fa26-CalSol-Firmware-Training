# ESP32 I2C Master-Peripheral Communication Guide

An educational guide and code reference for implementing basic I2C master communication with peripheral devices using ESP-IDF v5.2+ (`driver/i2c_master.h`).

---

## 📖 Overview

This repository demonstrates how to set up an ESP32 as an I2C master device, attach a peripheral device handle, and perform transmit (write), receive (read), and register read operations within a FreeRTOS task environment.

---

## ❓ Conceptual Self-Assessment & Quiz

Use these questions to check your understanding of the code structure, driver behavior, and return types before implementing I2C in your own projects.

### Question 1: Driver API & Responsibilities
Which `driver/i2c_master.h` functions perform each specific stage of the I2C setup and data transfer flow?
* **A.** Allocating and initializing the physical I2C controller bus hardware.
* **B.** Registering a target peripheral device's address and clock speed onto the bus.
* **C.** Transmitting data out to the peripheral device.
* **D.** Requesting and receiving raw data back from the peripheral device.
* **E.** Writing a register address first, then immediately reading data back without releasing the bus (combined Write-Read).

<details>
<summary><b>Click to reveal Answer</b></summary>

* **A.** `i2c_new_master_bus()`
* **B.** `i2c_master_bus_add_device()`
* **C.** `i2c_master_transmit()`
* **D.** `i2c_master_receive()`
* **E.** `i2c_master_transmit_receive()`
</details>

---

### Question 2: Error Handling & `esp_err_t`
In the task loop, operations return a type of `esp_err_t` saved into variable `ret`.
1. What does returning `ESP_OK` represent contextually?
2. What role does `ESP_ERROR_CHECK()` play during initialization versus checking `ret == ESP_OK` in the task loop?

<details>
<summary><b>Click to reveal Answer</b></summary>

1. **`ESP_OK`** is the standard ESP-IDF success status code (`0`). It indicates that the I2C transaction completed successfully without timeouts or NACK errors.
2. **`ESP_ERROR_CHECK()`** triggers a hardware reset/panic if initialization fails, which is ideal during boot-up setup. Checking **`ret == ESP_OK`** inside the loop allows the application to gracefully log an error and keep running if a peripheral briefly disconnects or misses an ACK.
</details>

---

### Question 3: Handles and Pointers
Why do we initialize `i2c_master_bus_handle_t` and `i2c_master_dev_handle_t` as `NULL` pointers in `app_main()` and pass them as address pointers (`&bus_handle`, `&dev_handle`) into `i2c_master_init()`?

<details>
<summary><b>Click to reveal Answer</b></summary>

In C, handles are opaque pointers that reference internal driver structures. Passing their memory addresses (`&bus_handle`) allows the initialization functions (`i2c_new_master_bus` and `i2c_master_bus_add_device`) to modify the original handles in `app_main()` and populate them with active hardware references.
</details>

---

### Question 4: FreeRTOS Task Context
Why is the device handle `dev_handle` passed as the parameter argument (`(void *)arg`) into `xTaskCreate()`, and why is `vTaskDelay()` required inside the `while(1)` loop?

<details>
<summary><b>Click to reveal Answer</b></summary>

* `dev_handle` is passed so the task knows which target peripheral instance to communicate with when calling driver functions.
* `vTaskDelay()` yields CPU control back to the FreeRTOS scheduler, preventing the task from starving the Watchdog Timer (WDT) and other system tasks.
</details>

---

### Question 5: Configuration Settings
What are the roles of `.glitch_ignore_cnt` and `.flags.enable_internal_pullup` in `i2c_master_bus_config_t`?

<details>
<summary><b>Click to reveal Answer</b></summary>

* **`.glitch_ignore_cnt`**: Configures hardware filtering to ignore noise pulses or glitches on the SDA/SCL lines shorter than a specified number of clock cycles (7 in this code).
* **`.flags.enable_internal_pullup`**: Toggles internal pull-up resistors on SDA/SCL lines. It is set to `false` when strong external pull-up resistors (e.g., 2.2 kΩ - 10 kΩ) are present on the hardware board.
</details>

---

## 🛠️ Hardware Setup

| Signal | ESP32 Pin | Description |
| :--- | :--- | :--- |
| **SCL** | GPIO 14 | Serial Clock Line |
| **SDA** | GPIO 13 | Serial Data Line |
| **GND** | GND | Common Ground |
| **VCC** | 3.3V | Power Supply |

---
