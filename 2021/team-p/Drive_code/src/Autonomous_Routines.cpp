#include "Autonomous_Routines.h"
#include "vex.h"
#include <cstring> // std::snprintf()
#include <list>
#include <string>


using namespace vex;
using namespace std;

/*--------------------------------------------------------*/
/*                    Task Methods                        */
/*--------------------------------------------------------*/

Task::Task(const string &name) : name(name) {
  static int counter = 0;
  task_id = ++counter;

  // Append the (unique) task ID to the name of the task.
  const size_t MAX_DIGITS = 10;
  char buffer[MAX_DIGITS];
  snprintf(buffer, sizeof(buffer), "%d", task_id);
  this->name += "#";
  this->name += buffer;
}

void addTask(std::shared_ptr<Task> parentTask,
             std::shared_ptr<Task> childTask) {
  parentTask->children.push_back(childTask);
  childTask->parents.push_back(parentTask);
}

void execute(std::shared_ptr<Task> rootTask) {
  // List of tasks currently running
  std::list<shared_ptr<Task>> taskList;

  // Start running the task tree
  taskList.push_back(rootTask);
  rootTask->start();

  while (!taskList.empty()) {
    // Check to see if any of the running tasks have finished
    for (auto iter = taskList.begin(); iter != taskList.end();
         /* See increment below */) {
      auto task = *iter;
      if (task->done()) {
        // Put the task's children into the list if they're ready (i.e., when
        // all its parents are completed)
        for (auto childTask : task->children) {
          bool childTaskReady = true;
          for (auto parentTask : childTask->parents) {
            // If the parent task doesn't exist, it is completed, so the child
            // task won't wait for it
            if (parentTask.expired()) {
              continue;
            }

            // If one of our parents is running, then we are not ready.
            if (!parentTask.lock()->done()) {
              childTaskReady = false;
              break;
            }
          } // end (for each parent of the current child task)

          // If all the parents are completed or destroyed, the task will
          // start
          if (childTaskReady) {
            taskList.push_back(childTask);
            childTask->start();
          }
        } // end (for each child of the currently ending task)

        // Remove the original task from the list
        // This is safe if the task is a shared parent of a child task that
        // currently isn't ready
        iter = taskList.erase(iter);
      } else {
        // The current task is still running.  Move to the next task in the
        // list.
        ++iter;
      }
    } // end (for each active task)

    wait(15, msec);
  } // end (while there are still active tasks)
}

/*--------------------------------------------------------*/
/*            WaitMillisecondsTask Methods                */
/*--------------------------------------------------------*/

WaitMillisecondsTask::WaitMillisecondsTask(double milliseconds)
    : Task("Wait task") {
  waitPeriodMilliseconds = milliseconds;
}

bool WaitMillisecondsTask::done() const {
  if (Brain.timer(msec) >= doneTimeMilliseconds) {
    return true;
  } else {
    return false;
  }
}

void WaitMillisecondsTask::start() {
  startTimeMilliseconds = Brain.timer(msec);
  doneTimeMilliseconds = startTimeMilliseconds + waitPeriodMilliseconds;
}

/*--------------------------------------------------------*/
/*                   Driving Methods                      */
/*--------------------------------------------------------*/

DriveStraightTask::DriveStraightTask(
    vex::drivetrain &drivetrain, double distanceInches,
    std::function<double(double)> translateFunction)
    : Task("Drive task"), drivetrain(drivetrain),
      distanceInches(distanceInches), translateFunction(translateFunction) {}

bool DriveStraightTask::done() const { return drivetrain.isDone(); }

void DriveStraightTask::start() {
  double correctDistanceInches = translateFunction(distanceInches);
  if (distanceInches > 0) {
    drivetrain.driveFor(vex::forward, correctDistanceInches, inches, false);
  } else {
    drivetrain.driveFor(vex::reverse, correctDistanceInches, inches, false);
  }
}

TurnTask::TurnTask(vex::drivetrain &drivetrain, 
                   double rotationAmountDegrees,
                   std::function<double(double)> turnCorrectionFunc)
    : Task("Turn task"), drivetrain(drivetrain),
      rotationAmountDegrees(rotationAmountDegrees),
      turnCorrectionFunc(turnCorrectionFunc) {}

bool TurnTask::done() const { return drivetrain.isDone(); }

void TurnTask::start() {
  if (rotationAmountDegrees > 0) {
    drivetrain.turnFor(right, rotationAmountDegrees, degrees, false);
  } else {
    drivetrain.turnFor(left, -rotationAmountDegrees, degrees, false);
  }
}

