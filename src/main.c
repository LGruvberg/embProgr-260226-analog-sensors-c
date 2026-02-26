#include <stdio.h>
#include <avr/interrupt.h>
#include "analogRead.h"
#include "millis.h"
#include "uart.h"

#define IN_PIN PC0

#define BIT_SET(a, b) (a |= (1U << b))
#define BIT_CLEAR(a, b) (a &= ~(1U << b))
#define BIT_FLIP(a, b) (a ^= (1U << b))
#define BIT_CHECK(a, b) (a & (1U << b))

int main() {
	BIT_CLEAR(DDRC, IN_PIN);

	millis_init();
	sei();
	init_serial();

	uint16_t value;
	uint16_t old_value;
	millis_t millis_since_last_print = 0;
	millis_t current_millis = 0;

	while (1) {
		current_millis = millis();
		value = analogRead(IN_PIN);

		// Printa indatan varje sekund
		/*if (current_millis - millis_since_last_print >= 1000) {
			printf("Current value: %u\n", value);
			millis_since_last_print = current_millis;
		}*/

		// Printa varje förändring
		if (old_value != value) {
			old_value = value;
			printf("Current value: %u\n", value);
		}
	}
	return 0;
}
