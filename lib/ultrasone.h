#ifndef ULTRASONE_H
#define ULTRASONE_H

#include "basicio.h"

typedef struct {
    output_t trigger;
    input_t echo;
} ultrasone_t;

void ultrasone_init(ultrasone_t ultrasone);

#endif
