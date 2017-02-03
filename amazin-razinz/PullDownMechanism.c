//NOTE: I have no idea how vex works so this code is probably broken.

/*
These are the #defines.

A #define basically tells the compiler to do a find and replace before compiling the code.
It looks like:

#define (text to replace) (text to replace it with)
*/

/* Joystick Defines */
#define LeftStickY Ch3
#define RightStickY Ch2
#define RightBumper YouGuysForgotToDefineTheRightBumper
#define LeftBumper YouGuysForgotToDefineTheLeftBumper

/* Motor Defines */
// NOTE: Whoever's job it is to get this code functional, fill in the "portnum" for each wheel.
#define FrontRightWheel 2
#define FrontLeftWheel 3
#define BackRightWheel 4
#define BackLeftWheel 5

#define RightMotor1 YouGuysForgotToDefineThis
#define RightMotor2 YouGuysForgotToDefineThis
#define LeftMotor1 YouGuysForgotToDefineThis
#define LeftMotor2 YouGuysForgotToDefineThis

/* Code */
task moveMotors(int speed, int time) {
	motor[RightMotor1] = speed;
	motor[RightMotor2] = speed;
	motor[LeftMotor1] = speed;
	motor[LeftMotor2] = speed;

	wait(time);

	motor[RightMotor1] = 0;
	motor[RightMotor2] = 0;
	motor[LeftMotor1] = 0;
	motor[LeftMotor2] = 0;
}

task main()
{
	while(true) {
		motor[FrontLeftWheel] = vexRT[LeftStickY];
		motor[FrontRightWheel] = vexRT[RightStickY];

		if(vexRT[RightBumper] == 1)
		{
			// Potential bug: This may interrupt the rest of the function.
			moveMotors(127, 1);
		}

		if(vexRT[LeftBumper] == 1)
		{
			moveMotors(-127, 1);
		}

		wait1Msec(10);
	}
}
