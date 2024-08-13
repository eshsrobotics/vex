#ifndef __ILIFT_H_INCLUDED__
#define __ILIFT_H_INCLUDED__

#include <string>

class Ilift {
    public:
        /**
         * Each one of our Ilift prototypes will need all of the height values.
         * This struct stores each one. However, each lift will have different
         * values for each of them. Each derived class will implement its own
         * values for these.
         *
         * All values should range from 0.0 to 1.0 (which is the same range
         * returned by this->lift().)
         */
         struct LiftHeights {
            // The lowest, or ground height. May be equal to mobileGoalHeight on
            // some robots.
            //
            // Should be no less than 0.0 and no greater than 1.0.
            double defaultHeight;

            // Correct lift height for intaking into mobile goals.
            //
            // Should be no less than defaultHeight, and no greater than 1.0.
            double mobileGoalHeight;

            // Correct lift height for intaking into alliance stakes.
            //
            // Should be no less than mobileGoalHeight, and no greater than 1.0.
            double allianceStakeHeight;

            // Correct lift height for intaking into wall stakes.
            //
            // Should be no less than allianceStakeHeight, and no greater than 1.0.
            double wallStakeHeight;
        };

    public:

        /**
         * The lift method will determine how much will the lift raise up. We need
         * this to make sure our lift raises appropriately for mobile goals,
         * alliance stakes, and neutral wall stakes.
         *
         * @param position position will be a value between 0 and 1. 1 will be the
         * maximum distance which the lift can raise up.
         */
        virtual void lift(double position) = 0;

        /**
         * Query the lift's position.
         * @return returns a number between 0 and 1. 0 is lift's lowest position
         * while 1 is the lift's highest position. The values are determined
         * experimentally.
         */
        virtual double liftPosition() const = 0;

        // Returns true if the lift can go all the way to the ground.
        virtual bool canReachGround() const { return false; }

        /**
         * Returns the default height value constants. However, each robot will
         * have different height values for their lift. The derived classes can
         * override the default values.
         */
        virtual LiftHeights liftHeights() const {
            return LiftHeights {
                .defaultHeight=0,
                .mobileGoalHeight=0.2,
                .allianceStakeHeight=0.4,
                .wallStakeHeight=0.6,
            };
        }
};

#endif // __ILIFT_H_INCLUDED__