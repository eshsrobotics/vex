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
    parser = argparse.ArgumentParser(prog="calculate.py")

    parser.add_argument(
        "X",
        type=float,
        help="Base of the right triangle; outward extent of the arm.")
    parser.add_argument(
        "Y",
        type=float,
        help="Height of the right triangle; upward extent of the arm.")
    parser.add_argument(
        "L1",
        type=float,
        help="Length of the upper arm (shoulder to elbow) in inches.")
    parser.add_argument(
        "L2",
        type=float,
        help="Length of the forearm (elbow to wrist), again in inches.")
    parser.add_argument(
        "-v",
        "--verbose",
        type=bool,
        default=False,
        help="If supplied, causes this script to print more verbose messages.")

    parser.parse_args()

    verbosity = parser.verbose

    return parser.L1, parser.L2, parser.X, parser.Y


if __name__ == "__main__":
    L1, L2, X, Y = parseArguments()

    errorMessage = ""

    h = math.sqrt(X * X + Y * Y)

    if X < 0:
        errorMessage = "Illegal negative value for X"
    elif Y < 0:
        errorMessage = "Illegal negative value for Y"
    elif h < math.abs(L2 - L1):
        errorMessage = f"Impossible hypotenuse (elbow squeezed too tightly; cannot be less than {L2:.2f} - {L1:.2f} = {L2 - L1:.2f})"
    elif h > L1 + L2:
        errorMessage = "Impossible hypotenuse (arm stretched too far; cannot be greater than {L1:.2f} + {L2:.2f})"

    if errorMessage != "":
        print(
            f"Illegal argument detected.  Error message was:\n  {errorMessage}")
        exit(1)

    # If control makes it here, all values are okay.
