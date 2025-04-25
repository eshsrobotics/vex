#include "vex.h"
#include "mcnugget.h"
#include <algorithm>

using namespace vex;
using namespace std;

brain NuggetMind;
controller Spatula;

// The bot uses 3 motors connected to a gear train. If the gear train has an odd
// number of gears, then all motors on one side will be moving the same
// direction because all gears will be moving in the same direction. If an even
// number of gears are used, then the back top motor on each side will be moving
// in the opposite direction as the other motors on its side. The number of gears
// hasn't been decided yet. If odd, reverse the back top gears relative to the other
// motors on their side.

// If one or more sides are found moving the wrong direction in testing, then the
// motor objects that are being called with bool reverse = true should be called 
// with reverse = false instead, and the motors that originally had reverse = false
// should be called with reverse = true instead.
motor LeftFront(LEFT_FRONT_PORT, false);
motor LeftBackTop(LEFT_BACK_TOP_PORT, false);
motor LeftBack(LEFT_BACK_PORT, false);

motor RightFront(RIGHT_FRONT_PORT, true);
motor RightBackTop(RIGHT_BACK_TOP_PORT, true);
motor RightBack(RIGHT_BACK_PORT, true);

motor_group Left(LeftFront, LeftBackTop, LeftBack);
motor_group Right(RightFront, RightBackTop, RightBack);

void letHimCook(double leftNuggetSpeed, double rightNuggetSpeed){

    // This is our tank drive formula. In normal tank drive, the left joystick
    // controls the left side motors, so pushing only the left joystick will
    // make the robot turn right. What Elias opted for is more of a War Thunder
    // style, where turning the left joystick makes the bot turn left. This means
    // the left joystick controls the right side, and vice versa.

    // The left side motors spin at a speed decided by the position of the right
    // joystick along axis 2, which is expressed as a percentage between -100
    // and 100. The same is true for the right side motors and the left
    // joystick position along axis 3. If the percentage passed in is 100, then
    // the motors spin forwards at full speed.

    // These two lines here are just to ensure the speed value passed in is not
    // less than -100 or more than 100:
    leftNuggetSpeed = max(-100.0, min(leftNuggetSpeed, 100.0));
    rightNuggetSpeed = max(-100.0, min(rightNuggetSpeed, 100.0));

    Left.spin(fwd, leftNuggetSpeed, velocityUnits::pct);
    Right.spin(fwd, rightNuggetSpeed, velocityUnits::pct);

}