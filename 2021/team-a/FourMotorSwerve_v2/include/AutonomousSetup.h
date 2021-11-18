enum LiftDirection { INWARD, OUTWARD };

// Moves the lfit backward, returns no value, bool either true or false
void MoveLift(LiftDirection dir);

enum ArmDirection { UP, DOWN };

// Moves the lfit backward, returns no value, bool either true or false
void MoveArm(ArmDirection dir);

enum forkDirection { up, down };

// Moves the lfit backward, returns no value, bool either true or false
void MovepMotor(forkDirection dir);