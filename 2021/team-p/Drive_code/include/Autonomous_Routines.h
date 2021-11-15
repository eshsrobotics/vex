#include <memory>  // unique_ptr<T>
#include <vector>
#include <string>

struct Task {
  // Task name, not unique whatsoever
  std::string name;
  // Task ID, unique for every task
  int task_id;
  // The parent tasks for the current task, the task runs when all parents are finished
  std::vector<std::unique_ptr<Task>> parents;
  // The child tasks of the current task, run when the task is finished
  std::vector<std::unique_ptr<Task>> children;
  // Task parameter, the amount to do the task
  double parameter;

  // Returns true if the task is completed, false if not completed
  virtual bool done() const = 0;
  // Starts the current task
  virtual void start() = 0;

  // Add a new or existing task as a child of the current task
  void addTask(std::unique_ptr<Task> task);

  // Generates the unique task ID
  int makeUniqueID() const;
};

// Delays other tasks from starting
struct WaitMillisecondsTask : public Task {
  WaitMillisecondsTask(double milliseconds);

  bool done() const;
  void start();
};