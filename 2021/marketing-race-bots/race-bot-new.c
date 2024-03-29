#pragma config(Motor,  port2,           Front_Right,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           Back_Right,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           Front_Left,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           Back_Left,     tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(true) {

		int leftJoystick = vexRT[Ch3];
		int rightJoystick = vexRT[Ch2];
		int DEADZONE_THRESHOLD = 10;

		// Deadzone low joystick values.
		if(leftJoystick > -DEADZONE_THRESHOLD && leftJoystick < DEADZONE_THRESHOLD) {
			leftJoystick = 0;
		}
		if(rightJoystick > -DEADZONE_THRESHOLD && rightJoystick < DEADZONE_THRESHOLD) {
			rightJoystick = 0;
		}

		// Drive the motors.
		motor[Back_Left] = leftJoystick;
		motor[Front_Left] = leftJoystick;
		motor[Back_Right] = rightJoystick;
		motor[Front_Right] = rightJoystick;
	}
}
