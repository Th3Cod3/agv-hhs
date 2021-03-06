#ifndef BASICIO_H
#define BASICIO_H

#include <avr/io.h>
#include <inttypes.h>

#define TYPE_LOGIC_HIGH 0
#define TYPE_LOGIC_LOW 1

#define LED_TYPE_GROUND TYPE_LOGIC_HIGH
#define LED_TYPE_VCC TYPE_LOGIC_LOW

#define BUTTON_TYPE_DISABLE TYPE_LOGIC_HIGH
#define BUTTON_TYPE_PULLUP TYPE_LOGIC_LOW

#define LOW 0
#define HIGH 1

#define LED_LOW LOW
#define LED_HIGH HIGH

#define BASIC_DDR 0
#define BASIC_PORT 1
#define BASIC_PIN 2

#define BASIC_NULL 0
#define BASIC_A 1
#define BASIC_B 2
#define BASIC_C 3
#define BASIC_D 4
#define BASIC_E 5
#define BASIC_F 6
#define BASIC_G 7
#define BASIC_H 8
#define BASIC_J 9
#define BASIC_K 10
#define BASIC_L 11

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
