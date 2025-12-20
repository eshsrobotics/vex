/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       sanjaynataraj                                             */
/*    Created:      7/13/2025, 2:55:55 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "hardware.h"
#include "auton.h"
#include <vector>

using namespace vex;
vex::motor test_motor = vex::motor(vex::PORT10, false);
// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  // The first half of the motor ports are for the left side, and the second
  // half are for the right side
  // If you need to reverse a motor, make its port number negative
  std::vector<int> ports = {vex::PORT3, vex::PORT4, vex::PORT5, vex::PORT6};
  createDriveMotors(ports);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  
  // This autonomous is need to perform an experiment for linear regression. All
  // it can do is drive forward and stop. 
  //
  // To perform the experiment: 
  // 1. Choose a distance you want the robot to move in inches.
  // 2. Set up a yard stick to measure distance traveled by the front of the
  //    robot as it travels straight
  // 3. Select amount of time to drive, and put it in as the second start time
  //    in the task list below.
  // 4. Deploy autonomous code and run it.
  // 5. compare distance traveled by the front of the robot by the distance you
  //    want it to travel 5a. If the distance is too short increase the drive
  //    time 5b. If the distance traveled is too long decrease the drive time
  // 6. once you have a drive time that drives the correct chosen distance,
  //    record both the time and the distance in a data table, X is the
  //    distance, Y is the time
  // 7. Repeat steps 1-6 with a different chosen distance. Remember to record
  //    this new data as next data point in the table
  // 8. Once you have 4 or 5 data points, feed them to Desmos and perform a
  //    linear regression.
  // 9. Desmos will give a slope M and a Y-intercept B for the equation y = mx +
  //    b. The DDTT function will return M * distanceInches + B
  std::vector<AutonTask> autonTaskList = {
    // Operation, Start Time, Argument
    //{AutonOperationType::intake, 0, -100}
     {AutonOperationType::turn, 0, 100},
     {AutonOperationType::drive, 460, 67},
     {AutonOperationType::turn, 857.5, 100},
     {AutonOperationType::drive, 1809.8, 67},
     {AutonOperationType::turn, 2207.31, 100},
     {AutonOperationType::intake, 2797.81, -100},
     {AutonOperationType::turn, 3247.81, -100},
     {AutonOperationType::turn, 3461.81, 100},
     {AutonOperationType::intake, 3675.81, -100},
     {AutonOperationType::turn, 4125.81, -100},
     {AutonOperationType::turn, 4339.81, 100},
     {AutonOperationType::intake, 4553.81, -100},
     {AutonOperationType::turn, 5003.81, -100},
     {AutonOperationType::drive, 5238.81, 67},
     {AutonOperationType::turn, 5921.31, 100},
     {AutonOperationType::lift, 6881.21, -100},
     {AutonOperationType::intake, 8018.21, 100},
     {AutonOperationType::turn, 8626.21, -100},
     {AutonOperationType::drive, 9216.71, -67},
     {AutonOperationType::turn, 9471.71, 100},
     {AutonOperationType::lift, 10789.71, 75},
     {AutonOperationType::intake, 11003.71, 100},
     {AutonOperationType::turn, 11611.71, -100},
     {AutonOperationType::drive, 12553.71, -67},
     {AutonOperationType::turn, 12808.71, 100},
     {AutonOperationType::drive, 14793.28, 67},
     {AutonOperationType::lift, 15190.78, -75},
     {AutonOperationType::turn, 15404.28, 100},
     {AutonOperationType::intake, 15736.88, 100},
     {AutonOperationType::turn, 16236.88, 0},
  };

  // // This autonomous is to test turning. It will turn at 100% power and stop
  // // after a period of time under our control.
  // std::vector<AutonTask> autonTaskList = {
  //   // Operation, Start Time, Argument
  //   {AutonOperationType::turn, 0, 100},
  //   {AutonOperationType::turn, 2150, 0},
  // };


  executeAuton(autonTaskList); // Executes a test program for gathering linear regression data

  // executeAuton(leftSideAuton()); // Executes our auton win point
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  // test_motor.spin(fwd);
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // The minus signs are infront of userController.Axis3 and 4 is because the controls were reversed. 
    controller userController;
    double controllerFrontBackPosition = userController.Axis3.position();
    double controllerLeftRightPosition = -userController.Axis4.position();

    drive(controllerLeftRightPosition, controllerFrontBackPosition);

    // Allow the user to control the intake
    if (userController.ButtonY.pressing()) {
      // Reverse the intake
      intakeControl(-INTAKE_SPEED_PERCENT);
    } else if (userController.ButtonA.pressing()) {
      // Drive intake forward
      intakeControl(INTAKE_SPEED_PERCENT);
    } else {
      // Stop the intake
      intakeControl(0);
    }

    //Allows the user to raise and lower the arm.
    if (userController.ButtonR1.pressing()) {
      // Raises the arms.
      armControl(-ARM_SPEED_PERCENT);
    } else if (userController.ButtonR2.pressing()) {
      // Lowers the arms.
      armControl(ARM_SPEED_PERCENT);
    } else {
      // Stop the arms.
      armControl(0);
    }
    
    if (userController.ButtonX.pressing()) {
      descoreControl(DESCORE_SPEED_PERCENT);
    } else if (userController.ButtonB.pressing()) {
      descoreControl(-DESCORE_SPEED_PERCENT);
    } else {
      descoreControl(0);
    }
  
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
