// https://www.teachmemicro.com/arduino-pid-control-tutorial/
#ifndef PID_H
#define PID_H
#include <inttypes.h>

typedef struct PID_t {
    double kp;
    double ki;
    double kd;
    double error;
    double cumError;
    double rateError;
    double lastError;
    double output;
    double setPoint;
    uint32_t currentTime;
    uint32_t previousTime;
    double elapsedTime;
} PID_t;

double PID_calculateOutput(PID_t* pid);
double PID_computed(PID_t* pid, double distance);

#endif