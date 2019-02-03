Main teleop controls
====================

* Movement: Standard Mecanum controls.
  * Left joystick (`Ch3` and `Ch4`): Strafing forward/back/left/right
  * Right joystick (`Ch1`): Turning left/right
* Arm
  * `Btn5D` [front of controller, bottom right]: Raise arm [**common**]
  * `Btn6D` [front of controller, bottom left]: Lower arm [**common**]
* Wrist
  * `Btn7U` [top left button pad of controller, top button]: Rotate wrist clockwise
  * `Btn7D` [top left button pad of controller, bottom button]: Rotate wrist counterclockwise
* Precision
  * `Btn5U` [front of controller, top left]: When held down, movements
    in the main drive and wrist rotation motor are slowed by 50%.
    Note that the arm is not affected.

Pre-programmed sequences
========================

* `Btn7L`: Execute autonomous routine #1 [*extremely rare*; might require button to be held down]
* `Btn8L`: Stop execution of autonomous test routine, returning to full teleop