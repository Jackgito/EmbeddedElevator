#ifndef ISR_CONTROLLER_H
#define ISR_CONTROLLER_H

#include <avr/io.h>
#include <avr/interrupt.h>

void isr_init(void);
void enable_timer_interrupt(uint16_t interval_ms);
void enable_external_interrupt(uint8_t pin);
void disable_timer_interrupt(void);

#endif
