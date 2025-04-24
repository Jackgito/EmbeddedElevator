#define F_CPU 16000000UL
#include "buzzer_controller.h"
#include <avr/io.h>
#include <util/delay.h>

#define BUZZER_PIN PB3  // Digital pin 11
#define BUZZER_NOTE_DURATION 500

void buzzer_init(void) {
	DDRB |= (1 << BUZZER_PIN);  // Set buzzer pin as output
}

void play_tone(uint16_t frequency) {
	if (frequency == 0) return;

	// Calculate OCR1A for Phase and Frequency Correct PWM (Mode 9)
	uint16_t top = (F_CPU / (2UL * frequency));
	OCR1A = top;

	// Set Waveform Generation Mode 9 (PWM, Phase and Frequency Correct)
	TCCR1A = (1 << COM1A0) | (1 << WGM10);  // Toggle OC1A on compare match
	TCCR1B = (1 << WGM13) | (1 << CS10);    // No prescaler, Phase/Frequency Correct PWM mode

	// Play tone for the specified duration
	_delay_ms(100);

	// Stop the tone after the duration
	stop_tone();
}

void stop_tone(void) {
	// Disable the timer to stop the buzzer tone
	TCCR1A = 0;
	TCCR1B = 0;

	// Ensure buzzer is turned off
	PORTB &= ~(1 << BUZZER_PIN);
}

void play_melody(void) {
	uint16_t melody[] = {262, 294, 330, 349};  // C4, D4, E4, F4
	uint16_t duration[] = {300, 300, 300, 300};

	for (int i = 0; i < 4; i++) {
		play_tone(melody[i]);
		_delay_ms(100);  // Short pause between notes
	}
}
