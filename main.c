// don't forget to put all the include files here.
#include "lib/PID.h"
#include "lib/basicio.h"
#include "lib/dcmotor.h"
#include "lib/debug.h"
#include "lib/millis.h"
#include "lib/ultrasoon.h"
#include <avr/interrupt.h>
#include <avr/io.h>

#define MIN_SPEED 10

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
    uint32_t lastMillis = 0;
    uint8_t ledState = 0;
    uint8_t speed = 0;
    double output = 0;

    while (1) {
        ultrasoon_setDistance(&frontUltrasoon);
        ultrasoon_setDistance(&leftUltrasoon);
        ultrasoon_setDistance(&rightUltrasoon);

        output = PID_computed_custom(&rideStraightPID, rightUltrasoon.distance);

        if (basic_readInput(automaticButton)) {
            if (basic_readInput(detectLeft) || basic_readInput(detectRight)) { // ToDo: time out
                basic_outputMode(signalLeds, HIGH);
                dcmotor_pwm_instruction(leftMotor, 0);
                dcmotor_pwm_instruction(rightMotor, 0);
                // ToDo: wait 5 seconds
            } else if (frontUltrasoon.distance > 20) {
                speed = 40;
                basic_outputMode(signalLeds, LOW);
                dcmotor_pwm_instruction(leftMotor, output < speed - MIN_SPEED ? speed - output : MIN_SPEED);
                dcmotor_pwm_instruction(rightMotor, speed);
            } else if (frontUltrasoon.distance > 10) {
                basic_outputMode(signalLeds, LOW);
                dcmotor_pwm_instruction(leftMotor, output < speed - MIN_SPEED ? speed - output : MIN_SPEED);
                dcmotor_pwm_instruction(rightMotor, speed);
            } else {
                if (lastMillis + 100 < millis()) {
                    ledState = !ledState;
                    lastMillis = millis();
                }
                if (ledState) {
                    basic_outputMode(signalLeds, HIGH);
                } else {
                    basic_outputMode(signalLeds, LOW);
                }
                dcmotor_pwm_instruction(leftMotor, 0);
                dcmotor_pwm_instruction(rightMotor, 0);
            }
        } else if (basic_readInput(followButton)) {
            uint8_t _detectFrontLeft = basic_readInput(detectFrontLeft);
            uint8_t _detectFrontRight = basic_readInput(detectFrontRight);
            speed = 50;

            if (!_detectFrontLeft && !_detectFrontRight) {
                dcmotor_pwm_instruction(leftMotor, 0);
                dcmotor_pwm_instruction(rightMotor, 0);
            } else if (_detectFrontLeft && !_detectFrontRight) {
                dcmotor_pwm_instruction(leftMotor, 0);
                dcmotor_pwm_instruction(rightMotor, speed);
            } else if (!_detectFrontLeft && _detectFrontRight) {
                dcmotor_pwm_instruction(leftMotor, speed);
                dcmotor_pwm_instruction(rightMotor, 0);
            } else if (_detectFrontLeft && _detectFrontRight) {
                if (frontUltrasoon.distance > 10) {
                    basic_outputMode(signalLeds, LOW);
                    dcmotor_pwm_instruction(leftMotor, speed);
                    dcmotor_pwm_instruction(rightMotor, speed);
                } else if (frontUltrasoon.distance > 5) {
                    speed = 30;
                    basic_outputMode(signalLeds, LOW);
                    dcmotor_pwm_instruction(leftMotor, speed);
                    dcmotor_pwm_instruction(rightMotor, speed);
                } else {
                    if (lastMillis + 100 < millis()) {
                        ledState = !ledState;
                        lastMillis = millis();
                    }
                    if (ledState) {
                        basic_outputMode(signalLeds, HIGH);
                    } else {
                        basic_outputMode(signalLeds, LOW);
                    }
                    dcmotor_pwm_instruction(leftMotor, 0);
                    dcmotor_pwm_instruction(rightMotor, 0);
                }
            }
        } else {
            dcmotor_pwm_instruction(leftMotor, 0);
            dcmotor_pwm_instruction(rightMotor, 0);
        }
    }
}
