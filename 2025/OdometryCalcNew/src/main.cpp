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
#include <iostream>
#include <string>
#include <sstream>


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
double RightRotations = RightWheel.angle(degrees);
double LeftRotations = LeftWheel.angle(degrees); 

//Distance from left wheel to center
double LeftSpacing = 4.75;
double RightSpacing = 4.75;

//Wheel Diameters
double LeftDiameter = 2.75;
double RightDiameter = 2.75;


//output variables from angle calculator

double BotPositionX = 0;
double BotPositionY = 0;
double BotAngleNew = 0;
double TravelLeft = 0;
double TravelRight = 0;
double RadiusLeft = 0;
double RadiusRight = 0;


//transformed postions

double BotPostionXTransformed = 0;
double BotPostionYTransformed = 0; 

// true global variables



double TrueGlobalX = 0;
double TrueGlobalY = 0;
double TrueGlobalRotation = 0;






int main() {

    

    

    LeftWheel.setReversed(true);

    LeftWheel.resetPosition();
    RightWheel.resetPosition();

    


    

    while(1==1) 
    {
        // Updating Values
        LeftRotations = LeftWheel.position(degrees);
        RightRotations = RightWheel.position(degrees);

        TravelLeft  = (LeftRotations  / 360.0) * M_PI * LeftDiameter;
        TravelRight = (RightRotations / 360.0) * M_PI * RightDiameter;
       
        if (LeftRotations == RightRotations)
        {
            BotAngleNew = 0;
            BotPositionX = 0;
            BotPositionY = TravelRight;
        }
        else
        {
            //angle calculator stuff
            BotAngleNew = (LeftRotations - RightRotations)/(LeftSpacing + RightSpacing);
            RadiusLeft = TravelLeft/BotAngleNew;       
            RadiusRight = RadiusLeft - (LeftSpacing + RightSpacing);
            BotPositionX = -(RadiusLeft - LeftSpacing) * (BotAngleNew) + RadiusLeft - LeftSpacing;
            BotPositionY = (RadiusLeft - LeftSpacing) * sin(BotAngleNew);
        }
        

        //Transformed Postions

        BotPostionXTransformed = (cos(atan2(BotPositionX,BotPositionY) - TrueGlobalRotation) * std::sqrt(std::pow(BotPositionX, 2) + std::pow(BotPositionY, 2)));
        BotPostionYTransformed = (sin(atan2(BotPositionX,BotPositionY) - TrueGlobalRotation) * std::sqrt(std::pow(BotPositionX, 2) + std::pow(BotPositionY, 2)));

        //True Global

        TrueGlobalRotation = BotAngleNew + TrueGlobalRotation;
        TrueGlobalX =  BotPostionXTransformed + TrueGlobalX;
        TrueGlobalY = BotPostionYTransformed + TrueGlobalY;


        //display stuff
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1,1);

        Brain.Screen.print("Left Rotation: ");
        Brain.Screen.print(LeftRotations);
        Brain.Screen.newLine();
        Brain.Screen.print("Right Rotation: ");
        Brain.Screen.print(RightRotations);
        Brain.Screen.newLine();
        Brain.Screen.print("Bot Postion X: ");
        Brain.Screen.print(BotPositionX);
        Brain.Screen.newLine();
        Brain.Screen.print("Bot Postion Y: ");
        Brain.Screen.print(BotPositionY);
        Brain.Screen.newLine();
        Brain.Screen.print("Bot Angle New: ");
        Brain.Screen.print(BotAngleNew);
        Brain.Screen.newLine();
        Brain.Screen.print("Bot Postion X Transformed: ");
        Brain.Screen.print(BotPostionXTransformed);
        Brain.Screen.newLine();
        Brain.Screen.print("Bot Postion Y Transformed: ");
        Brain.Screen.print(BotPostionYTransformed);
        Brain.Screen.newLine();
        Brain.Screen.print("True Global Rotation: ");
        Brain.Screen.print(TrueGlobalRotation);
        Brain.Screen.newLine();
        Brain.Screen.print("True Global X: ");
        Brain.Screen.print(TrueGlobalX);
        Brain.Screen.newLine();
        Brain.Screen.print("True Global Y: ");
        Brain.Screen.print(TrueGlobalY);



        // reset local varibales
        
        LeftWheel.resetPosition();
        RightWheel.resetPosition();
       
        BotAngleNew = 0;
        TravelLeft  = 0;
        TravelRight = 0;
        RadiusLeft = 0;       
        RadiusRight = 0;
        BotPositionX = 0;
        BotPositionY = 0;

        BotPostionXTransformed = 0;
        BotPostionYTransformed = 0;

       
       

        
        wait(0.05, seconds);
        
    }

}
