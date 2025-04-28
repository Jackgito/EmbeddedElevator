#define F_CPU 16000000UL
#define EMERGENCY_BUTTON_PIN PE4

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "isr_controller/isr_controller.h"
#include "elevator_controller/elevator_controller.h"
#include "keypad_controller/keypad.h"
#include "lcd_controller_MEGA/lcd.h"
#include "uart_debug/uart_debug.h"
#include "communication/communication_master.h"

#define MAX_FLOOR 99

void setup() {
	lcd_init(LCD_DISP_ON);// initialize the LCD
	KEYPAD_Init(); //initialize the keypad
	
	// Set pin as input and enable internal pull-up to make ISR emergency system work
	DDRE &= ~(1 << 4);    // Set PE4 as input
	PORTE |= (1 << 4);    // Enable pull-up resistor on PE4
}

// Main function handles inputs and interrups. Elevator logic is in the controller file
int main(void) {
	setup();
	uart_init(103); // UART for debug
	lcd_clrscr();
	KEYPAD_Init();
	TWI_init();
	
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

		} else if (key == '#') { // # Is used on the keypad to select the floor and start moving elevator towards it
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
			lcd_clrscr();
			lcd_puts("Invalid floor!");
			print("No such floor exists. Floor selection has been reset.");
			buffer_index = 0;
			input_buffer[0] = '\0';
			_delay_ms(1500);
			lcd_clrscr();
			lcd_puts("Choose floor: ");
		}
	}
}

