#include "communication.h"
#include "buzzer_controller.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Define the emergency button pin
#define EMERGENCY_BUTTON_PIN PD2

uint8_t isEmergencyButtonPressed(void) {
    return !(PIND & (1 << EMERGENCY_BUTTON_PIN));
}

int main(void) {
    // Initialize TWI as master (Mega will act as slave)
    TWI_init();
    
    // Initialize the buzzer
    buzzer_init();
    
    // Main loop
    while (1) {
        // Continuously check for received data
        TWI_receive();
        
        if (isEmergencyButtonPressed()) {
            // Send emergency message over TWI
            TWI_send_data("Start emergency"); // Sends Button press data to master through TWI
            
            // Activate the buzzer (play melody)
            play_melody();
            
            // Optional: Add debounce delay after button press
            _delay_ms(500);
        }
    }

    return 0;
}
