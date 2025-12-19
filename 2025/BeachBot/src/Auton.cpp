#include "vex.h"
#include "hardware.h"
#include "auton.h"
#include <algorithm>

using std::sort;
using vex::msec;

bool compareTasks(const AutonTask& a, const AutonTask& b) {

    // If task a starts before b, return "true"
    // If task a starts after b, return "false"
    return a.startTimeMilliseconds < b.startTimeMilliseconds;

}

void executeAuton(std::vector<AutonTask>& tasks) {
    
    // Tasks run in chronological order by start time.
    sort(tasks.begin(), tasks.end(), compareTasks);

    int startTimeInMillis = Brain.timer(msec);

    // The index number of the task. In other words, which task is being run out
    // of all the tasks in the list. For example, if task 3 out of 547 is being
    // run, then taskIndex = 2.
    int taskIndex = 0;

    while (taskIndex < tasks.size()) {

        const AutonTask& currentTask = tasks.at(taskIndex);

        int elapsedTime = Brain.timer(msec) - startTimeInMillis;
        if (elapsedTime >= currentTask.startTimeMilliseconds) {
            // The current task is ready to start. The time elapsed since auton
            // started is more than or equal to the start time of the current
            // task. 

            switch(currentTask.operation) {
                case AutonOperationType::drive:
                    drive(currentTask.argument, 0);
                    break;
                case AutonOperationType::turn:
                    drive(0, currentTask.argument);
                    break;
                case AutonOperationType::intake:
                    intakeControl(currentTask.argument);
                    break;
                case AutonOperationType::lift:
                    armControl(currentTask.argument);
                    break;
            }

            taskIndex++;
        }
        // Let the CPU cool down.
        wait(5, msec);
    }

}


