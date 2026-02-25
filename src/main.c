#include <stdio.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "analogRead.h"
#include "millis.h"
#include "uart.h"
#include "max72xx.h"

#define VERT_PIN 0
#define HORZ_PIN 1

#define BIT_SET(a, b) (a |= (1U << b))
#define BIT_CLEAR(a, b) (a &= ~(1U << b))
#define BIT_FLIP(a, b) (a ^= (1U << b))
#define BIT_CHECK(a, b) (a & (1U << b))

void clear(){
	for(int col = 3; col < 6; col++)
	{
		max7219b_clr(col, 3);
		max7219b_clr(col, 4);
		max7219b_clr(col, 5);
	}
}

void draw(int tal) {
	if(tal == 1) {
		max7219b_set(4, 4);
	}
	else if(tal == 2) {
		max7219b_set(3, 3);
		max7219b_set(5, 5);
	}
	else if(tal == 3) {
		max7219b_set(3, 3);
		max7219b_set(4, 4);
		max7219b_set(5, 5);
	}
	else if(tal == 4) {
		max7219b_set(3, 3);
		max7219b_set(3, 5);
		max7219b_set(5, 3);
		max7219b_set(5, 5);
	}
	else if(tal == 5) {
		max7219b_set(3, 3);
		max7219b_set(3, 5);
		max7219b_set(4, 4);
		max7219b_set(5, 3);
		max7219b_set(5, 5);
	}
	else if(tal == 6) {
		max7219b_set(3, 3);
		max7219b_set(3, 4);
		max7219b_set(3, 5);
		max7219b_set(5, 3);
		max7219b_set(5, 4);
		max7219b_set(5, 5);
	}
	max7219b_out();
}

int main()
{
	BIT_CLEAR(DDRC, VERT_PIN);
	BIT_CLEAR(DDRC, HORZ_PIN);

 	millis_init();
    sei();

	init_serial();
	max7219_init();

	int tal = 1;
	bool change = true;
	millis_t millis_since_last_read = 0;
	millis_t current_millis = 0;
	uint16_t oldhorz = 0;
	uint16_t oldvert = 0;

	while (1) {
		current_millis = millis();

		// Joysticken kommer kontinuerligt ge värden, så vi läser bara var 170:e ms så att vi kan gå ett steg i taget
		if (current_millis - millis_since_last_read > 170) {
			millis_since_last_read = current_millis;

			// Läs joystick
			uint16_t horz = analogRead(HORZ_PIN);
			uint16_t vert = analogRead(VERT_PIN);

			// Printa horz och vert, men bara om de ändrats
			if (horz != oldhorz) {
				printf("Horz: %u\n", horz);
				oldhorz = horz;
			}
			if (vert != oldvert) {
				printf("Vert: %u\n", vert);
				oldvert = vert;
			}

			// Kontrollera om vi läst en signal som innebär modifiering av tal.
			// LEFT: -1, RIGHT: +1, UP: +2, DOWN: -2
			if (horz < 300) { // RIGHT
				change = true;

				if (++tal == 7) {
					tal = 1;
				}
			}
			else if (horz > 700) { // LEFT
				change = true;

				if (--tal == 0) {
					tal = 6;
				}
			}

			if (vert > 700) { // UP
				change = true;
				tal += 2;

				if (tal > 6) {
					tal -= 6;
				}
			}
			else if (vert < 300) { // DOWN
				change = true;
				tal -= 2;

				if (tal < 1) {
					tal += 6;
				}
			}

			if (change) {
				change = false;
				clear();
				printf("tal: %d\n", tal);
				draw(tal);
			}
		}
	}
	return 0;
}