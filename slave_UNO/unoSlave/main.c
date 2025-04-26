#define F_CPU 16000000UL

#include "communications/communication_slave.h"
#include "buzzer_controller/buzzer_controller.h"
#include "led_controller/led_controller.h"
#include "uart_debug/uart_debug.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

int main(void) {
	uart_init(103); // UART for debugging
	TWI_init();
	buzzer_init();
	led_init();

	while (1) {
		// Wait for TWI message from master
		TWI_listen();
		char* message = TWI_get_data();
		//print(message);

		// Handle door control
		if (strcmp(message, "open_door") == 0) {
			set_movement_led(false);
			set_door_led(true);
		
		} else if (strcmp(message, "close_door") == 0) {
			set_movement_led(false);
			set_door_led(false);
		}

		// Emergency handling
		else if (strcmp(message, "emergency") == 0) {
			play_emergency_melody(); // Activates buzzer and blinks movement LED 3 times
		}

		// Fault handling
		else if (strcmp(message, "fault") == 0) {
			blink_movement_led();
		}

		// Elevator movement
		else if (strcmp(message, "moving") == 0) {
			set_movement_led(true);
			set_door_led(false);
		}
		_delay_ms(100);
	}
	return 0;
}
