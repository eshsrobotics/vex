/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       gavinashen                                                */
/*    Created:      3/8/2026, 3:37:55 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include <cmath>


using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here

// Port Assignments


//Odometry wheels

rotation LeftWheel = rotation(PORT1);
rotation RightWheel = rotation(PORT2);

//inertial sensor
inertial myInertial = inertial(PORT3,left);


// Tracking Variables
double RightRotations = 0;
double LeftRotations = 0;

//Distance from left wheel to center
double LeftSpacing = 3;
double RightSpacing = 3;

//Wheel Diameters
double LeftDiameter = 2.75;
double RightDiameter = 2.75;


double AngleCalculator(double LeftRotations, double RightRotations, double LeftSpacing, double RightSpacing)
{
    double BotAngleNew = (LeftRotations - RightRotations)/(LeftSpacing + RightSpacing);
    double TravelLeft  = (LeftRotations  / 360.0) * M_PI * LeftDiameter;
    double TravelRight = (RightRotations / 360.0) * M_PI * RightDiameter;
    double RadiusLeft = TravelLeft/BotAngleNew;       
    double RadiusRight = RadiusLeft - (LeftSpacing + RightSpacing);
    double BotPositionX = -(RadiusLeft - LeftSpacing) * cos(BotAngleNew) + RadiusLeft - LeftSpacing;
    double BotPositionY = sqrt(std::pow((RadiusLeft - LeftSpacing), 2) - std::pow(((-(RadiusLeft - LeftSpacing) * cos(BotAngleNew) + RadiusLeft - LeftSpacing) - RadiusLeft + LeftSpacing),2));

    return BotPositionX;
    return BotPositionY;
    return BotAngleNew;
}



int main() {

   
    Brain.Screen.print("IM WORKING");

     while(1==1) {
        // Updating Values
        double LeftRotations = LeftWheel.angle(degrees); 
        double RightRotations = RightWheel.angle(degrees);
        AngleCalculator(LeftRotations, RightRotations, LeftSpacing, RightSpacing);


        

    }

}
