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

/*----------------------------------------------------------*/
/* Drives the robot straight for a certain number of inches */
/*----------------------------------------------------------*/
struct DriveStraightInches : public Task {
  double inchAmount;
  double backLeftEncoder;
  double backRightEncoder;
  double frontLeftEncoder;
  double frontRightEncoder;

  DriveStraightInches(double distInches);

  bool done() const;
  void start();
};