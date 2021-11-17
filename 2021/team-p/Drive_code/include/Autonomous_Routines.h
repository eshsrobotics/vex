#include <memory>  // shared_ptr<T>
#include <vector>
#include <string>

struct Task {
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

  // Returns true if the task is completed, false if not completed
  virtual bool done() const = 0;

  // Starts the current task
  virtual void start() = 0;

  // Add a new or existing task as a child of the current task
  friend void addTask(std::shared_ptr<Task> parentTask, 
                      std::shared_ptr<Task> childTask);

  // Generates the unique task ID
  Task();
};

// Delays other tasks from starting
struct WaitMillisecondsTask : public Task {
  double startTimeMilliseconds;
  double doneTimeMilliseconds;
  double waitPeriodMilliseconds;  

  WaitMillisecondsTask(double milliseconds);

  bool done() const;
  void start();
};