#!/usr/bin/env python

import argparse
import math

verbosity = False


def parseArguments():
  """
    Parses the command-line arguments and returns our four critical
    parameters: X, Y, L1, and L2.

    Returns:
      Returns a four-tuple of (x, y, l1, l2).
    """
  parser = argparse.ArgumentParser(prog="calculate.py",
                                   description="""This program performs inverse kinematics to figure out the trigonometric angles of a three-joint robotic arm with three degrees of freedom.""")

  parser.add_argument("X",
                      type=float,
                      help="Base of the right triangle; outward extent of the arm.")
  parser.add_argument("Y",
                      type=float,
                      help="Height of the right triangle; upward extent of the arm.")
  parser.add_argument("L1",
                      type=float,
                      help="Length of the upper arm (shoulder to elbow) in inches.")
  parser.add_argument("L2",
                      type=float,
                      help="Length of the forearm (elbow to wrist), again in inches.")
  parser.add_argument("-v",
                      "--verbose",
                      type=bool,
                      default=False,
                      help="If supplied, causes this script to print more verbose messages.")
  args = parser.parse_args()

  verbosity = args.verbose

  return args.L1, args.L2, args.X, args.Y


if __name__ == "__main__":
  RADIANS_TO_DEGREES = 180.0 / math.pi 
  L1, L2, X, Y = parseArguments()
  EPSILON = 1e-03

  errorMessage = ""

  h = math.sqrt(X * X + Y * Y)

  if X < 0:
    errorMessage = "Illegal negative value for X"
  elif Y < 0:
    errorMessage = "Illegal negative value for Y"
  elif h < EPSILON:
    errorMessage = f"Impossible hypotenuse (elbow squeezed too tightly; cannot be less than {EPSILON:.3f} inches)"
  elif h < math.fabs(L2 - L1):
    errorMessage = f"Impossible hypotenuse (elbow squeezed too tightly; cannot be less than {L2:.2f} - {L1:.2f} = {L2 - L1:.2f} inches)"
  elif h > L1 + L2:
    errorMessage = f"Impossible hypotenuse (arm stretched too far; cannot be greater than {L1:.2f} + {L2:.2f} inches)"

  if errorMessage != "":
    print(f"Extremely Illegal argument detected.  Error message was:\n  {errorMessage}")
    exit(1)

  # If control makes it here, all values are okay.
  gamma = math.acos((h * h - L1 * L1 - L2 * L2) / (-2 * L1 * L2))
  alpha = math.asin(L2 * math.sin(gamma) / h)
  beta = math.pi - alpha - gamma
  theta = math.asin(Y / h)
  phi = math.asin(X / h)
  
  # The arm starts vertically oriented.  We want angles the encoders will be happy with for PID.
  
  # Need the -90 term because the the math says the shoulder should be 90 degrees
  # at vertical, but the encoders say that this is really 0 degrees.
  shoulderAngle = (alpha + theta) * RADIANS_TO_DEGREES - 90
  elbowAngle = gamma * RADIANS_TO_DEGREES 
  wristAngle = (beta + phi) * RADIANS_TO_DEGREES
  
  if verbosity:
    print(f"""h = {h} inches
ɣ = {gamma} radians
ɑ = {alpha} radians
β = {beta} radians
θ = {theta} radians
φ = {phi} radians

shoulder = ɑ + θ = {shoulderAngle}° (from vertical)
elbow    = ɣ     = {elbowAngle}° (bending outward)
wrist    = β + φ = {wristAngle}° (from pointing straight)
""")
  else:
    print(f"""shoulder = {shoulderAngle:.2f}° (from vertical)
elbow    = {elbowAngle:.2f}° (bending outward)
wrist    = {wristAngle:.2f}° (from pointing straight)
""")
