// AUTON_TASK_TREE.H: declarations for Task base class, tree execution, and other derived Task classes

#include <functional>
#include <memory> // shared_ptr<T>
#include <string>
#include <vector>
#include "vex.h"


/*--------------------------------------------------------------------------*/
/*     The struct task is how our whole autonomouis code runs, each task    */
/* has one function that it runs for sutonomous, and each task has children */
/*               and parents which run before and after it.                 */
/*--------------------------------------------------------------------------*/
struct Task {
  // Generates the unique task ID
  Task(const std::string &name);

  /*--------------------------------------------------------*/
  /*                     Member data                        */
  /*--------------------------------------------------------*/

  // Task name, not unique whatsoever
  std::string name;

  // Task ID, unique for every task
  int task_id;

  // The parent tasks for the current task, the task runs when all parents are
  // finished
  std::vector<std::weak_ptr<Task>> parents;

  // The child tasks of the current task, run when the task is finished
  std::vector<std::shared_ptr<Task>> children;

  /*--------------------------------------------------------*/
  /*                  Virtual Methods                       */
  /*--------------------------------------------------------*/

  // Returns true if the task is completed, false if not completed
  virtual bool done() const = 0;

  // Starts the current task
  virtual void start() = 0;

  /*--------------------------------------------------------*/
  /*                  Public Functions                      */
  /*--------------------------------------------------------*/

  // Add a new or existing task as a child of the current task
  friend void addTask(std::shared_ptr<Task> parentTask,
                      std::shared_ptr<Task> childTask);

  // Executes this task, all of its children, and so on, some tasks may run in
  // parallel
  friend void execute(std::shared_ptr<Task> rootTask);
};

extern void addTask(std::shared_ptr<Task> parentTask,
                    std::shared_ptr<Task> childTask);

extern void execute(std::shared_ptr<Task> rootTask);

/*-----------------------------------------------------------------------*/
/* Delays other tasks form starting for a certain number of milliseconds */
/*-----------------------------------------------------------------------*/
struct WaitMillisecondsTask : public Task {
  double startTimeMilliseconds;
  double doneTimeMilliseconds;
  double waitPeriodMilliseconds;

  WaitMillisecondsTask(double milliseconds);

  bool done() const;
  void start();
};

/*--------------------------------------------------------------------------------------*/
/* Drives the robot forward or backward a certain number of inches using the
 * drivetrain */
/*--------------------------------------------------------------------------------------*/
struct DriveStraightTask : public Task {
  vex::motor_group &left_motor_group;
  vex::motor_group &right_motor_group;
  double distanceInches;
  std::function<double (double)> translateFunction;

  // If a negative number is passed in, the robot will drive backwards instead
  // of forwards
  DriveStraightTask(
      vex::motor_group &motor_group1, vex::motor_group &motor_group2, double distanceInches,
      std::function<double(double)> translateFunction = [](double d) {
        return d;
      });

  // Returns true is the drivetrain has stopped moving
  // WARNING: Also applies if there is a turning task and a driving task
  // executing at the same time, they will both end when one of them finishes,
  // we can't do anything to fix that for now
  bool done() const;
  void start();
};

/*------------------------------------------------------------------------------------------------*/
/* Turns the robot clockwise or counterclockwise a certain number of degrees
 * using the drivetrain */
/*------------------------------------------------------------------------------------------------*/
// If the turning and driving tasks are running at the same time, one of them
// will overwrite the other, because they are both using the same drivetrain.
struct TurnTask : public Task {
  vex::motor_group &left_motor_group;
  vex::motor_group &right_motor_group;
  double rotationAmountDegrees;

  // If a positive number is passed in, the robot will turn clockwise (right),
  // otherwise, the robot will turn counterclockwise (left)
  //
  // Unfortunatly some drives don't turn the correct number of degrees when asked to do so.
  // (Note that drive that uses a gyro WILL turn correct numbeer of degrees.)
  // For drives that don't turn correctly, you may pass in a correction function that maps an input 
  // to a number that will casuse a drive to turn correctly.
  // The defualt correction function is just the identity function.
  TurnTask(vex::motor_group &motor_group1, vex::motor_group &motor_group2, double rotationAmountDegrees);

  bool done() const;
  void start();
};

// These are the different types of autonomous trajectories we will support.
enum AUTON_TYPE {

  // This is the autonomous routine for when the robot starts at the 
  // side of the ramp that is down, and when we also want the win point.
  TEST_AUTON
};

// Returns the autonomous task tree that the caller requested.
//
// There are different types of autonomous that our robot can do!  It all
// depends on whether or not we wish to score the win point for autonomous
// and which side of the ramp we start on.
//
// A lot of these trees reuse common elements, so it makes sense to
// generate all fo them here.
std::shared_ptr<Task> get_auton(AUTON_TYPE type);

