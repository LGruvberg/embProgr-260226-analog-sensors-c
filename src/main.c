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

	// uint16_t value;
	uint16_t value = 0;
	// uint16_t old_value;
	millis_t millis_since_last_print = 0;
	// millis_t current_millis = 0;
	
	while (1) {
		millis_t current_millis = millis();

		//	Read and print every 1000ms
		if (current_millis - millis_since_last_print >= 1000) {
			millis_since_last_print = current_millis;
			value = analogRead(IN_PIN);

			if (value == 0) {
				printf("Ljudlöst (%u)\n", value);
			}
			else if (value < 250) {
				printf("Låg volym (%u)\n", value);
			}
			else if (value < 500) {
				printf("Medel volym (%u)\n", value);
			}
			else if (value < 750) {
				printf("Hög volym! (%u)\n", value);
			}
			else {
				printf("Väldigt hög volym!!! (%u)\n", value);
			}
		}
		// current_millis = millis();

		// // value = analogRead(IN_PIN);

		// // Printa indatan varje sekund
		// /*if (current_millis - millis_since_last_print >= 1000) {
		// 	printf("Current value: %u\n", value);
		// 	millis_since_last_print = current_millis;
		// }*/

		// // Printa varje förändring
		// if (old_value != value) {
		// 	old_value = value;
		// 	printf("Current value: %u\n", value);
		// }
	}
	return 0;
}
