#ifndef ULTRASOON_H
#define ULTRASOON_H

#include "basicio.h"

#define MAX_DISTANCE 50 // cm
#define SPEED_OF_SOUND 0.0343 // cm/us
#define ULTRASOON_TIMEOUT (MAX_DISTANCE * 2 / SPEED_OF_SOUND) // us

typedef struct ultrasoon_t {
    output_t trigger;
    input_t echo;
    uint32_t start_time;
    uint32_t end_time;
    uint16_t distance;
} ultrasoon_t;

void ultrasoon_init(ultrasoon_t ultrasoon);
void ultrasoon_setDistance(ultrasoon_t* ultrasoon);

#endif
