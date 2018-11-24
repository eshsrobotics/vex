Building tasks
==============
1. [ ] ARM: Add high-friction padding to the claw
1. [ ] ROBOT: Add counter-weights to the back of the robot so it does not tip over
   when the arm is extended with a load
1. [ ] ROBOT: Rewire the motors according to the assignments in
   [./proposed-motor-port-scheme.md](proposed-motor-port-scheme.md)
1. [ ] ARM: Install a limit switch to prevent the arm from traveling up more
   than it ought to.

Programming tasks
=================
1. [ ] ARM: Figure out how to detect the current rotation of the wrist
   rotation motor's potentiometer
1. [ ] DRIVE: Convert the encoders' measurement of the robot's travel at a
   known distance from clicks to meters using a measuring tape
1. [ ] DRIVE: Write a `driveForward(float meters)` function and test it
   relentlessly
1. [ ] DRIVE [gyro]: Mount the gyro on rubber grommets, as
   [http://vexwiki.org/vex_robotics_platforms/vex_edr/sensors/gyroscope#mountingvibration](this
   link) (and [https://www.youtube.com/watch?v=KSoC4d5VVsE](this video))
   recommends
1. [ ] DRIVE [gyro]: Reset `SensorType[in8]` (or whichever analog port you've
   connected to the gyro) to `sensorNone` for at least 1.5 seconds during the
   pre-autonomous phase, as
   [http://www.robotc.net/blog/2011/10/13/programming-the-vex-gyro-in-robotc/](this
   link) suggests
1. [ ] DRIVE [gyro]: Write a `turn(float degrees)` function and test it relentlessly

Programming notes
=================
1. According to
   [https://renegaderobotics.org/vex-sensors-jumper-clips-led-indicators/](this
   link):
       1. We can get a value from a digital sensor using `SensorValue[dgtl4]`
          (or some other port.)
       1. When a jumper cable is on a digital sensor,
          `SensorValue[thatDigitalPort]` will be equal to *0*, not 1.
       1. You can affix the LEDs to extension cables.  This is often the best
          way to mount them somewhere where other VEX teams can see them.
       1. RobotC also allows you to set up LEDs in the Motor and Sensor Setup
          dialog.  Just use:
          - _VEX LED_ or _Digital Out_ for LEDs, and
          - _Digital In_ for ordinary jumper cables.
          - There is a difference: when LEDs are set to _VEX LED_, you turn
            them on by assigning 1 to `SensorValue[LEDName]` and turn it off
            by assigning a 0 to it.  When LEDs are set to _Digital Out_, the
            opposite is true.
1. In autonomous, you don't want to come to sudden stops; inertia will cause
   the robot to drift.  Instead, when you've reached your goal, [https://renegaderobotics.org/new-programming-concepts/](reverse
   direction) very briefly (say, 50ms) and _then_ cut the power.  The robot
   will stop on a dime.
