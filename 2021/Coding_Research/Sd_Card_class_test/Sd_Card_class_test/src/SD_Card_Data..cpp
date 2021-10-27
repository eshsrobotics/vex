
#include "vex.h"
#include "robot-config.h"
using namespace vex;
//vex::competition Competition;
//std::ofstream ofs;

void drive() {
  Motor1.setVelocity(100, vex::velocityUnits::pct);
  Motor2.setVelocity(100, vex::velocityUnits::pct);
  Motor3.setVelocity(100, vex::velocityUnits::pct);
  Motor4.setVelocity(100, vex::velocityUnits::pct);
  Motor5.setVelocity(100, vex::velocityUnits::pct);
  Motor6.setVelocity(100, vex::velocityUnits::pct);
  Motor7.setVelocity(100, vex::velocityUnits::pct);
  Motor8.setVelocity(100, vex::velocityUnits::pct);
  Motor9.setVelocity(100, vex::velocityUnits::pct);
  Motor10.setVelocity(100, vex::velocityUnits::pct);
  Motor11.setVelocity(100, vex::velocityUnits::pct);
  Motor12.setVelocity(100, vex::velocityUnits::pct);
  Motor13.setVelocity(100, vex::velocityUnits::pct);
  Motor14.setVelocity(100, vex::velocityUnits::pct);
  Motor15.setVelocity(100, vex::velocityUnits::pct);
  Motor16.setVelocity(100, vex::velocityUnits::pct);
  Motor17.setVelocity(100, vex::velocityUnits::pct);
  Motor18.setVelocity(100, vex::velocityUnits::pct);
  Motor19.setVelocity(100, vex::velocityUnits::pct);
  Motor20.setVelocity(100, vex::velocityUnits::pct);

  Motor1.spin(vex::directionType::fwd);
  Motor2.spin(vex::directionType::fwd);
  Motor3.spin(vex::directionType::fwd);
  Motor4.spin(vex::directionType::fwd);
  Motor5.spin(vex::directionType::fwd);
  Motor6.spin(vex::directionType::fwd);
  Motor7.spin(vex::directionType::fwd);
  Motor8.spin(vex::directionType::fwd);
  Motor9.spin(vex::directionType::fwd);
  Motor10.spin(vex::directionType::fwd);
  Motor11.spin(vex::directionType::fwd);
  Motor12.spin(vex::directionType::fwd);
  Motor13.spin(vex::directionType::fwd);
  Motor14.spin(vex::directionType::fwd);
  Motor15.spin(vex::directionType::fwd);
  Motor16.spin(vex::directionType::fwd);
  Motor17.spin(vex::directionType::fwd);
  Motor18.spin(vex::directionType::fwd);
  Motor19.spin(vex::directionType::fwd);
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
void Motor1Data() {
  ofs << "," << Motor1.efficiency(vex::percentUnits::pct) << ","
      << Motor1.velocity(vex::velocityUnits::rpm) << ","
      << Motor1.velocity(vex::velocityUnits::dps) << ","
      << Motor1.velocity(vex::velocityUnits::pct) << ","
      << Motor1.rotation(vex::rotationUnits::deg) << ","
      << Motor1.rotation(vex::rotationUnits::rev) << ","
      << Motor1.rotation(vex::rotationUnits::raw) << ","
      << Motor1.torque(vex::torqueUnits::Nm) << ","
      << Motor1.torque(vex::torqueUnits::InLb) << ","
      << Motor1.current(vex::currentUnits::amp) << ","
      << Motor1.power(vex::powerUnits::watt) << ","
      << Motor1.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor1.temperature(vex::percentUnits::pct);
}

void Motor2Data() {
  ofs << "," << Motor2.efficiency(vex::percentUnits::pct) << ","
      << Motor2.velocity(vex::velocityUnits::rpm) << ","
      << Motor2.velocity(vex::velocityUnits::dps) << ","
      << Motor2.velocity(vex::velocityUnits::pct) << ","
      << Motor2.rotation(vex::rotationUnits::deg) << ","
      << Motor2.rotation(vex::rotationUnits::rev) << ","
      << Motor2.rotation(vex::rotationUnits::raw) << ","
      << Motor2.torque(vex::torqueUnits::Nm) << ","
      << Motor2.torque(vex::torqueUnits::InLb) << ","
      << Motor2.current(vex::currentUnits::amp) << ","
      << Motor2.power(vex::powerUnits::watt) << ","
      << Motor2.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor2.temperature(vex::percentUnits::pct);
}

void Motor3Data() {
  ofs << "," << Motor3.efficiency(vex::percentUnits::pct) << ","
      << Motor3.velocity(vex::velocityUnits::rpm) << ","
      << Motor3.velocity(vex::velocityUnits::dps) << ","
      << Motor3.velocity(vex::velocityUnits::pct) << ","
      << Motor3.rotation(vex::rotationUnits::deg) << ","
      << Motor3.rotation(vex::rotationUnits::rev) << ","
      << Motor3.rotation(vex::rotationUnits::raw) << ","
      << Motor3.torque(vex::torqueUnits::Nm) << ","
      << Motor3.torque(vex::torqueUnits::InLb) << ","
      << Motor3.current(vex::currentUnits::amp) << ","
      << Motor3.power(vex::powerUnits::watt) << ","
      << Motor3.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor3.temperature(vex::percentUnits::pct);
}

void Motor4Data() {
  ofs << "," << Motor4.efficiency(vex::percentUnits::pct) << ","
      << Motor4.velocity(vex::velocityUnits::rpm) << ","
      << Motor4.velocity(vex::velocityUnits::dps) << ","
      << Motor4.velocity(vex::velocityUnits::pct) << ","
      << Motor4.rotation(vex::rotationUnits::deg) << ","
      << Motor4.rotation(vex::rotationUnits::rev) << ","
      << Motor4.rotation(vex::rotationUnits::raw) << ","
      << Motor4.torque(vex::torqueUnits::Nm) << ","
      << Motor4.torque(vex::torqueUnits::InLb) << ","
      << Motor4.current(vex::currentUnits::amp) << ","
      << Motor4.power(vex::powerUnits::watt) << ","
      << Motor4.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor4.temperature(vex::percentUnits::pct);
}

void Motor5Data() {
  ofs << "," << Motor5.efficiency(vex::percentUnits::pct) << ","
      << Motor5.velocity(vex::velocityUnits::rpm) << ","
      << Motor5.velocity(vex::velocityUnits::dps) << ","
      << Motor5.velocity(vex::velocityUnits::pct) << ","
      << Motor5.rotation(vex::rotationUnits::deg) << ","
      << Motor5.rotation(vex::rotationUnits::rev) << ","
      << Motor5.rotation(vex::rotationUnits::raw) << ","
      << Motor5.torque(vex::torqueUnits::Nm) << ","
      << Motor5.torque(vex::torqueUnits::InLb) << ","
      << Motor5.current(vex::currentUnits::amp) << ","
      << Motor5.power(vex::powerUnits::watt) << ","
      << Motor5.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor5.temperature(vex::percentUnits::pct);
}

void Motor6Data() {
  ofs << "," << Motor6.efficiency(vex::percentUnits::pct) << ","
      << Motor6.velocity(vex::velocityUnits::rpm) << ","
      << Motor6.velocity(vex::velocityUnits::dps) << ","
      << Motor6.velocity(vex::velocityUnits::pct) << ","
      << Motor6.rotation(vex::rotationUnits::deg) << ","
      << Motor6.rotation(vex::rotationUnits::rev) << ","
      << Motor6.rotation(vex::rotationUnits::raw) << ","
      << Motor6.torque(vex::torqueUnits::Nm) << ","
      << Motor6.torque(vex::torqueUnits::InLb) << ","
      << Motor6.current(vex::currentUnits::amp) << ","
      << Motor6.power(vex::powerUnits::watt) << ","
      << Motor6.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor6.temperature(vex::percentUnits::pct);
}

void Motor7Data() {
  ofs << "," << Motor7.efficiency(vex::percentUnits::pct) << ","
      << Motor7.velocity(vex::velocityUnits::rpm) << ","
      << Motor7.velocity(vex::velocityUnits::dps) << ","
      << Motor7.velocity(vex::velocityUnits::pct) << ","
      << Motor7.rotation(vex::rotationUnits::deg) << ","
      << Motor7.rotation(vex::rotationUnits::rev) << ","
      << Motor7.rotation(vex::rotationUnits::raw) << ","
      << Motor7.torque(vex::torqueUnits::Nm) << ","
      << Motor7.torque(vex::torqueUnits::InLb) << ","
      << Motor7.current(vex::currentUnits::amp) << ","
      << Motor7.power(vex::powerUnits::watt) << ","
      << Motor7.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor7.temperature(vex::percentUnits::pct);
}

void Motor8Data() {
  ofs << "," << Motor8.efficiency(vex::percentUnits::pct) << ","
      << Motor8.velocity(vex::velocityUnits::rpm) << ","
      << Motor8.velocity(vex::velocityUnits::dps) << ","
      << Motor8.velocity(vex::velocityUnits::pct) << ","
      << Motor8.rotation(vex::rotationUnits::deg) << ","
      << Motor8.rotation(vex::rotationUnits::rev) << ","
      << Motor8.rotation(vex::rotationUnits::raw) << ","
      << Motor8.torque(vex::torqueUnits::Nm) << ","
      << Motor8.torque(vex::torqueUnits::InLb) << ","
      << Motor8.current(vex::currentUnits::amp) << ","
      << Motor8.power(vex::powerUnits::watt) << ","
      << Motor8.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor8.temperature(vex::percentUnits::pct);
}

void Motor9Data() {
  ofs << "," << Motor9.efficiency(vex::percentUnits::pct) << ","
      << Motor9.velocity(vex::velocityUnits::rpm) << ","
      << Motor9.velocity(vex::velocityUnits::dps) << ","
      << Motor9.velocity(vex::velocityUnits::pct) << ","
      << Motor9.rotation(vex::rotationUnits::deg) << ","
      << Motor9.rotation(vex::rotationUnits::rev) << ","
      << Motor9.rotation(vex::rotationUnits::raw) << ","
      << Motor9.torque(vex::torqueUnits::Nm) << ","
      << Motor9.torque(vex::torqueUnits::InLb) << ","
      << Motor9.current(vex::currentUnits::amp) << ","
      << Motor9.power(vex::powerUnits::watt) << ","
      << Motor9.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor9.temperature(vex::percentUnits::pct);
}

void Motor10Data() {
  ofs << "," << Motor10.efficiency(vex::percentUnits::pct) << ","
      << Motor10.velocity(vex::velocityUnits::rpm) << ","
      << Motor10.velocity(vex::velocityUnits::dps) << ","
      << Motor10.velocity(vex::velocityUnits::pct) << ","
      << Motor10.rotation(vex::rotationUnits::deg) << ","
      << Motor10.rotation(vex::rotationUnits::rev) << ","
      << Motor10.rotation(vex::rotationUnits::raw) << ","
      << Motor10.torque(vex::torqueUnits::Nm) << ","
      << Motor10.torque(vex::torqueUnits::InLb) << ","
      << Motor10.current(vex::currentUnits::amp) << ","
      << Motor10.power(vex::powerUnits::watt) << ","
      << Motor10.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor10.temperature(vex::percentUnits::pct);
}

void Motor11Data() {
  ofs << "," << Motor11.efficiency(vex::percentUnits::pct) << ","
      << Motor11.velocity(vex::velocityUnits::rpm) << ","
      << Motor11.velocity(vex::velocityUnits::dps) << ","
      << Motor11.velocity(vex::velocityUnits::pct) << ","
      << Motor11.rotation(vex::rotationUnits::deg) << ","
      << Motor11.rotation(vex::rotationUnits::rev) << ","
      << Motor11.rotation(vex::rotationUnits::raw) << ","
      << Motor11.torque(vex::torqueUnits::Nm) << ","
      << Motor11.torque(vex::torqueUnits::InLb) << ","
      << Motor11.current(vex::currentUnits::amp) << ","
      << Motor11.power(vex::powerUnits::watt) << ","
      << Motor11.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor11.temperature(vex::percentUnits::pct);
}

void Motor12Data() {
  ofs << "," << Motor12.efficiency(vex::percentUnits::pct) << ","
      << Motor12.velocity(vex::velocityUnits::rpm) << ","
      << Motor12.velocity(vex::velocityUnits::dps) << ","
      << Motor12.velocity(vex::velocityUnits::pct) << ","
      << Motor12.rotation(vex::rotationUnits::deg) << ","
      << Motor12.rotation(vex::rotationUnits::rev) << ","
      << Motor12.rotation(vex::rotationUnits::raw) << ","
      << Motor12.torque(vex::torqueUnits::Nm) << ","
      << Motor12.torque(vex::torqueUnits::InLb) << ","
      << Motor12.current(vex::currentUnits::amp) << ","
      << Motor12.power(vex::powerUnits::watt) << ","
      << Motor12.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor12.temperature(vex::percentUnits::pct);
}

void Motor13Data() {
  ofs << "," << Motor13.efficiency(vex::percentUnits::pct) << ","
      << Motor13.velocity(vex::velocityUnits::rpm) << ","
      << Motor13.velocity(vex::velocityUnits::dps) << ","
      << Motor13.velocity(vex::velocityUnits::pct) << ","
      << Motor13.rotation(vex::rotationUnits::deg) << ","
      << Motor13.rotation(vex::rotationUnits::rev) << ","
      << Motor13.rotation(vex::rotationUnits::raw) << ","
      << Motor13.torque(vex::torqueUnits::Nm) << ","
      << Motor13.torque(vex::torqueUnits::InLb) << ","
      << Motor13.current(vex::currentUnits::amp) << ","
      << Motor13.power(vex::powerUnits::watt) << ","
      << Motor13.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor13.temperature(vex::percentUnits::pct);
}

void Motor14Data() {
  ofs << "," << Motor14.efficiency(vex::percentUnits::pct) << ","
      << Motor14.velocity(vex::velocityUnits::rpm) << ","
      << Motor14.velocity(vex::velocityUnits::dps) << ","
      << Motor14.velocity(vex::velocityUnits::pct) << ","
      << Motor14.rotation(vex::rotationUnits::deg) << ","
      << Motor14.rotation(vex::rotationUnits::rev) << ","
      << Motor14.rotation(vex::rotationUnits::raw) << ","
      << Motor14.torque(vex::torqueUnits::Nm) << ","
      << Motor14.torque(vex::torqueUnits::InLb) << ","
      << Motor14.current(vex::currentUnits::amp) << ","
      << Motor14.power(vex::powerUnits::watt) << ","
      << Motor14.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor14.temperature(vex::percentUnits::pct);
}

void Motor15Data() {
  ofs << "," << Motor15.efficiency(vex::percentUnits::pct) << ","
      << Motor15.velocity(vex::velocityUnits::rpm) << ","
      << Motor15.velocity(vex::velocityUnits::dps) << ","
      << Motor15.velocity(vex::velocityUnits::pct) << ","
      << Motor15.rotation(vex::rotationUnits::deg) << ","
      << Motor15.rotation(vex::rotationUnits::rev) << ","
      << Motor15.rotation(vex::rotationUnits::raw) << ","
      << Motor15.torque(vex::torqueUnits::Nm) << ","
      << Motor15.torque(vex::torqueUnits::InLb) << ","
      << Motor15.current(vex::currentUnits::amp) << ","
      << Motor15.power(vex::powerUnits::watt) << ","
      << Motor15.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor15.temperature(vex::percentUnits::pct);
}

void Motor16Data() {
  ofs << "," << Motor16.efficiency(vex::percentUnits::pct) << ","
      << Motor16.velocity(vex::velocityUnits::rpm) << ","
      << Motor16.velocity(vex::velocityUnits::dps) << ","
      << Motor16.velocity(vex::velocityUnits::pct) << ","
      << Motor16.rotation(vex::rotationUnits::deg) << ","
      << Motor16.rotation(vex::rotationUnits::rev) << ","
      << Motor16.rotation(vex::rotationUnits::raw) << ","
      << Motor16.torque(vex::torqueUnits::Nm) << ","
      << Motor16.torque(vex::torqueUnits::InLb) << ","
      << Motor16.current(vex::currentUnits::amp) << ","
      << Motor16.power(vex::powerUnits::watt) << ","
      << Motor16.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor16.temperature(vex::percentUnits::pct);
}

void Motor17Data() {
  ofs << "," << Motor17.efficiency(vex::percentUnits::pct) << ","
      << Motor17.velocity(vex::velocityUnits::rpm) << ","
      << Motor17.velocity(vex::velocityUnits::dps) << ","
      << Motor17.velocity(vex::velocityUnits::pct) << ","
      << Motor17.rotation(vex::rotationUnits::deg) << ","
      << Motor17.rotation(vex::rotationUnits::rev) << ","
      << Motor17.rotation(vex::rotationUnits::raw) << ","
      << Motor17.torque(vex::torqueUnits::Nm) << ","
      << Motor17.torque(vex::torqueUnits::InLb) << ","
      << Motor17.current(vex::currentUnits::amp) << ","
      << Motor17.power(vex::powerUnits::watt) << ","
      << Motor17.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor17.temperature(vex::percentUnits::pct);
}

void Motor18Data() {
  ofs << "," << Motor18.efficiency(vex::percentUnits::pct) << ","
      << Motor18.velocity(vex::velocityUnits::rpm) << ","
      << Motor18.velocity(vex::velocityUnits::dps) << ","
      << Motor18.velocity(vex::velocityUnits::pct) << ","
      << Motor18.rotation(vex::rotationUnits::deg) << ","
      << Motor18.rotation(vex::rotationUnits::rev) << ","
      << Motor18.rotation(vex::rotationUnits::raw) << ","
      << Motor18.torque(vex::torqueUnits::Nm) << ","
      << Motor18.torque(vex::torqueUnits::InLb) << ","
      << Motor18.current(vex::currentUnits::amp) << ","
      << Motor18.power(vex::powerUnits::watt) << ","
      << Motor18.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor18.temperature(vex::percentUnits::pct);
}

void Motor19Data() {
  ofs << "," << Motor19.efficiency(vex::percentUnits::pct) << ","
      << Motor19.velocity(vex::velocityUnits::rpm) << ","
      << Motor19.velocity(vex::velocityUnits::dps) << ","
      << Motor19.velocity(vex::velocityUnits::pct) << ","
      << Motor19.rotation(vex::rotationUnits::deg) << ","
      << Motor19.rotation(vex::rotationUnits::rev) << ","
      << Motor19.rotation(vex::rotationUnits::raw) << ","
      << Motor19.torque(vex::torqueUnits::Nm) << ","
      << Motor19.torque(vex::torqueUnits::InLb) << ","
      << Motor19.current(vex::currentUnits::amp) << ","
      << Motor19.power(vex::powerUnits::watt) << ","
      << Motor19.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor19.temperature(vex::percentUnits::pct);
}

void Motor20Data() {
  ofs << "," << Motor20.efficiency(vex::percentUnits::pct) << ","
      << Motor20.velocity(vex::velocityUnits::rpm) << ","
      << Motor20.velocity(vex::velocityUnits::dps) << ","
      << Motor20.velocity(vex::velocityUnits::pct) << ","
      << Motor20.rotation(vex::rotationUnits::deg) << ","
      << Motor20.rotation(vex::rotationUnits::rev) << ","
      << Motor20.rotation(vex::rotationUnits::raw) << ","
      << Motor20.torque(vex::torqueUnits::Nm) << ","
      << Motor20.torque(vex::torqueUnits::InLb) << ","
      << Motor20.current(vex::currentUnits::amp) << ","
      << Motor20.power(vex::powerUnits::watt) << ","
      << Motor20.temperature(vex::temperatureUnits::fahrenheit) << ","
      << Motor20.temperature(vex::percentUnits::pct);
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
void Motor1Header() { ofs << "Motor1,,,,,,,,,,,,,"; }
void Motor2Header() { ofs << "Motor2,,,,,,,,,,,,,"; }
void Motor3Header() { ofs << "Motor3,,,,,,,,,,,,,"; }
void Motor4Header() { ofs << "Motor4,,,,,,,,,,,,,"; }
void Motor5Header() { ofs << "Motor5,,,,,,,,,,,,,"; }
void Motor6Header() { ofs << "Motor6,,,,,,,,,,,,,"; }
void Motor7Header() { ofs << "Motor7,,,,,,,,,,,,,"; }
void Motor8Header() { ofs << "Motor8,,,,,,,,,,,,,"; }
void Motor9Header() { ofs << "Motor9,,,,,,,,,,,,,"; }
void Motor10Header() { ofs << "Motor10,,,,,,,,,,,,,"; }
void Motor11Header() { ofs << "Motor11,,,,,,,,,,,,,"; }
void Motor12Header() { ofs << "Motor12,,,,,,,,,,,,,"; }
void Motor13Header() { ofs << "Motor13,,,,,,,,,,,,,"; }
void Motor14Header() { ofs << "Motor14,,,,,,,,,,,,,"; }
void Motor15Header() { ofs << "Motor15,,,,,,,,,,,,,"; }
void Motor16Header() { ofs << "Motor16,,,,,,,,,,,,,"; }
void Motor17Header() { ofs << "Motor17,,,,,,,,,,,,,"; }
void Motor18Header() { ofs << "Motor18,,,,,,,,,,,,,"; }
void Motor19Header() { ofs << "Motor19,,,,,,,,,,,,,"; }
void Motor20Header() { ofs << "Motor20,,,,,,,,,,,,,"; }

void stopMotor() {
  Motor1.stop();
  Motor2.stop();
  Motor3.stop();
  Motor4.stop();
  Motor5.stop();
  Motor6.stop();
  Motor7.stop();
  Motor8.stop();
  Motor9.stop();
  Motor10.stop();
  Motor11.stop();
  Motor12.stop();
  Motor13.stop();
  Motor14.stop();
  Motor15.stop();
  Motor16.stop();
  Motor17.stop();
  Motor18.stop();
  Motor19.stop();
  Motor20.stop();
}

void sensorHeader() {
  ofs << "time (msec),";
  BatteryHeader();
  // Controller1troller1Header();
  Motor1Header();
  Motor2Header();
  Motor3Header();
  Motor4Header();
  Motor5Header();
  Motor6Header();
  Motor7Header();
  Motor8Header();
  Motor9Header();
  Motor10Header();
  Motor11Header();
  Motor12Header();
  Motor13Header();
  Motor14Header();
  Motor15Header();
  Motor16Header();
  Motor17Header();
  Motor18Header();
  Motor19Header();
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
  Motor1Data();
  Motor2Data();
  Motor3Data();
  Motor4Data();
  Motor5Data();
  Motor6Data();
  Motor7Data();
  Motor8Data();
  Motor9Data();
  Motor10Data();
  Motor11Data();
  Motor12Data();
  Motor13Data();
  Motor14Data();
  Motor15Data();
  Motor16Data();
  Motor17Data();
  Motor18Data();
  Motor19Data();
  Motor20Data();

  ofs << "\n";
}

bool fexists(const char *filename) {
  std::ifstream ifile(filename);
  return (bool)ifile;
}