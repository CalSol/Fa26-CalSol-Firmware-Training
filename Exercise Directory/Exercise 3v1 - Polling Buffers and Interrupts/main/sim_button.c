// Simulated startup button (you don't need to edit this file). See sim_button.h.

#include <stddef.h>
#include "esp_timer.h"
#include "sim_button.h"

typedef struct {
    int start_ms;
    int length_us;
} press_t;

// Feel free to change this to test out your code more!
static const press_t presses[] = {
    {300, 100000},
    {900, 150000},
    {1623, 300},     // a very quick 0.3 ms tap: polling almost always misses it
    {2200, 100000},
};
#define NUM_PRESSES (sizeof(presses) / sizeof(presses[0]))

static int64_t start_us;
static void (*user_handler)(void);
static esp_timer_handle_t press_timers[NUM_PRESSES];

void sim_button_start(void)
{
    start_us = esp_timer_get_time();
}

int sim_button_read(void)
{
    int64_t elapsed_us = esp_timer_get_time() - start_us;
    for (int i = 0; i < NUM_PRESSES; i++) {
        int64_t press_start_us = (int64_t)presses[i].start_ms * 1000;
        if (elapsed_us >= press_start_us &&
            elapsed_us < press_start_us + presses[i].length_us) {
            return 0; // pressed
        }
    }
    return 1; // released
}

static void on_press_timer(void *arg)
{
    if (user_handler != NULL) {
        user_handler();
    }
}

void sim_button_attach_interrupt(void (*handler)(void))
{
    user_handler = handler;
    int64_t now_us = esp_timer_get_time();

    for (int i = 0; i < NUM_PRESSES; i++) {
        if (press_timers[i] == NULL) {
            esp_timer_create_args_t args = { .callback = on_press_timer, .name = "sim_button" };
            esp_timer_create(&args, &press_timers[i]);
        }
        esp_timer_stop(press_timers[i]);

        int64_t press_at_us = start_us + (int64_t)presses[i].start_ms * 1000;
        if (press_at_us > now_us) {
            esp_timer_start_once(press_timers[i], press_at_us - now_us);
        }
    }
}
