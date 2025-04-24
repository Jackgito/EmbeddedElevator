#ifndef ELEVATOR_CONTROLLER_H_
#define ELEVATOR_CONTROLLER_H_

#include <stdint.h>

/**
 * @brief Initializes elevator state and peripherals.
 */
void elevator_init(void);

/**
 * @brief Resets the elevator UI to the default prompt ("Choose floor").
 */
void elevator_reset_ui(void);

/**
 * @brief Handles the movement of the elevator to a specific floor.
 * 
 * @param floor Target floor number.
 */
void move_elevator(uint8_t floor);

/**
 * @brief Opens the elevator door and triggers the appropriate UI and signals.
 */
void open_door(void);

/**
 * @brief Closes the elevator door and resets UI after a short delay.
 */
void close_door(void);

/**
 * @brief Immediately stops the elevator and triggers emergency behavior.
 * Sends an emergency signal to the slave (e.g., blink + buzzer).
 */
void emergency_stop(void);

/**
 * @brief Handles a fault condition (e.g., same floor requested).
 * Sends fault indication to slave and displays error.
 */
void handle_fault(void);

/**
 * @brief Displays the current floor and state on the LCD.
 * 
 * @param floor The floor number to display.
 */
void display_floor(uint8_t floor);

#endif /* ELEVATOR_CONTROLLER_H_ */
