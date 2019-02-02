/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
	// ..........................................................................
	// Insert user code here.
	// ..........................................................................

	// Remove this function call once you have "real" code.
	AutonomousCodePlaceholderForTesting();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
		// This is the main execution loop for the user control program.
		// Each time through the loop your program should update motor + servo
		// values based on feedback from the joysticks.

		// ........................................................................
		// Insert user code here. This is where you use the joystick values to
		// update your motors, etc.
		// ........................................................................

		// Remove this function call once you have "real" code.
		UserControlCodePlaceholderForTesting();
	}
}

void clearGyro()
{

	//Completely clear out any previous sensor readings by setting the port to "sensorNone"
	SensorType[in8] = sensorNone;
	wait1Msec(1000);
	//Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
	SensorType[in8] = sensorGyro;
	wait1Msec(2000);

	//Adjust SensorScale to correct the scaling for your gyro
	//SensorScale[in8] = 260;
	//Adjust SensorFullCount to set the "rollover" point. A value of 3600 sets the rollover point to +/-3600
	//SensorFullCount[in8] = 3600;
}

void clearMotorEncoder()
{
	//Clear the encoders associated with the left and right motors
	nMotorEncoder[rightMotor] = 0;
	nMotorEncoder[leftMotor] = 0;
	nMotorEncoder[rightMotor] = 0;
	nMotorEncoder[leftMotor] = 0;
}


void turn(int degrees)
{
	int error = 5,degrees10;
	degrees10 = degrees * 10;
	//While the absolute value of the gyro is less than the desired rotation - 100...
	while(abs(SensorValue[in8]) < degrees10 - 100)
	{
		motor[rightMotor] = 50;
		motor[leftMotor] = -50;
	}
	//Brief brake to eliminate some drift
	motor[rightMotor] = -5;
	motor[leftMotor] = 5;
	wait1Msec(100);

	//Second while loop to move the robot more slowly to its goal, also setting up a range
	//for the amount of acceptable error in the system
	while(abs(SensorValue[in8]) > degrees10 + error || abs(SensorValue[in8]) < degrees10 - error)
	{
		if(abs(SensorValue[in8]) > degrees10)
		{
			motor[rightMotor] = -30;
			motor[leftMotor] = 30;
		}
		else
		{
			motor[rightMotor] = 30;
			motor[leftMotor] = -30;
		}
	}
	//Stop
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;
	wait1Msec(250);
}

void Drive(int threshold)
{
	int X2 = 0, Y1 = 0, X1 = 0;
	//Create "deadzone" for Y1/Ch3
	if(abs(vexRT[Ch3]) > threshold)
		Y1 = vexRT[Ch3];
	else
		Y1 = 0;
	//Create "deadzone" for X1/Ch4
	if(abs(vexRT[Ch4]) > threshold)
		X1 = vexRT[Ch4];
	else
		X1 = 0;
	//Create "deadzone" for X2/Ch1
	if(abs(vexRT[Ch1]) > threshold)
		X2 = vexRT[Ch1];
	else
		X2 = 0;

	//Remote Control Commands
	motor[frontRight] = Y1 - X2;
	motor[backRight] =  Y1 - X2;
	motor[frontLeft] = Y1 + X2;
	motor[backLeft] =  Y1 + X2;
	motor[center] =  X1;
}

void moveBot(int speed, int targetDistance)
{
	int power, buffer = 500;
	power = (speed/4)*3



 while(nMotorEncoder[rightMotor] < targetDistance - buffer)
	{
		//Move forward at half power
		motor[rightMotor] = power;
		motor[leftMotor]	= power;
		motor[rightMotor] = power;
		motor[leftMotor]	= power;
	}
	while(nMotorEncoder[rightMotor]) > targetDistance + error || nMotorEncoder[rightMotor] < targetDistance - error)
  {
    if(nMotorEncoder[rightMotor] > degrees10)
    {
      motor[rightMotor] = -30;
      motor[leftMotor] = 30;
    }
    else
    {
      motor[rightMotor] = 30;
      motor[leftMotor] = -30;
    }
  }
  //Stop
  motor[rightMotor] = 0;
  motor[leftMotor] = 0;
  wait1Msec(250);
}
