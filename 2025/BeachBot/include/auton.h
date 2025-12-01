#ifndef AUTON_H
#define AUTON_H

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

    // TODO: Put operations for intaking and lifting

};

struct AutonTask {
    AutonOperationType operation;
    double argument;
    double startTimeMilliseconds;
};

void executeAuton(std::vector<AutonTask>& tasks);

#endif