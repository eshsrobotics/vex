// PROTOTYPES.H -- Concrete classes for all VEX drive prototype robots.
#ifndef __PROTOTYPE_H_INCLUDED__
#define __PROTOTYPE_H_INCLUDED__

#include <vector>

#include "vex.h"
#include "Idrive.h"
#include "Iintake.h"
#include "Ilift.h"
#include "ImobileGoalIntake.h"



/**
 *
 */
class PivotRampPrototype : public Idrive, public Iintake, public Ilift,
                           public ImobileGoalIntake {
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
         * @param left   The list of all motors on the left side of the drive.
         *               Setting each motor's velocity to a positive value
         *               should cause the left side of the robot to drive
         *               forward.
         * @param right  The list of all motors on the right side of the drive.
         *               Setting each motor's velocity to a positive value
         *               should cause the right side of the robot to drive
         *               forward.
         * @param intake The list of all motors responsible for intaking.
         *               Setting the velocity +1 will be full power intaking
         *               while -1 will be full power outaking. 0 will be no
         *               motion.
         * @param lift   The motor group handling all motors responsible for
         *               moving the lift. The position passed into the lift
         *               function is a value between 0 and 1 that represents a
         *               percentage of the lift's maximum extension.
         * @param rotationsToTop The number of rotations that the lift's input
         *               motor has to make for the lift to extend.  This value
         *               must be determined experimentally (please see
         *               setLiftRotationsDebug()).
         * @param pneumaticsClamp A digital_out object connected to a double
         *               solenoid for controlling pneumatic mobile goal grabber.
         */
        PivotRampPrototype(const std::vector<vex::motor>& left_motors_,
                           const std::vector<vex::motor>& right_motors_,
                           const std::vector<vex::motor>& intake, const std::vector<vex::motor>& lift,
                           double rotationsToTop, const vex::digital_out& pneumaticsClamp);

        /**
         * Drive the robot at the given speeds.
         *
         * A fwd parameter of +1.0 means full speed forward.  -1.0 is full speed reverse.
         * A turn parameters of +1.0 turns full speed clockwise.  -1.0 is full speed counterclockwise.
         * drive = 0, turn = 0 stops the drive.
         */
        void drive(double fwd, double turn);

        /**
         * The number of times a specific motor in our drive train has rotated.
         *
         * "What?", you ask. "A specific motor?  Why just one?  Why not average
         * them?" Because, it doesn't really matter.  We only need
         * this code in specific contexts, such as measuring the number of
         * rotations needed to make a given drive go forward X meters.  In that
         * case, one wheel is good as any other.
         *
         * @return A rotation value that could be positive or negative.
         */
        virtual double getRotations() const;

        /**
         * Resets the encoders to 0.
         *
         */
        virtual void resetEncoders();

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

        bool isLiftAvailable() const;

        LiftHeights liftHeights() const {
            return liftHeights_;
        }

        void setLiftHeights(LiftHeights liftHeights);

        /**
         * Clamps and unclamps the mobile goal grabber.
         * @param active true for the clamp to close and false for open
        */
        void clamp(bool active);

    private:
        std::vector<vex::motor> left_motors;
        std::vector<vex::motor> right_motors;
        std::vector<vex::motor> intake_motors;
        std::vector<vex::motor> lift_motors;
        double rotationsToTop;

        LiftHeights liftHeights_;

    public: // Temporary for testing
        vex::digital_out pneumaticClamp;
};

#endif // (ifndef __PROTOTYPE_H_INCLUDED__)—