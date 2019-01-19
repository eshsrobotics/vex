Notes
=====

1. Motor ports 1 and 10 are two-wire ports.  They have built-in controllors so
   a controller cable is not needed.
2. There are two circuit breakers for the VEX motor ports: one for ports 1-5
   and another for ports 6-10.  Heavily used motors (such as drive motors, and
   the two arm motors) should be evenly distributed between these two
   sections.
3. Because we can't use extension cables, ports 1 and 10 should be motors that
   are always close to the Cortex, like drive motors.
4. See http://vexwiki.org/vex_robotics_platforms/vex_edr/cpu/cortex/motor_ports
   for more information.

Proposal
========

Motor ports
-----------

1. DRIVE: Back right Mecanum wheel
2. DRIVE: Climb motor
3. DRIVE: Front left Mecanum wheel
4. ARM: Right arm motor
5. ARM: Claw motor
6. ARM: Wrist rotation motor
7. ARM: Wrist elevation motor
8. ARM: Left arm motor
9. DRIVE: Front right Mecanum wheel
10. DRIVE: Back left Mecanum wheel

We chose drive wheels for ports 1 and 10 since those are two-wire
ports rather than 3-wire, and thus cannot take a 3-wire extension
cable.  Better, then, to use motors that are never going to be far
away from the Cortex.

Analog ports
------------
4. ~ARM: Right arm potentiometer?~
5. DRIVE: Gyro
6. ~ARM: Claw potentiometer~
7. ARM: Wrist rotation potentiometer
8. ~ARM: Wrist elevation potentiometer~

I2C
---

The Mechanum wheel encoder daisy-chain is connected to the I2C port on the Cortex and is available as `I2C_1`.
