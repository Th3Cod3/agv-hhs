#ifndef BASICIO_H
#define BASICIO_H

#include <avr/io.h>
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

#define BASIC_DDR 0
#define BASIC_PORT 1
#define BASIC_PIN 2

#define BASIC_A 0
#define BASIC_B 1
#define BASIC_C 2
#define BASIC_D 3
#define BASIC_E 4
#define BASIC_F 5
#define BASIC_G 6
#define BASIC_H 7
#define BASIC_J 8
#define BASIC_K 9
#define BASIC_L 10

#define DEFAULT_OUTPUT                 \
    {                                  \
        .port = 0, .pin = 0, .type = 0 \
    }
#define DEFAULT_INPUT DEFAULT_OUTPUT

typedef struct output_t {
    uint8_t port;
    uint8_t pin;
    uint8_t type;
} output_t;

typedef struct input_t {
    uint8_t port;
    uint8_t pin;
    uint8_t type;
} input_t;

extern volatile const uint8_t* ports[][3];

void basic_initOutput(output_t output);
void basic_initInput(input_t input);
void basic_outputMode(output_t output, uint8_t mode);
uint8_t basic_readInput(input_t output);
uint8_t* basic_portRegister(uint8_t portNumber, uint8_t registerType);

#endif
