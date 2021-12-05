#include <memory>  // shared_ptr<T>
#include <vector>
#include <string>
#include <functional>

/*--------------------------------------------------------------------------*/
/*     The struct task is how our whole autonomouis code runs, each task    */
/* has one function that it runs for sutonomous, and each task has children */
/*               and parents which run before and after it.                 */
/*--------------------------------------------------------------------------*/
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
/* Drives the robot forward or backward a certain number of inches using the drivetrain */
/*--------------------------------------------------------------------------------------*/
struct DriveStraightTask : public Task {
  vex::drivetrain& drivetrain;
  double distanceInches;

  // If a negative number is passed in, the robot will drive backwards instead of forwards
  DriveStraightTask(vex::drivetrain& drivetrain, double distanceInches);

  // Returns true is the drivetrain has stopped moving
  // WARNING: Also applies if there is a turning task and a driving task executing at the same 
  // time, they will both end when one of them finishes, we can't do anything to fix that for now
  bool done() const;
  void start();
};

/*------------------------------------------------------------------------------------------------*/
/* Turns the robot clockwise or counterclockwise a certain number of degrees using the drivetrain */
/*------------------------------------------------------------------------------------------------*/
// If the turning and driving tasks are running at the same time, one of them will overwrite the
// other, because they are both using the same drivetrain.
struct TurnTask : public Task {
  vex::drivetrain& drivetrain;
  double rotationAmountDegrees;

  // If a positive number is passed in, the robot will turn clockwise (right), otherwise,
  // the robot will turn counterclockwise (left)
  TurnTask(vex::drivetrain& drivetrain, double rotationAmountDegrees);

  bool done() const;
  void start();
};

struct MoveMotorTask : public Task {
  vex::motor& motor;
  double gearRatio; // Ratio of the motor (input) to the output
  double rotationAmountDegrees;
  std::function<bool(void)> endRotation;

  // If a positive number is passed in, the motor will turn clockwise (right), otherwise,
  // the motor will turn counterclockwise (left)
  MoveMotorTask(vex::motor& motor, double gearRatio, double rotationAmountDegrees);
  
  // This allows a motor to move until either it moves hte correct number of degrees
  // or the predicate returns true
  template<typename UnaryPredicate>
  MoveMotorTask(vex::motor& motor, double gearRatio, double rotationAmountDegrees, UnaryPredicate p)
    : Task("Move motor task"),
      motor(motor),
      rotationAmountDegrees(rotationAmountDegrees),
      endRotation([&p] () { return p(); }) {}

  bool done() const;
  void start();
};