#ifndef ISR_CONTROLLER_H
#define ISR_CONTROLLER_H

#include <avr/interrupt.h>

#define EMERGENCY_BUTTON_PIN 2

// Initializes global interrupt system
void isr_init(void);

// Enables external interrupt on PD3 (INT1) for emergency button
void enable_external_interrupt(uint8_t);

#endif // ISR_CONTROLLER_H
