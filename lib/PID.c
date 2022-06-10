// https://www.teachmemicro.com/arduino-pid-control-tutorial/

#include "PID.h"
#include "millis.h"

double PID_calculateOutput(PID_t* pid)
{
    return pid->kp * pid->error + pid->ki * pid->cumError + pid->kd * pid->rateError;
}

double PID_computed(PID_t* pid, double distance)
{
    pid->currentTime = millis(); // get current time
    pid->elapsedTime = (double)(pid->currentTime - pid->previousTime); // compute time elapsed from previous computation

    pid->error = pid->setPoint - distance; // determine error
    pid->cumError += pid->error * pid->elapsedTime; // compute integral
    pid->rateError = (pid->error - pid->lastError) / pid->elapsedTime; // compute derivative

    double output = PID_calculateOutput(pid); // PID output

    pid->lastError = pid->error; // remember current error
    pid->previousTime = pid->currentTime; // remember current time

    return output; // have function return the PID output
}