#include "main.h"
#include <iostream>
#include <array>
#include <cmath>
#include <ctime>

const double EPSILON = 0.001;
const double MAX_MOTOR_SPEED = 127;
const double MIN_MOTOR_SPEED = 20;
const double GEAR_RATIO = 66 / 12; // Number of teeth in turntable vs. number of teeth in bevel gear
using std::array;
using std::clock;
using std::cout;
using std::abs;

int currentPosition = 4; // Starts at 0 degrees.

constexpr double sgn(double num) { return (num > 0 ? 1 : (num < 0 ? -1 : 0)); }

// Our encoder, measuring the rotation of the turntable in degrees.
pros::ADIEncoder turntableQuadEncoder(1, 2);

struct pidState {
	pidState(double kP_, double kI_ = 0, double kD_ = 0, double gearRatio_ = 1.0) 
	  : kP(kP_ * gearRatio_), kI(kI_ * gearRatio_), kD(kD_ * gearRatio_), lastError(0), lastIntegral(0), 
	    lastInvocationTimeSeconds(0), gearRatio(gearRatio_) { }

	double kP, kI, kD;
	double lastError;
	double lastIntegral;
	double lastInvocationTimeSeconds;
	double gearRatio;
};

double pidControl(pidState& state, double currentValue, double desiredValue) {
	
	double error = -(desiredValue - currentValue / state.gearRatio);
	if (abs(error) > EPSILON) {
		state.lastIntegral = 0;
	}

	double currentTimeSeconds = static_cast<double>(clock())/ CLOCKS_PER_SEC;
	double elapsedTimeSeconds = currentTimeSeconds - state.lastInvocationTimeSeconds;
	double integral = state.lastIntegral + error * elapsedTimeSeconds;
	double derivative = (error - state.lastError) / elapsedTimeSeconds;

	double output = error*state.kP + integral*state.kI + derivative*state.kD;
	if (abs(output) > MAX_MOTOR_SPEED) {
		output = sgn(output) * MAX_MOTOR_SPEED;
	} else if (abs(output) < MIN_MOTOR_SPEED) {
		output = 0;
	}

	cout << "deltaT: " << elapsedTimeSeconds << ", error: " << error 
	     << ", integral: " << integral << ", derivative: " << derivative << ", SPEED = " 
		 << output << "\n";
	state.lastError = error;
	state.lastIntegral = integral;
	state.lastInvocationTimeSeconds = currentTimeSeconds;
	return output;
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_mtr(1);
	pros::Motor right_mtr(2);
	pros::ADIMotor turntable(5); // Legacy Port E

	// The places where we want the turntable mechanism to stop.  These are measured in degrees,
	// with the initial position of the turntable being at 0.
	array<int, 9> waypoints = { -360, -270, -180, -90,
								0, 
	                            90, 180, 270, 360 };

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		left_mtr = left;
		right_mtr = right;

		const double kP = 1.0 /*2.00*/, kI = 0 /*0.25*/, kD = 0;
		pidState state(kP, kI, kD, GEAR_RATIO);
		double speed = pidControl(state, turntableQuadEncoder.get_value() / GEAR_RATIO, waypoints[currentPosition]);
		turntable.set_value(speed);

		pros::lcd::print(3, "Goal: %d, Quad: %d", 
			waypoints[currentPosition], 
			turntableQuadEncoder.get_value());
		//cout << "Quadrature encoder value: current = " 
		//	 << turntableQuadEncoder.get_value() << ", desired = "
		//	 << desiredAngle << ", speed = " << speed << "\n";

		pros::delay(20);
	}
}
