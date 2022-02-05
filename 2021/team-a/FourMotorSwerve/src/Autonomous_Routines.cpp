#include "vex.h"
#include "Autonomous_Routines.h"

using namespace vex;
using namespace std;

double translate(double desiredDistanceInches) {
  // Assigns the variables for changing the input value so the output value is equal to it
  // We got these numbers by plotting 5 points from testing and finding the line of best fit
  const double M_VALUE = 1.03;
  const double B_VALUE = 0.702;
  // This formula creates the new value that is input into the driveFor function to get an 
  // of the original distanceInches
  double correctDistanceInches = (desiredDistanceInches - B_VALUE) / M_VALUE;
  return correctDistanceInches;
}

double rotationCorrection(double desiredRotationDegrees) {
  const double M_VALUE = 1.73;
  const double B_VALUE = 0.5;
  double correctRotationDegrees = (desiredRotationDegrees - B_VALUE) / M_VALUE;
  return correctRotationDegrees;
}

std::shared_ptr<Task> selectAutonomousRoutine(AutonomousTypes autonomousType, bool& spatulaRetracted, bool& pneumaticClawOpen) { 
  const double BEETLE_LIFT_MOTOR_GEAR_RATIO = 5;
  // Pneumatic Claw Lift both motor gear ratios are 84:12 = 7.
  const double CLAW_LIFT_MOTORS_GEAR_RATIO = 7;
  
  // SMART POINTERS that allow for easy access when creating parents and children of tree.
  // Pneumatic spatula lift tasks
  auto toggleSpatulaTask1 = shared_ptr<Task>(new  SolenoidTask(PneumaticSpatula, spatulaRetracted));
  auto toggleSpatulaTask2 = shared_ptr<Task>(new SolenoidTask(PneumaticSpatula, spatulaRetracted));
  auto toggleSpatulaTask3 = shared_ptr<Task>(new SolenoidTask(PneumaticSpatula, spatulaRetracted));
  auto toggleSpatulaTask4 = shared_ptr<Task>(new SolenoidTask(PneumaticSpatula, spatulaRetracted));
  auto toggleSpatulaTask5 = shared_ptr<Task>(new SolenoidTask(PneumaticSpatula, spatulaRetracted));
  auto toggleSpatulaTask6 = shared_ptr<Task>(new  SolenoidTask(PneumaticSpatula, spatulaRetracted));
  auto toggleSpatulaTask7 = shared_ptr<Task>(new  SolenoidTask(PneumaticSpatula, spatulaRetracted));
  auto toggleSpatulaTask8 = shared_ptr<Task>(new  SolenoidTask(PneumaticSpatula, spatulaRetracted));
  auto toggleSpatulaTask9 = shared_ptr<Task>(new  SolenoidTask(PneumaticSpatula, spatulaRetracted));


  // Pneumatic Claw tasks
  auto toggleClawTask1 = shared_ptr<Task>(new SolenoidTask(PneumaticClaw, pneumaticClawOpen));
  auto toggleClawTask2 = shared_ptr<Task>(new SolenoidTask(PneumaticClaw, pneumaticClawOpen));
  auto toggleClawTask3 = shared_ptr<Task>(new SolenoidTask(PneumaticClaw, pneumaticClawOpen));
  auto toggleClawTask4 = shared_ptr<Task>(new SolenoidTask(PneumaticClaw, pneumaticClawOpen));
  auto toggleClawTask3Short = shared_ptr<Task>(new SolenoidTask(PneumaticClaw, pneumaticClawOpen));
  auto toggleClawTask4Short = shared_ptr<Task>(new SolenoidTask(PneumaticClaw, pneumaticClawOpen));
  
  // Reverse FourBar Lift tasks
  auto raiseClawLiftLEFTTask = shared_ptr<Task>(new MoveMotorTask(ArmMotorLeft, CLAW_LIFT_MOTORS_GEAR_RATIO, 50));
  auto raiseClawLiftRIGHTTask = shared_ptr<Task>(new MoveMotorTask(ArmMotorRight, CLAW_LIFT_MOTORS_GEAR_RATIO, 50));
  auto lowerClawLiftLEFTTask = shared_ptr<Task>(new MoveMotorTask(ArmMotorLeft, CLAW_LIFT_MOTORS_GEAR_RATIO, -50));
  auto lowerClawLiftRIGHTTask = shared_ptr<Task>(new MoveMotorTask(ArmMotorRight, CLAW_LIFT_MOTORS_GEAR_RATIO, -50));
  auto raiseClawLiftLEFTTask2 = shared_ptr<Task>(new MoveMotorTask(ArmMotorLeft, CLAW_LIFT_MOTORS_GEAR_RATIO, 55));
  auto raiseClawLiftRIGHTTask2 = shared_ptr<Task>(new MoveMotorTask(ArmMotorRight, CLAW_LIFT_MOTORS_GEAR_RATIO, 55));
  auto lowerClawLiftLEFTTask2 = shared_ptr<Task>(new MoveMotorTask(ArmMotorLeft, CLAW_LIFT_MOTORS_GEAR_RATIO, -55));
  auto lowerClawLiftRIGHTTask2 = shared_ptr<Task>(new MoveMotorTask(ArmMotorRight, CLAW_LIFT_MOTORS_GEAR_RATIO, -55));
  auto raiseClawLiftLEFTTask2Short = shared_ptr<Task>(new MoveMotorTask(ArmMotorLeft, CLAW_LIFT_MOTORS_GEAR_RATIO, 55));
  auto raiseClawLiftRIGHTTask2Short = shared_ptr<Task>(new MoveMotorTask(ArmMotorRight, CLAW_LIFT_MOTORS_GEAR_RATIO, 55));
  auto lowerClawLiftLEFTTask2Short = shared_ptr<Task>(new MoveMotorTask(ArmMotorLeft, CLAW_LIFT_MOTORS_GEAR_RATIO, -55));
  auto lowerClawLiftRIGHTTask2Short = shared_ptr<Task>(new MoveMotorTask(ArmMotorRight, CLAW_LIFT_MOTORS_GEAR_RATIO, -55));
  
  // Drive tasks
  auto driveForwardTask = shared_ptr<Task>(new DriveStraightTask(Drivetrain, 9, translate));
  auto driveForwardtoMobileGoalTask = shared_ptr<Task>(new DriveStraightTask(Drivetrain, 42, translate));
  auto driveBackwardsTask = shared_ptr<Task>(new DriveStraightTask(Drivetrain, -17, translate));
  auto drivetoAllianceSideTask = shared_ptr<Task>(new DriveStraightTask(Drivetrain, -23, translate));
  auto driveBackwardSetMobileGoal = shared_ptr<Task>(new DriveStraightTask(Drivetrain, -5, translate));
  auto driveForwardtoBigMogoTask = shared_ptr<Task>(new DriveStraightTask(Drivetrain, 65, translate));
  auto driveBackwardsTask2 = shared_ptr<Task>(new DriveStraightTask(Drivetrain, -11.2, translate));
  auto driveForwardTask2 = shared_ptr<Task>(new DriveStraightTask(Drivetrain, 4, translate));
  auto driveForwardtoMobileGoalTask2 = shared_ptr<Task>(new DriveStraightTask(Drivetrain, 44, translate));
  auto drivetoAllianceSideTask2 = shared_ptr<Task>(new DriveStraightTask(Drivetrain, -25, translate));
  auto driveBackwardsTask3 = shared_ptr<Task>(new DriveStraightTask(Drivetrain, -8, translate));
  auto driveBackwardSetMobileGoal2 = shared_ptr<Task>(new DriveStraightTask(Drivetrain, -10, translate));
  auto driveBackwardsTask2Short = shared_ptr<Task>(new DriveStraightTask(Drivetrain, -11.2, translate));
  auto driveBackwardsTask3Short = shared_ptr<Task>(new DriveStraightTask(Drivetrain, -8, translate));
  auto driveForwardTask2Short = shared_ptr<Task>(new DriveStraightTask(Drivetrain, 4, translate));
  
  // Drivetrain turn tasks
  // Second argument is number of degrees turned, + or - changes direction
  auto driveTurnLeftTask = shared_ptr<Task>(new TurnTask(Drivetrain, -90, rotationCorrection));
  auto driveTurnRightTask = shared_ptr<Task>(new TurnTask(Drivetrain, 95, rotationCorrection));
  auto driveTurnRightTask2 = shared_ptr<Task>(new TurnTask(Drivetrain, 110, rotationCorrection));
  auto driveTurnRightTask3 = shared_ptr<Task>(new TurnTask(Drivetrain, -65, rotationCorrection));
  auto driveTurnLeftTask2 = shared_ptr<Task>(new TurnTask(Drivetrain, -10, rotationCorrection));
  // Must correct angle of driveTurnRightTask4 for autonomous to pick up the Mogo
  auto driveTurnRightTask4 = shared_ptr<Task>(new TurnTask(Drivetrain, 145, rotationCorrection));
  auto driveTurnRightTask5 = shared_ptr<Task>(new TurnTask(Drivetrain, 90, rotationCorrection));
  auto driveTurnRightTask4Short = shared_ptr<Task>(new TurnTask(Drivetrain, 145, rotationCorrection));
  
  // Beetle Lift motor tasks
  // left and right are for the left and right mop_make_shared_tagtors on the lift
  auto lowerBeetleArmLEFTTask = shared_ptr<Task>(new MoveMotorTask(LeftLiftMotor, BEETLE_LIFT_MOTOR_GEAR_RATIO, -45));
  auto lowerBeetleArmRIGHTTask = shared_ptr<Task>(new MoveMotorTask(RightLiftMotor, BEETLE_LIFT_MOTOR_GEAR_RATIO, -45));
  auto raiseBeetleArmLEFTTask = shared_ptr<Task>(new MoveMotorTask(LeftLiftMotor, BEETLE_LIFT_MOTOR_GEAR_RATIO, 45));
  auto raiseBeetleArmRIGHTTask = shared_ptr<Task>(new MoveMotorTask(RightLiftMotor, BEETLE_LIFT_MOTOR_GEAR_RATIO, 45));
  auto lowerBeetleArmLEFTTask2 = shared_ptr<Task>(new MoveMotorTask(LeftLiftMotor, BEETLE_LIFT_MOTOR_GEAR_RATIO, -10));
  auto lowerBeetleArmRIGHTTask2 = shared_ptr<Task>(new MoveMotorTask(RightLiftMotor, BEETLE_LIFT_MOTOR_GEAR_RATIO, -10));
  auto lowerBeetleArmLEFTTask2Short = shared_ptr<Task>(new MoveMotorTask(LeftLiftMotor, BEETLE_LIFT_MOTOR_GEAR_RATIO, -10));
  auto lowerBeetleArmRIGHTTask2Short = shared_ptr<Task>(new MoveMotorTask(RightLiftMotor, BEETLE_LIFT_MOTOR_GEAR_RATIO, -10));
  
  
  


  // AUTONOMOUS (left side GOAL ON PLATFORM)
  // format is addtask(parentTask, childTask);
  // Starts with wait 0 milliseconds task as the rootTask
  auto rootTask = shared_ptr<Task>(new WaitMillisecondsTask(0));
  auto MogoWait = shared_ptr<Task>(new WaitMillisecondsTask(2500));
  auto MogoWait2 = shared_ptr<Task>(new WaitMillisecondsTask(3000));
  auto spatulaToggleFix = shared_ptr<Task>(new WaitMillisecondsTask(200));


  switch (autonomousType) {
    case RAMP_DOWN:
      // drives backwards 10in, raises pneumatic claw lift (children of rootTask)
      addTask(rootTask, driveBackwardsTask);
      addTask(rootTask, raiseClawLiftLEFTTask);
      addTask(rootTask, raiseClawLiftRIGHTTask);
      // toggles claw closed (child of raiseClawLiftLEFTTask)
      addTask(raiseClawLiftRIGHTTask, toggleClawTask1); 
      // toggles claw open (child of toggleClawTask1)
      addTask(toggleClawTask1, toggleClawTask2);
      // Lowers claw lift and dirves forwards (children of toggleClawTask2)
      addTask(toggleClawTask2, lowerClawLiftLEFTTask);
      addTask(toggleClawTask2, lowerClawLiftRIGHTTask);
      addTask(toggleClawTask2, driveForwardTask);
      // turns right (child of drive forward task)
      addTask(driveForwardTask, driveTurnRightTask);
      // Drives forwards and toggles spatula out (children of turn right task)
      addTask(driveTurnRightTask, toggleSpatulaTask1);
      addTask(driveTurnRightTask, driveForwardtoMobileGoalTask);
      //addTask(driveForwardtoMobileGoalTask, toggleSpatulaTask1);
      // Toggles spatula in (picking up mobile goal) (child of toggle spatula 1 task)
      addTask(driveForwardtoMobileGoalTask, toggleSpatulaTask2);
      addTask(driveForwardtoMobileGoalTask, MogoWait);
      //addTask(toggleClawTask2, MogoWait);
      // Drives backwards (Child of toggle spatula 2 task)
      addTask(toggleSpatulaTask2, drivetoAllianceSideTask);
      // Turns right (child of drive backwards task)
      addTask(drivetoAllianceSideTask, driveTurnRightTask2);
      // drives forwards (child of turn right task)
      //addTask(driveTurnRightTask, driveForwardtoMobileGoalTask);
      //toggles spatula out (child of drive forwards task)
      //addTask(driveForwardtoMobileGoalTask, toggleSpatulaTask1);
      //addTask(drivetoAllianceSideTask, toggleSpatulaTask3);
      addTask(driveTurnRightTask2, toggleSpatulaTask3);
      addTask(toggleSpatulaTask3, driveBackwardSetMobileGoal);
      addTask(driveBackwardSetMobileGoal, toggleSpatulaTask4);
      addTask(toggleSpatulaTask4, driveTurnRightTask3);
      addTask(driveTurnRightTask3, driveForwardtoBigMogoTask);
      addTask(driveTurnRightTask3, toggleSpatulaTask5);
      
      break;

    case RAMP_UP:
      addTask(rootTask, driveBackwardsTask2);
      addTask(rootTask, raiseClawLiftLEFTTask2);
      addTask(rootTask, raiseClawLiftRIGHTTask2);
      addTask(raiseClawLiftRIGHTTask2, toggleClawTask3);
      addTask(toggleClawTask3, toggleClawTask4);
      addTask(toggleClawTask3, lowerBeetleArmLEFTTask2);
      addTask(toggleClawTask3, lowerBeetleArmRIGHTTask2);
      addTask(toggleClawTask4, lowerClawLiftLEFTTask2);
      addTask(toggleClawTask4, lowerClawLiftRIGHTTask2);
      addTask(toggleClawTask4, driveBackwardsTask3);
      addTask(driveBackwardsTask3, driveForwardTask2);
      addTask(driveForwardTask2, driveTurnRightTask4);
      // Check angle of driveTurnRightTask4 to correct angle to pick up neutral mobile goal.
      addTask(driveTurnRightTask4, toggleSpatulaTask6);
      addTask(driveTurnRightTask4, driveForwardtoMobileGoalTask2);
      addTask(driveForwardtoMobileGoalTask2, toggleSpatulaTask7);
      addTask(driveForwardtoMobileGoalTask2, MogoWait2);
      addTask(toggleSpatulaTask7, drivetoAllianceSideTask2);
      addTask(drivetoAllianceSideTask2, driveTurnRightTask5);
      addTask(driveTurnRightTask5, toggleSpatulaTask8);
      addTask(toggleSpatulaTask8, driveBackwardSetMobileGoal2);
      addTask(driveBackwardSetMobileGoal2, toggleSpatulaTask9);
      
      break;
      case RAMP_UP_SHORT:
      addTask(rootTask, driveBackwardsTask2Short);
      addTask(rootTask, raiseClawLiftLEFTTask2Short);
      addTask(rootTask, raiseClawLiftRIGHTTask2Short);
      addTask(raiseClawLiftRIGHTTask2Short, toggleClawTask3Short);
      addTask(toggleClawTask3Short, toggleClawTask4Short);
      addTask(toggleClawTask3Short, lowerBeetleArmLEFTTask2Short);
      addTask(toggleClawTask3Short, lowerBeetleArmRIGHTTask2Short);
      addTask(toggleClawTask4Short, lowerClawLiftLEFTTask2Short);
      addTask(toggleClawTask4Short, lowerClawLiftRIGHTTask2Short);
      addTask(toggleClawTask4Short, driveBackwardsTask3Short);
      addTask(driveBackwardsTask3Short, driveForwardTask2Short);
      addTask(driveForwardTask2Short, driveTurnRightTask4Short);
    default:
      break;
    
  }
  return rootTask;
}
