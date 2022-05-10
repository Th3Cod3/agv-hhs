#ifndef DCMOTOR_H
#define DCMOTOR_H

#include <inttypes.h>
#include "basicio.h"

#define DCMOTOR_STOP 0
#define DCMOTOR_FORWARD 1
#define DCMOTOR_BACKWARD 2

typedef struct
{
    Output pinA;
    Output pinB;
    Input limit;
} DcMotor;

void dcmotor_init(DcMotor motor);
void dcmotor_instruction(DcMotor motor, char instruction);
uint8_t dcmotor_end_limit(DcMotor motor);

#endif
