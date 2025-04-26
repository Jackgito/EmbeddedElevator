#ifndef UART_DEBUG_H
#define UART_DEBUG_H

#include <stdio.h>
#include <avr/io.h>

/*
 * UART is used to enable print commands with PuTTY
 * Initializes the UART for communication.
 * Call this once at startup with a UBRR value.
 */
void uart_init(uint16_t ubrr);

/*
 * Transmits a single character over UART.
 * Used internally by the printf mechanism.
 */
int uart_putchar(char c, FILE *stream);

/*
 * Receives a single character from UART.
 * Used internally by scanf-style functions.
 */
int uart_getchar(FILE *stream);

/*
 * Prints a basic string over UART (no formatting).
 * Similar to puts(), but without newline added.
 * Usage: print("Hello World\n");
 */
void print(const char* msg);

/*
 * Prints a formatted string over UART, like printf.
 * Usage: debug_print("Floor: %d\n", floor_num);
 */
#define debug_print(...) printf(__VA_ARGS__)

// Stream handles for stdio redirection
extern FILE uart_output;
extern FILE uart_input;

#endif
