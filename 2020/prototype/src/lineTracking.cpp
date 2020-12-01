#include "lineTracking.h"


bool sensorSeesLine(line& lineTracker) {
  switch(environment) {
    case KARLEES_ROOM_GREEN_ON_WHITE:
      // TODO: replace with actual measured value.
      if (lineTracker.reflectivity() < 30) {
        return true;
      }
      break;
    case BRANDONS_DARKENED_ROOM_DARK_VS_WHITE:
      // White envelope (line) has 95 reflectivity vs the Dark Brown Table (floor) which has 8 reflectivity
      if (lineTracker.reflectivity() > 70) {
        return true;
      }
      break;
  } 
  return false;
}

// Returns true if on a line and false if not on a line
bool onLine() {
  if (sensorSeesLine(MiddleLineTracker) || (sensorSeesLine(LeftLineTracker) && sensorSeesLine(RightLineTracker))) {
    return true;
  }
  return false;
}

// Returns true if no sensors detect a line and false if atleast one sensor detects a line
bool notOnLine() {
  if (!sensorSeesLine(MiddleLineTracker) && !sensorSeesLine(LeftLineTracker) && !sensorSeesLine(RightLineTracker)) {
    return true;
  }
  return false;
}

// Returns true if only left sensor sees a line and false if left sensor doesn't see a line or other sensors see a line
bool leftOfLine() {
  if (!sensorSeesLine(MiddleLineTracker) && sensorSeesLine(LeftLineTracker) && !sensorSeesLine(RightLineTracker)) {
    return true;
  }
  return false;
}

// Returns true if only right sensor sees a line and false if right sensor doesn't see a line or other sensors see a line
bool rightOfLine() {
  if (!sensorSeesLine(MiddleLineTracker) && !sensorSeesLine(LeftLineTracker) && sensorSeesLine(RightLineTracker)) {
    return true;
  }
  return false;
}

