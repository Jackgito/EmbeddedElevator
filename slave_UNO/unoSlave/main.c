#include "communication.h"
#include "buzzer_controller.h"
#include <avr/io.h>
#include <util/delay.h>

// Define the emergency button pin
#define EMERGENCY_BUTTON_PIN PD2

uint8_t isEmergencyButtonPressed(void) {
	return !(PIND & (1 << EMERGENCY_BUTTON_PIN));
}

int main(void) {
	// Initialize communication (SPI slave)
	initSPI_Slave();
	
	// Initialize the buzzer
	buzzer_init();
	
	// Main loop
	while (1) {
		// Check if emergency button is pressed
		if (isEmergencyButtonPressed()) {
			// Send emergency message over SPI
			sendSPI_Data("Start emergency");
			
			// Activate the buzzer (play melody)
			play_melody();
			
			// Optional: Add debounce delay after button press
			_delay_ms(500);
		}

	}

	return 0;
}
