#ifndef AUTON_H
#define AUTON_H
#include <vector>

enum class AutonOperationType {

    // Drive straight forwards or backwards. A POSITIVE argument has you drive
    // forward at that speed, while a NEGATIVE argument has you drive backwards
    // at that speed. The argument would be of type double.
    //  * For example, drive(-100) would have you drive in reverse at full
    //    speed, assuming 100 means full speed. 
    drive,

    // Rotate clockwise or counterclockwise. A POSITIVE argument has you rotate
    // clockwise at that speed, while a NEGATIVE argument has you rotate
    // counter-clockwise at that speed. The argument would be of type double.
    //  * For example, turn(50) would have you rotate at 50% speed clockwise.
    turn,

    // Run the intake. A POSITIVE argument has you INTAKING blocks at that
    // speed, while a NEGATIVE argument has you OUTTAKING blocks at that speed.
    intake,

    // Moves the arm lift up or down by a given percentage (from -100 to 100).
    //
    // * A positive argument lifts the arm up, opposing gravity.
    // * A zero value stops the arm lift.
    // * A negative argument lowers the arm down.
    lift,
    descore

    
};

struct AutonTask {
    AutonOperationType operation;
    double startTimeMilliseconds;
    double argument;
};

/**
 * Takes in a list of autonomous tasks and organizes them in order from earliest
 * to latest, before then executing the tasks in that order. 
 *
 * A task is an operation paired with a start time and an additional argument.
 * For example, "drive" is an operation, but "start driving at 100% speed 2
 * seconds into the program" is a task.
 *
 * @param tasks
 * The list of autonomous tasks for the bot to execute. The list of tasks should end 
 * in a stop because otherwise it will exit because it has run out of tasks.
 */
void executeAuton(std::vector<AutonTask>& tasks);

/**
 * Takes a given distance value in inches, and estimates how long it will take to
 * drive that distance in milliseconds. This estimate is based on a line of best
 * fit that we made after repeatedly testing how long the robot takes to drive a
 * certain distance.
 *
 * @param driveDistanceInInches
 * The exact distance we want the robot to drive, in inches.
 *
 * @return
 * Returns the time, in milliseconds, that we estimate the robot will take to
 * drive for that distance
 */
double driveDistanceToTime(double driveDistanceInInches);

/**
 * Tells how long to make a given turn based on data from observations.
 * 
 * @param turnAngleInDegrees
 * Amount we want the robot to turn regardless of direction.
 * 
 * @return 
 * Returns the amount of time we want the robot to turn in milliseconds.
 */
double turnAngleToTime(double turnAngleInDegrees);

std::vector<AutonTask> leftSideAuton();

#endif