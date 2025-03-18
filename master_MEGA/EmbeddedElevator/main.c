// main.c
#include <avr/io.h>
#include <util/delay.h>
#include "elevator_controller.h"
#include "keypad_controller.h"
#include "lcd_controller.h"
#include "led_controller.h"

#define MAX_FLOOR 99  // Assuming the maximum floor is 99

int main(void) {
	uint8_t target_floor = 0;  // Variable to store the floor selected with the numpad

	// Initialize the elevator system
	elevator_init();

	while (1) {
		// Wait for user input from the keypad
		target_floor = KEYPAD_GetKey();

		// Check if the input is within valid range (0 - 99)
		if (target_floor <= MAX_FLOOR) {
			// Move the elevator to the selected floor
			move_elevator(target_floor);
			} else {
			// If the input is out of range, display an error message
			lcd_clrscr();
			lcd_puts("Invalid floor");
			_delay_ms(1000);  // Wait for a while to let the user read the error
			lcd_clrscr();
			lcd_puts("Choose the floor");
		}
	}
}
