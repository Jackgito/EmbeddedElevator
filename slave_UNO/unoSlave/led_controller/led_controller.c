#define F_CPU 16000000UL
#include <util/delay.h> 
#include "led_controller.h"
#include <avr/io.h>  // Include AVR library for I/O operations
#include <stdbool.h>

// Define the pin numbers for movement and door LEDs
#define MOVEMENT_LED_PIN PB0
#define DOOR_LED_PIN PB1
#define LED_BLINK_INTERVAL 1000  // Set a constant interval for blinking

// Led controller can be used to turn the movement and door opening LEDs on and off. It also has blink function for emergencies.

void led_init(void) {
	DDRB |= (1 << MOVEMENT_LED_PIN) | (1 << DOOR_LED_PIN);
	set_movement_led(0);
	set_door_led(true);
}

void set_movement_led(bool state) {
	if (state)
	PORTB |= (1 << MOVEMENT_LED_PIN);
	else
	PORTB &= ~(1 << MOVEMENT_LED_PIN);
}

void set_door_led(bool state) {
	if (state)
	PORTB |= (1 << DOOR_LED_PIN);
	else
	PORTB &= ~(1 << DOOR_LED_PIN);
}


void blink_movement_led() {
	for (uint8_t i = 0; i < 3; i++) {
		PORTB ^= (1 << MOVEMENT_LED_PIN);
		_delay_ms(LED_BLINK_INTERVAL);
		PORTB ^= (1 << MOVEMENT_LED_PIN);
		_delay_ms(LED_BLINK_INTERVAL);
	}
}
