#include "lib/basicio.h"
#include "lib/dcmotor.h"
#include "lib/debug.h"
#include <avr/interrupt.h>
#include <avr/io.h>

DcMotor rightMotor = {
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

DcMotor leftMotor = {
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

Output signalLeds = {
    .pDdr = &DDRC,
    .pPort = &PORTC,
    .pin = PC1, // D36
    .type = LED_TYPE_GROUND,
};

Output enableA = {
    .pDdr = &DDRE,
    .pPort = &PORTE,
    .pin = PE4, // D2
    .type = LED_TYPE_GROUND,
};

Output enableB = {
    .pDdr = &DDRH,
    .pPort = &PORTH,
    .pin = PH4, // D7
    .type = LED_TYPE_GROUND,
};

Input automaticButton = {
    .pDdr = &DDRC,
    .pPort = &PORTC,
    .pPin = &PINC,
    .pin = PC7, // D30
    .type = BUTTON_TYPE_PULLUP,
};

Input followButton = {
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
