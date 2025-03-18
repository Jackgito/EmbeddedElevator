#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <avr/io.h>

// Function prototypes
void initSPI_Master();
void initSPI_Slave();
void sendSPI_Data(char *data, uint8_t length);
void receiveSPI_Data(char *buffer, uint8_t length);

#endif
