/*
  wiring.c - Partial implementation of the Wiring API for the ATmega8.
  Part of Arduino - http://www.arduino.cc/
  Copyright (c) 2005-2006 David A. Mellis
  https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/wiring.c
  See the GNU Lesser General Public License for more details.
*/
#include "millis.h"
#include <avr/interrupt.h>
#include <avr/io.h>

volatile uint32_t timer0_overflow_count = 0;
volatile uint32_t timer0_millis = 0;
static uint8_t timer0_fract = 0;

ISR(TIMER0_OVF_vect)
{
    // copy these to local variables so they can be stored in registers
    // (volatile variables must be read from memory on every access)
    uint32_t m = timer0_millis;
    uint8_t f = timer0_fract;

    m += MILLIS_INC;
    f += FRACT_INC;
    if (f >= FRACT_MAX) {
        f -= FRACT_MAX;
        m += 1;
    }

    timer0_fract = f;
    timer0_millis = m;
    timer0_overflow_count++;
}

uint32_t millis()
{
    uint32_t m;
    uint8_t oldSREG = SREG;

    // disable interrupts while we read timer0_millis or we might get an
    // inconsistent value (e.g. in the middle of a write to timer0_millis)
    cli();
    m = timer0_millis;
    SREG = oldSREG;

    return m;
}

/*
 * micros with uint64_t takes 66.6us (1067 cycles)
 * max time = 2^64us = 584542 years
 * micros with uint32_t takes 3.5us (58 cycles)
 * max time = 2^32us = 1.19hours
 */
uint32_t micros()
{
    uint32_t m;
    uint8_t oldSREG = SREG, t;

    cli();
    m = timer0_overflow_count;
    t = TCNT0;

    if ((TIFR0 & _BV(TOV0)) && (t < 255))
        m++;

    SREG = oldSREG;

    return ((m << 8) + t) * (64 / clockCyclesPerMicrosecond());
}

void initMillis()
{
    TCCR0B |= _BV(CS01) | _BV(CS00);
    TIMSK0 |= _BV(TOIE0);
    sei();
}