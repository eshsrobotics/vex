#ifndef PID__H__
#define PID__H__
class PidController {
    public:
        /**
         * @param P Proportional: The objective is to give a large amount of power when
         * there is a long way to go, but only a small amount of power when you'are
         * close to your setpoint.
         * @param I Integral: As you approach your setpoint, it speeds you up.
         * @param D Derivative: Looks at the rate of change of error (how far away are
         * you from setpoint). It slows you down to prevent overshooting.
         */
        PidController(const double P, const double I, const double D);

        /**
         * Calculates the next output from the PID controller.
         *
         * @param measurement The current, unitless measurement that you are getting
         * from your sensor e.g. gyros, encoders, accelerometers.
         * @param setpoint Our desired value of measurement before we stop applying
         * power.
         * @return Returns the power that the system should be apply next to get the
         * measurement closer to setpoint.
         *
         */
        double calculate(const double measurement, const double setpoint) const;

    private:
        // The accumulated error terms over time
        double integral;

        // The error from previous call to calculate. We will use this to
        // calculate the derivative term.
        double previousError;

        const double P;
        const double I;
        const double D;
};


#endif // (ifndef PID__H__)
