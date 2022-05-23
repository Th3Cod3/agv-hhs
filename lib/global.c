#include "basicio.h"
#include "dcmotor.h"
#include "debug.h"
#include "millis.h"
#include "ultrasoon.h"
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
    .type = TYPE_LOGIC_HIGH,
};

output_t enableB = {
    .port = BASIC_H,
    .pin = PH4, // D7
    .type = TYPE_LOGIC_HIGH,
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

input_t detectLeft = {
    .port = BASIC_F,
    .pin = PF1, // A1
    .type = TYPE_LOGIC_LOW,
};

input_t detectRight = {
    .port = BASIC_F,
    .pin = PF2, // A2
    .type = TYPE_LOGIC_LOW,
};

input_t detectFrontLeft = {
    .port = BASIC_F,
    .pin = PF5, // A5
    .type = TYPE_LOGIC_LOW,
};

input_t detectFrontRight = {
    .port = BASIC_F,
    .pin = PF6, // A6
    .type = TYPE_LOGIC_LOW,
};

ultrasoon_t leftUltrasoon = {
    .echo = {
        .port = BASIC_A,
        .pin = PA0, // D22
        .type = TYPE_LOGIC_HIGH,
    },
    .trigger = {
        .port = BASIC_A,
        .pin = PA1, // D23
        .type = TYPE_LOGIC_LOW,
    }
};

ultrasoon_t rightUltrasoon = {
    .echo = {
        .port = BASIC_A,
        .pin = PA2, // D24
        .type = TYPE_LOGIC_HIGH,
    },
    .trigger = {
        .port = BASIC_A,
        .pin = PA3, // D25
        .type = TYPE_LOGIC_LOW,
    }
};

ultrasoon_t frontUltrasoon = {
    .echo = {
        .port = BASIC_A,
        .pin = PA4, // D26
        .type = TYPE_LOGIC_HIGH,
    },
    .trigger = {
        .port = BASIC_A,
        .pin = PA5, // D27
        .type = TYPE_LOGIC_LOW,
    }
};

void initGlobal()
{
    INIT_DEBUG_SIGNAL
    initMillis();

    // init output
    basic_initOutput(signalLeds);
    basic_initOutput(enableA);
    basic_initOutput(enableB);

    // init input
    basic_initInput(automaticButton);
    basic_initInput(followButton);
    basic_initInput(detectLeft);
    basic_initInput(detectRight);
    basic_initInput(detectFrontLeft);
    basic_initInput(detectFrontRight);

    // init ultrasoon
    ultrasoon_init(leftUltrasoon);
    ultrasoon_init(rightUltrasoon);
    ultrasoon_init(frontUltrasoon);

    // init dc motor
    dcmotor_init(rightMotor);
    dcmotor_init(leftMotor);
}