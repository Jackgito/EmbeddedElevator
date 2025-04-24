#define F_CPU 16000000UL
#include "communication_slave.h"

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define SLAVE_ADDRESS 0b1010111
#define BUFFER_SIZE 20

static char twi_receive_data[BUFFER_SIZE];
static uint8_t twi_index = 0;

void TWI_init() {
	// Set slave address (7-bit address left-shifted, general call disabled)
	TWAR = (SLAVE_ADDRESS << 1);

	// Enable TWI and ACK
	TWCR = (1 << TWEN) | (1 << TWEA);
}

void TWI_listen() {
	uint8_t status;

	while (1) {
		// Wait for TWI interrupt flag
		while (!(TWCR & (1 << TWINT))) {
			;
		}

		// Read status and mask prescaler bits
		status = TWSR & 0xF8;

		// Re-enable TWI, ACK, clear interrupt
		TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);

		if ((status == 0x80) || (status == 0x90)) {
			// Data received and ACK returned
			if (twi_index < BUFFER_SIZE - 1) {
				twi_receive_data[twi_index++] = TWDR;
			}
			} else if ((status == 0x88) || (status == 0x98)) {
			// Data received and NACK returned
			if (twi_index < BUFFER_SIZE - 1) {
				twi_receive_data[twi_index++] = TWDR;
			}
			} else if (status == 0xA0) {
			// Stop or repeated start condition
			twi_receive_data[twi_index] = '\0';  // Null-terminate
			twi_index = 0;
			break;  // Stop listening until next call
		}
	}
}

char* TWI_get_data() {
	return twi_receive_data;
}
