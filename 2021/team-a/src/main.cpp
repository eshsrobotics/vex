// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// BackLeft             motor         12              
// BackRight            motor         14              
// FrontLeft            motor         11              
// FrontRight           motor         13              
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\FRC1                                             */
/*    Created:      Wed Sep 15 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//#include "robot-config.h"

#include "vex.h"


int main() {

    while(true) {
        
        // Axis 1: Right joystick left-right channel - Jacob wants this to be the rotation channel        
        // Axis 2: Right joystick up/down channel    - (UnUSED)
        // Axis 3: Left joystick up/down channel     - Jacob wants it to be Fwd-Bakwd
        // Axis 4: Left joystick left-right channel  - Jacob wants it to be left-right strafe
        
        // Chart of channel sums for holonomic omniwheel X-drives
        // (From https://www.youtube.com/watch?v=1-Ju_VqYLAU&t=8m02s)
        //
        //     | Y-direction    X-direction   Rotation
        // ----+--------------------------------------
        // LFM | +ch3           +ch4          +ch1 
        // LBM | +ch3           -ch4          +ch1
        // RFM | -ch3           +ch4          +ch1
        // RBM | -ch3           -ch4          +ch1
        // 
        
        auto ch1 =  Controller1.Axis1.value();
        auto ch3 = -Controller1.Axis3.value();
        auto ch4 =  Controller1.Axis4.value();

        BackLeft.spin(vex::directionType::fwd,    ch3 + ch1 - ch4, vex::velocityUnits::pct);
        BackRight.spin(vex::directionType::fwd,  -ch3 + ch1 - ch4, vex::velocityUnits::pct);
        FrontLeft.spin(vex::directionType::fwd,   ch3 + ch1 + ch4, vex::velocityUnits::pct);
        FrontRight.spin(vex::directionType::fwd, -ch3 + ch1 + ch4, vex::velocityUnits::pct);

        vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources.
    }
    
    //  chassis arrangement of motors:
    //  
    //   

    // Motion : mot1 mot2 mot3 mot3
    // fwd : lfm:ccw  rfm:cw    lbm:ccw rbm:cw
    // bak : lfm:cw   rfm:ccw   lbm:cw  rbm:ccw
    // slf : lfm:   rfm:    lbm:  rbm: 
    // srt : lfm:  rfm:   lbm:  rbm: 
    // rlf : lfm:   rfm:    lbm:  rbm: 
    // rrt : lfm:   rfm:    lbm:  rbm: 
}