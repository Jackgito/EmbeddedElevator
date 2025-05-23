#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "elevator_controller.h"
#include "../lcd_controller_MEGA/lcd.h"
#include "../keypad_controller/keypad.h"
#include "../uart_debug/uart_debug.h"
#include "../communication/communication_master.h"

#define MAX_FLOOR 99
#define TIME_PER_FLOOR 400 // Time it takes for elevator to move 1 floor

static volatile uint8_t emergency_handled = 0;
static uint8_t current_floor = 0;
static uint8_t target_floor = 0;

typedef enum {
	IDLE,
	MOVING,
	DOOR_OPENING,
	DOOR_CLOSING,
	EMERGENCY,
	FAULT
} ElevatorState;

static ElevatorState current_state = IDLE;

void elevator_init(void) {
	current_floor = 0;
	current_state = IDLE;
}

void elevator_reset_ui(void) {
	current_state = IDLE;
	lcd_clrscr();
	lcd_puts("Choose floor:");
	lcd_gotoxy(0, 1);
	print("Choose floor");
}

// Handles elevator movement between floors with regular floor update display.
// Movement can be interrupted if an emergency is triggered.
void move_elevator(uint8_t floor) {
	
	printf("Current floor: %d\n", current_floor);
	printf("Target floor: %d\n", floor);
	
	send_TWI_data("moving");

	if (floor == current_floor) {
		handle_fault();
		return;
	}

	target_floor = floor;
	current_state = MOVING;
	display_floor(current_floor);

	while (current_floor != floor) {
		
		if (emergency_handled == 1) { // Stop moving after emergency
			emergency_handled = 0;
			return;
		}
		
		current_floor += (floor > current_floor) ? 1 : -1;
		display_floor(current_floor);
		_delay_ms(TIME_PER_FLOOR);
	}
	open_door();
}

void open_door(void) {
	current_state = DOOR_OPENING;
	send_TWI_data("open_door");

	lcd_clrscr();
	lcd_puts("Door opened");
	print("Door opened");

	_delay_ms(5000);  // Door open duration

	close_door();
}

void close_door(void) {
	current_state = DOOR_CLOSING;
	send_TWI_data("close_door");

	lcd_clrscr();
	lcd_puts("Door closed");
	print("Door closed");

	_delay_ms(1000);
	elevator_reset_ui();
}

// This is called via ISR when button is pressed
void emergency_stop(void) {
	if (emergency_handled) {
		return; // Already handled, ignore
	}

	emergency_handled = 1; // Stop multiple emergency triggers

	current_state = EMERGENCY;
	send_TWI_data("emergency");

	lcd_clrscr();
	lcd_puts("EMERGENCY");
	print("EMERGENCY");
	_delay_ms(4000);
	open_door();  // open_door() will call close_door() automatically
	current_state = IDLE;
}

void handle_fault(void) {
	current_state = FAULT;
	send_TWI_data("fault");

	lcd_clrscr();
	lcd_puts("Fault: Same floor");
	print("Fault: Same floor");

	_delay_ms(2000);
	elevator_reset_ui();
}

void display_floor(uint8_t floor) {
	lcd_clrscr();

	char floor_str[4];
	itoa(floor, floor_str, 10);

	lcd_gotoxy(0, 0);
	lcd_puts("Floor: ");
	lcd_puts(floor_str);

	lcd_gotoxy(0, 1);
	const char* state_str = "";

	switch (current_state) {
		case IDLE:
		state_str = "IDLE";
		lcd_puts("Choose floor:");
		break;

		case MOVING: {
			state_str = "MOVING";

			// Line 1: Show current floor
			lcd_puts("Floor: ");
			char current_str[4];
			itoa(current_floor, current_str, 10);
			lcd_puts(current_str);

			// Line 2: Show target floor
			lcd_gotoxy(0, 1);
			lcd_puts("Target: ");
			char target_str[4];
			itoa(target_floor, target_str, 10); // Use a simple target_floor variable
			lcd_puts(target_str);
			break;
		}

		case DOOR_OPENING:
		case DOOR_CLOSING:
		state_str = (current_state == DOOR_OPENING) ? "DOOR OPEN" : "DOOR CLOSED";
		lcd_puts(state_str);
		break;

		case EMERGENCY:
		state_str = "EMERGENCY";
		lcd_puts("EMERGENCY");
		break;

		case FAULT:
		state_str = "FAULT";
		lcd_puts("FAULT: Same floor");
		break;
	}

	// Print debug info over UART
	char debug_msg[50];
	snprintf(debug_msg, sizeof(debug_msg), "Floor: %d | State: %s", floor, state_str);
	print(debug_msg);
}
