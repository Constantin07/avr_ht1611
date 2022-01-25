/*
 * ht1611.c
 *
 * Created: 1/23/2022 10:09:43 AM
 * Author: cosbug@gmail.com
 * Holtek 10 digit HT1611 based LCD
 
 Notes:
 1. When interfacing with uC, the HK pin must be connected to ground (CMOS in pull-high).
 2. The S1, S2 and TMR pins must be left unconnected (CMOS in pull-low).
 */

#include <avr/io.h>
#include <util/delay.h>
#include "ht1611.h"

void ht1611_init(void)
{
    HT_PORT_DIR |= (_BV(DI) | _BV(SK));     // configure DI and SK pins as outputs
    HT_PORT &= ~(_BV(DI) | _BV(SK));        // clear DI and SK
    _delay_ms(POWER_ON_DELAY_MS);           // allow LCD enough time to initialize
}

void ht1611_display_char(char chr)
{
    int8_t i;
    // Map supported ASCII characters to LCD data codes, comment out lines not needed
    switch (chr) {
        case ' ': chr = 0; break;   // blank
        case '0': chr = 10; break;
        case 192: chr = 11; break;  // '?'
        case 217: chr = 12; break;  // '?'
        case 'F': chr = 13; break;
        case 'P': chr = 14; break;
        case '-': chr = 15; break;
    }

    for (i = 3; i >= 0; --i) {
        on(SK);                     // set SK high before sending data
        if (chr & 1<<i) {
            on(DI);
        } else { 
            off(DI);
        }
        _delay_us(TA_TIME_US);
        off(SK);                    // set SK to low to latch the bit
        _delay_us(TB_TIME_US);
    }
    _delay_us(TC_TIME_US);          // wait for inter digit delay		
}

void ht1611_display_str(char *s)
{
    while(*s)
    ht1611_display_char(*s++);
    off(SK);                        // keep SK low to avoid LED switching to timer mode
}

void ht1611_display_clear(void)
{
    int8_t digit;
    for (digit = 0; digit < DIGITS_COUNT; digit++) {
        ht1611_display_char(0);     // display blank character
    }
    off(SK);                        // keep SK low to avoid LED switching to timer mode
}

inline void on(uint8_t bit) {
    HT_PORT |= _BV(bit);
}

inline void off(uint8_t bit) {
    HT_PORT &= ~_BV(bit);
}
