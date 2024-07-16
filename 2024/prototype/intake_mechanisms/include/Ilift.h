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
};


#endif // __ILIFT_H_INCLUDED__