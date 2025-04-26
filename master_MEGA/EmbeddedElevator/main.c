#define F_CPU 16000000UL
#define EMERGENCY_BUTTON_PIN PE4

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "isr_controller/isr_controller.h"
#include "elevator_controller/elevator_controller.h"
#include "keypad_controller/keypad.h"
#include "lcd_controller_MEGA/lcd.h"
#include "uart_debug/uart_debug.h"
#include "communication/communication_master.h"

#define MAX_FLOOR 99  // Assuming the maximum floor is 99

/*
uint8_t isEmergencyButtonPressed(void) {
	uint8_t pressed = !(PINE & (1 << EMERGENCY_BUTTON_PIN));
	if (pressed == 1) {
		print("Pressed");	
	} else {
		print("Not pressed");	
	}
	return pressed;
}
*/

// Main function handles inputs and interrups. Elevator logic is in the controller file
int main(void) {
	uart_init(103); // UART for debug
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	KEYPAD_Init();
	TWI_init();
	_delay_ms(100); // Add a small delay to ensure the screen clears
	lcd_puts("Hello world");
	
	elevator_reset_ui();  // Initial UI prompt

	char input_buffer[3] = {0};  // Store up to 2 digits + null terminator
	uint8_t buffer_index = 0;
	
	
	// Set pin as input and enable internal pull-up to make ISR emergency system work
	DDRE &= ~(1 << EMERGENCY_BUTTON_PIN);    // Set PE4 as input

	isr_init();
	enable_external_interrupt(EMERGENCY_BUTTON_PIN);

	while (1) {
		uint8_t key = KEYPAD_GetKey();

		if (key >= '0' && key <= '9' && buffer_index < 2) {
			input_buffer[buffer_index++] = key;
			input_buffer[buffer_index] = '\0';
			lcd_gotoxy(0, 1);
			lcd_puts(input_buffer);
			print(input_buffer);

		} else if (key == '#') {
			if (buffer_index > 0) {
				uint8_t target_floor = atoi(input_buffer);

				if (target_floor <= MAX_FLOOR) {
					move_elevator(target_floor);
					} else {
					lcd_clrscr();
					lcd_puts("Invalid floor");
					print("Invalid floor");
					_delay_ms(1000);
					elevator_reset_ui();
				}
			}

			// Reset input
			buffer_index = 0;
			input_buffer[0] = '\0';

		} else if (key == '*') { 			// Clear input
			buffer_index = 0;
			input_buffer[0] = '\0';
			lcd_gotoxy(0, 1);
			lcd_puts("              ");  // Clear line
			lcd_gotoxy(0, 1);
		} else { // Reset input
			print("No such floor exists. Floor selection has been reset.");
			buffer_index = 0;
			input_buffer[0] = '\0';
		}
	}
}

