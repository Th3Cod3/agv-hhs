#ifndef DCMOTOR_H
#define DCMOTOR_H

#include <inttypes.h>

#include "basicio.h"

#define DCMOTOR_STOP 0
#define DCMOTOR_FORWARD 1
#define DCMOTOR_BACKWARD 2

#define DEFAULT_DCMOTOR           \
    {                             \
        .pinA = DEFAULT_OUTPUT,   \
        .pinB = DEFAULT_OUTPUT,   \
        .enable = DEFAULT_OUTPUT, \
        .limit = DEFAULT_INPUT    \
    }

typedef struct dc_motor_t {
    output_t pinA;
    output_t pinB;
    input_t limit;
} dc_motor_t;

typedef struct pwm_dc_motor_t {
    dc_motor_t motor;
    output_t enable;
    volatile int16_t* OCR;
} pwm_dc_motor_t;

void dcmotor_init(dc_motor_t motor);
void dcmotor_instruction(dc_motor_t motor, uint8_t instruction);
uint8_t dcmotor_end_limit(dc_motor_t motor);

void dcmotor_pwm_init(pwm_dc_motor_t motor);
void dcmotor_pwm_instruction(pwm_dc_motor_t motor, int16_t speed);

#endif
