#ifndef __IINTAKE_H_INCLUDED__
#define __IINTAKE_H_INCLUDED__

class Iintake {
  public:
    /**
     * Turn on the intake given a specific speed. The speed will be
     * different for different lift prototypes.
     *
     * @param speed_pct The speed at which the intake spins relative to its
     *                  maximum potential speed. The values are between 1
     *                  (intaking at full speed) and -1 (outaking at full
     *                  speed).  A value of 0 stops the intake.
     */
    virtual void intake(double speed_pct) = 0;
};

#endif //__IINTAKE_H_INCLUDED__