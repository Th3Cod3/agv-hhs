#include <avr/io.h>
#include "basicio.h"
#include "dcmotor.h"

void dcmotor_instruction(DcMotor motor, char instruction)
{
    if (dcmotor_end_limit(motor) && instruction != DCMOTOR_STOP){
        return dcmotor_instruction(motor, DCMOTOR_STOP);
    }

    switch (instruction)
    {
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
void dcmotor_init(DcMotor motor)
{
    basic_initInput(motor.limit);
    basic_initOutput(motor.pinA);
    basic_initOutput(motor.pinB);
    dcmotor_instruction(motor, DCMOTOR_STOP);
}

uint8_t dcmotor_end_limit(DcMotor motor)
{
    return basic_readInput(motor.limit);
}
