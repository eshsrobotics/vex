#ifndef __AUTONOMOUS_TASK_TREE_H_INCLUDED__
#define __AUTONOMOUS_TASK_TREE_H_INCLUDED__

#include <functional>
#include <memory> // shared_ptr<T>
#include <string>
#include <vector>
#include "vex.h"

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

#endif // (ifndef __AUTONOMOUS_TASK_TREE_H_INCLUDED__)