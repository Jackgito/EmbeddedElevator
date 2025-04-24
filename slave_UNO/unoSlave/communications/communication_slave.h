#ifndef COMMUNICATION_SLAVE_H
#define COMMUNICATION_SLAVE_H

#include <stdint.h>

void TWI_init(void);
void TWI_listen(void);
char* TWI_get_data(void);

#endif // COMMUNICATION_SLAVE_H
