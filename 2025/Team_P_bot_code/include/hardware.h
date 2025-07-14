#ifndef HARDWARE_H
#define HARDWARE_H

#include <vector>

/**
 * VEX doesn't like it when you copy motors, so normally when we declare motor
 * objects we declare them as global externs to avoid running into an issue
 * where the motor object is defined in multiple compilation units. However,
 * right now we don't know if we will be using 4 or 6 motors for our
 * differential drive, so we need to make a differential drive that is flexible
 * and can work whether we have 4 or 6 motors. 
 * 
 * This function allocates motor ports for the drive internally without creating
 * any additional external copies, so it achieves the same thing we were doing
 * before but can work with any even number of motors.
 * 
 * @param driveMotorPorts
 * A list of the motor ports on the brain that the caller will want to use for
 * the drive. The first half of the elements in this list will be the ports for
 * the left side motors of the drive, and the second half of the elements will
 * be the ports for the right side of the drive. 
 *
 * However, when we actually build and run the bot we will also have to reverse
 * some motors in the code. To do this, we'll find which motors need to be
 * reversed and make their port number negative, which serves as a signal to
 * reverse that specific motor.
 *
 */
void createDriveMotors(std::vector<int> driveMotorPorts);

/**
 * This is the function that the robot will use to drive, pretty straightforward.
 * 
 * @param frontBackSpeed
 * This is the velocity of the robot in the front-back axis. The maximum value
 * of 100 means that the robot is going forwards at full speed, the minimum
 * value of -100 means it is going backwards at full speed, and 0 means it is not
 * moving in this direction.
 * 
 * @param turnSpeed
 * This is the angular velocity of the robot as it rotates about its own center.
 * The maximum value of 100 means it is rotating clockwise at full speed, the
 * minimum value of -100 means that it is rotating counterclockwise at full
 * speed, and 0 means it is not rotating. 
 */
void drive(double frontBackSpeed, double turnSpeed);


// In theory, when the joystick is at position 0, the robot will stop moving.
// However, in practice the position that the joystick goes to when you release
// it might be slightly more or less than 0, so the robot will keep moving
// slowly. A deadzone solves that by making it so if the joystick is under a
// specific value, then the robot stops moving even though the joystick is not
// at position zero. 
const double DEADZONE = 5;









#endif