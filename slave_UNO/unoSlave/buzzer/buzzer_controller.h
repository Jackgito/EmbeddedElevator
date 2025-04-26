#ifndef BUZZER_CONTROLLER_H
#define BUZZER_CONTROLLER_H

#include <avr/io.h>
#include <util/delay.h>

void buzzer_init(void);
void play_emergency_melody(void);
void play_chime(void);

#endif
