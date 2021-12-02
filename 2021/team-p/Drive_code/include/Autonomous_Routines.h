#include <memory>  // shared_ptr<T>
#include <vector>
#include <string>

struct Task {
  // Generates the unique task ID
  Task(const std::string& name);

  /*--------------------------------------------------------*/
  /*                     Member data                        */
  /*--------------------------------------------------------*/

  // Task name, not unique whatsoever
  std::string name;

  // Task ID, unique for every task
  int task_id;

  // The parent tasks for the current task, the task runs when all parents are finished
  std::vector<std::weak_ptr<Task>> parents;

  // The child tasks of the current task, run when the task is finished
  std::vector<std::shared_ptr<Task>> children;

  // Task parameter, the amount to do the task
  double parameter;

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

  // Executes this task, all of its children, and so on, some tasks may run in parallel
  friend void execute(std::shared_ptr<Task> rootTask);
};

extern void addTask(std::shared_ptr<Task> parentTask, 
                    std::shared_ptr<Task> childTask);

extern void execute(std::shared_ptr<Task> rootTask);

// Delays other tasks from starting
struct WaitMillisecondsTask : public Task {
  double startTimeMilliseconds;
  double doneTimeMilliseconds;
  double waitPeriodMilliseconds;  

  WaitMillisecondsTask(double milliseconds);

  bool done() const;
  void start();
};


struct DriveStraightTask : public Task {
  vex::drivetrain& drivetrain;
  double distanceInches;

  // If a negative number is passed in, it will drive backwards instead of forwards
  DriveStraightTask(vex::drivetrain& drivetrain, double distanceInches);

  // Returns true is the drivetrain has stopped moving
  // WARNING: Also applies if there is a turning task and a driving task executing at the same 
  // time, they will both end when one of them finishes, we can't do anything to fix that for now
  bool done() const;
  void start();
};