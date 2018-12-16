#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in5,    gyro,           sensorGyro)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           backRight,     tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port2,           climb,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           frontLeft,     tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port4,           armRight,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           clawMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           wristRotate,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           wristElevation, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           armLeft,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           frontRight,    tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port10,          backLeft,      tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* --------------------------------------------------------------------------- */
/*                               Description:                                  */
/*                                                                             */
/*    This is the source code for Spudnik 1, a robot programmed by the El      */
/*    Segundo High School P.O.T.A.T.O.E.S. for the 2018-2019 VEX Turning Point */
/*    competition.                                                             */
/*                                                                             */
/*    The robot is designed as a holonomic Mecanum drive with strafing         */
/*    controlled by the left joystick (Ch3/Ch4) and turning controlled by the  */
/*    horizontal axis of the right joystick (Ch1).  The drive is driven by     */
/*    five 393 motors (one for each wheel, plus one more motor for the         */
/*    climbing wheels at the bottom of the robot).                             */
/*                                                                             */
/*    To overcome joystick sensitivity issues, the holonomic drive allows for  */
/*    a "deadzone" threshold; any values the joystick gives us below that      */
/*    will be ignored.                                                         */
/*                                                                             */
/*    The main feature of the robot is its arm, a double-reverse four-bar arm  */
/*    lift driven by two 393 motors.  We use an additional 393 motor at the    */
/*    end of the arm to articulate the "wrist" up and down, another to rotate  */
/*    the "wrist" clockwise and counterclockwise, and one final motor to       */
/*    control the gripping claw at the end of the wrist, giving us a grand     */
/*    total of 10 motors.                                                      */
/* --------------------------------------------------------------------------- */

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*********************/
/* GLOBAL VARIABLES  */
/*********************/
int gyroAngle = 0;
// These variables control acceleration of the robot's drive.
float realLeftRight = 0.0;
float realForwardBack = 0.0;
float realTurn = 0.0;
const float acceleration = 0.1;

// Claw and wrist variables.
const int CLAW_MOTOR_SPEED = 45;
const int WRIST_ROTATE_SPEED = 40;
const int WRIST_ELEVATION_SPEED = 40;

// OPEN CLAW
// This function starts the process of opening the claw.  It takes about 1.5
// seconds to complete; the robot code has no other way of knowing when the
// claw is fully opened.
void openClaw() {
    motor[clawMotor] = CLAW_MOTOR_SPEED;
}

// CLOSE CLAW
// This function starts the process of closing the claw, again taking about
// 1.5 seconds to complete from our tests.
void closeClaw() {
    motor[clawMotor] = -CLAW_MOTOR_SPEED;
}

// CLOSE CLAW
// This function starts the process of closing the claw, again taking about
// 1.5 seconds to complete from our tests.
void stopClaw() {
    motor[clawMotor] = 0;
}


void raiseWrist() {
          motor[wristElevation] = WRIST_ELEVATION_SPEED;
}

void lowerWrist() {
          motor[wristElevation] = -WRIST_ELEVATION_SPEED;
}

void stopWrist() {
          motor[wristElevation] = 0;
}

void rotateWristClockwise() {
        motor[wristRotate] = WRIST_ROTATE_SPEED;
}

void rotateWristCounterClockwise() {
        motor[wristRotate] = -WRIST_ROTATE_SPEED;
}

void stopRotatingWrist() {
        motor[wristRotate] = 0;
}


// ORIENT WRIST AND OPEN CLAW
// If the claw is right-side up already, this function just opens the claw.
// If the claw is upside-down, this function instructs the wrist to orient
// itself properly (so the claw's moving portion is oriented upward) before
// opening the claw.
//
// This function is only meant to be used in response to manual input; this is
// what gets executed when a human hits the "open claw" button.
void orientWristAndOpenClaw() {
    // TODO: Implement
}

// Starts the process of raising the arm.  The arm will not stop until
// lowerArm() or stopArm() is called.
//
// The arm takes about 5 seconds to raise in our tests, but the system
// provides no feedback when this is done, and it is possible to raise the arm
// with this function until the gears slip and the motor strains.  Take care!
void raiseArm() {
    motor[armRight] = 127;
    motor[armLeft] = 127;
}

// Starts the process of lowering the arm.  The arm will not stop until
// raiseArm() or stopArm() is called.
//
// See caveats and warnings in the documentation for raiseArm().
void lowerArm() {
    motor[armRight] = -127;
    motor[armLeft] = -127;
}

// Stops the arm from raising or lowering.
void stopArm() {
    motor[armRight] = 0;
    motor[armLeft] = 0;
}

