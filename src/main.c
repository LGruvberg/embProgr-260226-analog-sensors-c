#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <avr/interrupt.h>
#include "analogRead.h"
#include "millis.h"
#include "uart.h"

#define IN_PIN	PC0

#define BIT_SET(a, b)	(a |= (1U << b))
#define BIT_CLEAR(a, b)	(a &= ~(1U << b))
#define BIT_FLIP(a, b)	(a ^= (1U << b))
#define BIT_CHECK(a, b)	(a & (1U << b))

#define B_LED	PB2   // Pin 10
#define G_LED	PB3   // Pin 11
#define R_LED	PB4   // Pin 12

int main() {
	BIT_CLEAR(DDRC, IN_PIN);

	/////////
	BIT_SET(DDRB, B_LED);
	BIT_SET(DDRB, G_LED);
	BIT_SET(DDRB, R_LED);
	/////////

	millis_init();
	sei();
	init_serial();

	uint16_t value = 0;
	float celsius = 0;
	int16_t integer = 0;
	int16_t decimals = 0;
	millis_t millis_since_last_print = 0;
	millis_t current_millis = 0;

	while (1) {
		current_millis = millis();
		value = analogRead(IN_PIN);

		// Printa indatan varje sekund
		if (current_millis - millis_since_last_print >= 1000) {
			// Beräkningen är tagen från wokwis beskrivning av komponenten
			celsius = 1 / (log(1 / (1023. / value - 1)) / 3950. + 1.0 / 298.15) - 273.15;
			// Speciallösning då vårat väldigt simpla uart-bibliotek inte kan printa flyttal
			integer = (int)celsius;
			decimals = abs((int)((celsius - integer) * 100));
			printf("Current value: %d.%d\n", integer, decimals);

			/////////
			// Turn off LEDs
			BIT_CLEAR(PORTB, B_LED);
			BIT_CLEAR(PORTB, G_LED);
			BIT_CLEAR(PORTB, R_LED);

			if (celsius < 10) {
				BIT_SET(PORTB, B_LED);
			}
			else if (celsius > 30) {
				BIT_SET(PORTB, R_LED);
			}
			else {
				BIT_SET(PORTB, G_LED);
			}
			/////////

			millis_since_last_print = current_millis;
		}
	}
	return 0;
}