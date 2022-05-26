#include "dcmotor.h"
#include "basicio.h"
#include <avr/io.h>

void dcmotor_instruction(dc_motor_t motor, uint8_t instruction)
{
    if (!motor.limit.port && dcmotor_end_limit(motor) && instruction != DCMOTOR_STOP) {
        return dcmotor_instruction(motor, DCMOTOR_STOP);
    }

    switch (instruction) {
    case DCMOTOR_FORWARD:
        basic_outputMode(motor.pinA, HIGH);
        basic_outputMode(motor.pinB, LOW);
        return;

    case DCMOTOR_BACKWARD:
        basic_outputMode(motor.pinA, LOW);
        basic_outputMode(motor.pinB, HIGH);
        return;

    case DCMOTOR_STOP:
        basic_outputMode(motor.pinA, LOW);
        basic_outputMode(motor.pinB, LOW);
        return;
    }
}

/*
 * init a motor
 */
void dcmotor_init(dc_motor_t motor)
{
    basic_initInput(motor.limit);
    basic_initOutput(motor.pinA);
    basic_initOutput(motor.pinB);
    basic_initOutput(motor.pinB);
    dcmotor_instruction(motor, DCMOTOR_STOP);
}

/*
 * enable_pwm and init motor
 */
void dcmotor_pwm_init(pwm_dc_motor_t motor)
{
    dcmotor_init(motor.motor);
    basic_initOutput(motor.enable);
    dcmotor_pwm_instruction(motor, 0);
}

void dcmotor_pwm_instruction(pwm_dc_motor_t motor, int16_t speed)
{
    if (speed > 100 || speed < -100) {
        basic_outputMode(motor.enable, HIGH);
    } else if (!speed) {
        basic_outputMode(motor.enable, LOW);
        dcmotor_instruction(motor.motor, DCMOTOR_STOP);
        return;
    }

    if (speed > 0) {
        dcmotor_instruction(motor.motor, DCMOTOR_FORWARD);
    } else if (speed < 0) {
        dcmotor_instruction(motor.motor, DCMOTOR_BACKWARD);
    }
}

uint8_t dcmotor_end_limit(dc_motor_t motor)
{
    return basic_readInput(motor.limit);
}
