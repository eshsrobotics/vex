
#include "vex.h"

enum LineTrackingEnvironment {
    // Environment: Karlee's room, artificial lighting.
    // Line color: green painter tape.
    // Floor color: line paper (white).
    KARLEES_ROOM_GREEN_ON_WHITE,
    
    // Enviornment: Brandon's room, no lighting.
    // Line color: White envelope.
    // Floor color: Dark Brown Table.
    BRANDONS_DARKENED_ROOM_DARK_VS_WHITE,


    // TBD.
    FIRST_COMPETITION
};

const LineTrackingEnvironment environment = KARLEES_ROOM_GREEN_ON_WHITE;

// if tracker detects a line in the current environment then return true.
bool sensorSeesLine(vex::line& lineTracker);

// Returns true if on a line and false if not on a line
bool onLine();

// Returns true if no sensors detect a line and false if atleast one sensor detects a line
bool notOnLine();

// Returns true if only left sensor sees a line and false if left sensor doesn't see a line or other sensors see a line
bool leftOfLine();

// Returns true if only right sensor sees a line and false if right sensor doesn't see a line or other sensors see a line
bool rightOfLine();