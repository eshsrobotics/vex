#ifndef __IDRIVE_H_INCLUDED__
#define __IDRIVE_H_INCLUDED__

/**
 * Interface for prototypes that are capable of differential driving -- that is,
 * they have a left side and a right side that can be made to drive in opposite
 * directions.
 *
 * The number of motors used for the drive is irrelevant to the consumers of
 * this API.
 */
class Idrive {
    public:
        /**
         * Drive the robot with the given relative speeds. A value of +1.0 will
         * be full speed forward while -1.0 will be full speed backward.
         *
         * To stop the robot, pass 0 for both parameters.
         *
         * @param fwd  Drive speed in the forward direction.+1.0 is maximum
         *             speed forward; -1.0 is maxim speed in reverse.
         * @param turn Turning speed. +1.0 turns clockwise at full speed and
         *             -1.0 turns counterclockwise at full speed.
         */
        virtual void drive(double fwd, double turn) = 0;
};

#endif //__IDRIVE_H_INCLUDED__

