// elevatorController.h
#ifndef ELEVATOR_CONTROLLER_H
#define ELEVATOR_CONTROLLER_H

#include <stdbool.h>  // For using bool type

// Function prototypes
void elevator_init(void);  // Initialize elevator system
void move_elevator(uint8_t floor);  // Move elevator to the selected floor
void open_door(void);  // Open the elevator door
void close_door(void);  // Close the elevator door
void emergency_stop(void);  // Handle emergency stop
void handle_fault(void);  // Handle fault if the selected floor is the same as the current floor
void display_floor(uint8_t floor);  // Display the current floor on the LCD

#endif
