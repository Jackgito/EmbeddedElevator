#ifndef COMMUNICATION_MASTER_H_
#define COMMUNICATION_MASTER_H_

#include <avr/io.h>
#include <stdint.h>

// I2C slave address of the UNO
#define SLAVE_ADDRESS 0x57  // 7-bit address (0b1010111)

/**
 * @brief Initializes the TWI (I2C) interface as master.
 */
void TWI_init(void);

/**
 * @brief Sends a START condition on the TWI bus.
 */
void TWI_start(void);

/**
 * @brief Sends a STOP condition on the TWI bus.
 */
void TWI_stop(void);

/**
 * @brief Sends one byte of data over TWI.
 * 
 * @param data The byte to be sent.
 */
void TWI_write(uint8_t data);

/**
 * @brief Sends a null-terminated message to the slave device over TWI.
 * 
 * @param message The string message to send (e.g. "open_door").
 */
void send_TWI_data(const char* message);

#endif /* COMMUNICATION_MASTER_H_ */
