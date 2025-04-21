#include "elevator_controller.h"
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "led_controller.h"
#include "keypad.h"
#include "buzzer_controller.h"
#include "isr_controller.h"

#define MOVEMENT_LED_PIN 0
#define DOOR_LED_PIN 1
#define MAX_QUEUE_SIZE 10

uint8_t current_floor = 0;
uint8_t floor_queue[MAX_QUEUE_SIZE];
uint8_t queue_start = 0, queue_end = 0;

// Add floor request to the queue
void enqueue_floor(uint8_t floor) {
	if ((queue_end + 1) % MAX_QUEUE_SIZE == queue_start) {
		return;  // Queue full, ignore request
	}
	floor_queue[queue_end] = floor;
	queue_end = (queue_end + 1) % MAX_QUEUE_SIZE;
}

// Get next floor from queue
uint8_t dequeue_floor(void) {
	if (queue_start == queue_end) {
		return 255;  // Queue empty
	}
	uint8_t floor = floor_queue[queue_start];
	queue_start = (queue_start + 1) % MAX_QUEUE_SIZE;
	return floor;
}

void elevator_init(void) {
	led_init();
	keypad_init();
	buzzer_init();

	lcd_init(LCD_DISP_ON);
	lcd_puts("Choose the floor");

	isr_init();
	enable_timer_interrupt(500);
	enable_external_interrupt(PD2);
	enable_external_interrupt(PD3);
}

void process_floor_queue(void) {
	while (queue_start != queue_end) {
		uint8_t floor = dequeue_floor();
		if (floor != 255) {
			move_elevator(floor);
		}
	}
}

void move_elevator(uint8_t floor) {
	if (floor == current_floor) {
		handle_fault();
		return;
	}

	set_movement_led(true);
	display_floor(current_floor);

	while (current_floor != floor) {
		current_floor += (floor > current_floor) ? 1 : -1;
		display_floor(current_floor);
		_delay_ms(100);
	}

	open_door();
}

void open_door(void) {
	set_door_led(true);
	lcd_clrscr();
	lcd_puts("Door Opening");
	_delay_ms(5000);
	close_door();
}

void close_door(void) {
	set_door_led(false);
	lcd_clrscr();
	lcd_puts("Door Closed");
	_delay_ms(1000);
	lcd_clrscr();
	lcd_puts("Choose the floor");

	process_floor_queue();
}

void emergency_stop(void) {
	lcd_clrscr();
	lcd_puts("EMERGENCY");

	blink_led(MOVEMENT_LED_PIN, 3, 500);
    
	open_door();
	play_melody();
	close_door();
}

void handle_fault(void) {
	blink_led(MOVEMENT_LED_PIN, 3, 500);

	lcd_clrscr();
	lcd_puts("Fault: Same floor");
	_delay_ms(2000);
	lcd_clrscr();
	lcd_puts("Choose the floor");
}

void display_floor(uint8_t floor) {
	lcd_clrscr();
	char floor_str[3];
	itoa(floor, floor_str, 10);
	lcd_puts(floor_str);
}

// ISR for keypad input (PD2)
ISR(INT0_vect) {
	uint8_t floor = KEYPAD_GetKey();
	if (floor != current_floor) {
		enqueue_floor(floor);
		if (queue_start == queue_end - 1) {  // If only one request, process immediately
			process_floor_queue();
		}
	}
}

// ISR for emergency stop (PD3)
ISR(INT1_vect) {
	emergency_stop();
}
