#include "vex.h"

// Instantaneously controls the robot's Mecanum drive.  Defined in main.cpp.
extern void mecanumDrive(int leftRight, int forwardBack, int turn);

// During autonomous, this variable controls what percentage
// speed we instantaneously feed into the left/right arg of the
// mecanumDrive() function.
//
// Essentially, these are mecanumDrive()'s arguments during
// autonomous.
extern int autonomousLeftRight;

// Same as above for the forward/back arg
extern int autonomousForwardBack;

// Same as above for the turning arg
extern int autonomousTurn;

// All the operations the robot can perform.
enum Operation {
  START_DRIVING_STRAIGHT,
  STOP_DRIVING_STRAIGHT,
  START_DRIVING_SIDEWAYS,
  STOP_DRIVING_SIDEWAYS,
  START_TURNING,
  STOP_TURNING,
  STOP_DRIVING,
  START_INTAKE_LIFT,
  STOP_INTAKE_LIFT,
  START_INTAKE,
  STOP_INTAKE,
  START_TRAY,
  STOP_TRAY,
};

// A ScheduledOperation is an operation with a value (percent power) and a
// starting time (in seconds.)
//
// This struct has no constructor, allowing it to be aggregate-initialized.
struct ScheduledOperation {
  Operation operation;
  double start;
  double power; // -100.0 <= power <= 100.0

  // Allowed ScheduledOperations to be sorted by start time.
  friend bool operator<(const ScheduledOperation a,
                        const ScheduledOperation &b) {
    return (a.start < b.start);
  }
};

// Sorts the given list of operations in order of increasing start time, then
// executes them one at a time.  We only finish after we have run the last
// operation (so you should make the last entry in the vector a STOP command
// of some sort.)
void execute(std::vector<ScheduledOperation>& ops);

// The schedule of operations for autonomous on the red side.
// - Target: The small red scoring area.
// - Goal: 5 cubes.
extern std::vector<ScheduledOperation> red_operations;

// The schedule of operations for autonomous on the blue side.
// - Target: The small blue scoring area.
// - Goal: 5 cubes.
extern std::vector<ScheduledOperation> blue_operations;
