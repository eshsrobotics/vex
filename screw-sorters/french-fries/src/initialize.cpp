#include "main.h"
#include <iostream>

using std::cout;

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	pros::lcd::set_text(7, "<- Turn Left        Home       Turn Right ->");

	pros::lcd::register_btn1_cb(on_center_button);
	pros::lcd::register_btn0_cb([] () { currentPosition = currentPosition + 1; if (currentPosition >= 9) currentPosition = 8; });
	pros::lcd::register_btn1_cb([] () { home_position(); });
	pros::lcd::register_btn2_cb([] () { currentPosition = currentPosition - 1; if (currentPosition < 0) currentPosition = 0; });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
