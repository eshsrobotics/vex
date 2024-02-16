// AUTON_TASK_TREE.CPP: Contains definitions for Auton_task_tree.h

#include "auton_task_tree.h"
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

DriveStraightTask::DriveStraightTask(vex::motor_group &left_motor_group, 
                                     vex::motor_group &right_motor_group, 
                                     double distanceInches,
                                     int speed,
                                     std::function<double(double)> translateFunction)
    : Task("Drive task"), left_motor_group(left_motor_group), right_motor_group(right_motor_group),
      distanceInches(distanceInches), speed(speed), translateFunction(translateFunction) {}

bool DriveStraightTask::done() const { return left_motor_group.isDone(); }

void DriveStraightTask::start() {
  double correctDistanceInches = translateFunction(distanceInches);
  const bool WAIT_FOR_COMPLETION = false;
  left_motor_group.setVelocity(speed, percent);
  right_motor_group.setVelocity(speed, percent);
  if (distanceInches > 0) {
    left_motor_group.spinFor(vex::forward, (distanceInches*360)/WHEEL_CIRCUMFERENCE, degrees, WAIT_FOR_COMPLETION);
    right_motor_group.spinFor(vex::forward, (distanceInches*360)/WHEEL_CIRCUMFERENCE, degrees, WAIT_FOR_COMPLETION);
  } else {
    left_motor_group.spinFor(vex::reverse, -(distanceInches*360)/WHEEL_CIRCUMFERENCE, degrees, WAIT_FOR_COMPLETION);
    right_motor_group.spinFor(vex::reverse, -(distanceInches*360)/WHEEL_CIRCUMFERENCE, degrees, WAIT_FOR_COMPLETION);
  }
}

// For TurnTask, positive is counterclockwise, negative is clockwise
TurnTask::TurnTask(vex::motor_group &left_motor_group, 
                   vex::motor_group &right_motor_group,
                   double rotationAmountDegrees)
    : Task("Turn task"), left_motor_group(left_motor_group), right_motor_group(right_motor_group),
      rotationAmountDegrees(rotationAmountDegrees) {}

bool TurnTask::done() const { return left_motor_group.isDone(); }

void TurnTask::start() {
  left_motor_group.setVelocity(40, percent);
  right_motor_group.setVelocity(40, percent);
  // Had to use trial and error to find what value to multiply by, but it works now
  left_motor_group.spinFor(0.58*(rotationAmountDegrees*WHEEL_BASE_INCHES)/WHEEL_DIAMETER, degrees, false);
  right_motor_group.spinFor(0.58*(-rotationAmountDegrees*WHEEL_BASE_INCHES)/WHEEL_DIAMETER, degrees, false);
}

PneumaticTask::PneumaticTask(vex::digital_out &pneumatic, 
                   bool value)
    : Task("Pneumatic task"), pneumatic(pneumatic),
      value(value) {}

bool PneumaticTask::done() const { return pneumatic.value() == value; }

void PneumaticTask::start() {
  pneumatic.set(value);
}

