#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../led_controller/led_controller.h"

// Notes (frequencies in Hz)
const uint16_t melody_notes[] = {
200, 500, 600, 300, 420, 200, 600, 300, 50, 200, 500, 600, 300, 420, 200, 600
};

#define BUZZER_PIN PB3

const uint8_t note_count = sizeof(melody_notes) / sizeof(melody_notes[0]);

void buzzer_init(void) {
	// Set PB3 (Pin 11, OC2A) as output
	DDRB |= (1 << BUZZER_PIN);

	// Reset Timer2
	TCCR2A = 0;
	TCCR2B = 0;
	TCNT2 = 0;

	// Toggle OC2A on Compare Match
	TCCR2A |= (1 << COM2A0);

	// CTC mode
	TCCR2A |= (1 << WGM21);

	// Prescaler will be set later
}

void set_buzzer_frequency(uint16_t frequency) {
	if (frequency == 0) {
		// Stop Timer2
		TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
		return;
	}

	// Use prescaler 64
	TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
	TCCR2B |= (1 << CS22); // prescaler = 64

	// Calculate OCR2A value
	uint16_t ocr = (F_CPU / (2UL * 64UL * frequency)) - 1;

	if (ocr > 255) ocr = 255; // Limit to 8-bit max
	OCR2A = (uint8_t)ocr;
}

// Activates buzzer and blinks movement LED 3 times
// This is done in same function so the actions can be done simultaneously
void play_emergency_melody(void) {
	for (uint8_t i = 0; i < note_count; i++) {
		set_buzzer_frequency(melody_notes[i]);

		// Every fourth note (i % 4 == 0) is longer (200ms), others are shorter (100ms)
		if (i % 4 == 0) {
			set_movement_led(true);
			_delay_ms(200);
			} else if  (i == note_count - 1) {
			_delay_ms(500);
		} else {
			set_movement_led(false);
			_delay_ms(100);
		}

		set_buzzer_frequency(0);  // Turn off the buzzer

		// Small pause between notes
		_delay_ms(50);
	}
	set_movement_led(false);
}





void play_chime(void) {
	set_buzzer_frequency(1568);

	for (uint16_t i = 0; i < 5500; i++) {
		_delay_ms(1);
	}

	set_buzzer_frequency(1245);

	for (uint16_t i = 0; i < 12000; i++) {
		_delay_ms(1);
	}

	set_buzzer_frequency(0);
}
