#include "lib/PID.h"
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
extern PID_t rideStraightPID;
void initGlobal();

int main(void)
{
    initGlobal();
    uint8_t speed = 0;
    double output = 0;

    while (1) {
        ultrasoon_setDistance(&frontUltrasoon);
        ultrasoon_setDistance(&leftUltrasoon);
        ultrasoon_setDistance(&rightUltrasoon);

        output = PID_computed(&rideStraightPID, rightUltrasoon.distance);

        if (basic_readInput(automaticButton)) {
            basic_outputMode(signalLeds, LOW);
            dcmotor_pwm_instruction(leftMotor, 0);
            dcmotor_pwm_instruction(rightMotor, 0);
        } else if (frontUltrasoon.distance > 20) {
            speed = 40;
            basic_outputMode(signalLeds, LOW);
            dcmotor_pwm_instruction(leftMotor, speed - output);
            dcmotor_pwm_instruction(rightMotor, speed);
        } else if (frontUltrasoon.distance > 10) {
            speed = 20;
            basic_outputMode(signalLeds, LOW);
            dcmotor_pwm_instruction(leftMotor, speed - output);
            dcmotor_pwm_instruction(rightMotor, speed);
        } else {
            basic_outputMode(signalLeds, HIGH);
            dcmotor_pwm_instruction(leftMotor, 0);
            dcmotor_pwm_instruction(rightMotor, 0);
        }
    }
}
