#include "task.h"

// Allows users to easily switch between autonomous task trees.
enum AutonomousTypes {
  RAMP_DOWN, 
  RAMP_UP,
  PROGRAMMING_SKILLS,
  RAMP_UP_SHORT,
  RAMP_DOWN_SHORT,
};

// Allows user to slelect autonomous routine between task trees. 
std::shared_ptr<Task> selectAutonomousRoutine(AutonomousTypes autonomousType, bool& spatulaRetracted, bool& pneumaticClawOpen);

