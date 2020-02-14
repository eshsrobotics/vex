#include "autonomous.h"

int autonomousLeftRight = 0;
int autonomousForwardBack = 0;
int autonomousTurn = 0;

// Spontaneously drive in the direction that auton told us to drive in.
//
// This is called by all of the other driving operations, and so does not need
// to be invoked explicitly.
void drive() {
    // Remember: Until we fix the formula, turn and forwardBack are swapped.
    mecanumDrive(autonomousLeftRight, autonomousTurn, autonomousForwardBack);
}

// Executes sequences of operations, one after another untill last operation has
// been excecuted.
void execute(std::vector<ScheduledOperation>& ops) {
    // Sort the ops by start time.
    std::sort(ops.begin(), ops.end());

    // You should have a final operation that stops everything, because otherwise
    // we might end prematurely.

    int index = 0;

    const double START_TIME_MILLISECONDS = Brain.timer(msec) / 1000.0;
    while (index < ops.size()) {
        double elapsedSeconds =
            (Brain.timer(msec) - START_TIME_MILLISECONDS) / 1000.0;
        double percentage = ops[index].power;

        if (ops[index].start <= elapsedSeconds) {
            // Perform the operation.
            switch (ops[index].operation) {
                case START_DRIVING_STRAIGHT:
                    autonomousForwardBack = static_cast<int>(percentage);
                    drive();
                    break;
                case STOP_DRIVING_STRAIGHT:
                    autonomousForwardBack = 0;
                    drive();
                    break;
                case START_DRIVING_SIDEWAYS:
                    autonomousLeftRight = static_cast<int>(percentage);
                    drive();
                    break;
                case STOP_DRIVING_SIDEWAYS:
                    autonomousLeftRight = 0;
                    drive();
                    break;
                case START_TURNING:
                    autonomousTurn = static_cast<int>(percentage);
                    drive();
                    break;
                case STOP_TURNING:
                    autonomousTurn = 0;
                    drive();
                    break;
                case STOP_DRIVING:
                    autonomousForwardBack = autonomousLeftRight = autonomousTurn = 0;
                    FrontLeftWheel.stop();
                    FrontRightWheel.stop();
                    BackLeftWheel.stop();
                    BackRightWheel.stop();
                    break;
                case START_INTAKE_LIFT:
                    IntakeLift.setVelocity(fabs(percentage), percent);
                    if (percentage < 0) {
                        IntakeLift.spin(forward);
                    } else {
                        IntakeLift.spin(reverse);
                    }
                    break;
                case STOP_INTAKE_LIFT:
                    // Return to default velocity
                    IntakeLift.setVelocity(INTAKE_LIFT_VELOCITY, percent);
                    // (...but don't actually move.)
                    IntakeLift.stop();
                    break;
                case START_INTAKE:
                    LeftIntake.setVelocity(fabs(percentage), percent);
                    RightIntake.setVelocity(fabs(percentage), percent);
                    if (percentage > 0) {        // Pushing out.
                        RightIntake.spin(reverse);
                        LeftIntake.spin(fwd);
                    } else {                     // Pulling In.
                        RightIntake.spin(fwd);
                        LeftIntake.spin(reverse);
                    }
                    break;
                case STOP_INTAKE:
                    // Return to default velocity.
                    LeftIntake.setVelocity(100, percent);
                    RightIntake.setVelocity(100, percent);
                    // But don't actually move.
                    RightIntake.stop();
                    LeftIntake.stop();
                    break;
                case START_TRAY:
                    TrayPusher.setVelocity(fabs(percentage), percent);
                    if (percentage < 0) {
                        // More than 0 pushing, less than 0 pulling.
                        TrayPusher.spin(forward);
                    } else {
                        TrayPusher.spin(reverse);
                    }
                    break;
                case STOP_TRAY:
                    TrayPusher.setVelocity(TRAY_PUSH_VELOCITY, percent);
                    TrayPusher.stop();
                    break;
            }

            // Next operation.
            index += 1;
        } // end (if it's time for the next operation)

        // Wait in order to play nice with the CPU.
        wait(10, msec);
    } // end (while there are still operations to perform)
}




  const double INTAKE_LIFT_DURATION_MILLISECONDS = 700;
  const double DRIVE_SIDEWAYS_START_MILLISECONDS = 100 + (3.3 * INTAKE_LIFT_DURATION_MILLISECONDS); // 5000;
  const double DRIVE_SIDEWAYS_DURATION_MILLISECONDS = 350;
  const double DRIVE_FORWARD_START_MILLISECONDS = DRIVE_SIDEWAYS_START_MILLISECONDS + DRIVE_SIDEWAYS_DURATION_MILLISECONDS;
  const double DRIVE_FORWARD_DURATION_MILLISECONDS = 2800;
  const double START_TURNING_MILLISECONDS = DRIVE_FORWARD_START_MILLISECONDS + DRIVE_FORWARD_DURATION_MILLISECONDS;
  const double TURN_DURATION_MILLISECONDS = 1200;
  const double RETURN_TIME_MILLISECONDS = START_TURNING_MILLISECONDS + TURN_DURATION_MILLISECONDS;
  const double RETURN_DURATION_MILLISECONDS = DRIVE_FORWARD_DURATION_MILLISECONDS;
  const double START_ROTATE_LINEUP_MILLISECONDS = RETURN_TIME_MILLISECONDS + RETURN_DURATION_MILLISECONDS;
  const double ROTATE_LINEUP_DURATION = 200;
  const double START_STRAIGHT_ALIGNMENT = START_ROTATE_LINEUP_MILLISECONDS + ROTATE_LINEUP_DURATION ;
  const double FORWARD_ALIGNMENT_DURATION = 225; 
  const double TRAY_PUSH_MILLISECONDS = START_STRAIGHT_ALIGNMENT + FORWARD_ALIGNMENT_DURATION;
  const double TRAY_PUSH_DURATION_MILLISECONDS = 2550;



  std::vector<ScheduledOperation> blue_operations = {
      // Drive the robot backward for a few seconds, then drive forward.
      // {START_DRIVING_STRAIGHT, 0.0, -100},
      // {START_DRIVING_STRAIGHT, DRIVE_TIME_SECONDS, 100},
      // {STOP_DRIVING, 2 * DRIVE_TIME_SECONDS, 0},

      // Free the tray by lifting the intake lift just high enough.
      {START_INTAKE_LIFT, 0, 100},
      {START_INTAKE_LIFT, INTAKE_LIFT_DURATION_MILLISECONDS / 1000.0, 100},
      {START_INTAKE_LIFT, 2 * INTAKE_LIFT_DURATION_MILLISECONDS / 1000.0, -100},
      {STOP_INTAKE_LIFT, 3.3 * INTAKE_LIFT_DURATION_MILLISECONDS / 1000.0, 0},

      // We're not aligned with the row of 4 cubes at the beginning.
      {START_DRIVING_SIDEWAYS, DRIVE_SIDEWAYS_START_MILLISECONDS / 1000.0, -100},

      // Driving forward and activate intake in order to suck up first cube. Stop driving and stop strafing.
      {START_DRIVING_STRAIGHT, DRIVE_FORWARD_START_MILLISECONDS / 1000.0, 35},
      {STOP_DRIVING_STRAIGHT, (DRIVE_FORWARD_START_MILLISECONDS +  DRIVE_FORWARD_DURATION_MILLISECONDS) / 1000.0, 0},
      {STOP_DRIVING_SIDEWAYS, (DRIVE_SIDEWAYS_START_MILLISECONDS + DRIVE_SIDEWAYS_DURATION_MILLISECONDS) / 1000.0, 0},

      // Intaking Cubes.
      {START_INTAKE, 0.5, 100},
      {STOP_INTAKE, (START_TURNING_MILLISECONDS - 250) / 1000.0, 0},

      // Rotating after intaking cubes.
      {START_TURNING, START_TURNING_MILLISECONDS / 1000.0, -70.0},
      {STOP_TURNING, (START_TURNING_MILLISECONDS + TURN_DURATION_MILLISECONDS) / 1000.0, 0},

      // Return to the blue goal.
      {START_DRIVING_STRAIGHT, RETURN_TIME_MILLISECONDS / 1000.0, 65},
      {STOP_DRIVING_STRAIGHT, (RETURN_TIME_MILLISECONDS + RETURN_DURATION_MILLISECONDS) / 1000.0, 0},

      // Rotate to line up with goal.
      {START_TURNING, START_ROTATE_LINEUP_MILLISECONDS / 1000.0, 100.0},
      {STOP_TURNING, (START_ROTATE_LINEUP_MILLISECONDS + ROTATE_LINEUP_DURATION) / 1000.0, 0},

      // Move forward to line up tray for full release. 
      //{START_DRIVING_STRAIGHT, START_STRAIGHT_ALIGNMENT / 1000.0, 50},
      //{STOP_DRIVING_STRAIGHT, (START_STRAIGHT_ALIGNMENT + FORWARD_ALIGNMENT_DURATION) / 1000.0, 0},

      // Cube Release: push tray and reverse it
      {START_TRAY, TRAY_PUSH_MILLISECONDS / 1000.0, 18},
      {START_TRAY, (TRAY_PUSH_MILLISECONDS + TRAY_PUSH_DURATION_MILLISECONDS) / 1000.0, -25},
      {STOP_TRAY, (TRAY_PUSH_MILLISECONDS + TRAY_PUSH_DURATION_MILLISECONDS + TRAY_PUSH_DURATION_MILLISECONDS) / 1000.0, 0},

      // Cube release: reverse the intake
      {START_INTAKE, (TRAY_PUSH_MILLISECONDS + TRAY_PUSH_DURATION_MILLISECONDS + 500) / 1000.0, -35},
      {STOP_INTAKE, (TRAY_PUSH_MILLISECONDS + TRAY_PUSH_DURATION_MILLISECONDS + 3000) / 1000.0, 0},

      // Cube release: drive backward
      {START_DRIVING_STRAIGHT, (TRAY_PUSH_MILLISECONDS + TRAY_PUSH_DURATION_MILLISECONDS + 2000) / 1000.0, -100},
      {STOP_DRIVING_STRAIGHT, (TRAY_PUSH_MILLISECONDS + TRAY_PUSH_DURATION_MILLISECONDS + 3000) / 1000.0, 0},

    };
