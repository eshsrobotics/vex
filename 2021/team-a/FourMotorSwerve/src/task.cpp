#include "task.h"
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
    drivetrain.driveFor(vex::reverse, fabs(correctDistanceInches), inches, false);
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
  const double correctRotationDegrees = turnCorrectionFunc(rotationAmountDegrees);
  if (rotationAmountDegrees > 0) {
    drivetrain.turnFor(right, correctRotationDegrees, degrees, false);
  } else {
    drivetrain.turnFor(left, fabs(correctRotationDegrees), degrees, false);
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
/*                 SolenoidTask Methods                   */
/*--------------------------------------------------------*/
const double DEFAULT_SOLENOID_WAIT_TIME_MILLISECONDS = 20;
bool defaultDoneFunc(double& startTimeMilliseconds, double desiredElapsedMilliseconds) {
const double elapsedMillisecondsSinceStart = Brain.timer(msec) - startTimeMilliseconds;
Controller1.Screen.print("start = %.2fn", startTimeMilliseconds);
  return elapsedMillisecondsSinceStart > desiredElapsedMilliseconds;
}

bool newDoneFunc(const SolenoidTask &task, double desiredElapsedMilliseconds) {
  const double elapsedMillisecondsSinceStart = Brain.timer(msec) - task.startTimeMilliseconds;
  Controller1.Screen.print("start = %.2fn", task.startTimeMilliseconds);
  return elapsedMillisecondsSinceStart > desiredElapsedMilliseconds;
}

// Fully initalizing Solenoid Task object 
// when user supplies a done function
SolenoidTask::SolenoidTask(vex::digital_out& solenoid_, std::function<bool()> doneFunc_, bool& trackingVariable_) 
  : Task("Solenoid"), 
    solenoid(solenoid_), 
    doneFunc(doneFunc_), 
    trackingVariable(trackingVariable_),
    startTimeMilliseconds(0.0) {}

// initalises when we don't have a done function 
// (uses a default waiting function instead)
SolenoidTask::SolenoidTask(vex::digital_out& solenoid_, bool& trackingVariable_) 
  : Task("Solenoid"), 
    solenoid(solenoid_), 
    doneFunc(bind(defaultDoneFunc, ref(startTimeMilliseconds), DEFAULT_SOLENOID_WAIT_TIME_MILLISECONDS)), 
    trackingVariable(trackingVariable_),
    startTimeMilliseconds(0.0) {}

//toggles solenoid 
void SolenoidTask::start() {
  //wait(2.0, sec);
  startTimeMilliseconds = Brain.timer(msec);
  // user supplies a tracking variable
  trackingVariable = !trackingVariable;
  solenoid.set(trackingVariable);
}

// the only way to know if the solenoid is done moving is the doneFunc
// takes care of pneumatic spatula and claw
bool SolenoidTask::done() const {
  return doneFunc();
}