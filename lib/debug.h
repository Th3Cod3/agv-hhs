#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG_EN
#include <util/delay.h>
#ifdef __AVR_ATmega2560__
#define DEBUG_DDR DDRB
#define DEBUG_PORT PORTB
#define DEBUG_PIN PB6 // pin D12
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#define DEBUG_DDR DDRB
#define DEBUG_PORT PORTB
#define DEBUG_PIN PB1 // pin TX/D0
#endif // Arduino Uno/Nano
#define INIT_DEBUG_SIGNAL DEBUG_DDR |= _BV(DEBUG_PIN);
#define DEBUG_DELAY(delay)        \
    DEBUG_PORT ^= _BV(DEBUG_PIN); \
    _delay_us((double)(delay));      \
    DEBUG_PORT ^= _BV(DEBUG_PIN);
#define DEBUG_SIGNAL              \
    DEBUG_PORT ^= _BV(DEBUG_PIN); \
    DEBUG_PORT ^= _BV(DEBUG_PIN);
#else
#define DEBUG_SIGNAL
#define DEBUG_DELAY(delay)
#endif

#endif // DEBUG