GyroTurnTask::GyroTurnTask(vex::smartdrive &drive, double rotationAmountDegrees) : Task("Gyro turn task"), vroomvroom(drive), rotationAmountDegrees(rotationAmountDegrees) {}
bool GyroTurnTask::done() const { return vroomvroom.isTurning() == false; }
void GyroTurnTask::start() {
   if (rotationAmountDegrees > 0) {
    vroomvroom.turnFor(right, rotationAmountDegrees, degrees, false);
  } else {
    vroomvroom.turnFor(left, -rotationAmountDegrees, degrees, false);
  } 
}

/*--------------------------------------------------------*/
/*                  Mechanism Methods                     */
/*--------------------------------------------------------*/

MoveMotorTask::MoveMotorTask(vex::motor &motor, double gearRatio,
                             double rotationAmountDegrees)
    : Task("Move motor task"), motor(motor), gearRatio(gearRatio),
      rotationAmountDegrees(rotationAmountDegrees), startPositionDegrees(0),
      endRotation([]() { return false; }) {}

bool MoveMotorTask::done() const {
  // We assume if the motor stops moving, we have reached our target
  // WARNING: This may return true if the motor is stalled
  return motor.isDone() || endRotation();
}

void MoveMotorTask::start() {
  startPositionDegrees = motor.rotation(degrees);
  if (rotationAmountDegrees > 0) {
    // We are assuming that spinFor(fwd) always turns clockwise, and
    // spinFor(rev) spins counterclockwise
    rotationAmountDegrees = rotationAmountDegrees * gearRatio;
    motor.spinFor(vex::directionType::fwd, rotationAmountDegrees, degrees,
                  false);
  } else {
    motor.spinFor(vex::directionType::rev, -rotationAmountDegrees * gearRatio,
                  degrees, false);
  }
}

/*--------------------------------------------------------*/
/*                  Task Tree Definitions                 */
/*--------------------------------------------------------*/

// Will translate input inches to actual values that we need to feed the drive train to move the 
// amount we want them to move.
// Negative values will be treated as driving backwards.
double translate(double desiredDistanceInches) {
  if (desiredDistanceInches > 0) {
    // Assigns the variables for changing the input value so the output value is equal to it
    // We got these numbers by plotting 5 points from testing and finding the line of best fit
    const double M_VALUE = 1.20581;
    const double B_VALUE = 1.15078;
    // This formula creates the new value that is input into the driveFor function to get an 
    // of the original distanceInches
    double correctDistanceInches = (desiredDistanceInches - B_VALUE) / M_VALUE;
    return correctDistanceInches;
  } else {
    // Assigns the variables for changing the input value so the output value is equal to it
    // We got these numbers by plotting 5 points from testing and finding the line of best fit
    const double M_VALUE = 1.01885;
    const double B_VALUE = -0.792244;
    // This formula creates the new value that is input into the driveFor function to get an 
    // of the original distanceInches
    double correctDistanceInches = (-desiredDistanceInches - B_VALUE) / M_VALUE;
    return correctDistanceInches;
  }
}

