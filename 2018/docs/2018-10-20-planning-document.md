This is a planning document for the ESHS 2018 VEX team's Turning Point robot.

Drive
-----

The drive should be C-shaped in order to allow for payloads in the
middle, and it should be capable of strafing.

* Two drives that we know of are capable of this: A drive with 4
  omniwheels on the sides and one in the middle, and a holonomic drive
  based on mecanum wheels.

  <img src="http://www.robotc.net/blog/wp-content/gallery/mecanum-robot/dscf1337.jpg"
      alt="Mecanum drive sample image"
      width="150" />

  The question is this: _Which is
  easier to push off of the central platform?_ @jlim_20 was concerned
  that the omniwheel design might be easier to our foes to push, which
  is a point that @uakotaobi is willing to concede--but it should
  still be tested.

* Strafing (moving side-to-side without turning) @uakotaobi views as
  vital to simplifying the task of positioning the robot properly to
  place the caps on the elevated poles, the highest of which are 34
  inches off the ground.  Either design should allow for this.
    * The preferred control scheme is an open question.
        * @uakotaobi likes button pads.
        * The mecanum examples use the left joystick (and reserve the
          horizontal axis of the right joystick for turning.)

Arm
---

* The arm lift should be double-reverse 4-bar (DR4B) lift at a
  minimum.

  <img src="https://www.vexforum.com/index.php/attachment/56464da79abde_IMG_5336.jpg"
       alt="Double-reverse 4-bar arm lift sample image"
       width="150"/>
    * Measurements made by @jlim_20 on 2018-10-20 should that even the
      test lift that was made the week before should be capable of
      reaching that height if designed well.
    * If more reach is needed, we can consider a hybrid 6-bar lift/DR4B
      design.

      <img src="https://www.robolink.com/wp-content/uploads/2016/09/6-bar-lift-1024x794.jpg"
           alt="6-bar lift sample image"
           width="150"/>
* An elevator lift was considered, but experiences other teams have
  had needing to grease metal surfaces to prevent the sliding
  mechanism from failing have caused us to conclude that such designs
  are more trouble that they're worth.

* Rubber band tension and placement are *very* important for DR4B
  designs; done right, two motors should be enough to lift even a
  heavy arm.
    * Arm motors are preferably placed on the inside of the arm so
      they don't get caught on anything.
    * Should the motors be placed on the top gears of the DR4B lift,
      or on the bottom?
* Where will the claw be when the arm is down?
    * Horizontal and aligned with the floor, but in _front_ of the
      barrel mechanism (see below.)

Flipping mechanism
------------------

We need to be able to turn the caps to our side's color.  We
considered three mechanisms:
1. The "pancake device" - a stick or spatula at the bottom of the
   robot which would move upward to flip the tabs
2. (Possibly rotating) claw
3. Flipping by using the same barrel design commonly used for bar
   intake (two sprockets separated by rubber bands), but in reverse

Of the three designs, the barrel mechanism seems the most promising
for the following reasons:
* Should be able to flip the caps with ease: Just drive up to them
* Can *steal balls* by reversing the barrel and intentionally running
  into the balls
    * We'd need to determine the height of the barrel carefully to
      make this happen; remember that the arm still needs to reach the
      ground.
        * Possibly use smaller sprockets?
* Re-reverse the barrel to donate stolen balls to our teammates.

Claw
----

* Maybe none?  A passive fork design with four prongs may be all we
  need to pick up the caps
    * Must be able to pick up the caps _quickly_ and _efficiently_,
      without a lot of worry about repositioning.
