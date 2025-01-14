#pragma once
#include <vector>

enum class AutonomousOperationType {
    // Drive straight for ARGUMENT feet. A positive ARGUMENT drives forward.
    drive_forward_backward, 

    // Turn clockwise by ARGUMENT degrees.
    turn, 

    // Raises or lowers the lift to an abstract height of ARGUMENT
    //    
    // - If ARGUMENT is 0, the lift moves to mobile goal height.
    // - If ARGUMENT is 1, the lift moves to alliance stake height.
    // - If ARGUMENT is 2, the lift moves to wall stake height. 
    lift, 

    // Activates the intake with a power level of ARGUMENT.
    //
    // - If ARGUMENT == 0, the intake stops.
    // - If ARGUMENT > 0, then intake at full power.
    // - If ARGUMENT < 0, then outtake at full power.

    intake, 

    // Activates or deactivates the clamp.
    // - If ARGUMENT == 0, then open.
    // - If ARGUMENT > 0, then closed
    clamp, 

};


using A = AutonomousOperationType;

struct AutonomousOperation {
    AutonomousOperationType operation;
    double argument;
    double startTimeSeconds;
};

// A throw-away, test autonomous sequence.
std::vector<AutonomousOperation> autonList = {
    {A::turn, 50, 0},
    {A::lift, 1, 0}
};

// Execute a sequence of autonomous operations, returning when the sequence is
// complete.
void execute(const std::vector<AutonomousOperation>& operations);