// MECHANUM DRIVE
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

  // Don't let the controller drive the motors directly.  Instead, the controller
  // represents the desired state, and we increment our way towards that.
  realLeftRight += sgn(leftRight - realLeftRight) * acceleration;
  realForwardBack += sgn(forwardBack - realForwardBack) * acceleration;
  realTurn += sgn(turn - realTurn) * acceleration;

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

  motor[frontRight] = realForwardBack - realTurn - realLeftRight;
  motor[backRight] =  realForwardBack - realTurn + realLeftRight;
  motor[frontLeft] = realForwardBack + realTurn + realLeftRight;
  motor[backLeft] =  realForwardBack + realTurn - realLeftRight;

  // Determine when to activate the center climbing assistance wheels.
  motor[climb] = forwardBack;
}

task brake()
{

	const int clicksToBrake = 20;
	int startClicks = nMotorEncoder[frontRight];

	while (abs(startClicks - nMotorEncoder[frontRight]) < clicksToBrake)
	{
			mecanumDrive(0, -127, 0)
	}
	mecanumDrive(0, 0, 0);
}// end (task brake)

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
	SensorType[in5] = sensorNone;
	wait1Msec(10);
	SensorType[in5] = sensorGyro;
	wait1Msec(3500);
	//in order for the gyro to show the correct values, you must wair l0 mil secs after sensorType = sensorNone, and 3500 mil secs after SensorType = sensorGyro
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
    nMotorEncoder[frontRight] = 0;

  }
  const float L = periodLengthMilliseconds;

  if (nMotorEncoder[frontRight] < 500) {
  	mecanumDrive(0, 127, 0);

  	return true;
  } else {
    // Stop.
  	startTask (brake);

  	return false;
	}
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
	clearTimer(timer1);
	while (time1[timer1] < 3000)
	{
		mecanumDrive(0, 127, 0);
	}
	mecanumDrive(0,0,0);
  // ..........................................................................
  //nMotorEncoder[backRight] = 0;
  //while(nMotorEncoder[backRight] < "x")


  // ..........................................................................

  // Remove this function call once you have "real" code.
  //AutonomousCodePlaceholderForTesting();
}

// MECHANUM CONTROL
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
void mecanumControl(int leftRightJoystickChannel, int frontBackJoystickChannel, int turnJoystickChannel, int deadzoneThreshold=15) {

  //Create "deadzone" variables. Adjust threshold value to increase/decrease deadzone
  int X2 = 0, Y1 = 0, X1 = 0;

  //Create "deadzone" for Y1/Ch3
  if(abs(vexRT[frontBackJoystickChannel]) > deadzoneThreshold)
    Y1 = vexRT[frontBackJoystickChannel];
  else
    Y1 = 0;

  //Create "deadzone" for X1/Ch4
  if(abs(vexRT[leftRightJoystickChannel]) > deadzoneThreshold)
    X1 = vexRT[leftRightJoystickChannel];
  else
    X1 = 0;

  //Create "deadzone" for X2/Ch1
  if(abs(vexRT[turnJoystickChannel]) > deadzoneThreshold)
    X2 = vexRT[turnJoystickChannel];
  else
    X2 = 0;

  mecanumDrive(X1, Y1, X2);
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

	int autonomousControl = 0;
  while (true)
  {
  	gyroAngle = sensorValue[in5];
  	//sync gyroAngle to gyroValue so that the gyroValue is shown during debugging
    // Button 7L toggles "autonomous"
    // vs. manual mode, but it must be held down for at least half
    // a second.
    if (autonomousControl == 0 && vexRT[Btn7L] > 0) {
      autonomousControl = 1;
      clearTimer(timer2);
    } else if (autonomousControl == 1) {
      if (vexRT[Btn7L] > 0) {
        if (time1[timer2] > 1000) {
          // Button held down for 1 second--activate.
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
      if (vexRT[Btn7L] > 0 && time1[timer2] > 500) {
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

    ///////////////////
    // ARM ELEVATION //
    ///////////////////
    // While user presses button 5D then arm goes up, and while user presses
    // button 6D the arm goes down.
    if (vexRT[Btn5D] > 0) {
        raiseArm();
    } else if (vexRT[Btn6D] > 0) {
        lowerArm();
    } else {
        stopArm();
    }

    //////////
    // CLAW //
    //////////
    // Buttons: 8D (open), 8U (close)

    if (vexRT[Btn8D] > 0) {
        openClaw();
    } else if (vexRT[Btn8U] > 0) {
        closeClaw();
    } else {
        stopClaw();
    }

    /////////////////////
    // WRIST ELEVATION //
    /////////////////////
    // Buttons: 7U (up), 7D (down)

    if (vexRT[Btn7U] > 0) {
        raiseWrist();
    } else if (vexRT[Btn7D] > 0) {
        lowerWrist();
    } else {
        stopWrist();
    }

    ////////////////////
    // WRIST ROTATION //
    ////////////////////
    // Buttons: 5U (counterclockwise), 6U (clockwise)

    if (vexRT[Btn5U] > 0) {
        rotateWristCounterClockwise();
    } else if (vexRT[Btn6U] > 0) {
        rotateWristClockwise();
    } else {
        stopRotatingWrist();
    }


  } // end (while true)
} // end (task usercontrol)
