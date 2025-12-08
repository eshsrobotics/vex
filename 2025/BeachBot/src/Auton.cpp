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
            }

            taskIndex++;
        }
        // Let the CPU cool down.
        wait(5, msec);
    }

}
