#include "pid.h"
#include <cmath> // fabs

PidController::PidController(const double P_, const double I_, const double D_)
    : integral(0), P(P_), I(I_), D(D_) {}

double PidController::calculate(const double measurement, const double setpoint) const {

    // The calculate function feels like it should be const; it is only
    // calculating and not actuating anything. However, it is technically not
    // const as it is modifying its internal state; thus, we are making it const
    // and const_casting it.
    auto that = const_cast<PidController *>(this);
    double error = setpoint - measurement;
    that->integral = integral + error;


    const double epsilon = 0.005;
    bool reachedSetPoint = (fabs(error) <= epsilon);

    // Trying to prevent integral wind-up, When the error is greater than the
    // setPoint, we are worried that our integral gain will be too great so
    // reset the integral term to 0. This is especially important if the proportional gain is too small compared to the integral gain.
    bool errorIsTooLarge = (fabs(error) > fabs(setpoint));
    if (reachedSetPoint || errorIsTooLarge) {
        that->integral = 0;
    }

    double derivative = error - previousError;
    that->previousError = error;


    double power = error * P + integral * I + derivative * D;
    return power;
}
