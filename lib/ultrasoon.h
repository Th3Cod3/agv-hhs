#ifndef ULTRASOON_H
#define ULTRASOON_H

#include "basicio.h"

typedef struct ultrasoon_t {
    output_t trigger;
    input_t echo;
} ultrasoon_t;

void ultrasoon_init(ultrasoon_t ultrasoon);

#endif
