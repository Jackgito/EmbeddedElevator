#include "communication.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include elevator_controller.h

#define SLAVE_ADDRESS 0x57 // 7-bit address (0b1010111)

char twi_send_data[20] = "Master to Slave\n"; // Data to send

void TWI_init() {
    // Set up TWI (I2C) as master
    TWBR = 3;  // Set bit rate
    TWSR = 0x00; // Prescaler value
    TWCR |= (1 << TWEN); // Enable TWI
}

void TWI_start() {
    // Send start condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    // Wait for the TWI interrupt flag to be set
    while (!(TWCR & (1 << TWINT))) {
        ;
    }
}

void TWI_stop() {
    // Send stop condition
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_write(uint8_t data) {
    // Load data into the TWI data register
    TWDR = data;
    // Clear the interrupt flag to continue communication
    TWCR = (1 << TWINT) | (1 << TWEN);
    // Wait for the TWI interrupt flag to be set
    while (!(TWCR & (1 << TWINT))) {
        ;
    }
}

void sendTWI_data() {
    // Send start condition
    TWI_start();

    // Send slave address with write bit (0)
    TWI_write(SLAVE_ADDRESS << 1);

    // Send data byte by byte
    for (uint8_t i = 0; i < strlen(twi_send_data); i++) {
        TWI_write(twi_send_data[i]);
    }

    // Send stop condition
    TWI_stop();
}

int main(void) {
    // Initialize TWI (I2C) as master
    TWI_init();
    
    while (1) {
        // Send data to the slave every 2 seconds
        sendTWI_data();
        _delay_ms(2000);
    }
    
    return 0;
}
