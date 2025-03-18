#include "isr_controller.h"
#include "led_controller.h"
#include "elevator_controller.h"

volatile uint8_t blink_count = 0;
volatile uint8_t max_blinks = 0;

// ISR (Interrupt Service Routine) controller improves responsiveness by handling events immediately, allowing the code to temporarily pause its current execution and jump to a specific task when an interrupt occurs. This eliminates delays and ensures faster system response.

void isr_init(void) {
	sei(); // Enable global interrupts
}

// Enable Timer Interrupt (for LED blinking)
void enable_timer_interrupt(uint16_t interval_ms) {
	TCCR1B |= (1 << WGM12) | (1 << CS12); // CTC Mode, Prescaler = 256
	TIMSK1 |= (1 << OCIE1A); // Enable Timer1 Compare Match Interrupt
	OCR1A = (F_CPU / 256 / 1000) * interval_ms; // Convert ms to Timer1 ticks
}

// Disable Timer Interrupt
void disable_timer_interrupt(void) {
	TIMSK1 &= ~(1 << OCIE1A);
}

// Timer ISR for LED Blinking
ISR(TIMER1_COMPA_vect) {
	if (blink_count < max_blinks) {
		toggle_led(); // Call LED function from ledController
		blink_count++;
		} else {
		disable_timer_interrupt();
	}
}

// Enable External Interrupt (for Keypad or Emergency Button)
void enable_external_interrupt(uint8_t pin) {
	if (pin == PD2) {
		EICRA |= (1 << ISC01); // Falling edge on INT0
		EIMSK |= (1 << INT0);  // Enable INT0
		} else if (pin == PD3) {
		EICRA |= (1 << ISC11); // Falling edge on INT1
		EIMSK |= (1 << INT1);  // Enable INT1
	}
}

// ISR for External Interrupt (e.g., Keypad press)
ISR(INT0_vect) {
	uint8_t floor = KEYPAD_GetKey();
	move_elevator(floor);
}

// ISR for Emergency Stop Button
ISR(INT1_vect) {
	emergency_stop();
}
