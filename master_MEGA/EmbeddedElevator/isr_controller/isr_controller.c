#define F_CPU 16000000UL
#include "isr_controller.h"
#include "../elevator_controller/elevator_controller.h"
#include "../keypad_controller/keypad.h"
#include "../uart_debug/uart_debug.h"

/*
 * ISR (Interrupt Service Routine) controller improves responsiveness by handling events immediately,
 * allowing the code to temporarily pause its current execution and jump to a specific task when an interrupt occurs.
 * This eliminates delays and ensures faster system response.
 */

void isr_init(void) {
	sei(); // Enable global interrupts
}

// Enable external interrupt on INT1 (PD3)
void enable_external_interrupt(uint8_t pin) {
	print("ISR enabled");
	if (pin == EMERGENCY_BUTTON_PIN) {
		EICRA |= (1 << ISC01);  // Trigger on falling edge
		EIMSK |= (1 << INT0);   // Enable INT0
	}
}

// ISR for Emergency Stop Button
ISR(INT0_vect) {
	emergency_stop();
}
