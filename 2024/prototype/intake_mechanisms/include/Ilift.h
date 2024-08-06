#ifndef __ILIFT_H_INCLUDED__
#define __ILIFT_H_INCLUDED__

class Ilift {
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
    virtual double lift() const = 0;

    // Returns true if the lift can go all the way to the ground.
    virtual bool canReachGround() const { return false; }
};


#endif // __ILIFT_H_INCLUDED__