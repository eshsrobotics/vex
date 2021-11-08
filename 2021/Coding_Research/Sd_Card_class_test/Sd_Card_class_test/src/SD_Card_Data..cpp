
#include "vex.h"
#include "robot-config.h"
using namespace vex;
vex::competition Competition;
std::ofstream ofs;

  /*   Drivetrain.velocity(percentUnits units);
    Drivetrain.velocity(velocityUnits units);
    Drivetrain.current();
    Drivetrain.current(percentUnits units);
    Drivetrain.efficiency();
    Drivetrain.isDone();
    Drivetrain.isMoving();
    Drivetrain.power();
    Drivetrain.temperature(percentUnits units);
    Drivetrain.torque();
    Drivetrain.voltage(); */
 










void drive() {
  m.setVelocity(100, vex::velocityUnits::pct);
  Motor2.setVelocity(100, vex::velocityUnits::pct);
  Motor3.setVelocity(100, vex::velocityUnits::pct);
  Motor4.setVelocity(100, vex::velocityUnits::pct);
 

  m.spin(vex::directionType::fwd);
  Motor2.spin(vex::directionType::fwd);
  Motor3.spin(vex::directionType::fwd);
  Motor4.spin(vex::directionType::fwd);
 
}


void Batterydata() {
  ofs << Brain.Battery.capacity(vex::percentUnits::pct) << ","
      << Brain.Battery.temperature(vex::temperatureUnits::fahrenheit) << ",";
}

void competitionDate() {
  ofs << Competition.isAutonomous() << ","
      << Competition.isDriverControl()
      << Competition.isCompetitionSwitch() << ","
      << Competition.isFieldControl() << Competition.isEnabled() << ",";
}

void Controller1troller1Data() {
  ofs << Controller1.Axis1.position() << "," << Controller1.Axis1.value() << ","
      << Controller1.Axis2.position() << "," << Controller1.Axis2.value() << ","
      << Controller1.Axis3.position() << "," << Controller1.Axis3.value() << ","
      << Controller1.Axis4.position() << "," << Controller1.Axis4.value() << ","
      << Controller1.ButtonA.pressing() << "," << Controller1.ButtonB.pressing()
      << "," << Controller1.ButtonX.pressing() << ","
      << Controller1.ButtonY.pressing() << ","
      << Controller1.ButtonUp.pressing() << ","
      << Controller1.ButtonDown.pressing() << ","
      << Controller1.ButtonLeft.pressing() << ","
      << Controller1.ButtonRight.pressing() << ","
      << Controller1.ButtonL1.pressing() << ","
      << Controller1.ButtonL2.pressing() << ","
      << Controller1.ButtonR1.pressing() << ","
      << Controller1.ButtonR2.pressing();
}

void Controller1troller2Data() {
  ofs << "," << Controller1.Axis1.position() << "," << Controller1.Axis1.value()
      << "," << Controller1.Axis2.position() << "," << Controller1.Axis2.value()
      << "," << Controller1.Axis3.position() << "," << Controller1.Axis3.value()
      << "," << Controller1.Axis4.position() << "," << Controller1.Axis4.value()
      << "," << Controller1.ButtonA.pressing() << ","
      << Controller1.ButtonB.pressing() << "," << Controller1.ButtonX.pressing()
      << "," << Controller1.ButtonY.pressing() << ","
      << Controller1.ButtonUp.pressing() << ","
      << Controller1.ButtonDown.pressing() << ","
      << Controller1.ButtonLeft.pressing() << ","
      << Controller1.ButtonRight.pressing() << ","
      << Controller1.ButtonL1.pressing() << ","
      << Controller1.ButtonL2.pressing() << ","
      << Controller1.ButtonR1.pressing() << ","
      << Controller1.ButtonR2.pressing();
}

void MotorData(vex::motor& m) {
  ofs << "," << m.efficiency(vex::percentUnits::pct) << ","
      << m.velocity(vex::velocityUnits::rpm) << ","
      << m.velocity(vex::velocityUnits::dps) << ","
      << m.velocity(vex::velocityUnits::pct) << ","
      << m.rotation(vex::rotationUnits::deg) << ","
      << m.rotation(vex::rotationUnits::rev) << ","
      << m.rotation(vex::rotationUnits::raw) << ","
      << m.torque(vex::torqueUnits::Nm) << ","
      << m.torque(vex::torqueUnits::InLb) << ","
      << m.current(vex::currentUnits::amp) << ","
      << m.power(vex::powerUnits::watt) << ","
      << m.temperature(vex::temperatureUnits::fahrenheit) << ","
      << m.temperature(vex::percentUnits::pct);
}


void BatteryHeader2() { ofs << "capacity,temperature,"; }

void competitionHeader2() {
  ofs << "isAutonomous,isDriverController1trol,isCompetitionSwitch,"
         "isFieldController1trol,"
         "isEnabled,";
}

void Controller1trollerHeader2() {
  ofs << "Axis1 (position),Axis1 (value),Axis2 "
         "(position),Axis2 (value),Axis3 (position),Axis3 (value),Axis4 "
         "(position),Axis4 "
         "(value),ButtonA,ButtonB,ButtonX,ButtonY,ButtonUp,ButtonDown,"
         "ButtonLeft,ButtonRight,ButtonL1,ButtonL2,ButtonR1,ButtonR2,";
}

void MotorHeader2() {
  ofs << "efficiency "
         "(percent),velocity (rpm),velocity (degrees per second),velocity "
         "(percent),rotation (degrees),rotation (rev),rotation (raw),torque "
         "(Nm),torque (InLb),current (amp),power (watt),temperature "
         "(fahrenheit),temperature (percent),";
}

void BatteryHeader() { ofs << "Battery,,"; }
void competitionHeader() { ofs << "Competition,,,,,"; }
void Controller1troller1Header() {
  ofs << "Controller1troller1,,,,,,,,,,,,,,,,,,,,";
}
void Controller1troller2Header() {
  ofs << "Controller1troller2,,,,,,,,,,,,,,,,,,,,";
}
void mHeader() { ofs << "m,,,,,,,,,,,,,"; }
void Motor2Header() { ofs << "Motor2,,,,,,,,,,,,,"; }
void Motor3Header() { ofs << "Motor3,,,,,,,,,,,,,"; }
void Motor4Header() { ofs << "Motor4,,,,,,,,,,,,,"; }


void stopMotor() {
  m.stop();
  Motor2.stop();
  Motor3.stop();
  Motor4.stop();
  
}

void sensorHeader() {
  ofs << "time (msec),";
  BatteryHeader();
  // Controller1troller1Header();
  mHeader();
  Motor2Header();
  Motor3Header();
  Motor4Header();
  
  
  ofs << "\n";
  ofs << "senors,";
  BatteryHeader2();
  // Controller1trollerHeader2();
  for (int n = 20; n > 0; n--) {
    MotorHeader2();
  }
  ofs << "\n";
}

void sensorWriter() {

  ofs << Brain.timer(vex::timeUnits::msec) << ",";

  Batterydata();
  // competitionDate();
  // Controller1troller1Data();
  mData();
  Motor2Data();
  Motor3Data();
  Motor4Data();

  ofs << "\n";
}

bool fexists(const char *filename) {
  std::ifstream ifile(filename);
  return (bool)ifile;
}