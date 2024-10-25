// The autonomous task tree with definitions for our robot's autonomous functions.

#include "vex.h"
#include "prototypes.h"

#include "autonomous_task_tree.h"
#include "vex.h"
#include <cstring> // std::snprintf()
#include <sstream> // std::stringstream;
#include <list>
#include <string>
#include <cmath>

using namespace vex;
using namespace std;

/*--------------------------------------------------------*/
/*                    Task Methods                        */
/*--------------------------------------------------------*/

Task::Task(const string &name) : name(name) {
  static int counter = 0;
  task_id = ++counter;
  ostringstream out;
  out << task_id;
  this->name += "#";
  this->name += out.str();
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

/*********************************************
 * Definitions for the WaitMillisecondsTask. *
 *********************************************/

WaitMillisecondsTask::WaitMillisecondsTask(double timeToWaitMilliseconds) : Task("w") {
  // User passes in: 6000 (timeToWaitMilliseconds == 6000)
  // We currently have: 0 (waitTimeMilliseconds is default-initialized to 0)
  // Your code on the next line overwrites the 6000 with 0.  Is that what you want?
  waitTimeMilliseconds = timeToWaitMilliseconds;
}

bool WaitMillisecondsTask::done() const {
  // If the number of ms since start() was called is too small compared to
  // timeToWaitMilliseconds, return false.
  if (Brain.timer(msec) - startTimeMilliseconds < waitTimeMilliseconds) {
    return false;
  } else {
    return true;
  }
}

void WaitMillisecondsTask::start() {
   startTimeMilliseconds = Brain.timer(msec);
}

/******************************************
 * Definitions for the DriveStraightTask. *
 ******************************************/

DriveStraightTask::DriveStraightTask(double desiredDistanceCentimeters, 
                                     Idrive& driveObject)
  : Task("l"),
    predictedDistanceCm([=](double rotations) { return SLOPE * rotations + Y_INTERCEPT; }),
    distanceToDriveCm{desiredDistanceCentimeters}, drive{driveObject} {} 

bool DriveStraightTask::done() const {

  // Predict the distance our bot has traveled given the *actual* number of
  // rotations since start() was called. 
  const double currentRotations = drive.getRotations() - startingRotations;
  const double predictedDistanceDriven = predictedDistanceCm(currentRotations);

  if (predictedDistanceDriven >= distanceToDriveCm) {
    drive.drive(0.0, 0.0);
    return true;
  } else {
    return false;
  }
}

void DriveStraightTask::start() {
  startingRotations = drive.getRotations();
  drive.drive(1.0, 0.0);
}

/********************************************
 * Definitions for the TestDriveTask class. *
 ********************************************/

TestDriveTask::TestDriveTask(double targetRotations_, Idrive& drivingRobot)
  : Task("t"), driveObject{drivingRobot}, targetRotations{targetRotations_} {}

bool TestDriveTask::done() const {
  // One the change in rotations pet frame is less than this value, we've come
  // to a stop.  At least, it's a good enough definition of "stopped."
  const double DEADZONE = 0.001;
  
  // We want to wait a particular amount before checking whether the motor is
  // stopped as the motor might be accelerating slowly instead -- it would be
  // tragic if we cut the motor off early because we were too impatient!
  const double MINIMUM_WAIT_TIME_MSEC = 300;

  // We want to edit these values but they are coming from a const function, we
  // const_cast to allow modification.
  double& currentRotations = const_cast<TestDriveTask*>(this)->currentRotationNumber;
  double& previousRotations = const_cast<TestDriveTask*>(this)->previousRotationNumber;

  currentRotations = driveObject.getRotations();
  
  // Just checking if the velocity is 0 is not sufficient. The robot may drift
  // farther even if the motors are stopped. This is a much more precise way of
  // making sure the motors are stopped by checking if the change in motor
  // rotation is small enough.

  if (currentRotations - previousRotationNumber <= DEADZONE &&
      Brain.timer(msec) - startTimeMsec >= MINIMUM_WAIT_TIME_MSEC) {
    Controller.Screen.setCursor(CONTROLLER_ROBOT_STOPPED_ROW, 1);
    Controller.Screen.print("STOPPED ");
    Controller.Screen.print("%.2f", currentRotations);
    driveObject.drive(0.0, 0.0);
    return true;
  } else {
    previousRotations = currentRotations;
    return false;
  }
}

void TestDriveTask::start() {
  driveObject.drive(1.0, 0.0);
  currentRotationNumber = 0;
  previousRotationNumber = driveObject.getRotations();
  startTimeMsec = Brain.timer(vex::timeUnits::msec);
}

/*********************************
 * Definitions for the TurnTask. *
 *********************************/

TurnTask::TurnTask(double desiredAngle, vex::gyro gyroscope, Idrive& driveObject)
  : Task ("r"), desiredAngle_{desiredAngle}, gyro_{gyroscope}, drive{driveObject} {}


// Scenario: Your robot's start angle is 45 degrees.
// The desired angle is 40 degrees.
// Proceed.

// Question #1: Positive angle == clockwise or counterclockwise?
//   * Confirmed: According to Idrive.h, it is clockwise.
//
// 45, 61, 92, 108, 117, 127, .........., 355, 10, 21, 36, 48, 59, ........ Never makes it to exactly 40.
//
// - We don't stop at the angle. [<---solved by PID.]
//   * Start with P=1, I=0, D=0.
//   * We need to calculate the ERROR every frame, which is the angle that
//     goes from the current angle to the target angle 
//     (= signed_delta of target angle and current angle.)
//
// - We're not rotating optimally [SOLVED by signed_delta().]
//   * Your current angle is 5 degrees.
//   * Your desired angle is 355 degrees (355 is -10 modulo 360.)
//   * Better to rotate 10 degrees counterclockwise than 350 degrees clockwise.
//
 
void TurnTask::start() {
  startAngle = gyro_.angle();
  drive.drive(0.0, 0.6);
}

// Right here.
double signedDelta(double currentAngle, double desiredAngle) {
  return std::fmod(desiredAngle - currentAngle + 180, 360) - 180;
}

bool TurnTask::done() const {
  //This is a bang-bang controller.
  double currentAngle = const_cast<TurnTask*>(this)->gyro_.angle();

  if (currentAngle < desiredAngle_) {
      drive.drive(0.0, 0.6);
      return false;
  } else if (currentAngle > desiredAngle_) {
      drive.drive(0.0, -0.6);
      return false;
  } else {
      return true;
  }
}

/*********************************
 * Definitions for the DriveMillisecondsTask. *
 *********************************/

DriveMillisecondsTask::DriveMillisecondsTask(double milliseconds, Idrive& drive) 
: Task ("s"), waitTimeMsec{milliseconds}, driveObject{drive} {

}

void DriveMillisecondsTask::start() {
  startTimeMsec = Brain.timer(vex::timeUnits::msec);
  driveObject.drive(1.0, 0.0);
}

bool DriveMillisecondsTask::done() const {
  const double currentTimeMsec = Brain.timer(msec);
  const double elapsedTimeMsec = currentTimeMsec - startTimeMsec;
  if (elapsedTimeMsec >= waitTimeMsec) {
    driveObject.drive(0, 0);
    return true;
  } else {
    return false;
  }
}
