#include "vex.h"
#include "Autonomous_Routines.h"
#include <list>
#include <string>
#include <cstring> // std::snprintf()

using namespace vex;
using namespace std;

/*--------------------------------------------------------*/
/*                    Task Methods                        */
/*--------------------------------------------------------*/

Task::Task(const string& name) : name(name) {
  static int counter = 0;
  task_id = ++counter;

  // Append the (unique) task ID to the name of the task.
  const size_t MAX_DIGITS = 10;
  char buffer[MAX_DIGITS];
  snprintf(buffer, sizeof(buffer), "%d", task_id);
  this->name += "#";
  this->name += buffer;
}

void addTask(std::shared_ptr<Task> parentTask, std::shared_ptr<Task> childTask) {
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
    for (auto iter = taskList.begin(); iter != taskList.end(); /* See increment below */) {
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
              break;
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

    wait(25, msec);
  } // end (while there are still active tasks)
}

/*--------------------------------------------------------*/
/*            WaitMillisecondsTask Methods                */
/*--------------------------------------------------------*/

WaitMillisecondsTask::WaitMillisecondsTask(double milliseconds) : Task("Wait task") {
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

DriveStraightTask::DriveStraightTask(vex::drivetrain& drivetrain, double distanceInches)
  : Task("Drive task"), drivetrain(drivetrain), distanceInches(distanceInches) {}

bool DriveStraightTask::done() const {
  return drivetrain.isDone();
}

void DriveStraightTask::start() {
  if (distanceInches > 0) {
    // Assigns the variables for changing the input value so the output value is equal to it
    // We got these numbers by plotting 5 points from testing and finding the line of best fit
    const double M_VALUE = 1.20581;
    const double B_VALUE = 1.15078;
    // This formula creates the new value that is input into the driveFor function to get an 
    // of the original distanceInches
    double correctDistanceInches = (distanceInches - B_VALUE) / M_VALUE;
    drivetrain.driveFor(vex::forward, correctDistanceInches, inches);
  } else {
    // Assigns the variables for changing the input value so the output value is equal to it
    // We got these numbers by plotting 5 points from testing and finding the line of best fit
    const double M_VALUE = 1.01885;
    const double B_VALUE = -0.792244;
    // This formula creates the new value that is input into the driveFor function to get an 
    // of the original distanceInches
    double correctDistanceInches = (-distanceInches - B_VALUE) / M_VALUE;
    drivetrain.driveFor(vex::reverse, correctDistanceInches, inches);
  }
}
