#include "basicio.h"

volatile const uint8_t* ports[][3] = {
    { 0, 0, 0 },
    { &DDRA, &PORTA, &PINA },
    { &DDRB, &PORTB, &PINB },
    { &DDRC, &PORTC, &PINC },
    { &DDRD, &PORTD, &PIND },
    { &DDRE, &PORTE, &PINE },
    { &DDRF, &PORTF, &PINF },
    { &DDRG, &PORTG, &PING },
    { &DDRH, &PORTH, &PINH },
    { &DDRJ, &PORTJ, &PINJ },
    { &DDRK, &PORTK, &PINK },
    { &DDRL, &PORTL, &PINL },
};

void basic_outputMode(output_t output, uint8_t mode)
{
    uint8_t* pPort = (basic_portRegister(output.port, BASIC_PORT));

    if (mode == LED_HIGH && output.type == LED_TYPE_GROUND) {
        *pPort |= _BV(output.pin);
    } else if (mode == LED_HIGH && output.type == LED_TYPE_VCC) {
        *pPort &= ~_BV(output.pin);
    } else if (mode == LED_LOW && output.type == LED_TYPE_GROUND) {
        *pPort &= ~_BV(output.pin);
    } else if (mode == LED_LOW && output.type == LED_TYPE_VCC) {
        *pPort |= _BV(output.pin);
    }
}

void basic_initOutput(output_t output)
{
    if (!output.port) {
        return;
    }

    uint8_t* pDdr = (basic_portRegister(output.port, BASIC_DDR));

    *pDdr |= _BV(output.pin); // INPUT
}

void basic_initInput(input_t input)
{
    if (!input.port) {
        return;
    }

    uint8_t* pDdr = (basic_portRegister(input.port, BASIC_DDR));
    uint8_t* pPort = (basic_portRegister(input.port, BASIC_PORT));

    *pDdr &= ~_BV(input.pin); // INPUT

    if (input.type == BUTTON_TYPE_PULLUP) {
        *pPort |= _BV(input.pin); // enable internal pullup
    } else if (input.type == BUTTON_TYPE_DISABLE) {
        *pPort &= ~_BV(input.pin); // disable internal pullup
    }
}

uint8_t basic_readInput(input_t input)
{
    uint8_t* pPin = (basic_portRegister(input.port, BASIC_PIN));

    if (input.type == BUTTON_TYPE_PULLUP) {
        return !(*pPin & _BV(input.pin));
    }

    return (*pPin & _BV(input.pin));
}

uint8_t* basic_portRegister(uint8_t portNumber, uint8_t registerType)
{
    return (uint8_t*)ports[portNumber][registerType];
}
