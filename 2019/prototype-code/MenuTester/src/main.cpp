#include "robot-config.h"

//Count for side menus
int menuCount;
//Menu Conditions
bool autonDone;
bool driverDone;
bool augmentDone;
bool reviewDone;
//Count for autonomous chooser
short count;
//Count for driver chooser
short driverCount;
//Boolean for augment chooser
short augmentCount;
//String arrays for display text
const char *autonModes[9];
const char *drivers[3];
const char *augmentModes[2];

/**
    A function to get the 
    length of a string
*/
int strLen(const char *arr){
    int len = 0;
    while(arr[len] != '\0'){
        len++;
    }
    return len;
}

int main() {
    //Initialize strings
    /*
        ALL the values from here to the dashed
        line are values that can be changed. 
        These are the strings that are displayed
        when shifting through the choices.
    */
    autonModes[0] = "Do Nothing";
    autonModes[1] = "Autonomous1";
    autonModes[2] = "Autonomous2";
    autonModes[3] = "Autonomous3";
    autonModes[4] = "Autonomous4";
    autonModes[5] = "Autonomous5";
    autonModes[6] = "Autonomous6";
    autonModes[7] = "Autonomous7";
    autonModes[8] = "Autonomous8";
    drivers[0] = "Driver1";
    drivers[1] = "Driver2";
    drivers[2] = "Driver3";
    augmentModes[0] = "No <Default>";
    augmentModes[1] = "Yes";
    //--------------------------------
    //Initialize menu variables
    menuCount = 0;
    autonDone = false;
    driverDone = false;
    augmentDone = false;
    reviewDone = false; 
    /* Sub-Menu Variable Initialization */
    //Autonomous Chooser
    count = 1;
    //Driver Chooser
    driverCount = 0;
    //Augment Chooser
    augmentCount = 0;
    //Run infinite loop
    while(true){
        switch(menuCount){
            //Autonomous chooser menu
            case 0:
                /*
                    In the case the "Start Over" button
                    was pressed, reset reviewDone.
                */
                reviewDone = false;
                //Clear screen
                Brain.Screen.clearScreen(vex::color::black);
                //Initial Text
                Brain.Screen.setFillColor(vex::color::black);
                Brain.Screen.setPenColor(vex::color::white);
                Brain.Screen.printAt(110, 20, "Pre-Autonomous Chooser v1.0"); 
                //"Select Autonomous Mode" and selected mode display
                Brain.Screen.printAt(130, 50, "Select Autonomous Mode");
                Brain.Screen.setFillColor(vex::color::white);
                Brain.Screen.drawRectangle(130, 70, 220, 50);
                //"Confirm" button
                Brain.Screen.setFillColor(vex::color::green);
                Brain.Screen.drawRectangle(380, 40, 80, 50);
                Brain.Screen.setPenColor(vex::color::black);
                Brain.Screen.printAt(385, 70, "Confirm");
                //"Previous" button
                Brain.Screen.setFillColor(vex::color::red);
                Brain.Screen.drawRectangle(130, 140, 100, 62.5);
                Brain.Screen.printAt(140, 175, "Previous");
                //"Next Button"
                Brain.Screen.drawRectangle(250, 140, 100, 62.5);
                Brain.Screen.printAt(280, 175, "Next");
                //"Nothing Button"
                Brain.Screen.setFillColor(vex::color::cyan);
                Brain.Screen.drawRectangle(370, 140, 100, 62.5);
                Brain.Screen.printAt(410, 165, "Do");
                Brain.Screen.printAt(385, 185, "Nothing");
                //Side Menus
                //Auton Selection Sidemenu
                if(autonDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 35, 100, 40);
                Brain.Screen.printAt(35, 60, "Auton");
                //Indicate current menu by showing a green square
                Brain.Screen.setFillColor(vex::color::green);
                Brain.Screen.drawRectangle(10, 35, 15, 15);
                //Driver Sidemenu
                if(driverDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 85, 100, 40);
                Brain.Screen.printAt(30, 110, "Driver");
                //Augmentation Sidemenu
                if(augmentDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 135, 100, 40);
                Brain.Screen.printAt(25, 160, "Augment");
                //Review Sidemenu
                if(reviewDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 185, 100, 40);
                Brain.Screen.printAt(27.5, 210, "Review");
                //Set default text color
                Brain.Screen.setFillColor(vex::color::white);
                while(!autonDone){
                    switch(count){
                        case 0:
                            //Clear out previous text in info box
                            Brain.Screen.setFillColor(vex::color::white);
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(185, 100, autonModes[count]);
                            /*
                            These two lines of code seem counterintuitive,
                            but they are an effective way to wait for a press
                            and wait for a release.
                            */
                            while(!Brain.Screen.pressing()){}//Wait for press
                            while(Brain.Screen.pressing()){}//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                count = 8;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 1;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                autonDone = true;
                                menuCount = 1;
                            }
                        break;
                        case 1:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out color box
                            Brain.Screen.setFillColor(vex::color::red);
                            Brain.Screen.drawRectangle(130, 70, 50, 50);
                            Brain.Screen.setFillColor(vex::color::white);
                            //Print out text
                            Brain.Screen.printAt(195, 100, autonModes[count]);
                            /*
                            These two lines of code seem counterintuitive,
                            but they are an effective way to wait for a press
                            and wait for a release.
                            */
                            while(!Brain.Screen.pressing()){}//Wait for press
                            while(Brain.Screen.pressing()){}//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                count = 8;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count++;
                            }
                            //"Nothing" box
                            else if(Brain.Screen.xPosition() > 370 && Brain.Screen.xPosition() < 470 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 0;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                autonDone = true;
                                menuCount = 1;
                            }
                        break;
                        case 2:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out color box
                            Brain.Screen.setFillColor(vex::color::red);
                            Brain.Screen.drawRectangle(130, 70, 50, 50);
                            Brain.Screen.setFillColor(vex::color::white);
                            //Print out text
                            Brain.Screen.printAt(185, 100, autonModes[count]);
                            /*
                            These two lines of code seem counterintuitive,
                            but they are an effective way to wait for a press
                            and wait for a release.
                            */
                            while(!Brain.Screen.pressing()){}//Wait for press
                            while(Brain.Screen.pressing()){}//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                count--;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count++;
                            }
                            //"Nothing" box
                            else if(Brain.Screen.xPosition() > 370 && Brain.Screen.xPosition() < 470 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 0;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                autonDone = true;
                                menuCount = 1;
                            }
                        break;
                        case 3:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out color box
                            Brain.Screen.setFillColor(vex::color::red);
                            Brain.Screen.drawRectangle(130, 70, 50, 50);
                            Brain.Screen.setFillColor(vex::color::white);
                            //Print out text
                            Brain.Screen.printAt(200, 100, autonModes[count]);
                            /*
                            These two lines of code seem counterintuitive,
                            but they are an effective way to wait for a press
                            and wait for a release.
                            */
                            while(!Brain.Screen.pressing()){}//Wait for press
                            while(Brain.Screen.pressing()){}//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                count--;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count++;
                            }
                            //"Nothing" box
                            else if(Brain.Screen.xPosition() > 370 && Brain.Screen.xPosition() < 470 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 0;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                autonDone = true;
                                menuCount = 1;
                            }
                        break;
                        case 4:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out color box
                            Brain.Screen.setFillColor(vex::color::red);
                            Brain.Screen.drawRectangle(130, 70, 50, 50);
                            Brain.Screen.setFillColor(vex::color::white);
                            //Print out text
                            Brain.Screen.printAt(190, 100, autonModes[count]);
                            /*
                            These two lines of code seem counterintuitive,
                            but they are an effective way to wait for a press
                            and wait for a release.
                            */
                            while(!Brain.Screen.pressing()){}//Wait for press
                            while(Brain.Screen.pressing()){}//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                count--;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count++;
                            }
                            //"Nothing" box
                            else if(Brain.Screen.xPosition() > 370 && Brain.Screen.xPosition() < 470 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 0;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                autonDone = true;
                                menuCount = 1;
                            }
                        break;
                        case 5:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out color box
                            Brain.Screen.setFillColor(vex::color::blue);
                            Brain.Screen.drawRectangle(130, 70, 50, 50);
                            Brain.Screen.setFillColor(vex::color::white);
                            //Print out text
                            Brain.Screen.printAt(190, 100, autonModes[count]);
                            /*
                            These two lines of code seem counterintuitive,
                            but they are an effective way to wait for a press
                            and wait for a release.
                            */
                            while(!Brain.Screen.pressing()){}//Wait for press
                            while(Brain.Screen.pressing()){}//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                count--;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count++;
                            }
                            //"Nothing" box
                            else if(Brain.Screen.xPosition() > 370 && Brain.Screen.xPosition() < 470 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 0;
                            } 
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                autonDone = true;
                                menuCount = 1;
                            }
                        break;
                        case 6:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out color box
                            Brain.Screen.setFillColor(vex::color::blue);
                            Brain.Screen.drawRectangle(130, 70, 50, 50);
                            Brain.Screen.setFillColor(vex::color::white);
                            //Print out text
                            Brain.Screen.printAt(185, 100, autonModes[count]);
                            /*
                            These two lines of code seem counterintuitive,
                            but they are an effective way to wait for a press
                            and wait for a release.
                            */
                            while(!Brain.Screen.pressing()){}//Wait for press
                            while(Brain.Screen.pressing()){}//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                count--;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count++;
                            }
                            //"Nothing" box
                            else if(Brain.Screen.xPosition() > 370 && Brain.Screen.xPosition() < 470 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 0;
                            } 
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                autonDone = true;
                                menuCount = 1;
                            }
                        break;
                        case 7:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out color box
                            Brain.Screen.setFillColor(vex::color::blue);
                            Brain.Screen.drawRectangle(130, 70, 50, 50);
                            Brain.Screen.setFillColor(vex::color::white);
                            //Print out text
                            Brain.Screen.printAt(195, 100, autonModes[count]);
                            /*
                            These two lines of code seem counterintuitive,
                            but they are an effective way to wait for a press
                            and wait for a release.
                            */
                            while(!Brain.Screen.pressing()){}//Wait for press
                            while(Brain.Screen.pressing()){}//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                count--;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count++;
                            }
                            //"Nothing" box
                            else if(Brain.Screen.xPosition() > 370 && Brain.Screen.xPosition() < 470 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 0;
                            } 
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                autonDone = true;
                                menuCount = 1;
                            }
                        break;
                        case 8:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out color box
                            Brain.Screen.setFillColor(vex::color::blue);
                            Brain.Screen.drawRectangle(130, 70, 50, 50);
                            Brain.Screen.setFillColor(vex::color::white);
                            //Print out text
                            Brain.Screen.printAt(190, 100, autonModes[count]);
                            /*
                            These two lines of code seem counterintuitive,
                            but they are an effective way to wait for a press
                            and wait for a release.
                            */
                            while(!Brain.Screen.pressing()){}//Wait for press
                            while(Brain.Screen.pressing()){}//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                count--;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 1;
                            }
                            //"Nothing" box
                            else if(Brain.Screen.xPosition() > 370 && Brain.Screen.xPosition() < 470 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 0;
                            } 
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                autonDone = true;
                                menuCount = 1;
                            }
                        break;
                        default:
                            count = 0;
                        break;
                    }//end auton switch   
                }//end auton while
            break;
            //Driver chooser menu
            case 1:
                //Clear screen
                Brain.Screen.clearScreen(vex::color::black);
                //Initial Text
                Brain.Screen.setFillColor(vex::color::black);
                Brain.Screen.setPenColor(vex::color::white);
                Brain.Screen.printAt(110, 20, "Pre-Autonomous Chooser v1.0"); 
                //"Select Driver" and selected mode display
                Brain.Screen.printAt(170, 50, "Select Driver");
                Brain.Screen.setFillColor(vex::color::white);
                Brain.Screen.drawRectangle(130, 70, 220, 50);
                //Set pen to black color
                Brain.Screen.setPenColor(vex::color::black);
                //"Confirm" button
                Brain.Screen.setFillColor(vex::color::green);
                Brain.Screen.drawRectangle(380, 40, 80, 50);
                Brain.Screen.setPenColor(vex::color::black);
                Brain.Screen.printAt(385, 70, "Confirm");
                //"Previous" button
                Brain.Screen.setFillColor(vex::color::red);
                Brain.Screen.drawRectangle(130, 140, 100, 62.5);
                Brain.Screen.printAt(140, 175, "Previous");
                //"Next Button"
                Brain.Screen.drawRectangle(250, 140, 100, 62.5);
                Brain.Screen.printAt(280, 175, "Next");
                //Side Menus
                //Auton Selection Sidemenu
                if(autonDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 35, 100, 40);
                Brain.Screen.printAt(35, 60, "Auton");
                //Driver Sidemenu
                if(driverDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 85, 100, 40);
                Brain.Screen.printAt(30, 110, "Driver");
                //Indicate current menu by showing a green square
                Brain.Screen.setFillColor(vex::color::green);
                Brain.Screen.drawRectangle(10, 85, 15, 15);
                //Augmentation Sidemenu
                if(augmentDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 135, 100, 40);
                Brain.Screen.printAt(25, 160, "Augment");
                //Review Sidemenu
                if(reviewDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 185, 100, 40);
                Brain.Screen.printAt(27.5, 210, "Review");
                //Set default text color
                Brain.Screen.setFillColor(vex::color::white);
                while(!driverDone){
                    switch(driverCount){
                        case 0:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(160, 100, drivers[driverCount]);
                            /*
                            These two lines of code seem counterintuitive,
                            but they are an effective way to wait for a press
                            and wait for a release.
                            */
                            while(!Brain.Screen.pressing()){}//Wait for press
                            while(Brain.Screen.pressing()){}//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                driverCount = 2;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                driverCount++;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                driverDone = true;
                                menuCount = 2;
                            }
                        break;
                        case 1:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(210, 100, drivers[driverCount]);
                            /*
                            These two lines of code seem counterintuitive,
                            but they are an effective way to wait for a press
                            and wait for a release.
                            */
                            while(!Brain.Screen.pressing()){}//Wait for press
                            while(Brain.Screen.pressing()){}//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                driverCount--;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                driverCount++;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                driverDone = true;
                                menuCount = 2;
                            }
                        break;
                        case 2:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(220, 100, drivers[driverCount]);
                            /*
                            These two lines of code seem counterintuitive,
                            but they are an effective way to wait for a press
                            and wait for a release.
                            */
                            while(!Brain.Screen.pressing()){}//Wait for press
                            while(Brain.Screen.pressing()){}//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                driverCount--;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                driverCount = 0;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                driverDone = true;
                                menuCount = 2;
                            }
                        break;
                        default:
                            driverCount = 0;    
                        break;
                    }
                }
            break;
            //Augment chooser menu
            case 2:
                //Clear screen
                Brain.Screen.clearScreen(vex::color::black);
                //Initial Text
                Brain.Screen.setFillColor(vex::color::black);
                Brain.Screen.setPenColor(vex::color::white);
                Brain.Screen.printAt(110, 20, "Pre-Autonomous Chooser v1.0"); 
                //"Augment Driver Control?" and selected mode display
                Brain.Screen.printAt(130, 50, "Augment Driver Control?");
                Brain.Screen.setFillColor(vex::color::white);
                Brain.Screen.drawRectangle(130, 70, 220, 50);
                //Set pen to black color
                Brain.Screen.setPenColor(vex::color::black);
                //"Confirm" button
                Brain.Screen.setFillColor(vex::color::green);
                Brain.Screen.drawRectangle(380, 40, 80, 50);
                Brain.Screen.setPenColor(vex::color::black);
                Brain.Screen.printAt(385, 70, "Confirm");
                //"Previous" button
                Brain.Screen.setFillColor(vex::color::red);
                Brain.Screen.drawRectangle(130, 140, 100, 62.5);
                Brain.Screen.printAt(165, 175, "Yes");
                //"Next Button"
                Brain.Screen.drawRectangle(250, 140, 100, 62.5);
                Brain.Screen.printAt(290, 175, "No");
                //Side Menus
                //Auton Selection Sidemenu
                if(autonDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 35, 100, 40);
                Brain.Screen.printAt(35, 60, "Auton");
                //Driver Sidemenu
                if(driverDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 85, 100, 40);
                Brain.Screen.printAt(30, 110, "Driver");
                //Augmentation Sidemenu
                if(augmentDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 135, 100, 40);
                Brain.Screen.printAt(25, 160, "Augment");
                //Indicate current menu by showing a green square
                Brain.Screen.setFillColor(vex::color::green);
                Brain.Screen.drawRectangle(10, 135, 15, 15);
                //Review Sidemenu
                if(reviewDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 185, 100, 40);
                Brain.Screen.printAt(27.5, 210, "Review");
                //Set default text color
                Brain.Screen.setFillColor(vex::color::white);
                while(!augmentDone){
                    switch(augmentCount){
                        case 0:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(180, 100, augmentModes[augmentCount]);
                            /*
                            These two lines of code seem counterintuitive,
                            but they are an effective way to wait for a press
                            and wait for a release.
                            */
                            while(!Brain.Screen.pressing()){}//Wait for press
                            while(Brain.Screen.pressing()){}//Wait for release
                            //"Yes" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                augmentCount = 1;
                            }
                            //"No" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                augmentCount = 0;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                augmentDone = true;
                                menuCount = 3;
                            }
                        break;
                        case 1:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(225, 100, augmentModes[augmentCount]);
                            /*
                            These two lines of code seem counterintuitive,
                            but they are an effective way to wait for a press
                            and wait for a release.
                            */
                            while(!Brain.Screen.pressing()){}//Wait for press
                            while(Brain.Screen.pressing()){}//Wait for release
                            //"Yes" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                augmentCount = 1;
                            }
                            //"No" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                augmentCount = 0;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                augmentDone = true;
                                menuCount = 3;
                            }
                        break;
                        default:
                            augmentCount = 0;
                        break;
                    }
                }
            break;
            //Review menu
            case 3:
                //Clear screen
                Brain.Screen.clearScreen(vex::color::black);
                //Initial Text
                Brain.Screen.setFillColor(vex::color::black);
                Brain.Screen.setPenColor(vex::color::white);
                Brain.Screen.printAt(110, 20, "Pre-Autonomous Chooser v1.0"); 
                //"Review" Text
                Brain.Screen.printAt(220, 50, "Review");
                //Information box headers
                Brain.Screen.setFillColor(vex::color::black);
                Brain.Screen.printAt(155, 90, "Autonomous Mode:");
                Brain.Screen.printAt(200, 140, "Driver:");
                Brain.Screen.printAt(180, 190, "Augment DC:");
                //Information boxes
                Brain.Screen.setFillColor(vex::color::white);
                Brain.Screen.drawRectangle(145, 100, 180, 20);
                Brain.Screen.drawRectangle(145, 150, 180, 20);
                Brain.Screen.drawRectangle(145, 200, 180, 20);
                //Text in information boxes
                Brain.Screen.setPenColor(vex::color::black);
                /*------------Format to be in center-----------------*/
                //Display Autonomous Mode text
                //Initialize temporary string 
                const char *autonStr;
                //Set temp string
                autonStr = autonModes[count];
                //Initialize int for length of string
                int autonNumChar;
                //Set length of string
                autonNumChar = strLen(autonStr);
                //Initiaze int for padding
                int autonPadding;
                //Calculate the needed padding to center the string
                autonPadding = (180 - ((autonNumChar)*10))/2;
                //Print the string at a location with the offset of the padding
                Brain.Screen.printAt((145 + autonPadding), 116, autonModes[count]);
                //Display Driver text
                /* Format to be in center */
                //Initialize temporary string
                const char *driverStr;
                //Set temp string
                driverStr = drivers[driverCount];
                //Initialize int for length of string
                int driverNumChar;
                //Set length of string
                driverNumChar = strLen(driverStr);
                //Initiaze int for padding
                int driverPadding;
                //Calculate the needed padding to center the string
                driverPadding = (180 - ((driverNumChar)*10))/2;
                //Print the string at a location with the offset of the padding
                Brain.Screen.printAt((145 + driverPadding), 166, drivers[driverCount]);
                //Display Augment text
                /* Format to be in center */
                //Initialize temporary string
                const char *augmentStr;
                //Set temp string
                augmentStr = augmentModes[augmentCount];
                //Initialize int for length of string
                int augmentNumChar;
                //Set length of string
                augmentNumChar = strLen(augmentStr);
                //Initiaze int for padding
                int augmentPadding;
                //Calculate the needed padding to center the string
                augmentPadding = (180 - ((augmentNumChar)*10))/2;
                //Print the string at a location with the offset of the padding
                Brain.Screen.printAt((145 + augmentPadding), 216, augmentModes[augmentCount]);
                //Set pen to black color
                Brain.Screen.setPenColor(vex::color::black);
                //"Confirm" button
                Brain.Screen.setFillColor(vex::color::green);
                Brain.Screen.drawRectangle(360, 60, 100, 50);
                Brain.Screen.printAt(375, 90, "Confirm");
                //"Start Over" Button
                Brain.Screen.setFillColor(vex::color::red);
                Brain.Screen.drawRectangle(360, 130, 100, 50);
                Brain.Screen.printAt(385, 152, "Start");
                Brain.Screen.printAt(390, 172, "Over");
                /*----------------Side Menus------------------*/
                //Auton Selection Sidemenu
                if(autonDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 35, 100, 40);
                Brain.Screen.printAt(35, 60, "Auton");
                //Driver Sidemenu
                if(driverDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 85, 100, 40);
                Brain.Screen.printAt(30, 110, "Driver");
                //Augmentation Sidemenu
                if(augmentDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 135, 100, 40);
                Brain.Screen.printAt(25, 160, "Augment");
                //Review Sidemenu
                if(reviewDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 185, 100, 40);
                Brain.Screen.printAt(27.5, 210, "Review");
                //Indicate current menu by showing a green square
                Brain.Screen.setFillColor(vex::color::green);
                Brain.Screen.drawRectangle(10, 185, 15, 15);
                //Set default text color
                Brain.Screen.setFillColor(vex::color::white);
                while(!reviewDone){
                    /*
                        These two lines of code seem counterintuitive,
                        but they are an effective way to wait for a press
                        and wait for a release.
                    */
                    while(!Brain.Screen.pressing()){}//Wait for press
                    while(Brain.Screen.pressing()){}//Wait for release
                    //"Confirm" box
                    if(Brain.Screen.xPosition() > 360 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 60 && Brain.Screen.yPosition() < 110){
                        reviewDone = true;
                        menuCount = 4;
                    } 
                    //"Start Over" button
                    if(Brain.Screen.xPosition() > 360 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 130 && Brain.Screen.yPosition() < 180){
                        //Default all values
                        autonDone = false;
                        driverDone = false;
                        augmentDone = false;
                        count = 1;
                        driverCount = 0;
                        augmentCount = 0;
                        menuCount = 0;
                        //Set reviewDone to true to escape loop
                        reviewDone = true;
                    }
                }
            break;
            //Post-Review Menu
            case 4:
                Brain.Screen.clearScreen();
                //Initial Text
                Brain.Screen.setFillColor(vex::color::black);
                Brain.Screen.setPenColor(vex::color::white);
                Brain.Screen.printAt(110, 20, "Pre-Autonomous Chooser v1.0"); 
                //Information box headers
                Brain.Screen.setFillColor(vex::color::black);
                Brain.Screen.printAt(155, 70, "Autonomous Mode:");
                Brain.Screen.printAt(200, 120, "Driver:");
                Brain.Screen.printAt(180, 170, "Augment DC:");
                //Information boxes
                Brain.Screen.setFillColor(vex::color::white);
                Brain.Screen.drawRectangle(145, 80, 180, 20);
                Brain.Screen.drawRectangle(145, 130, 180, 20);
                Brain.Screen.drawRectangle(145, 180, 180, 20);
                //Text in information boxes
                Brain.Screen.setPenColor(vex::color::black);
                /*----------Format to be in center-----------------*/
                //Display Autonomous Mode text
                Brain.Screen.printAt((145 + autonPadding), 96, autonModes[count]);
                //Display Driver text
                /* Format to be in center */
                Brain.Screen.printAt((145 + driverPadding), 146, drivers[driverCount]);
                //Display Augment text
                /* Format to be in center */
                Brain.Screen.printAt((145 + augmentPadding), 196, augmentModes[augmentCount]);
                //Set pen to black color
                Brain.Screen.setPenColor(vex::color::black);
                /*----------------Side Menus------------------*/
                //Auton Selection Sidemenu
                if(autonDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 35, 100, 40);
                Brain.Screen.printAt(35, 60, "Auton");
                //Driver Sidemenu
                if(driverDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 85, 100, 40);
                Brain.Screen.printAt(30, 110, "Driver");
                //Augmentation Sidemenu
                if(augmentDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 135, 100, 40);
                Brain.Screen.printAt(25, 160, "Augment");
                //Review Sidemenu
                if(reviewDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 185, 100, 40);
                Brain.Screen.printAt(27.5, 210, "Review");
                //Set default text color
                Brain.Screen.setFillColor(vex::color::white);
                while(true){}
            break;
            default:
                
            break;
        }//end menu switch
    }//end infinite loop
}//end main