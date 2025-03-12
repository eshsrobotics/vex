#include "vex.h"
#include "mcnugget.h"

using namespace vex;

// Some of these motors are reversed because when the robot is assembled, if the
// motor layout is symmetrical then half the motors will be spinning in the
// wrong direction.
// Which motors are reversed will be decided after testing, these are just
// placeholders.
// The middle motors on each side will be moving in the opposite direction as
// the other two motors on that side due to physics, so their reversal status is
// the opposite of the front/back motors on that side to make them go in the
// other direction.
motor LeftFront(LEFT_FRONT_PORT, true);
motor LeftMiddle(LEFT_MIDDLE_PORT);
motor LeftBack(LEFT_BACK_PORT, true);

motor RightFront(RIGHT_FRONT_PORT);
motor RightMiddle(RIGHT_MIDDLE_PORT, true);
motor RightBack(RIGHT_BACK_PORT);

motor_group Left(LeftFront, LeftMiddle, LeftBack);
motor_group Right(RightFront, RightMiddle, RightBack);

void letHimCook(double frontBackSpeed, double turnSpeed){


    // drive code goes here


}