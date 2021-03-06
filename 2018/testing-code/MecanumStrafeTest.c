#pragma config(Motor,  port2,           backRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           backLeft,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           frontLeft,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           frontRight,    tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Mecanum Drive with Deadzone Thresholds
- This program allows you to remotely control a robot with mecanum wheels.
- The left joystick Y-axis controls the robot's forward and backward movement.
- The left joystick X-axis controls the robot's left and right movement.
- The right joystick X-axis controls the robot's rotation.
- This program incorportes a threshold/deadzone that allows very low Joystick values to be ignored.
This allows the robot to ignore values from the Joysticks when they fail to center at 0,
and provides a margin of error for the driver when they only want the robot to move in one axis.

[I/O Port]          [Name]              [Type]                [Description]
Motor Port 2        frontRight          VEX Motor             Front Right motor
Motor Port 3        backRight           VEX Motor             Back Right motor
Motor Port 4        frontLeft           VEX Motor             Front Left motor
Motor Port 5        backLeft            VEX Motor             Back Left motor
----------------------------------------------------------------------------------------------------*/

// Given a holonomic, 4-wheel Mecanum drive and three joystick values, this
// function moves the robot in the desired direction.
//
// To strafe left and right, simply provide a value for leftRight (and maybe
// forwardBack) without providing a value for the turning channel.
//
// Remember that this function provides instantaneous motion, and must be
// called in a loop to take place continuously.
//
// Arguments:
// - leftRight: The value sent by the left-right joystick channel (-127 for
//   full leftward motion and 127 for full rightward motion.)
//
//   This is usualy Ch3 on the left joystick.
//
// - forwardBack: The value sent by the forward-back joystick channel (-127
//   for full leftward motion and 127 for full rightward motion.)
//
//   This is usually Ch4 on the left joystick.
//
// - turn: The value sent by the turning joystick channel (-127 to turn left
//   at full speed and 127 to turn right at full speed.)
//
//   This is usually Ch1 on the right joystick.

void mecanumDrive(int leftRight, int forwardBack, int turn) {

	if (leftRight < -127) {
		leftRight = -127;
	}
	if (leftRight > 127) {
		leftRight = 127;
	}
	if (forwardBack < -127) {
		forwardBack = -127;
	}
	if (forwardBack > 127) {
		forwardBack = 127;
	}

	if (turn < -127) {
		turn = -127;
	}
	if (turn > 127) {
		turn = 127;
	}

	motor[frontRight] = forwardBack - turn - leftRight;
	motor[backRight] =  forwardBack - turn + leftRight;
	motor[frontLeft] = forwardBack + turn + leftRight;
	motor[backLeft] =  forwardBack + turn - leftRight;
}

// Given a holonomic, 4-wheel Mecanum drive and three joystick channels, this
// function calls mecanumDrive() correctly to allow a human using those
// joysticks to drive the bot.
//
// Remember that this function provides instantaneous motion, and must be
// called in a loop to take place continuously.
//
// Arugments:
// - leftRightJoystickChannel: The channel that controls horizontal
//   strafing -- ordinarily Ch3 on the left joystick.
// - frontBackJoystickChannel: The channel that controls front-back
//   movement -- ordinarily Ch4 on the left joystick.
// - turnJoystickChannel: The channel that controls
//   counterclockwise/clockwise turning -- ordinarily Ch1 on the right joystick.
// - deadzoneThreshold: Any channel value whose aboslute value is less than this
//   will be ignored.  This compensates for the fact that joysticks sometimes
//   tend not to rest at perfect 0.
//   This variable will only have effect if it is non-negative.  Setting it too
//   high will make driving unresponsive and difficult.
//
void mecanumControl(int leftRightJoystickChannel, int frontBackJoystickChannel, int turnJoystickChannel, int deadzoneThreshold=15) {

	//Create "deadzone" variables. Adjust threshold value to increase/decrease deadzone
	int X2 = 0, Y1 = 0, X1 = 0;

	//Create "deadzone" for Y1/Ch3
	if(abs(vexRT[leftRightJoystickChannel]) > deadzoneThreshold)
		Y1 = vexRT[leftRightJoystickChannel];
	else
		Y1 = 0;
	//Create "deadzone" for X1/Ch4
	if(abs(vexRT[frontBackJoystickChannel]) > deadzoneThreshold)
		X1 = vexRT[frontBackJoystickChannel];
	else
		X1 = 0;
	//Create "deadzone" for X2/Ch1
	if(abs(vexRT[turnJoystickChannel]) > deadzoneThreshold)
		X2 = vexRT[turnJoystickChannel];
	else
		X2 = 0;

	mecanumDrive(X1, Y1, X2);
}

// Uses the mecanumDrive() function to drive in set patterns, testing whether everything was wired correctly.
//
// Remember that this function provides instantaneous motion, and must be
// called in a loop to take place continuously.
//
// Arguments:
// - periodLengthMilliseconds: The duration of the programmed cycle of behavior.
//   Must be less than 32,767 (the maximum duration of the vex timers.)
//
// Return values:
// - True if we've reached the end of our cycle, false otherwise.  The cycle
//   will repeat itself again naturally unless you stop calling autonomousTest().
bool autonomousTest(int periodLengthMilliseconds) {

	float milliseconds = time1[timer1];
	if (milliseconds > periodLengthMilliseconds) {
		clearTimer(timer1);
		milliseconds = 0;
	}
	const float L = periodLengthMilliseconds;

	if (milliseconds >= 0.0 * L && milliseconds < 0.2 * L) {
		// Drive forward.
		mecanumDrive(0, 127, 0);
		} else if (milliseconds >= 0.2 * L && milliseconds < 0.4 * L) {
		// Drive right.
		mecanumDrive(127, 0, 0);
		} else if (milliseconds >= 0.4 * L && milliseconds < 0.6 * L) {
		// Drive backward.
		mecanumDrive(0, -127, 0);
		} else if (milliseconds >= 0.6 * L && milliseconds < 0.8 * L) {
		// Drive left.
		mecanumDrive(-127, 0, 0);
		} else {
		// Stop.
		mecanumDrive(0, 0, 0);
		return true;
	}
	return false;
}

task main()
{
	int autonomousControl = 0;

	//Loop Forever
	while(1 == 1)
	{
		// Button 5U (the upper left trigger) toggles "autonomomous"	vs. manual mode,
		// but it must be help down for at least half a second.
		if (autonomousControl == 0 && vexRT[Btn5U] > 0) {
			autonomousControl = 1;
			clearTimer(timer2);
			} else if (autonomousControl == 1) {
			if (vexRT[Btn5U] > 0) {
				if (time1[timer2] > 500) {
					// Button held down for 5 seconds--activate.
					autonomousControl = 2;
					clearTimer(timer2);
				}
				} else {
				// Button released before we could switch; autonomous canceled.
				autonomousControl = 0;
			}
			}	else if (autonomousControl == 2) {
			// If the button is pressed again, we cancel, but only after a threshold
			// (to allow the human to release the button.)
			if (vexRT[Btn5U] > 0 && time1[timer2] > 500) {
				autonomousControl = 0;
				} else {
				autonomousTest(10000);
			}
		}

		// If we're not driving in a square, the human can have a go.
		if (autonomousControl != 2) {
			//Remote Control Commands
			int threshold = 50;
			mecanumControl(Ch4, Ch3, Ch1, threshold);
		}
	}
}
