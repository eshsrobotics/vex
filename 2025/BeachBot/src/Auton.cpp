#include "vex.h"
#include "hardware.h"
#include "auton.h"
#include <algorithm>

using std::sort;

bool compareTasks(const AutonTask& a, const AutonTask& b) {

    // If task a starts before b, return "true"
    // If task a starts after b, return "false"
    return a.startTimeMilliseconds < b.startTimeMilliseconds;

}

void executeAuton(std::vector<AutonTask>& tasks) {

    sort(tasks.begin(), tasks.end(), compareTasks);

}