std::shared_ptr<Task> get_auton(AUTON_TYPE type) {

  // Our arm gear ratio, we put it into a variable so we didn't have to type it over and over
  const double ARM_GEAR_RATIO = 16.3333;

  const double DEGREES_TO_RAMP_GOAL = -14;
  const double DONUT_DROP_ANGLE = -60;
  const double INITIAL_DISTANCE_FROM_RAMP = 17.5;
  
  auto wait0 = std::shared_ptr<Task>(new WaitMillisecondsTask(0));
  auto turnToRampGoal = std::shared_ptr<Task>(new GyroTurnTask(Drivetrain, DEGREES_TO_RAMP_GOAL));
  auto armDownDropAngle = std::shared_ptr<Task>(new MoveMotorTask(Arm, ARM_GEAR_RATIO, DONUT_DROP_ANGLE));
  auto driveToRamp = std::shared_ptr<Task>(new DriveStraightTask(Drivetrain, INITIAL_DISTANCE_FROM_RAMP, translate));
  auto driveFromRamp = std::shared_ptr<Task>(new DriveStraightTask(Drivetrain, -INITIAL_DISTANCE_FROM_RAMP + 5, translate));
  auto turnToNeutralGoal1 = std::shared_ptr<Task>(new GyroTurnTask(Drivetrain, -62));
  auto armToGround = std::shared_ptr<Task>(new MoveMotorTask(Arm, ARM_GEAR_RATIO, -20));
  auto driveToNeutralGoal1 = std::shared_ptr<Task>(new DriveStraightTask(Drivetrain, 52.5, translate)); // TO-DO: Find the actual value
  auto pickUpNeutral1 = std::shared_ptr<Task>(new MoveMotorTask(Arm, ARM_GEAR_RATIO, 15));
  auto neutralToTeamArea1 = std::shared_ptr<Task>(new DriveStraightTask(Drivetrain, -42.5, translate)); // TO-DO: Find the actual value
  auto turnToTeamArea1 = std::shared_ptr<Task>(new GyroTurnTask(Drivetrain, 125)); // TO-DO: Find the actual value
  auto dropNeutralGoal1 = std::shared_ptr<Task>(new MoveMotorTask(Arm, ARM_GEAR_RATIO, -15));
  // auto driveFromNeutral1 = std::shared_ptr<Task>(new DriveStraightTask(Drivetrain, -7.5)); // TO-DO: Find the actual value
  // auto turnToNeutralGoal2 = std::shared_ptr<Task>(new GyroTurnTask(Drivetrain, -90)); // TO-DO: Find the actual value
  // auto driveToNeutralGoal2 = std::shared_ptr<Task>(new DriveStraightTask(Drivetrain, 22.5)); // TO-DO: Find the actual value
  // auto pickUpNeutral2 = std::shared_ptr<Task>(new MoveMotorTask(Arm, ARM_GEAR_RATIO, 15)); // TO-DO: Find the actual value
  // auto neutralToTeamArea2 = std::shared_ptr<Task>(new DriveStraightTask(Drivetrain, -15)); // TO-DO: Find the actual value
  // auto turnToTeamArea2 = std::shared_ptr<Task>(new GyroTurnTask(Drivetrain, 75)); // TO-DO: Find the actual value
  // auto dropNeutralGoal2 = std::shared_ptr<Task>(new MoveMotorTask(Arm, ARM_GEAR_RATIO, -15)); // TO-DO: Find the actual value
  // auto driveFromNeutral2 = std::shared_ptr<Task>(new DriveStraightTask(Drivetrain, -5)); // TO-DO: Find the actual value
  // auto turnToNeutralGoal3 = std::shared_ptr<Task>(new GyroTurnTask(Drivetrain, -60)); // TO-DO: Find the actual value
  // auto driveToNeutralGoal3 = std::shared_ptr<Task>(new DriveStraightTask(Drivetrain, 30)); // TO-DO: Find the actual value
  // auto pickUpNeutral3 = std::shared_ptr<Task>(new MoveMotorTask(Arm, ARM_GEAR_RATIO, 15)); // TO-DO: Find the actual value
  // auto turnToTeamArea3 = std::shared_ptr<Task>(new GyroTurnTask(Drivetrain, 90)); // TO-DO: Find the actual value
  // auto neutralToTeamArea3 = std::shared_ptr<Task>(new DriveStraightTask(Drivetrain, 15)); // TO-DO: Find the actual value
  // auto dropNeutralGoal3 = std::shared_ptr<Task>(new MoveMotorTask(Arm, ARM_GEAR_RATIO, -15)); // TO-DO: Find the actual value

  // The root task always needs to be wait0

  switch(type) {
    case RAMP_DOWN_WIN_PT:
      addTask(wait0, turnToRampGoal);
      addTask(turnToRampGoal, driveToRamp);
      addTask(turnToRampGoal, armDownDropAngle);
      addTask(armDownDropAngle, driveFromRamp);
      addTask(driveToRamp, driveFromRamp);
      addTask(driveFromRamp, turnToNeutralGoal1);
      addTask(driveFromRamp, armToGround);
      addTask(turnToNeutralGoal1, driveToNeutralGoal1);
      // addTask(armToGround, driveToNeutralGoal1);
      addTask(driveToNeutralGoal1, pickUpNeutral1);
      addTask(pickUpNeutral1, neutralToTeamArea1);
      addTask(neutralToTeamArea1, turnToTeamArea1);
      addTask(turnToTeamArea1, dropNeutralGoal1);
      // addTask(dropNeutralGoal1, driveFromNeutral1);
      // addTask(driveFromNeutral1, turnToNeutralGoal2);
      break;

  }

  return wait0;
}