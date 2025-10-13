Halloween 2025 Claw-Bot
=======================

This robot is designed to be used by small children to pick up Halloween candy
at our club's booth during the 2025 El Segundo Halloween Frolic.  It features:

* Two motors (one for each side of the claw)
* A bump sensor that can toggle the claw open and closed

Actions
-------

* When bumper sensor is **pressed**:
    - The Claw continuously closes until either:
        1. The button is released; or
        2. The _closing limit switch_ detects that we have closed enough.
* When bumper sensor is **released**:
    - The Claw continuously opens until:
        1. The button is pressed again; or
        2. The _opening limit switch_ detects that we have opened enough.
 
Safety considerations
---------------------

* The robot should not close its claw with enough force to hurt anyone.
  - Limit switches should help here.

