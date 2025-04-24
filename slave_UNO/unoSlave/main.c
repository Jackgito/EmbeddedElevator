#define F_CPU 16000000UL

#include "communications/communication_slave.h"
#include "buzzer_controller/buzzer_controller.h"
#include "led_controller/led_controller.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

int main(void) {
	TWI_init();
	buzzer_init();
	led_init();

	while (1) {
		// Wait for TWI message from master
		TWI_listen();
		char* message = TWI_get_data();

		// Handle door control
		if (strcmp(message, "open") == 0) {
			set_door_led(true);
			} else if (strcmp(message, "close") == 0) {
			set_door_led(false);
		}

		// Emergency handling
		else if (strcmp(message, "emergency") == 0) {
			blink_movement_led();  // Blink 3x
			set_door_led(true);
			play_melody();
			// Response to master is not yet implemented in TWI_send_data
		}

		// Fault handling
		else if (strcmp(message, "fault") == 0) {
			blink_movement_led();
		}

		// Elevator movement
		else if (strcmp(message, "moving") == 0) {
			set_movement_led(true);
			} else {
			set_movement_led(false);
		}

		_delay_ms(100);
	}

	return 0;
}
