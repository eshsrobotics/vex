#ifndef __AUTONOMOUS_TASK_TREE_H_INCLUDED__
#define __AUTONOMOUS_TASK_TREE_H_INCLUDED__

#include <functional> // function<T, ...>
#include <memory> // shared_ptr<T>
#include <string>
#include <vector>

#include "Idrive.h"
#include "vex.h"

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

    friend void
    addTask(std::shared_ptr<Task> parentTask, std::shared_ptr<Task> childTask);

    friend void execute(std::shared_ptr<Task> rootTask);

    /*-------------------*/
    /* PROTECTED METHODS */
    /*-------------------*/
  protected:
    void modifyTaskName(std::string name);
};

/*----------------------------------------------------------*/
/*                 Stand-alone Functions                    */
/*----------------------------------------------------------*/

// Add a new or existing task as a child of the parent task
extern void
addTask(std::shared_ptr<Task> parentTask, std::shared_ptr<Task> childTask);

// Executes this task, all of its children, and so on, some tasks may run in
// parallel
extern void execute(std::shared_ptr<Task> rootTask);

/*****************************************************
 * A TASK THAT WAITS FOR A SPECIFIED PERIOD OF TIME. *
 *****************************************************/

class WaitMillisecondsTask: public Task {
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
 * A TASK THAT DRIVES FORWARD FOR A SPECIFIED DISTANCE. *
 ********************************************************/
class DriveStraightTask: public Task {
  public:
    DriveStraightTask(double distanceCentimeters, Idrive& drive);
    bool done() const;
    void start();

  private:
    // std::function is a thing a reference to a function. It works with
    // functions, lambdas, functors, and function pointers.

    // A function
    std::function<double(double)> predictedDistanceCm;
    double distanceToDriveCm;
    Idrive& drive;

    double startingRotations;

    // TODO: Use Desmos to perform a linear regression after calculating
    // distance traveled for several rotation values. Replace the variables
    // below with the SLOPE and Y-INTERCEPT that Desmos has calculated.
    //
    // This will alow us to roughly predict how many rotations will get us to a
    // given distance.
    const double SLOPE = 46.10714;
    const double Y_INTERCEPT = 9.49643;
};

//////////////////////////////////////////////////////////////////////////
// A TASK TO DETERMINE THE CONVERSION FACTOR THAT CONVERTS THE NUMBER OF//
// ROTATIONS DRIVEN TO CENTIMETERS.                                     //
//////////////////////////////////////////////////////////////////////////

/// We will use this task to get the number of rotations for driving straight.
/// We will later divide this value by the distance drove to get the conversion
/// factor. The conversion factor needs to be determined before implementing the
/// drivestraighttask.
class TestDriveTask: public Task {
  public:
    /// Constructs an instance of this class.
    ///
    /// @param targetRotations number of rotations to tell the motors to drive
    TestDriveTask(double targetRotations, Idrive& drivingRobot);

    // Prints number of rotations on controller. Returns true if target reached,
    // false otherwise.
    bool done() const;

    /// Starts driving for as many drive motor revolutions as specified in
    /// target
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
class TurnTask: public Task {
  public:
    /**
     * Constructs a TurnTask that turns for a given number of degrees using a
     * given gyro.
     *
     * @param angleDegrees the amount to rotate in degrees: positive numbers
     * rotate clockwise and negative numbers rotate counterclockwise
     * @param gyro_ a yaw rate gyroscope used to measure the current chasis's
     * bearing
     * @param drive a reference to an Idrive object which actually does the
     * driving
     */
    TurnTask(double angleDegrees, vex::gyro gyro_, Idrive& drive);

    bool done() const;

    void start();

  private:
    /**
     * Where the robot's gyro was at the point the robot start()ed to rotate.
     */
    double startAngle;

    double desiredAngle_;
    gyro gyro_;
    Idrive& drive;
};

/**
 * Need to drive the robot for arbitrary seconds to implement the testing
 * protocol for the prototypes. The experimental protocol will be done
 * autonomously. This task will be ran for x amount of seconds that will remain
 * the same for all prototypes.
 */
class DriveMillisecondsTask: public Task {
  public:
    DriveMillisecondsTask(
        Idrive& drive,
        double milliseconds,
        double driveVelocity = 1.0
    );

    bool done() const;

    void start();

  private:
    Idrive& driveObject;
    double waitTimeMsec;
    double driveVelocity_;
    double startTimeMsec;
};

/**
 * An intake task that will make the intake motors go vroom for a particular
 * number of seconds at a particular number of seconds.
 */
class IntakeMillisecondsTask: public Task {
  public:
    /**
     * The constructor for the IntakeTaskSeconds task
     *
     * @param seconds the number of seconds that the intake motors will rotate
     * @param intake_speed the speed of the intake motors. We will pass in a
     * value between 1 and -1. 1 means intaking and -1 means outtaking.
     * Most likely, we will not need different velocities, only different
     * directions.
     *
     * @param intake_bot a reference to an object that IS an Intake
     */
    IntakeMillisecondsTask(
        Iintake& intake_bot,
        double msec,
        double intake_speed = 1
    );

    bool done() const;

    void start();

  private:
    Iintake& intakeObject;
    double desiredIntakingTimeMsec;
    double intake_speed_;
    double startTimeMsec;
};

class MobileGoalIntakeTask: public WaitMillisecondsTask {
  public:
    MobileGoalIntakeTask(ImobileGoalIntake& mobileGoalIntake, bool clamp);

    bool done() const;

    void start();

  private:
    ImobileGoalIntake& mobileGoalIntakeObject;
    bool clamp_;
};

#endif // (ifndef __AUTONOMOUS_TASK_TREE_H_INCLUDED__)