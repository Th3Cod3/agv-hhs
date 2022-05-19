#include "lib/basicio.h"
#include "lib/dcmotor.h"
#include "lib/ultrasone.h"
#include "lib/debug.h"
#include <avr/interrupt.h>
#include <avr/io.h>

dc_motor_t rightMotor = {
    .pinA = {
        .port = BASIC_E,
        .pin = PE5, // D3
        .type = TYPE_LOGIC_HIGH,
    },
    .pinB = {
        .port = BASIC_G,
        .pin = PG5, // D4
        .type = TYPE_LOGIC_HIGH,
    },
    .limit = DEFAULT_INPUT,
};

dc_motor_t leftMotor = {
    .pinA = {
        .port = BASIC_H,
        .pin = PH3, // D6
        .type = TYPE_LOGIC_HIGH,
    },
    .pinB = {
        .port = BASIC_E,
        .pin = PE3, // D5
        .type = TYPE_LOGIC_HIGH,
    },
    .limit = DEFAULT_INPUT,
};

output_t signalLeds = {
    .port = BASIC_C,
    .pin = PC1, // D36
    .type = LED_TYPE_GROUND,
};

output_t enableA = {
    .port = BASIC_E,
    .pin = PE4, // D2
    .type = LED_TYPE_GROUND,
};

output_t enableB = {
    .port = BASIC_H,
    .pin = PH4, // D7
    .type = LED_TYPE_GROUND,
};

input_t automaticButton = {
    .port = BASIC_C,
    .pin = PC7, // D30
    .type = BUTTON_TYPE_PULLUP,
};

input_t followButton = {
    .port = BASIC_C,
    .pin = PC6, // D31
    .type = BUTTON_TYPE_PULLUP,
};

ultrasone_t rightUltrasone = {
    .echo = {
        .port = BASIC_C,
        .pin = PC6, // D31
        .type = BUTTON_TYPE_PULLUP,
    },
    .trigger = {
        .port = BASIC_H,
        .pin = PH4, // D7
        .type = LED_TYPE_GROUND,
    }
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
