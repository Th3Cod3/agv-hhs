#include "basicio.h"
#include <avr/io.h>

void basic_outputMode(Output output, uint8_t mode)
{
    if (mode == LED_HIGH && output.type == LED_TYPE_GROUND) {
        *output.pPort |= _BV(output.pin);
    } else if (mode == LED_HIGH && output.type == LED_TYPE_VCC) {
        *output.pPort &= ~_BV(output.pin);
    } else if (mode == LED_LOW && output.type == LED_TYPE_GROUND) {
        *output.pPort &= ~_BV(output.pin);
    } else if (mode == LED_LOW && output.type == LED_TYPE_VCC) {
        *output.pPort |= _BV(output.pin);
    }
}

void basic_initOutput(Output output)
{
    *output.pDdr |= _BV(output.pin); // INPUT
}

void basic_initInput(Input input)
{
    *input.pDdr &= ~_BV(input.pin); // INPUT

    if (input.type == BUTTON_TYPE_PULLUP) {
        *input.pPort |= _BV(input.pin); // PULLUP
    } else if (input.type == BUTTON_TYPE_PULLDOWN) {
        *input.pPort &= ~_BV(input.pin); // PULLDOWN
    }
}

uint8_t basic_readInput(Input input)
{
    if (input.type == BUTTON_TYPE_PULLUP) {
        return !(*input.pPin & _BV(input.pin));
    }

    return (*input.pPin & _BV(input.pin));
}
