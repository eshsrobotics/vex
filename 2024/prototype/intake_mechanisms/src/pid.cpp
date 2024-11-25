#include "pid.h"
#include <cmath> // fabs

PidController::PidController(const double P_, const double I_, const double D_) 
    : integral(0), P(P_), I(I_), D(D_) {}

double PidController::calculate(const double measurement, const double setpoint) {
    double error = setpoint - measurement;
    integral = integral + error;
    
    
    const double epsilon = 0.005;
    bool reachedSetPoint = (fabs(error) <= epsilon);

    // Trying to prevent integral wind-up, 
    // When the error is greater than the setPoint, we are worried
    bool errorIsTooLarge = (fabs(error) > fabs(setpoint));
    if (reachedSetPoint || errorIsTooLarge) {
        integral = 0;
    }



    previousError = error;

    // This code is not complete. It should be replaced with the actual PID
    // formula. For now, we just want to build the code.
    return 0;
}