#ifndef BUZZER_CONTROLLER_H_
#define BUZZER_CONTROLLER_H_

#include <stdint.h>


void buzzer_init(void);
void play_tone(uint16_t frequency);
void stop_tone(void);
void play_melody(void);

#endif
