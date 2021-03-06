#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           backLeft,      tmotorVex393_HBridge, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port8,           backRight,     tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port9,           frontLeft,     tmotorVex393_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port10,          center,        tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code aims to stop the robot at a certain point (initially). Then tests were done to find a method to stop that decreases the amount of drift (so the robot can stop at the point rater than over)

bool isBraking = false;

void clearEncoders() {
	nMotorEncoder[frontRight] = 0;
	nMotorEncoder[backRight] = 0;
	nMotorEncoder[backLeft] = 0;
	nMotorEncoder[frontLeft] = 0;
}

void startMotors(int speed) {
	motor[backLeft] = speed;
}

void stopMotors() {
	motor[backLeft] = 0;
}

// Gets direction of vehicle, mostly dependent on if clickDistance is positive or negative
// 1 if going forward; -1 if going backwards; 0 if no transformation
int getDirection(int clickDistance, int initialSpeed) {
	if(clickDistance > 0) {
		return 1;
	}
	else if(clickDistance < 0) {
		return -1;
	}
	return 0;
}

int speedAfterDrift(int clickDistance, int initialSpeed) {
	int absEncoderValue = abs(nMotorEncoder[backLeft]);
	int absClickDistance = abs(clickDistance);
	int newSpeed;

	// If less than 90% complete, slow down motor to 75% speed
	if(absEncoderValue <= absClickDistance * 0.5) {
		newSpeed = initialSpeed;
	}
	// If 90% complete, slow down motor to 75% speed
	else if(absEncoderValue > absClickDistance * 0.8) {
		newSpeed = initialSpeed * 0.75;
	}
	// If 97% complete, slow down motor to 25% speed
	else if(absEncoderValue > absClickDistance * 0.90) {
		newSpeed = initialSpeed * 0.25;
	}
	// If overshoot
	else if(absEncoderValue > absClickDistance) {
		newSpeed = -initialSpeed * 0.25;
	}
	else {
		newSpeed = initialSpeed;
	}
	// newSpeed = correctInvalidSpeed(newSpeed);
	return newSpeed;
}

// Move robot straigh line dependent on click value
// Assuming initialSpeed is positive
int moveClicks(int clickDistance, int initialSpeed) {
	int direction = getDirection(clickDistance, initialSpeed);

	long newSpeed;
	if(direction == 1) {
		newSpeed = speedAfterDrift(clickDistance, initialSpeed);
		startMotors(newSpeed);
	}
	else if(direction == -1) {
		newSpeed = speedAfterDrift(clickDistance, -initialSpeed);
		startMotors(newSpeed);
	}
	else {
		stopMotors();
	}
	return newSpeed;
}

/* task break stops the motor gradually, decreasing the motor speedd
	 at every frame by a multiple of 'k'. This is slightly more
	 accurate than the other coolReverseBrake task and takes much longer
	 to stop (50.5 feet).
*/
task brake() {
	isBraking = true;

	// This is temporary; not what we actually want

	const float k = 0.849;
	const float epsilon = 0.01;

	while(true) {
		motor[backLeft] *= k;
		motor[backRight] *= k;
		motor[frontLeft] *= k;
		motor[frontRight] *= k;

		if(abs(motor[frontLeft]) < epsilon) {
			isBraking = false;
			return;
		}
	}
}

/* coolReverseBrake stops the motor as it reaches the distance
	 and reverses for a small amount of seconds at a certain motor
	 speed. This is supposed to eliminate a lot of drift and allow
	 the robot to stop faster. It is slightly less accurate than the
	 other taask break() and stops sooner (49.8 feet).
*/
task coolReverseBrake() {
	isBraking = true;
	clearTimer(timer2);
	const float k = 2;

	while(time1[timer2] < 10) {
		motor[backLeft] = -k;
		motor[backRight] = -k;
		motor[frontLeft] = -k;
		motor[frontRight] = -k;
	}
	motor[backLeft] = 0;
	motor[backRight] = 0;
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
	isBraking = false;
}

task main() {

	clearEncoders();

	int clickDistance = 1500;
	int initialSpeed = 127;
	int state = 0;

	while(true) {
		if(vexRT[Btn7R] == 1) {
			state = 1;
			clearTimer(timer1);
		}

		switch(state) {
			case 1:
				motor[backLeft] = initialSpeed;
				motor[backRight] = initialSpeed;
				motor[frontLeft] = initialSpeed;
				motor[frontRight] = initialSpeed;

				if(time1[timer1] > 2000) {
						state = 2;
				}
				break;
			case 2:
				startTask(coolReverseBrake);
				if (!isBraking) {
					state = 0;
				}
		}

		if(vexRT[Btn8U] == 1) {
			motor[backLeft] = initialSpeed;
			motor[backRight] = initialSpeed;
			motor[frontLeft] = initialSpeed;
			motor[frontRight] = initialSpeed;
		}
		// int newSpeed = moveClicks(clickDistance, initialSpeed);
		// initialSpeed = newSpeed;

		// Brake on button press if not already braking
		if(vexRT[Btn8D] == 1 && !isBraking) {
			startTask(coolReverseBrake);
		}
	}
}
