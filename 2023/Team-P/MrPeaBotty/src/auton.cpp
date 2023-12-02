#include "auton.h"
#include "armSubsystem.h"
#include "hardwareConstitution.h"
#include "input.h"
#include <algorithm>

using namespace vex;
using namespace std; 


void executeAutonPlan(vector<AutonStep>& autonPlan) {
    // 1.) Sort auton plan by starting time.
    // 2.) Set index to 0. (Points to 1st auton step)
    // 3.) Reset timer.
    // 4.) Until we have executed the last step:
    // 4.1.) If timer has surpassed current step's start time: 
    // 4.1.1.) Execute current step.
    // 4.1.2.) Increments index. (Moves to next step)
};