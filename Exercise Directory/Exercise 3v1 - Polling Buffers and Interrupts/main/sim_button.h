// Simulated startup button (you don't need to edit this file)
//
// QEMU can't press a real button, so this pretends to be the final project's
// startup button on GPIO 8. (You will eventually test it in real hardware in your checkoff) 
// Like the real one, it is active low:
//   1 = released, 0 = pressed
//
// Every time you call sim_button_start(), the same presses happen again,
// measured from that moment:
//   300 ms (100 ms long), 900 ms (150 ms long), 1623 ms (a very quick 0.3 ms tap), 2200 ms (100 ms long)

#pragma once

// Restart the press schedule from time 0.
void sim_button_start(void);

// Read the button right now. Same idea as gpio_get_level(STARTUP_BUTTON_GPIO).
int sim_button_read(void);

// Call handler() at the moment each press starts. Same idea as gpio_isr_handler_add().
void sim_button_attach_interrupt(void (*handler)(void));
