#include "communication.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#define SLAVE_ADDRESS 0x57 // 7-bit address (0b1010111)

char twi_receive_data[20]; // Buffer for receiving data
uint8_t twi_index = 0;

void TWI_init() {
    // Set up TWI for slave mode
    TWAR = SLAVE_ADDRESS << 1; // Set slave address
    TWCR |= (1 << TWEA) | (1 << TWEN); // Enable TWI and enable acknowledgement (TWEA)
}

void TWI_receive() {
    // Wait for TWI interrupt to signal data reception
    while (!(TWCR & (1 << TWINT))) {
        ;
    }
    // If data has been received, store it in the buffer
    twi_receive_data[twi_index] = TWDR;
    twi_index++;

    // If 20 bytes have been received, process the data
    if (twi_index >= sizeof(twi_receive_data)) {
        twi_receive_data[twi_index] = '\0'; // Null terminate the string
        printf("Received: %s\n", twi_receive_data); // Print received data
        twi_index = 0; // Reset index for the next message
    }
    
    // Clear TWINT flag to continue TWI operation
    TWCR |= (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
}

void TWI_send_data(char* data) {
    // Send data byte by byte to the master
    for (uint8_t i = 0; i < strlen(data); i++) {
        TWDR = data[i];  // Load data into the TWI data register
        TWCR = (1 << TWINT) | (1 << TWEN);  // Clear TWINT to continue communication
        while (!(TWCR & (1 << TWINT))) {  // Wait until data is transmitted
            ;
        }
    }
    
    // Clear TWINT flag to continue TWI operation
    TWCR |= (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
}

int main(void) {
    // Initialize TWI as slave
    TWI_init();
    
    while (1) {
        // Continuously check for received data
        TWI_receive();
    }
    
    return 0;
}
