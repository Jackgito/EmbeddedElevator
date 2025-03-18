#include "led_controller.h"
#include <avr/io.h>  // Include AVR library for I/O operations

// Define the pin numbers for movement and door LEDs
#define MOVEMENT_LED_PIN 0  // Example: pin 0 on PORTB
#define DOOR_LED_PIN 1      // Example: pin 1 on PORTB

void led_init(void) {
	DDRB |= (1 << MOVEMENT_LED_PIN) | (1 << DOOR_LED_PIN);
	set_movement_led(0);
	set_door_led(0);
}

void set_movement_led(uint8_t state) {
	if (state)
	PORTB |= (1 << MOVEMENT_LED_PIN);
	else
	PORTB &= ~(1 << MOVEMENT_LED_PIN);
}

void set_door_led(uint8_t state) {
	if (state)
	PORTB |= (1 << DOOR_LED_PIN);
	else
	PORTB &= ~(1 << DOOR_LED_PIN);
}

void blink_led(uint8_t led_pin, uint8_t times, uint16_t interval) {
	for (uint8_t i = 0; i < times; i++) {
		PORTB ^= (1 << led_pin);
		_delay_ms(interval);
		PORTB ^= (1 << led_pin);
		_delay_ms(interval);
	}
}