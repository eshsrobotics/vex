#ifndef __AUTONOMOUS_TASK_TREE_H_INCLUDED__
#define __AUTONOMOUS_TASK_TREE_H_INCLUDED__


#include <functional> // function<T, ...>
#include <memory>     // shared_ptr<T>
#include <string>
#include <vector>
#include "vex.h"
#include "Idrive.h"

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

/*****************************************************
 * A TASK THAT WAITS FOR A SPECIFIED PERIOD OF TIME. *
 *****************************************************/
class WaitMillisecondsTask : public Task {
  public: 
    WaitMillisecondsTask(double timeToWaitMilliseconds);
    bool done() const;
    void start();
  private:
    // The time at which start() was called.
    double startTimeMilliseconds;
    
    // The number of milliseconds to wait.
    double waitTimeMilliseconds;
};

/********************************************************
 * A task that drives forward for a specified distance. *
 ********************************************************/
class DriveStraightTask : public Task {
  public:
    DriveStraightTask(double distanceCentimeters, Idrive& drive);
    bool done() const;
    void start();
  private:  
    std::function<double(double)> predictedDistanceCm;
    double distanceToDriveCm;
    Idrive& drive;
    
    double startingRotations;
};

/// We will use this task to get the number of rotations for driving straight.
/// We will later divide this value by the distance drove to get the conversion factor.
/// The conversion factor needs to be determined before implementing the drivestraighttask.
class TestDriveTask : public Task {
  public:

    /// Constructs an instance of this class.
    ///
    /// @param targetRotations number of rotations to tell the motors to drive
    TestDriveTask(double targetRotations, Idrive& drivingRobot);

    // Prints number of rotations on controller. Returns true if target reached,
    // false otherwise.
    bool done() const; 

    /// Starts driving for as many drive motor revolutions as specified in target
    void start();
    
private:

    // Reference to Idrive to allow the robot to actually move
    Idrive& driveObject;
    double targetRotations;
    double currentRotationNumber;
    double previousRotationNumber;
    double startTimeMsec;
};


#endif // (ifndef __AUTONOMOUS_TASK_TREE_H_INCLUDED__)