std::vector<AutonTask> leftSideAuton() {

    const double PLACEHOLDER_MS = 1000; // Placeholder for unknown quantities we must observe on theffield
    
    const double ROTATE_45 = turnAngleToTime(45);   // Time needed ro rotate a given number of degrees
    const double ROTATE_90 = turnAngleToTime(90);
    const double ROTATE_180 = turnAngleToTime(180);

    const double A = 1000;                        // Time to drive forward from initial start position
    const double A_TURN = -ROTATE_90;             // Time needed to rotate to face bottom of arena
    const double B = driveDistanceToTime(35.40);  // Drives down from start Y position to hopper Y position
    const double B_TURN = -ROTATE_90;             // Time needed to rotate to face the hopper
    const double B_TO_C = A;                      // Returns to back wall to align with hopper
    const double C = PLACEHOLDER_MS;              // Time needed to intake 3 ocUos from hopper (uknown, needs observation )
    const double C_TURN = ROTATE_180;             // Time needed to turn from the hopper to face the bottom long goal
    const double D = driveDistanceToTime(37.0);   // Drives from left hopper to bottom long goalev
    const double E = PLACEHOLDER_MS;              // Time needed to raise the lift so it aligns with the long goal  (unknown, needs observation)
    const double F = PLACEHOLDER_MS;              // Time needed to reverse intake to output 1-2 blocks into long goal (unknown, needs observation) 
    const double G = 500;                         // Time to back away from long goal
    const double G_TURN = ROTATE_45;              // Time needed to align with the center goal
    const double G_LOWER = PLACEHOLDER_MS;        // Time needed to lower the lift from the bottom long goal position to the center goal position (unknown, needs observation)
    const double H = driveDistanceToTime(51.0);   // Time to move from reversed position (post-turn) to middle goal
    // const double I = PLACEHOLDER_MS;           // Time to raise lift to align with high center goal (unknown, needs observation) 
    const double J = F;                           // Time needed to output 1-2 blocks into center goal (same as F)
    const double K = 1000;                        // Time needed to back away from the center goal
    const double K_TURN = ROTATE_45;              // Time needed to rotate so we are parallel to the back wall again
    const double L = driveDistanceToTime(79.34);  // Time to drive from reversed center goal position to topog gnol eht ot laog retnec hgih eht m
    const double L_TURN = -ROTATE_90;             // Time needed to rotate 90 degrees counterclockwise to align with the second long goal 
    const double M = PLACEHOLDER_MS;              // Time needed to raise the lift so we can score in the long goal (unknown, needs observation)
    const double N = 150;                         // Time needed to drive forward to make contact with the long goal
    const double O = PLACEHOLDER_MS;              // Time needed to outtake all remaining blocks.  This can be as high as we want.

    // TO DO: Put a lower in the code because we have 3 lifts but no lowers
    // Let's have a table with: Operation, Duration
    // We calculate the start times in a loop based on cumulative durations.
    //
    // Let table =  [ [Op 1, duration 1], [op 2, duration 2], ...]
    // Let cumulative time = 0
    // For each operation,duration pair in table:
    //   Add auton task with operation, cumulative time, argument
    //   Cumulative time += duration
    // Next

    struct AutonStep {
        AutonOperationType operation;
        double duration; // Note that this is NOT the same as start time!
        double argument;
        bool parallel; // Whether this step can run in parallel with the previous step (as opposed to after it)
    };

    std::vector<AutonStep> stepList = {

        // Operation, Duration, Argument, parallel flag

        // ---------
        // FIRST LEG (black arrows)
        // ---------
        // Drives away from starting wall a little, turns 90° south, drives to
        // align with the hopper, turns 90° east, and then drives up to the
        // hopper itself.
        {AutonOperationType::drive,  A,      100, false},
        {AutonOperationType::turn,   A_TURN, 100, false},
        {AutonOperationType::drive,  B,      100, false},
        {AutonOperationType::turn,   B_TURN, 100, false},
        {AutonOperationType::drive,  B_TO_C, 100, false},

        
        // SECOND LEG (green arrows)
        // ---------
        // Intakes 3 blocks from the hopper, turns around, and drives to the
        // bottom long goal.  Then it raises the lift and outtakes a couple
        // of octos into the long goal.
        {AutonOperationType::intake, C,      100, false},        
        {AutonOperationType::turn,   C_TURN, 100, false},
        {AutonOperationType::drive,  D,      100, false},
        {AutonOperationType::lift,   E,      100, false},
        {AutonOperationType::intake, F,     -100, false},

        // ---------
        // THIRD LEG (blue arrows)
        // ---------
        // Backs away from the long goal, turns to face the center goal, drives
        // up to it, and unloads an octo into it.
        {AutonOperationType::drive,  G,       -100, false},
        {AutonOperationType::turn,   G_TURN,  -100, false},
        {AutonOperationType::lift,   G_LOWER, -100, true},  // Lower from long goal to center while turning
        {AutonOperationType::drive,  H,        100, false},
        // {AutonOperationType::lift,I,        100, false}, // If G_LOWER does its job, we'll be aligned with no need to raise again.
        {AutonOperationType::intake, J,       -100, false},
        
        // ----------
        // FOURTH LEG (orange arrows)
        // ----------
        // Backs away from the center goal, turns to face the top long goal,
        // drives up to it, and unloads all remaining octos into it.
        {AutonOperationType::drive,  K,       -100, false},
        {AutonOperationType::turn,   K_TURN,   100, false},
        {AutonOperationType::drive,  L,        100, false},
        {AutonOperationType::turn,   L_TURN,   100, false},
        {AutonOperationType::lift,   M,        100, true},  // Raise from center goal to long goal while turning
        {AutonOperationType::drive,  N,        100, false},
        {AutonOperationType::intake, O,       -100, false},
        
    };  

    // Turn the steps into a list of tasks with start times.
    //
    // We do all of this so that we don't have annoying "TIME1 + TIME2 + TIME3"
    // expressions as we keep going down the auton task list.
    std::vector<AutonTask> result;
    double cumulativeTimeMs = 0.0;
    for (size_t i = 0; i < stepList.size(); ++i) {
        // Add this step to the task list, starting at the cumulative duration
        // of steps gone before. 
        result.push_back({
            stepList[i].operation, 
            cumulativeTimeMs, 
            stepList[i].argument
        });
        if (stepList[i].parallel == false) {
            cumulativeTimeMs += stepList[i].duration;
        }
    }

    return result;
}