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
  char buffer[100];
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
    for (auto iter = taskList.begin(); iter != taskList.end(); ++iter) {
      auto task = *iter;
      if (task->done()) {
        // Put the task's children into the list if they're ready
        for (auto childTask : task->children) {
          // A child task is only ready when all of its parents are completed
          bool childTaskReady = true;
          for (auto parentTask : childTask->parents) {
            if (parentTask.expired()) {
              // If the parent task doesn't exist, it is completed, so the child task won't wait for it
              break;
            }
            if (!parentTask.lock()->done()) {
              // If one of our parents is running, then we are not ready.
              childTaskReady = false;
              break;
            }
          }

          if (childTaskReady) {
            // If all the parents are completed or destroyed, the task will start
            taskList.push_back(childTask);
            childTask->start();
          }
        }
        // Remove the original task from the list
        // This is safe if the task is a mutual parent of a task that currently isn't ready
        iter = taskList.erase(iter);
      }
    }

    wait(25, msec);
  }
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
    drivetrain.driveFor(vex::forward, distanceInches, inches);
  } else {
    drivetrain.driveFor(vex::reverse, -distanceInches, inches);
  }
}