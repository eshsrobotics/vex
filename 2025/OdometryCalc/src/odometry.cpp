#include <iostream>

#include <cmath>

double pi = M_PI;

//variables i think
float PerpendicularWheelDistRadian = 0;
float ParallelWheelDistRadian = 0;
float FinalRotation = 0;
int DriveBaseSquareControls = 0;

//Variables for Parallel stuff
float DParallel = 0; //Da
float YParallel = 0; //Ya
float XParallel = 0; //Xa
float DistanceTravelParallel = ((ParallelWheelDistRadian) / pi) * DParallel * pi; // Dta

//variables for perpendciular stuff
float DPerpendicular = 0; //Dp
float YPerpendicular = 0; //Dy
float XPerpendicular = 0; //Dx
float DistanceTravelPerpendicular = ((PerpendicularWheelDistRadian) / pi) * ((DPerpendicular) * pi); //Dtp

//something to do with t, which i think stands for travel

float DistanceBetweenWheel = std::sqrt(std::pow((XParallel - XPerpendicular), 2) + std::pow((YParallel - YPerpendicular), 2)); //Ds
float RotationBetweenWheel = atan2((XParallel-XPerpendicular),(YParallel-YPerpendicular));


float YParallelFinal = YParallel + DistanceTravelParallel;
float XPerpendicularFinal = XPerpendicular + DistanceTravelPerpendicular;

float XParallelFinal = XPerpendicularFinal - DistanceBetweenWheel * cos(FinalRotation + RotationBetweenWheel);
float YPerpendicularFinal = -(XParallelFinal - XPerpendicularFinal) * tan(FinalRotation + RotationBetweenWheel) + YParallelFinal;



void main();
