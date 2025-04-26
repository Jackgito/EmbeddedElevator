#include "uart_debug.h"

// Setup output and input streams for UART
FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input  = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

void uart_init(uint16_t ubrr) {
	// Set baud rate
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;

	// Enable receiver and transmitter
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

	// Set frame format: 8 data bits, 2 stop bits
	UCSR0C |= (1 << USBS0) | (3 << UCSZ00);

	// Redirect std I/O streams to UART
	stdout = &uart_output;
	stdin = &uart_input;
}

int uart_putchar(char c, FILE *stream) {
	// Convert newline to carriage return + newline
	if (c == '\n') {
		uart_putchar('\r', stream);
	}

	// Wait until buffer is empty
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
	return 0;
}

int uart_getchar(FILE *stream) {
	// Wait for incoming data
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void print(const char* msg) {
	// Print a string over UART, character by character
	while (*msg) {
		uart_putchar(*msg++, &uart_output);
	}
	uart_putchar('\n', &uart_output);  // Append newline at the end
}
