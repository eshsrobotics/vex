
#include "vex.h"
#include "robot-config.h"
using namespace vex;
vex::competition Competition;
std::ofstream ofs;

void drive() {
  m.setVelocity(100, vex::velocityUnits::pct);
  Motor2.setVelocity(100, vex::velocityUnits::pct);
  Motor3.setVelocity(100, vex::velocityUnits::pct);
  Motor4.setVelocity(100, vex::velocityUnits::pct);
  Motor5.setVelocity(100, vex::velocityUnits::pct);
  Motor6.setVelocity(100, vex::velocityUnits::pct);
  Motor7.setVelocity(100, vex::velocityUnits::pct);
  Motor8.setVelocity(100, vex::velocityUnits::pct);
  Motor9.setVelocity(100, vex::velocityUnits::pct);
  m0.setVelocity(100, vex::velocityUnits::pct);
  m1.setVelocity(100, vex::velocityUnits::pct);
  m2.setVelocity(100, vex::velocityUnits::pct);
  m3.setVelocity(100, vex::velocityUnits::pct);
  m4.setVelocity(100, vex::velocityUnits::pct);
  m5.setVelocity(100, vex::velocityUnits::pct);
  m6.setVelocity(100, vex::velocityUnits::pct);
  m7.setVelocity(100, vex::velocityUnits::pct);
  m8.setVelocity(100, vex::velocityUnits::pct);
  m9.setVelocity(100, vex::velocityUnits::pct);
  Motor20.setVelocity(100, vex::velocityUnits::pct);

  m.spin(vex::directionType::fwd);
  Motor2.spin(vex::directionType::fwd);
  Motor3.spin(vex::directionType::fwd);
  Motor4.spin(vex::directionType::fwd);
  Motor5.spin(vex::directionType::fwd);
  Motor6.spin(vex::directionType::fwd);
  Motor7.spin(vex::directionType::fwd);
  Motor8.spin(vex::directionType::fwd);
  Motor9.spin(vex::directionType::fwd);
  m0.spin(vex::directionType::fwd);
  m1.spin(vex::directionType::fwd);
  m2.spin(vex::directionType::fwd);
  m3.spin(vex::directionType::fwd);
  m4.spin(vex::directionType::fwd);
  m5.spin(vex::directionType::fwd);
  m6.spin(vex::directionType::fwd);
  m7.spin(vex::directionType::fwd);
  m8.spin(vex::directionType::fwd);
  m9.spin(vex::directionType::fwd);
  Motor20.spin(vex::directionType::fwd);
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
void Motor5Header() { ofs << "Motor5,,,,,,,,,,,,,"; }
void Motor6Header() { ofs << "Motor6,,,,,,,,,,,,,"; }
void Motor7Header() { ofs << "Motor7,,,,,,,,,,,,,"; }
void Motor8Header() { ofs << "Motor8,,,,,,,,,,,,,"; }
void Motor9Header() { ofs << "Motor9,,,,,,,,,,,,,"; }
void m0Header() { ofs << "m0,,,,,,,,,,,,,"; }
void m1Header() { ofs << "m1,,,,,,,,,,,,,"; }
void m2Header() { ofs << "m2,,,,,,,,,,,,,"; }
void m3Header() { ofs << "m3,,,,,,,,,,,,,"; }
void m4Header() { ofs << "m4,,,,,,,,,,,,,"; }
void m5Header() { ofs << "m5,,,,,,,,,,,,,"; }
void m6Header() { ofs << "m6,,,,,,,,,,,,,"; }
void m7Header() { ofs << "m7,,,,,,,,,,,,,"; }
void m8Header() { ofs << "m8,,,,,,,,,,,,,"; }
void m9Header() { ofs << "m9,,,,,,,,,,,,,"; }
void Motor20Header() { ofs << "Motor20,,,,,,,,,,,,,"; }

void stopMotor() {
  m.stop();
  Motor2.stop();
  Motor3.stop();
  Motor4.stop();
  Motor5.stop();
  Motor6.stop();
  Motor7.stop();
  Motor8.stop();
  Motor9.stop();
  m0.stop();
  m1.stop();
  m2.stop();
  m3.stop();
  m4.stop();
  m5.stop();
  m6.stop();
  m7.stop();
  m8.stop();
  m9.stop();
  Motor20.stop();
}

void sensorHeader() {
  ofs << "time (msec),";
  BatteryHeader();
  // Controller1troller1Header();
  mHeader();
  Motor2Header();
  Motor3Header();
  Motor4Header();
  Motor5Header();
  Motor6Header();
  Motor7Header();
  Motor8Header();
  Motor9Header();
  m0Header();
  m1Header();
  m2Header();
  m3Header();
  m4Header();
  m5Header();
  m6Header();
  m7Header();
  m8Header();
  m9Header();
  Motor20Header();
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
  Motor5Data();
  Motor6Data();
  Motor7Data();
  Motor8Data();
  Motor9Data();
  m0Data();
  m1Data();
  m2Data();
  m3Data();
  m4Data();
  m5Data();
  m6Data();
  m7Data();
  m8Data();
  m9Data();
  Motor20Data();

  ofs << "\n";
}

bool fexists(const char *filename) {
  std::ifstream ifile(filename);
  return (bool)ifile;
}