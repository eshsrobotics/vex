## Control scheme (How to Drive Robot)
- Switch modes: A (Auto -> Semi-Auto -> Manual)
  * MODE 1: Auto Mode (uses a state machine -- no user input)
  * Mode 2: Semi Auto Mode
    - R1: Spin catapult motor 180 degrees without waiting.
  * MODE 3: Manual Mode
    - R1: When held down, spins the catapult motor.

- Intake:
  * L1: Spins both intake motors outward (ejects a triball)
  * L2: Spins both intake motors forward (loads triball onto catapult)
  * R2: Spins only outer motor (Intakes triball without releasing to catapult)
  * Left: Basically shoots the triball.

- Differential drive (arcade drive scheme):
  * Axis 3 (left joystick vertical axis): Drives forward/backward
  * Axis 1 (right joystick horizontal axis): Turns left/right

- Winglet Controls (Pushing)
  * Left: (Open? Close?) winglets
  * Rigght: (Close? Open?) winglets