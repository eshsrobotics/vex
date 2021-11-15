#include "vex.h"
#include "Autonomous_Routines.h"

using namespace vex;
using namespace std;


Task::Task() {
  static int counter = 0;
  task_id = ++counter;
}

void addTask(std::shared_ptr<Task> parentTask, std::shared_ptr<Task> childTask) {
  parentTask->children.push_back(childTask);
  childTask->parents.push_back(parentTask);
}

WaitMillisecondsTask::WaitMillisecondsTask(double milliseconds) : Task() {
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