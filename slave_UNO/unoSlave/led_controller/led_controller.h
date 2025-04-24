#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

void led_init(void);
void set_movement_led(bool state);
void set_door_led(bool state);
void blink_movement_led();

#endif
