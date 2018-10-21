What are these files?
---------------------

Whenever we write software for our test-bots and our testing rigs, we keep the code here in hopes that it might be useful later.  We also put a little bit of the story behind the code in this file -- instructions, clever tricks the software does, lessons learned, and so forth.

Testbedmotortest.c ================== A simple program tat shows how
to use timers and touch sensors to toggle program state.  The
`toggleMotors` button is not vulnerable to button bounce because the
program waits before reactivating it.

MecanumStrafeTest.c
===================
Written by @uakotaobi on 2018-10-21 to test a 4-Mecanum-wheel holonomic drive he assembled the previous day.

* The code was originally copied from the sample program known as `Sample Programs/VEX2/Remote Control/Mecanum Drive with Deadzone Thresholds.c`.  The "deadzone threshold" was increased from its default of 15 to 50 to make the controls feel less sensitive.

* Code organization:

    * `void mecanumDrive(int leftRight, int forwardBack, int turn)`

       This is the function that actually drives the robot.  It needs
       three power values ranging from -127 (left or backward) to 127
       (right or forward.)  As long as `turn` is 0, the robot will
       theoretically stay facing its current direction as it travels.

    * `void mecanumControl(int leftRightJoystickChannel, int frontBackJoystickChannel, int turnJoystickChannel, int deadzoneThreshold)`

       A wrapper around `mecanumDrive()` akin to `tankControl()` or
       `arcadeControl()`.  Its purpose is to make it easy to control
       the Mecanum drive with joysticks -- just pass in the desired
       joystick channels and call the function continuously in a loop.

    * `autonomousTest()`

       A simple routine that makes the robot travel in a square --
       forward, right, back, and left -- in a 10-second loop.  To
       activate it, hold down `Btn5U` for half a second, and to
       deactivate it, press `Btn5u` while the robot is moving
       autonomously.`

       A real autonomous program must be much more sophisticated, but
       for now, this function illustrates how Mecanum drives can be
       made to strafe automatically.

    * `task main()`

       The code in here illustrates how to use and reset VEX's
       built-in 32-second timers.

* Lessons learned:
    1. Mecanum drives can rattle apart very, _very_ easily.  Always
       have some form of cross-bracing which is parallel to the wheel
       axles.
    2. Mecanum wheels are _chiral_.  There are two different types of
       mecanum wheels which are mirror-image _enantiomers_ of one
       another.  The appropriate configuration for a holonomic drive
       has the wheel "spokes" pointing dialogonally outward like an
       "X" from the perspective of the top of the robot, and "like a
       diamond" from the perspective of the bottom of the robot.
    3. When plugging in the male two-pin VEX 393 motor wiires into the
       female VEX 2-to-3 pin connnectors, te front two wheels should
       have the opposite polarity to the back two wheels (e.g.,
       red-to-red on the front tires and red-to-black on the back.)
    4. Don't accidentally plug the 3-pin connectors into the Cortex's
       digital ports.  Read the labels.

The test bot itself drifts very, _very_ easily when strafing so that
it seldom stays in alignment over long distances.  There's probably an
easy fix for this, but @uakotaobi isn't sure what it is.
