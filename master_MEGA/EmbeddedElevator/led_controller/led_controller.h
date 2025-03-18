#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <avr/io.h>
#include <util/delay.h>

void led_init(void);
void set_movement_led(uint8_t state);
void set_door_led(uint8_t state);
void blink_led(uint8_t led_pin, uint8_t times, uint16_t interval);

#endif
