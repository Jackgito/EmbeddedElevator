#include "buzzer_controller.h"

// Initialize the buzzer pin
void buzzer_init(void) {
	// Set buzzer pin as output (assuming PD2, adjust if needed)
	DDRD |= (1 << BUZZER_PIN);
	// Initially turn off the buzzer
	PORTD &= ~(1 << BUZZER_PIN);
}

// Function to play a melody with 4 notes
void play_melody(void) {
	// Define the melody notes (frequencies) and duration
	// You can adjust the frequency and timing according to your needs
	uint16_t melody[] = {262, 294, 330, 349}; // C, D, E, F notes in Hz
	uint16_t duration[] = {500, 500, 500, 500}; // Duration in milliseconds

	// Loop through the melody and play each note
	for (int i = 0; i < 4; i++) {
		// Generate the tone for the current note
		uint16_t frequency = melody[i];
		uint16_t delay_time = duration[i];

		// Turn on the buzzer
		PORTD |= (1 << BUZZER_PIN);

		// Create a tone with the specified frequency
		uint16_t half_period = 1000000 / (2 * frequency); // Half-period in microseconds
		for (int j = 0; j < delay_time * 1000 / (2 * half_period); j++) {
			// Toggle the buzzer to produce a square wave
			PORTD ^= (1 << BUZZER_PIN); // Toggle buzzer
			_delay_us(half_period);      // Wait for half-period
		}

		// Turn off the buzzer after the note
		PORTD &= ~(1 << BUZZER_PIN);
		_delay_ms(50); // Short delay between notes
	}
}
