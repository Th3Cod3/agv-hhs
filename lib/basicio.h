#ifndef BASICIO_H
#define BASICIO_H

#include <inttypes.h>

#define LED_TYPE_GROUND 0
#define LED_TYPE_VCC 1

#define TYPE_LOGIC_HIGH 0
#define TYPE_LOGIC_LOW 1

#define BUTTON_TYPE_PULLDOWN 0
#define BUTTON_TYPE_PULLUP 1

#define LED_LOW 0
#define LED_HIGH 1

#define LOW 0
#define HIGH 1

#define DEFAULT_OUTPUT                             \
    {                                              \
        .pDdr = 0, .pPort = 0, .pin = 0, .type = 0 \
    }
#define DEFAULT_INPUT                                         \
    {                                                         \
        .pDdr = 0, .pPort = 0, .pPin = 0, .pin = 0, .type = 0 \
    }

typedef struct {
    volatile uint8_t* pDdr;
    volatile uint8_t* pPort;
    uint8_t pin;
    uint8_t type;
} output_t;

typedef struct {
    volatile uint8_t* pDdr;
    volatile uint8_t* pPin;
    volatile uint8_t* pPort;
    uint8_t pin;
    uint8_t type;
} input_t;

void basic_initOutput(output_t output);
void basic_initInput(input_t input);
void basic_outputMode(output_t output, uint8_t mode);
uint8_t basic_readInput(input_t output);

#endif
