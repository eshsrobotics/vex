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
  /*                 Friend Declarations                    */
  /*--------------------------------------------------------*/
  
  friend void addTask(std::shared_ptr<Task> parentTask,
                      std::shared_ptr<Task> childTask);

  friend void execute(std::shared_ptr<Task> rootTask);
};

/*----------------------------------------------------------*/
/*                 Stand-alone Functions                    */
/*----------------------------------------------------------*/

// Add a new or existing task as a child of the parent task
extern void addTask(std::shared_ptr<Task> parentTask,
                    std::shared_ptr<Task> childTask);

// Executes this task, all of its children, and so on, some tasks may run in
// parallel
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

    // TODO: Use Desmos to perform a linear regression after calculating
    // distance traveled for several rotation values.  Replace the variables
    // below with the SLOPE and Y-INTERCEPT that Desmos has calculated.
    //
    // This will alow us to roughly predict how many rotations will get us to a
    // given distance.
    const double SLOPE = 0;
    const double Y_INTERCEPT = 0;
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

/**
 * The DriveStraightTask cannot make the robot turn. We do not have a logic in
 * the DriveStraightTask that translates how many rotations result in how many
 * degrees of the robot turning. We are creating a new task that will have the
 * logic for turning the robot.
 */
class TurnTask : public Task {
  public:
    TurnTask(double angleDegrees, vex::gyro gyro_, Idrive& drive);
    
    bool done() const;

    void start();
  
  private:
    double startAngle;
    double angleDegrees;
    gyro gyro_;
    Idrive& drive;

};

#endif // (ifndef __AUTONOMOUS_TASK_TREE_H_INCLUDED__)