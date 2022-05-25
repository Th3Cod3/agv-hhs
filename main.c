#include "lib/basicio.h"
#include "lib/dcmotor.h"
#include "lib/debug.h"
#include "lib/ultrasoon.h"
#include <avr/interrupt.h>
#include <avr/io.h>

extern dc_motor_t rightMotor;
extern dc_motor_t leftMotor;
extern output_t signalLeds;
extern output_t enableA;
extern output_t enableB;
extern input_t automaticButton;
extern input_t followButton;
extern input_t detectLeft;
extern input_t detectRight;
extern input_t detectFrontLeft;
extern input_t detectFrontRight;
extern ultrasoon_t leftUltrasoon;
extern ultrasoon_t rightUltrasoon;
extern ultrasoon_t frontUltrasoon;
void initGlobal();

int main(void)
{
    initGlobal();
    basic_outputMode(enableA, HIGH);
    basic_outputMode(enableB, HIGH);

    while (1) {
        DEBUG_SIGNAL
        ultrasoon_setDistance(&frontUltrasoon);
        DEBUG_DELAY(frontUltrasoon.distance)
        continue;

        if (basic_readInput(automaticButton) && frontUltrasoon.distance > 10) {
            basic_outputMode(signalLeds, LOW);
            dcmotor_instruction(leftMotor, DCMOTOR_FORWARD);
            dcmotor_instruction(rightMotor, DCMOTOR_FORWARD);
        } else if (basic_readInput(followButton) && frontUltrasoon.distance > 10) {
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
