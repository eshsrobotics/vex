Main teleop controls
====================

* Movement: Standard Mecanum controls.
  * Left joystick (`Ch3` and `Ch4`): Strafing forward/back/left/right
  * Right joystick (`Ch1`): Turning left/right
* Arm
  * `Btn5D` [front of controller, bottom right]: Raise arm [**common**]
  * `Btn6D` [front of controller, bottom left]: Lower arm [**common**]
* Wrist
  * `Btn7U` [front of controller, top left]: Rotate wrist clockwise
  * `Btn7D` [front of controller, top right]: Rotate wrist counterclockwise
* ~Claw~
  * ~`Btn8R` [top right button-pad of controller, right button]: Open claw [**common**]~
  * ~`Btn8D` [top right button-pad of controller, bottom button]: Close claw [**common**]~

Pre-programmed sequences
========================

* ~`Btn7R`: Grab with claw, rotate 180 degrees, then release claw [*common*; used for ground flips and for rarer air flips]~
* ~`Btn7U`: Raise wrist [**rare**; wrist is lowered and raised automatically at the beginning and end of teleop]~
* ~`Btn7D`: Lower wrist [**rare**; wrist is lowered and raised automatically at the beginning and end of teleop]~
* `Btn7L`: Execute autonomous routine #1 [*extremely rare*; might require button to be held down]
* `Btn8L`: Stop execution of autonomous test routine, returning to full teleop