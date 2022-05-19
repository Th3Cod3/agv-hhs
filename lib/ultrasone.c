#include "ultrasone.h"
#include <avr/io.h>

/*
 * init a motor
 */
void ultrasone_init(ultrasone_t ultrasone)
{
    basic_initInput(ultrasone.echo);
    basic_initOutput(ultrasone.trigger);
}

