#include "lib/basicio.h"
#include "lib/dcmotor.h"
#include "lib/debug.h"
#include <avr/interrupt.h>
#include <avr/io.h>

dc_motor_t rightMotor = {
    .pinA = {
        .pDdr = &DDRE,
        .pPort = &PORTE,
        .pin = PE5, // D3
        .type = TYPE_LOGIC_HIGH,
    },
    .pinB = {
        .pDdr = &DDRG,
        .pPort = &PORTG,
        .pin = PG5, // D4
        .type = TYPE_LOGIC_HIGH,
    },
    .limit = DEFAULT_INPUT,
};

dc_motor_t leftMotor = {
    .pinA = {
        .pDdr = &DDRH,
        .pPort = &PORTH,
        .pin = PH3, // D6
        .type = TYPE_LOGIC_HIGH,
    },
    .pinB = {
        .pDdr = &DDRE,
        .pPort = &PORTE,
        .pin = PE3, // D5
        .type = TYPE_LOGIC_HIGH,
    },
    .limit = DEFAULT_INPUT,
};

output_t signalLeds = {
    .pDdr = &DDRC,
    .pPort = &PORTC,
    .pin = PC1, // D36
    .type = LED_TYPE_GROUND,
};

output_t enableA = {
    .pDdr = &DDRE,
    .pPort = &PORTE,
    .pin = PE4, // D2
    .type = LED_TYPE_GROUND,
};

output_t enableB = {
    .pDdr = &DDRH,
    .pPort = &PORTH,
    .pin = PH4, // D7
    .type = LED_TYPE_GROUND,
};

input_t automaticButton = {
    .pDdr = &DDRC,
    .pPort = &PORTC,
    .pPin = &PINC,
    .pin = PC7, // D30
    .type = BUTTON_TYPE_PULLUP,
};

input_t followButton = {
    .pDdr = &DDRC,
    .pPort = &PORTC,
    .pPin = &PINC,
    .pin = PC6, // D31
    .type = BUTTON_TYPE_PULLUP,
};

int main(void)
{
    dcmotor_init(rightMotor);
    dcmotor_init(leftMotor);
    basic_initInput(automaticButton);
    basic_initInput(followButton);
    basic_initOutput(signalLeds);
    basic_outputMode(enableA, HIGH);
    basic_outputMode(enableB, HIGH);

    while (1) {
        if (basic_readInput(automaticButton)) {
            basic_outputMode(signalLeds, LOW);
            dcmotor_instruction(leftMotor, DCMOTOR_FORWARD);
            dcmotor_instruction(rightMotor, DCMOTOR_FORWARD);
        } else if (basic_readInput(followButton)) {
            basic_outputMode(signalLeds, LOW);
            dcmotor_instruction(leftMotor, DCMOTOR_BACKWARD);
            dcmotor_instruction(rightMotor, DCMOTOR_BACKWARD);
        } else {
            basic_outputMode(signalLeds, HIGH);
            dcmotor_instruction(leftMotor, DCMOTOR_STOP);
            dcmotor_instruction(rightMotor, DCMOTOR_STOP);
        }
    }
}