std::shared_ptr<Task> get_auton(AUTON_TYPE type) {

  auto initialWait = shared_ptr<Task>(new WaitMillisecondsTask(0));
  auto secondWait1 = shared_ptr<Task>(new WaitMillisecondsTask(1000));
  auto secondWait2 = shared_ptr<Task>(new WaitMillisecondsTask(1000));
  auto secondWait3 = shared_ptr<Task>(new WaitMillisecondsTask(1000));
  auto secondWait4 = shared_ptr<Task>(new WaitMillisecondsTask(1000));
  auto secondWait5 = shared_ptr<Task>(new WaitMillisecondsTask(1000));
  auto secondWait6 = shared_ptr<Task>(new WaitMillisecondsTask(1000));
  auto secondWait7 = shared_ptr<Task>(new WaitMillisecondsTask(1000));
  
  auto driveSlight = std::shared_ptr<Task>(new DriveStraightTask(leftMotors, rightMotors, 2.5, 25)); 
  auto turnToGoalMatchLoad = std::shared_ptr<Task>(new TurnTask(leftMotors, rightMotors, 30.0));
  auto pushTriballIn = shared_ptr<Task>(new DriveStraightTask(leftMotors, rightMotors, 20.0, 75));
  auto driveBack = shared_ptr<Task>(new DriveStraightTask(leftMotors, rightMotors, -18.0, 25));
  auto extendWingForTriball = std::shared_ptr<Task>(new PneumaticTask(winglet, false));
  auto pushTriballOut = std::shared_ptr<Task>(new TurnTask(leftMotors, rightMotors, -90.0));

  // auto driveToGoal = std::shared_ptr<Task>(new DriveStraightTask(leftMotors, rightMotors, 20.0, 25));
  // auto driveAwayFromGoal = std::shared_ptr<Task>(new DriveStraightTask(leftMotors, rightMotors, -18.0, 25));
  // auto driveToClimbPole = std::shared_ptr<Task>(new DriveStraightTask(leftMotors, rightMotors, 20.0, 25));

  auto driveMatchLoadBar = std::shared_ptr<Task>(new DriveStraightTask(leftMotors, rightMotors, 9.5, 15));
  auto driveToGoal = std::shared_ptr<Task>(new DriveStraightTask(leftMotors, rightMotors, 10.5, 75));
  auto driveFromGoal = std::shared_ptr<Task>(new DriveStraightTask(leftMotors, rightMotors, -6.5, 25));
  auto driveTowardPole = std::shared_ptr<Task>(new DriveStraightTask(leftMotors, rightMotors, 25.0, 25));
  auto driveToPole = std::shared_ptr<Task>(new DriveStraightTask(leftMotors, rightMotors, 25.0, 25));

  auto turnToGoalTriball = std::shared_ptr<Task>(new TurnTask(leftMotors, rightMotors, 55.0));
  auto turnFromGoal = std::shared_ptr<Task>(new TurnTask(leftMotors, rightMotors, 90.0));
  auto turnToPole = std::shared_ptr<Task>(new TurnTask(leftMotors, rightMotors, -30.0));

  auto extendHook = std::shared_ptr<Task>(new PneumaticTask(climbingHook, false));
  auto retractHook = std::shared_ptr<Task>(new PneumaticTask(climbingHook, true));
  auto extendWingForPole = std::shared_ptr<Task>(new PneumaticTask(winglet, false));
  
  // auto turnToPole = std::shared_ptr<Task>(new TurnTask(leftMotors, rightMotors, 45.0));
  auto turn90 = std::shared_ptr<Task>(new TurnTask(leftMotors, rightMotors, 90.0));
  auto turn180 = std::shared_ptr<Task>(new TurnTask(leftMotors, rightMotors, 180.0));
  
  // The root task always needs to be initialWait

  switch(type) {
    case TEST_AUTON:
      addTask(initialWait, turn90);
      break;
    case ALLIANCE_TRIBALL:
      // addTask(initialWait, driveToGoal);
      // addTask(driveToGoal, secondWait1);
      // addTask(secondWait1, driveAwayFromGoal);
      // addTask(driveAwayFromGoal, secondWait2);
      // addTask(secondWait2, driveSlight);
      // addTask(driveSlight, secondWait3);
      // addTask(secondWait3, turnToPole);
      // addTask(turnToPole, secondWait4);
      // addTask(secondWait4, driveToClimbPole);
      addTask(initialWait, driveMatchLoadBar);
      addTask(driveMatchLoadBar, secondWait1);
      addTask(secondWait1, turnToGoalTriball);
      // addTask(turnToGoal, extendHook);
      addTask(turnToGoalTriball, secondWait2);
      addTask(secondWait2, driveToGoal);
      addTask(driveToGoal, secondWait3);
      addTask(secondWait3, driveFromGoal);
      // addTask(driveFromGoal, retractHook);
      addTask(driveFromGoal, secondWait4);
      addTask(secondWait4, turnFromGoal);
      addTask(turnFromGoal, secondWait5);
      addTask(secondWait5, driveTowardPole);
      addTask(driveTowardPole, extendWingForPole);
      addTask(extendWingForPole, secondWait6);
      addTask(secondWait6, turnToPole);
      // addTask(turnToPole, secondWait7);
      // addTask(secondWait7, driveToPole);
    case MATCH_LOAD_ZONE:
      addTask(initialWait, driveSlight);
      addTask(driveSlight, turnToGoalMatchLoad);
      addTask(turnToGoalMatchLoad, pushTriballIn);
      addTask(pushTriballIn, driveBack);
      addTask(driveBack, extendWingForTriball);
      addTask(driveBack, pushTriballOut);
  }

  return initialWait;
}              