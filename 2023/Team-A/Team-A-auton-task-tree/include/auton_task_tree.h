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