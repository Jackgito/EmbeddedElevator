#define F_CPU 16000000UL
#include "isr_controller.h"
#include "../elevator_controller/elevator_controller.h"
#include "../keypad_controller/keypad.h"
#include "../uart_debug/uart_debug.h"

#define EMERGENCY_BUTTON_PIN PE4

/*
 * ISR (Interrupt Service Routine) controller improves responsiveness by handling events immediately,
 * allowing the code to temporarily pause its current execution and jump to a specific task when an interrupt occurs.
 * This eliminates delays and ensures faster system response.
 */

void isr_init(void) {
	sei(); // Enable global interrupts
}

void enable_external_interrupt(uint8_t pin) {
	if (pin == EMERGENCY_BUTTON_PIN) {
		EICRB |= (1 << ISC41);  // Falling edge trigger for INT4
		EIMSK |= (1 << INT4);   // Enable INT4
	}
}

// ISR for Emergency Stop Button
ISR(INT4_vect) {
	emergency_stop();
}
