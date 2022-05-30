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
    // OC4B = D7
    // OC3B = D2

    // Wave mode fast PWM 8bit (non-inverting)
    TCCR3A |= _BV(WGM30) | _BV(COM3B1);
    TCCR3B |= _BV(WGM32);

    // pre-scaler 1
    TCCR3B |= _BV(CS30);

    OCR3B = 10;
    TCNT3 = 0;

    // Wave mode fast PWM 8bit (non-inverting)
    TCCR4A |= _BV(WGM40) | _BV(COM4B1);
    TCCR4B |= _BV(WGM42);

    // pre-scaler 1
    TCCR4B |= _BV(CS40);

    OCR4B = 10;
    TCNT4 = 0;

    while (1) {
        continue;
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
