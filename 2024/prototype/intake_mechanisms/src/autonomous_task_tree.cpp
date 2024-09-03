// The autonomous task tree with definitions for our robot's autonomous functions.

#include "vex.h"
#include "prototypes.h"

#include "autonomous_task_tree.h"
#include "vex.h"
#include <cstring> // std::snprintf()
#include <sstream> // std::stringstream;
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
  if(Brain.timer(msec) - startTimeMilliseconds < waitTimeMilliseconds) {
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

DriveStraightTask::DriveStraightTask(double distanceCentimeters, Idrive& drive)
  : Task("l") {

}

bool DriveStraightTask::done() const {
  return true;
}

void DriveStraightTask::start() {
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

  double& currentRotations = const_cast<TestDriveTask*>(this)->currentRotationNumber;
  double& previousRotations = const_cast<TestDriveTask*>(this)->previousRotationNumber;

  currentRotations = driveObject.getRotations();
  if (currentRotations - previousRotationNumber <= DEADZONE){
    Brain.Screen.setCursor(CONTROLLER_ROBOT_STOPPED_ROW, 1);
    Brain.Screen.print("STOPPED");
    Brain.Screen.print(this->name);
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
}
