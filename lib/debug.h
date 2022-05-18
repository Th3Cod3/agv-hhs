#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG_EN
#include <util/delay.h>
#ifdef __AVR_ATmega2560__
#define DEBUG_DDR DDRB
#define DEBUG_PORT PORTB
#define DEBUG_PIN PB7 // pin D13
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#define DEBUG_DDR DDRB
#define DEBUG_PORT PORTB
#define DEBUG_PIN PB1 // pin TX/D0
#endif // DEBUG
#define DEBUG_SIGNAL(delay)       \
    DEBUG_DDR |= _BV(DEBUG_PIN);  \
    DEBUG_PORT ^= _BV(DEBUG_PIN); \
    _delay_us((int)(delay));      \
    DEBUG_PORT ^= _BV(DEBUG_PIN);
#else
#define DEBUG_SIGNAL(delay)
#endif

#endif // DEBUG