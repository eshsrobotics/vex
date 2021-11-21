#ifndef USERCONTROLTASK_H_INCLUDED
#define USERCONTROLTASK_H_INCLUDED

// Controls the pneumatics, chnages staes from true to false or false to true,
// function found at the end of main.cpp
void PneumaticControlClaw();
void PneumaticControlSpatula();

void usercontrol(void);

#endif