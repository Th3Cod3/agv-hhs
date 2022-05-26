#include "lib/basicio.h"
#include "lib/dcmotor.h"
#include "lib/debug.h"
#include "lib/ultrasoon.h"
#include <avr/interrupt.h>
#include <avr/io.h>

extern pwm_dc_motor_t rightMotor;
extern pwm_dc_motor_t leftMotor;
extern output_t signalLeds;
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

    while (1) {
        DEBUG_SIGNAL
        ultrasoon_setDistance(&frontUltrasoon);
        DEBUG_SIGNAL

        if (basic_readInput(automaticButton) && frontUltrasoon.distance > 20) {
            basic_outputMode(signalLeds, LOW);
            dcmotor_pwm_instruction(leftMotor, 100);
            dcmotor_pwm_instruction(rightMotor, 100);
        } else if (basic_readInput(followButton) && frontUltrasoon.distance > 20) {
            basic_outputMode(signalLeds, LOW);
            dcmotor_pwm_instruction(leftMotor, -100);
            dcmotor_pwm_instruction(rightMotor, -100);
        } else {
            basic_outputMode(signalLeds, HIGH);
            dcmotor_pwm_instruction(leftMotor, 0);
            dcmotor_pwm_instruction(rightMotor, 0);
        }
    }
}
