/*
 * main.c
 *
 * Created: 1/21/2022 6:24:45 PM
 * Author : cosbug@gmail.com
 */

// Define CPU frequency globally in Project > Properties > Toolchain > AVR/GNU C Compiler > Symbols in AtmelStudio
// or uncomment the below line
// #define F_CPU 8000000UL  // 8 MHz, internal RC oscillator

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "ht1611.h"

const char Message[] PROGMEM = "1234567890-,=+./";	// store string in FLASH memory

int main(void)
{
	uint8_t i;

	ht1611_init();
	ht1611_display_clear();

    while (1)
    {
		// from program memory
		for(i=0; i<sizeof(Message)-1; i++) {
			ht1611_display_char(pgm_read_byte(&Message[i]));
			_delay_ms(500);
		}
		_delay_ms(1000);
		ht1611_display_clear();
    }
}
