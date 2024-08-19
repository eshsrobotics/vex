// PROTOTYPES.H -- Concrete classes for all VEX drive prototype robots.
#ifndef __PROTOTYPE_H_INCLUDED__
#define __PROTOTYPE_H_INCLUDED__

#include "vex.h"
#include <vector>

#include "Idrive.h"
#include "Iintake.h"
#include "Ilift.h"

class FlywheelPrototype : public Idrive, Iintake {
    public:
        /**
         * Construct a flywheel prototype robot.
         *
         * The motor groups passed into this constructor require careful
         * consideration.  It is up to the caller -- to YOU -- to ensure that
         * all the motors turn in the correct direction (including calling
         * setReverse() as needed) so that nothing is damaged when the motor
         * group's velocity is set.
         *
         * @param left   The motor group handling all motors on the left side of
         *               the drive.  Setting its velocity to a positive value
         *               should cause the left side of the robot to drive
         *               forward.
         * @param right  The motor group handling all motors on the right side
         *               of the drive.  Setting its velocity to a positive value
         *               should cause the right side of the robot to drive
         *               forward.
         * @param intake_group The flywheel motors. A positive velocity means that the
         *               wheels are intaking. A negative velocity means that the wheels are
         *               outtaking. The two motors must spin in opposite directions for the
         *               game piece to go up. This will be achieved through specific wiring.
         */
        FlywheelPrototype(const vex::motor_group& left, const vex::motor_group& right,
                          const vex::motor_group& intake_group);

        /**
         * Drive the robot at the given speeds.
         *
         * A fwd parameter of +1.0 means full speed forward.  -1.0 is full speed reverse.
         * A turn parameters of +1.0 turns full speed clockwise.  -1.0 is full speed counterclockwise.
         * drive = 0, turn = 0 stops the drive.
         */
        void drive(double fwd, double turn);

        /**
         * Turn on the intake_group at a specific speed.
         *
         * A parameter of +1.0 means the intake_group sucks in at full speed. -1.0
         * means full speed outtaking.
         *
         * The motors need to spin in the opposite directions.
         */
        void intake(double intake_speed);

        /**
         * Returns the velocity of the first motor.
         *
         * @return A number ranging from -1.0 for full speed outaking to 1.0 for
         *        full speed intaking. A value of 0.0 means that the flywheels
         *        are idle.
         */
        double intake_speed();

    private:
        vex::motor_group left;
        vex::motor_group right;
        vex::motor_group intake_group;
};

/**
 *
 */
class PivotRampPrototype : public Idrive, public Iintake, public Ilift {
    public:
        /**
         * Construct a pivot ramp prototype robot.
         *
         * The motor groups passed into this constructor require careful
         * consideration.  It is up to the caller -- to YOU -- to ensure that
         * all the motors turn in the correct direction (including calling
         * setReverse() as needed) so that nothing is damaged when the motor
         * group's velocity is set.
         *
         * @param left   The motor group handling all motors on the left side of
         *               the drive.  Setting its velocity to a positive value
         *               should cause the left side of the robot to drive
         *               forward.
         * @param right  The motor group handling all motors on the right side
         *               of the drive.  Setting its velocity to a positive value
         *               should cause the right side of the robot to drive
         *               forward.
         * @param intake The motor group handling all motors responsible for
         *               intaking. Setting the velocity +1 will be full power
         *               intaking while -1 will be full power outaking. 0 will
         *               be no motion.
         * @param lift   The motor group handling all motors responsible for
         *               moving the lift. The position passed into the lift
         *               function is a value between 0 and 1 that represents a
         *               percentage of the lift's maximum extension.
         * @param rotationsToTop The number of rotations that the lift's input
         *               motor has to make for the lift to extend.  This value
         *               must be determined experimentally (please see
         *               setLiftRotationsDebug().)
         */
        PivotRampPrototype(const vex::motor_group& left, const vex::motor_group& right,
                           const vex::motor_group& intake, const vex::motor_group& lift,
                           double rotationsToTop);

        PivotRampPrototype(const std::vector<vex::motor>& left_motors_,
                           const std::vector<vex::motor>& right_motors_,
                           const vex::motor_group& intake, const vex::motor_group& lift,
                           double rotationsToTop);
        /**
         * Drive the robot at the given speeds.
         *
         * A fwd parameter of +1.0 means full speed forward.  -1.0 is full speed reverse.
         * A turn parameters of +1.0 turns full speed clockwise.  -1.0 is full speed counterclockwise.
         * drive = 0, turn = 0 stops the drive.
         */
        void drive(double fwd, double turn);

        /**
         * Turn on the intake_group at a specific speed.
         *
         * A parameter of +1.0 means the intake_group sucks in at full speed. -1.0
         * means full speed outtaking.
         */
        void intake(double intake_speed);

        /**
         * Move the lift to a certain position.
         *
         * Warning: Different types of lifts will permit different ranges for
         * this number.
         *
         * @param position a position in the closed interval [0, 1]. 0 is the
         * lift's bottom while 1 is maximum height.
         */
        void setLiftPosition(double position);

        /**
         * Returns the pivotramp lift's position. 0 is the lowest; 1 is the highest.
         */
        double getliftPosition() const;

        /**
         * Moves the lift directly by the given number of rotations.
         * @param rotations the number of revolutions to rotate the lift_motor group
         */
        void moveLiftDirect(double rotations);

        LiftHeights liftHeights() const {
            return liftHeights_;
        }

        void setLiftHeights(LiftHeights liftHeights);

    private:
        std::vector<vex::motor> left_motors;
        std::vector<vex::motor> right_motors;
        // vex::motor_group left;
        // vex::motor_group right;
        vex::motor_group intake_group;
        vex::motor_group lift_group;
        double rotationsToTop;

        LiftHeights liftHeights_;
};

#endif // (ifndef __PROTOTYPE_H_INCLUDED__)