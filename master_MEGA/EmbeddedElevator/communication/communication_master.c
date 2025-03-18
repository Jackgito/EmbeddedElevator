#include "communication.h"

// Define SPI pins for MEGA
#define SPI_SS   PB2  // Slave Select
#define SPI_MOSI PB3  // Master Out Slave In
#define SPI_MISO PB4  // Master In Slave Out
#define SPI_SCK  PB5  // Serial Clock

/*
SPI (Serial Peripheral Interface) is a communication protocol used communication between master (MEGA) and slave (UNO). It requires four signal lines:
MISO (Master In Slave Out)
MOSI (Master Out Slave In)
SCK (Clock)
SS (Slave Select)


This small library implements SPI communication for a master device. It listens to slave to detect if emergency button was pressed.
*/


void initSPI_Master() {
	// Set SS, MOSI, and SCK as outputs
	DDRB |= (1 << SPI_SS) | (1 << SPI_MOSI) | (1 << SPI_SCK);
	
	// Set MISO as input
	DDRB &= ~(1 << SPI_MISO);
	
	// Enable SPI, set as Master, set clock to fosc/16
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	
	// Set SS HIGH (inactive state)
	PORTB |= (1 << SPI_SS);
}

// This is probably not needed, since master is just receiving data from slave
void sendSPI_Data(char *data, uint8_t length) {
	// Enable Slave by setting SS LOW
	PORTB &= ~(1 << SPI_SS);

	for (uint8_t i = 0; i < length; i++) {
		SPDR = data[i]; // Send data byte

		// Wait for transmission to complete
		while (!(SPSR & (1 << SPIF)));

		// Read received byte (optional)
		char received_byte = SPDR;
	}

	// Disable Slave by setting SS HIGH
	PORTB |= (1 << SPI_SS);
}

void receiveSPI_Data(char *buffer, uint8_t length) {
	// Enable Slave by setting SS LOW
	PORTB &= ~(1 << SPI_SS);

	for (uint8_t i = 0; i < length; i++) {
		SPDR = 0xFF; // Send dummy data to trigger SPI clock

		// Wait for reception to complete
		while (!(SPSR & (1 << SPIF)));

		// Store received data
		buffer[i] = SPDR;
	}

	// Disable Slave by setting SS HIGH
	PORTB |= (1 << SPI_SS);
}
