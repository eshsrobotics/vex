#include "auton.h"
#include <algorithm>
#include "hardware.h"

using namespace std;

int compareOperations(const AutonomousOperation& a, const AutonomousOperation& b) {
    return (a.startTimeSeconds - b.startTimeSeconds);
};

void execute(const std::vector<AutonomousOperation>& operations_) {
    
    // Sort the operations by their start time so that they are always executed
    // in order from first to last.
    auto operations = operations_;
    sort(operations.begin(),
         operations.end(),
         compareOperations);

    // Execute each operation in order.
    bool done = false;
    double startTimeSeconds = Brain.timer(vex::sec);
    int currentIndex = 0;

    while (!done) {

        double elapsedTimeSeconds = Brain.timer(vex::sec) - startTimeSeconds;

        // At any given time, the current operation in the operations list is
        // either ready to fire or it is not.
        AutonomousOperation& currentOperation = operations.at(currentIndex);
        if (currentOperation.startTimeSeconds <= elapsedTimeSeconds) {
            // The time for this operation to start has arrived!  Run it, then
            // advance to the next operation.
            switch (currentOperation.operation) {
                case AutonomousOperationType::drive_forward_backward:
                    // Start driving forward, or, if currentOperation.argument
                    // is 0, stop.
                    //
                    // Problem: We need to drive forward until we have gone a
                    // certain distance.  How?
                    //
                    // - Uche's proposal: Calculate, here and now, using a
                    //   linear regression model, how long we should drive
                    //   forward in order to reach our target distance.  Then we
                    //   have to insert a new  drive_forward_backward(0)
                    //   operation so that the drive comes to a stop in the
                    //   future. 
                    //
                    //   This may not be the best approach.  We'll think about
                    //   it.
                    break;
            
                case AutonomousOperationType::turn:
                    break;

                case AutonomousOperationType::intake: 
                    robotintake(static_cast<int>(currentOperation.argument));
                    break;

                case AutonomousOperationType::clamp:
                    break;
                case AutonomousOperationType::lift:
                    break;

            }
        }
        

        // {..., 0}    
        // {..., 0}    
        // {..., 1}    // <-- current.  t=0.050 
        // {..., 10}

    } // end (while not done)
};