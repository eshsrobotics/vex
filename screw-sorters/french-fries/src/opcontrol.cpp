#include "main.h"
#include <iostream>
#include <array>
#include <cmath>
#include <ctime>

using std::array;
using std::clock;
using std::cout;
using std::abs;

const double EPSILON = 0.001;
const double MAX_MOTOR_SPEED = 127;
const double MIN_MOTOR_SPEED = 20;

// When our angle is this close to the goal (in degrees), it's good enough
// and we stop.  We only need this because these VEX 393 motors seem to have a dead band
// where we just can't move slowly enough to get them to stop accurately with PID.
const double SLOP_VALUE = 2.0; 

// Number of teeth in turntable vs. number of teeth in bevel gear.
//
// Exact and confirmed through counting.
const double TURNTABLE_GEAR_RATIO = 66 / 12; 

// The current turntable position -- it is designed to iterate between fixed angles.
int currentPosition = 0;

// Exits from the main loop.
// This isn't really working right now--the while loop quits, but the V5 brain still displays the program.
bool quit = false;

// Our turntable motor.
pros::ADIMotor turntable(5); // Legacy Port E
pros::ADIMotor elevator(3);  // Legacy port C

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
	} else if (abs(error) < SLOP_VALUE) {
		// It's good enough.  Leave the motor alone.
		state.lastIntegral = 0;
		return 0;
	}

	double currentTimeMilliseconds = static_cast<double>(clock())/ CLOCKS_PER_SEC;
	double elapsedTimeSeconds = currentTimeMilliseconds - state.lastInvocationTimeSeconds;
	double integral = state.lastIntegral + error * elapsedTimeSeconds;
	double derivative = (error - state.lastError) / elapsedTimeSeconds;

	double output = error*state.kP + integral*state.kI + derivative*state.kD;
	if (abs(output) > MAX_MOTOR_SPEED) {
		output = sgn(output) * MAX_MOTOR_SPEED;
	} else if (abs(output) < MIN_MOTOR_SPEED) {
		output = 0;
	}

	//cout << "deltaT: " << elapsedTimeSeconds << ", error: " << error 
	//     << ", integral: " << integral << ", derivative: " << derivative << ", SPEED = " 
	//	 << output << "\n";
	state.lastError = error;
	state.lastIntegral = integral;
	state.lastInvocationTimeSeconds = currentTimeMilliseconds;
	return output;
}

// The places where we want the turntable mechanism to stop.  These are measured in degrees,
// with the initial position of the turntable being at 0.
array<int, 9> waypoints = { -360, -270, -180, -90,
							0, 
							90, 180, 270, 360 };

// Returns to angle 0.
void home_position() { currentPosition = 4; }

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
	home_position();

	while (!quit) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		left_mtr = left;
		right_mtr = right;

		const double kP = 1.0, kI = 0.2 /*0.5*/, kD = 0;
		pidState state(kP, kI, kD, TURNTABLE_GEAR_RATIO);
		double speed = pidControl(state, turntableQuadEncoder.get_value(), waypoints[currentPosition]);
		turntable.set_value(speed);

		pros::lcd::print(3, "Goal: %d, Quad: %.1f", 
			waypoints[currentPosition], 
			turntableQuadEncoder.get_value() / TURNTABLE_GEAR_RATIO);
		//cout << "Quadrature encoder value: current = " 
		//	 << turntableQuadEncoder.get_value() << ", desired = "
		//	 << desiredAngle << ", speed = " << speed << "\n";

		// Intentional wobble for now with the elevation motor.
		int currentTimeMilliseconds =  (1000 * clock()) / CLOCKS_PER_SEC;
		if (currentTimeMilliseconds % 100 > 50) {
			elevator.set_value(0);
		} else {
			elevator.set_value(127);
		}
		cout << currentTimeMilliseconds << "\n";

		pros::delay(20);
	}
}
