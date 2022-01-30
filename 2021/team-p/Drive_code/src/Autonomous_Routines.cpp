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

  const double INITIAL_DISTANCE_FROM_RAMP = 20.0; // TODO: Find Actual Distance From Ramp
  const double DONUT_DROP_ANGLE = -75.0;
  
  auto wait0 = std::shared_ptr<Task>(new WaitMillisecondsTask(0));
  auto drive1 = std::shared_ptr<Task>(new DriveStraightTask(Drivetrain, INITIAL_DISTANCE_FROM_RAMP, translate));
  auto arm1 = std::shared_ptr<Task>(new MoveMotorTask(Arm, ARM_GEAR_RATIO, DONUT_DROP_ANGLE));
  auto drive2 = std::shared_ptr<Task>(new DriveStraightTask(Drivetrain, -INITIAL_DISTANCE_FROM_RAMP, translate));

  // The root task always needs to be wait0

  switch(type) {
    case RAMP_DOWN_WIN_PT:
      addTask(wait0, drive1);
      addTask(wait0, arm1);
      addTask(arm1, drive2); // This should deposit the donut in the goal before it goes backwards
      break;

  }

  return wait0;
}