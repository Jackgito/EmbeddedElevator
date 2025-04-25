#include "buzzer_controller.h"
#include <avr/io.h>
#include <avr/interrupt.h>

ISR (TIMER1_COMPA_vect)
{

}

void buzzer_init(void) {
    /* Set up the ports and pins */
    DDRB|= (1 << PB1); // OC1A pin 9
    
    /* Set up the 16-bit timer/counter1 */
    TCNT1  = 0; //reset timer/counter register
    TCCR1B = 0; //reset timer/counter control
    TCCR1A |= (1 << 6); //set compare output mode to toggle OC1A
    
    /* Set up waveform generation mode*/
    //In mode 9, the WGMn3 = 1 and WGMn0 = 1.
    TCCR1A |= (1 << 0); //Normal port operation
    TCCR1B |= (1 << 4); //Clear OCnA/OCnB/OCnC on compare match (set output to low level)

    /* Enable timer/counter compare match A interrupt */
    TIMSK1 |= (1 << 1);
    
    /* Enable interrupts command */
    sei();
}

// Function to play a melody with 4 notes
void play_melody(void) {
    uint16_t melody[] = {7641, 6067, 5102, 3822}; // C6 1046.5 Hz, E6 1318.51 Hz, G6 1567.98 Hz, C7 2093 Hz
    
    for (int i = 0; i < 4; i++) {
        TCCR1B |= (1 << 0); // Enable timer/counter1. Set prescaling to 1 (no prescaling)
        OCR1A = melody[i];	// Set output frequency
        _delay_ms(2000);
    }
    TCCR1B = 0; //reset timer/counter control
    TCCR1B |= (1 << 4); //Clear OCnA/OCnB/OCnC on compare match (set output to low level)
}

// Function to play chime
void play_chime(void) {
    TCCR1B |= (1 << 0); // Enable timer/counter1. Set prescaling to 1 (no prescaling)
    OCR1A = 5102;	// Set output frequency 1567.98 Hz (G6)
    _delay_ms(5500);
    TCCR1B |= (1 << 0); // Enable timer/counter1. Set prescaling to 1 (no prescaling)
    OCR1A = 6428;	// Set output frequency 1244.51 Hz (D6#)
    _delay_ms(12000);
    TCCR1B = 0; //reset timer/counter control
    TCCR1B |= (1 << 4); //Clear OCnA/OCnB/OCnC on compare match (set output to low level)
}