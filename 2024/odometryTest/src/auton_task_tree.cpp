#include "auton_task_tree.h"
#include "hardware.h"
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
  if (::brain.timer(msec) >= doneTimeMilliseconds) {
    return true;
  } else {
    return false;
  }
}

void WaitMillisecondsTask::start() {
  startTimeMilliseconds = ::brain.timer(msec);
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
    left_motor_group.spinFor(vex::reverse, (distanceInches*360)/wheelCircumferenceIn, degrees, WAIT_FOR_COMPLETION);
    right_motor_group.spinFor(vex::forward, (distanceInches*360)/wheelCircumferenceIn, degrees, WAIT_FOR_COMPLETION);
  } else {
    left_motor_group.spinFor(vex::forward, -(distanceInches*360)/wheelCircumferenceIn, degrees, WAIT_FOR_COMPLETION);
    right_motor_group.spinFor(vex::reverse, -(distanceInches*360)/wheelCircumferenceIn, degrees, WAIT_FOR_COMPLETION);
  }
}

// For TurnTask, positive is counterclockwise, negative is clockwise
TurnTask::TurnTask(vex::motor_group &left_motor_group, 
                   vex::motor_group &right_motor_group,
                   vex::inertial &inertial,
                   double rotationAmountDegrees)
    : Task("Turn task"), left_motor_group(left_motor_group), right_motor_group(right_motor_group),
      inertial(inertial), rotationAmountDegrees(rotationAmountDegrees) {}

bool TurnTask::done() const { 
    double currentAngle = inertial.angle(degrees);

    if(currentAngle == rotationAmountDegrees) {
      left_motor_group.stop();
      right_motor_group.stop();
      return true;
    } else {
      return false;
    }
}

void TurnTask::start() {
  left_motor_group.setVelocity(40, percent);
  right_motor_group.setVelocity(40, percent);
  
  left_motor_group.spin(vex::forward);
  right_motor_group.spin(vex::reverse);

  //double startAngle = inertial.angle(degrees);
}

PneumaticTask::PneumaticTask(vex::digital_out &pneumatic, 
                   bool value)
    : Task("Pneumatic task"), pneumatic(pneumatic),
      value(value) {}

bool PneumaticTask::done() const { return pneumatic.value() == value; }

void PneumaticTask::start() {
  pneumatic.set(value);
}

IntakeTask::IntakeTask(vex::motor &intakeMotor, int timeSec, double intakeSpeedPct) 
    : Task("Bottom intake task"), intakeMotor(intakeMotor), timeSec(timeSec), intakeSpeedPct(intakeSpeedPct) {}

bool IntakeTask::done() const {
  return true;
}

void IntakeTask::start() {
  intakeMotor.setVelocity(intakeSpeedPct, percent);
  intakeMotor.spinFor(timeSec, seconds);
  //bottomIntake.spin(vex::forward);
}
         