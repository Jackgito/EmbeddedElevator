#include "communication.h"
#include <string.h>

#define SPI_SS   PB2
#define SPI_MOSI PB3
#define SPI_MISO PB4
#define SPI_SCK  PB5

#define EMERGENCY_BUTTON PD2 // Example pin for emergency button
#define BUZZER_PIN PD3 // Example pin for buzzer

char spi_send_data[20]; // Buffer for sending data

/*
SPI (Serial Peripheral Interface) is a communication protocol used communication between master (MEGA) and slave (UNO). It requires four signal lines: 
MISO (Master In Slave Out)
MOSI (Master Out Slave In)
SCK (Clock)
SS (Slave Select)


This small library implements SPI communication for a slave device. It includes functions for initializing SPI in slave mode, sending data over SPI, receiving data from the master,
and responding to specific commands like triggering a buzzer when an "emergency" message is received. It also checks for a button press and sends an "emergency" message when pressed.
*/

void initSPI_Slave() {
	DDRB |= (1 << SPI_MISO); // MISO as output
	DDRB &= ~((1 << SPI_SS) | (1 << SPI_MOSI) | (1 << SPI_SCK)); // SS, MOSI, SCK as inputs
	SPCR |= (1 << SPE); // Enable SPI

	DDRD &= ~(1 << EMERGENCY_BUTTON); // Set emergency button as input
	DDRD |= (1 << BUZZER_PIN); // Set buzzer as output
}

void sendSPI_Data(const char *data) {
	// Copy the data string into the local buffer with size limit
	strncpy(spi_send_data, data, sizeof(spi_send_data) - 1);
	// Ensure the buffer is null-terminated
	spi_send_data[sizeof(spi_send_data) - 1] = '\0';

	// Loop through the data and send each character over SPI
	for (uint8_t i = 0; i < strlen(spi_send_data); i++) {
		SPDR = spi_send_data[i];              // Load data into the SPI Data Register
		while (!(SPSR & (1 << SPIF)));        // Wait until the data has been transmitted
	}

	// Send a null terminator after the data
	SPDR = '\0';  // Send the null terminator to indicate the end of the string
	while (!(SPSR & (1 << SPIF)));           // Wait until the null terminator is transmitted
}


void receiveSPI_Data(char *buffer, uint8_t buffer_size) {
	for (uint8_t i = 0; i < buffer_size - 1; i++) {
		while (!(SPSR & (1 << SPIF)));

		buffer[i] = SPDR;
		if (buffer[i] == '\0') break; // Stop reading at null terminator
	}

	buffer[buffer_size - 1] = '\0'; // Ensure string termination

	if (strcmp(buffer, "playBuzzer") == 0) {
		PORTD |= (1 << BUZZER_PIN); // Turn buzzer ON
		_delay_ms(1000);
		PORTD &= ~(1 << BUZZER_PIN); // Turn buzzer OFF
	}
}

void checkEmergencyButton() {
	if (!(PIND & (1 << EMERGENCY_BUTTON))) { // Button pressed (active LOW)
		sendSPI_Data("emergency");
		_delay_ms(500); // Debounce
	}
}
