#define F_CPU 16000000UL
#include "communication_master.h"
#include "../elevator_controller/elevator_controller.h"
#include "../uart_debug/uart_debug.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#define SLAVE_ADDRESS 0x57 // 7-bit address (0b1010111)

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
	uint16_t elapsed = 0;
    while (!(TWCR & (1 << TWINT))) {
		_delay_ms(1);
		if (++elapsed > 2000) {  // Wait 2 seconds
			print("TWI write timeout!");
			break;
		}
    }
}

void TWI_stop() {
    // Send stop condition
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

// Used in send_TWI_data for sending one bit a time
void TWI_write(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);

	uint16_t elapsed = 0;
	while (!(TWCR & (1 << TWINT))) {
		_delay_ms(1);
		if (++elapsed > 2000) {  // Wait 2 seconds
			print("TWI write timeout!");
			break;
		}
	}
}

// Can be used to send strings from master to slave to control slave behavior
void send_TWI_data(const char* message) {
	print("TWI: Starting transmission...");

	// Send start condition
	TWI_start();
	print("TWI: START condition sent");

	// Send slave address with write bit (0)
	print("TWI: Sending slave address...");
	TWI_write(SLAVE_ADDRESS << 1);
	print("TWI: Slave address sent");

	// Send data byte by byte from the provided message
	char debug_buf[32];
	for (uint8_t i = 0; i < strlen(message); i++) {
		snprintf(debug_buf, sizeof(debug_buf), "TWI: Sending byte %d: %c", i, message[i]);
		print(debug_buf);
		TWI_write(message[i]);
	}

	print("TWI: All bytes sent");

	// Send stop condition
	TWI_stop();
	print("TWI: STOP condition sent");

	print("TWI: Transmission complete.");
}
