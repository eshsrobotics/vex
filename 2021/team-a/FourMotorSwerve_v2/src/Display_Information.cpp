#include "Display_Information.h"
#include "vex.h"

using namespace vex;
using namespace std;

namespace {
// Converts a long name like "Left_Motor1" to a short name like "LM1".
//
// Rules:
// - The first alphanumeric character becomes the first character.
// - The first capital letter, or the first alphanumeric character that proceeds
// any
//   non-alphanumeric character is added to the list.
// - Intermediate alphanumeric characters that don't pertain to the above
//   two rules are ignored.
//
// @param s     The long name string to consider.
// @param limit The maximum number of characters in the result; 0 means
//              unlimited.
std::string makeShortName(const std::string &s, int limit = 0) {
  using std::string;
  string output = "";
  char prev = '\0';
  for (char c : s) {
    if (prev == '\0' ||                          // Adding 1st char
        !isalpha(prev) ||                        // First char after nonalphanumeric
        (!isalpha(c) && c != '_' && c != ' ') || // Most special characters are pass-through
        (!isupper(prev) && isupper(c))) {        // Handles CamelCase
      output += toupper(c);
    }
    prev = c;
  }

  if (limit <= 0) {                                     // "FOOBAR", 0 -> "FOOBAR"
    return output;
  } else if (output.size() < limit) {
    return output + string(limit - output.size(), ' '); // "LM", 3 -> "LM "
  } else {
    return output.substr(0, limit);                     // "CASE", 3 -> "CAS"
  }
}
} // end (unnamed namespace)


void Motor_Display::Add_Motor(std::string motor_name, vex::motor *motor) {
  _motors[motor_name] = motor;
}
void Motor_Display::Add_Drivetrain_Motor(std::string motor_name,
                                         vex::motor *motor) {
  _drivetrain_motors[motor_name] = motor;
}

void Motor_Display::Drivetrain_Efficiency_ControllerDisplay() {

  /* the display on the Contoller should look like this:

          Drv. Efficiency
          FLM 000 FRM 000
          RLM 000 RRM 000

  */

  map<string, motor*> all_motors;
  all_motors.insert(_drivetrain_motors.begin(), _drivetrain_motors.end());
  all_motors.insert(_motors.begin(), _motors.end());

  Controller1.Screen.print("Drv. Efficiency");
  Controller1.Screen.newLine();

  // Switch which set of motors we display every few seconds.
  static unsigned int start = 0;
  static int lastDisplayTimeMilliseconds = 0;
  const SWITCH_TIME_MILLISECONDS = 3000;
  if (Brain.timer(msec) - lastDisplayTimeMilliseconds >= SWITCH_TIME_MILLISECONDS) {
    lastDisplayTimeMilliseconds = Brain.timer(msec);
    start += 2; // Next line.
    // Wrap around so we're displaying all the motors, four at a time, until we
    // get to every one of them.
    if (start > all_motors.size() - 4) {
      start = 0;
    }
  }

  unsigned int i = 0;
  for (auto iter = all_motors.begin();
       iter != all_motors.end();
       ++iter, ++i) {
    if (i < start) {
      continue;
    }
    if (i >= start + 4) {
      break;
    }
    Controller1.Screen.print(makeShortName(iter->first, 3) + ": ");
    Controller1.Screen.print(iter->second->efficiency());
    if (i % 2 == 1) {
      Controller1.Screen.newLine();
    } else {
      Controller1.Screen.print(" ");
    }
  }
}

void clearAllScreens() {
  Brain.Screen.clearScreen();
  Controller1.Screen.clearScreen();
}

void temperatureColour(double temperatureReading) {
  if (temperatureReading >= 90) {
    Brain.Screen.setPenColor(red);
  } else if (temperatureReading < 90 && temperatureReading >= 80) {
    Brain.Screen.setPenColor(yellow);
  } else {
    Brain.Screen.setPenColor(green);
  }
}

void temperatureBrainDisplay() {
  // Prints the Drivetrain temperature

  /* the display on the brain should look like this:

                     Drivetrain temperatures
           FrontLeftMotor 000°F FrontRightMotor 000°F
           RearLeftMotor  000°F RearRightMotor  000°F
                       ArmMotor temperature
             ArmMotorLeft 000°F ArmMotorRight   000°F
                      LiftMotor temperatures
            LeftLiftMotor 000°F RightLiftMotor  000°F
  */
  Brain.Screen.setPenColor(white);
  Brain.Screen.print("Drivetrain temperatures: ");

  Brain.Screen.print("FrontLeftMotor: ");
  temperatureColour(FrontLeftMotor.temperature(fahrenheit));
  Brain.Screen.print(FrontLeftMotor.temperature(fahrenheit));
  Brain.Screen.setPenColor(white);

  Brain.Screen.print("FrontRightMotor: ");
  temperatureColour(FrontRightMotor.temperature(fahrenheit));
  Brain.Screen.print(FrontRightMotor.temperature(fahrenheit));
  Brain.Screen.newLine();

  Brain.Screen.setPenColor(white);
  Brain.Screen.print(" RearRightMotor: ");
  temperatureColour(RearLeftMotor.temperature(fahrenheit));
  Brain.Screen.print(RearLeftMotor.temperature(fahrenheit));

  Brain.Screen.setPenColor(white);
  Brain.Screen.print(" RearLeftMotor: ");
  temperatureColour(RearRightMotor.temperature(fahrenheit));
  Brain.Screen.print(RearRightMotor.temperature(fahrenheit));
  Brain.Screen.newLine();

  Brain.Screen.setPenColor(white);
  Brain.Screen.print("ArmMotor temperatures: ");

  // Prints the ArmMotor temperature.
  Brain.Screen.print("ArmMotorLeft: ");
  temperatureColour(ArmMotorLeft.temperature(fahrenheit));
  Brain.Screen.print((ArmMotorLeft.temperature(fahrenheit)));
  Brain.Screen.setPenColor(white);

  Brain.Screen.print(" ArmMotorRight: ");
  temperatureColour(ArmMotorRight.temperature(fahrenheit));
  Brain.Screen.print((ArmMotorRight.temperature(fahrenheit)));
  Brain.Screen.setPenColor(white);
  Brain.Screen.newLine();

  Brain.Screen.print("LiftMotor temperatures: ");
  Brain.Screen.newLine();

  // Prints the LeftLiftMotor temperature.
  Brain.Screen.print("LeftLiftMotor: ");
  temperatureColour(LeftLiftMotor.temperature(fahrenheit));
  Brain.Screen.print((LeftLiftMotor.temperature(fahrenheit)));
  Brain.Screen.setPenColor(white);

  // Prints the RightLiftMotor temperature.
  Brain.Screen.print(" RightLiftMotor: ");
  temperatureColour(RightLiftMotor.temperature(fahrenheit));
  Brain.Screen.print((RightLiftMotor.temperature(fahrenheit)));
  Brain.Screen.setPenColor(white);
  Brain.Screen.newLine();
}

void Drivetrain_Efficiency_ControllerDisplay() {
  /* the display on the Contoller should look like this:

          Drive Efficiency
          FLM 000 FRM 000
          RLM 000 RRM 000

  */

  Controller1.Screen.print("Drive Efficiency");
  Controller1.Screen.newLine();

  Controller1.Screen.print("FLM: ");
  Controller1.Screen.print(FrontLeftMotor.efficiency());

  Controller1.Screen.print("FRM: ");
  Controller1.Screen.print(FrontRightMotor.efficiency());
  Controller1.Screen.newLine();

  Controller1.Screen.print(" RLM: ");
  Controller1.Screen.print(RearLeftMotor.efficiency());

  Controller1.Screen.print(" RRM: ");
  Controller1.Screen.print(RearRightMotor.efficiency());
}

void Drivetrain_Rotation_ControllerDisplay_Degrees() {
  /* the display on the Contoller should look like this:

           Drive Degrees
          FLM 000 FRM 000
          RLM 000 RRM 000

  */

  Controller1.Screen.print(" Drive Degrees");
  Controller1.Screen.newLine();

  Controller1.Screen.print("FLM: ");
  Controller1.Screen.print(FrontLeftMotor.rotation(deg));

  Controller1.Screen.print("FRM: ");
  Controller1.Screen.print(FrontRightMotor.rotation(deg));
  Controller1.Screen.newLine();

  Controller1.Screen.print(" RLM: ");
  Controller1.Screen.print(RearLeftMotor.rotation(deg));

  Controller1.Screen.print(" RRM: ");
  Controller1.Screen.print(RearRightMotor.rotation(deg));
}

void Drivetrain_Rotation_ControllerDisplay_Revolutions() {
  /* the display on the Contoller should look like this:

             Drive Rev
          FLM 000 FRM 000
          RLM 000 RRM 000

  */

  Controller1.Screen.print("   Drive Rev");
  Controller1.Screen.newLine();

  Controller1.Screen.print("FLM: ");
  Controller1.Screen.print(FrontLeftMotor.rotation(rev));

  Controller1.Screen.print("FRM: ");
  Controller1.Screen.print(FrontRightMotor.rotation(rev));
  Controller1.Screen.newLine();

  Controller1.Screen.print(" RLM: ");
  Controller1.Screen.print(RearLeftMotor.rotation(rev));

  Controller1.Screen.print(" RRM: ");
  Controller1.Screen.print(RearRightMotor.rotation(rev));
}

void Drivetrain_Torque_ControllerDisplay_InchPounds() {
  /* the display on the Contoller should look like this:

             Drive InLb
          FLM 000 FRM 000
          RLM 000 RRM 000

  */

  Controller1.Screen.print("  Drive InLb");
  Controller1.Screen.newLine();

  Controller1.Screen.print("FLM: ");
  Controller1.Screen.print(FrontLeftMotor.torque(InLb));

  Controller1.Screen.print("FRM: ");
  Controller1.Screen.print(FrontRightMotor.torque(InLb));
  Controller1.Screen.newLine();

  Controller1.Screen.print(" RLM: ");
  Controller1.Screen.print(RearLeftMotor.torque(InLb));

  Controller1.Screen.print(" RRM: ");
  Controller1.Screen.print(RearRightMotor.torque(InLb));
}

void Drivetrain_Torque_ControllerDisplay_NewtonMeters() {
  /* the display on the Contoller should look like this:

          Drive Torque Nm
          FLM 000 FRM 000
          RLM 000 RRM 000

  */

  Controller1.Screen.print("Drive Torque Nm");
  Controller1.Screen.newLine();

  Controller1.Screen.print("FLM: ");
  Controller1.Screen.print(FrontLeftMotor.torque(Nm));

  Controller1.Screen.print("FRM: ");
  Controller1.Screen.print(FrontRightMotor.torque(Nm));
  Controller1.Screen.newLine();

  Controller1.Screen.print(" RLM: ");
  Controller1.Screen.print(RearLeftMotor.torque(Nm));

  Controller1.Screen.print(" RRM: ");
  Controller1.Screen.print(RearRightMotor.torque(Nm));
}

void Drivetrain_Current_ControllerDisplay() {
  /* the display on the Contoller should look like this:

            Drive Current
           FLM 000 FRM 000
           RLM 000 RRM 000

  */

  Controller1.Screen.print(" Drive Current");
  Controller1.Screen.newLine();

  Controller1.Screen.print("FLM: ");
  Controller1.Screen.print(FrontLeftMotor.current());

  Controller1.Screen.print("FRM: ");
  Controller1.Screen.print(FrontRightMotor.current());
  Controller1.Screen.newLine();

  Controller1.Screen.print(" RLM: ");
  Controller1.Screen.print(RearLeftMotor.current());

  Controller1.Screen.print(" RRM: ");
  Controller1.Screen.print(RearRightMotor.current());
}

void Drivetrain_Power_ControllerDisplay() {
  /* the display on the Contoller should look like this:

                 Drive Watts
               FLM 000 FRM 000
               RLM 000 RRM 000

   */

  Controller1.Screen.print("  Drive Watts");
  Controller1.Screen.newLine();

  Controller1.Screen.print("FLM: ");
  Controller1.Screen.print(FrontLeftMotor.power());

  Controller1.Screen.print("FRM: ");
  Controller1.Screen.print(FrontRightMotor.power());
  Controller1.Screen.newLine();

  Controller1.Screen.print(" RLM: ");
  Controller1.Screen.print(RearLeftMotor.power());

  Controller1.Screen.print(" RRM: ");
  Controller1.Screen.print(RearRightMotor.power());
}

void Drivetrain_Voltage_ControllerDisplay_Volts() {
  /* the display on the Contoller should look like this:

               Drive Voltage
              FLM 000 FRM 000
              RLM 000 RRM 000

  */

  Controller1.Screen.print(" Drive Voltage ");
  Controller1.Screen.newLine();

  Controller1.Screen.print("FLM: ");
  Controller1.Screen.print(FrontLeftMotor.voltage());

  Controller1.Screen.print("FRM: ");
  Controller1.Screen.print(FrontRightMotor.voltage());
  Controller1.Screen.newLine();

  Controller1.Screen.print(" RLM: ");
  Controller1.Screen.print(RearLeftMotor.voltage());

  Controller1.Screen.print(" RRM: ");
  Controller1.Screen.print(RearRightMotor.voltage());
}

void Drivetrain_Temperature_ControllerDisplay_Celsius() {
  /* the display on the Contoller should look like this:

               Drive Temp °C
              FLM 000 FRM 000
              RLM 000 RRM 000

  */

  Controller1.Screen.print(" Drive Temp °C");
  Controller1.Screen.newLine();

  Controller1.Screen.print("FLM: ");
  Controller1.Screen.print(FrontLeftMotor.temperature(celsius));

  Controller1.Screen.print("FRM: ");
  Controller1.Screen.print(FrontRightMotor.temperature(celsius));
  Controller1.Screen.newLine();

  Controller1.Screen.print(" RLM: ");
  Controller1.Screen.print(RearLeftMotor.temperature(celsius));

  Controller1.Screen.print(" RRM: ");
  Controller1.Screen.print(RearRightMotor.temperature(celsius));
}

void Drivetrain_Temperature_ControllerDisplay_Fahrenheit() {
  /* the display on the Contoller should look like this:

               Drive Temp °F
              FLM 000 FRM 000
              RLM 000 RRM 000

  */

  Controller1.Screen.print(" Drive Temp °F");
  Controller1.Screen.newLine();

  Controller1.Screen.print("FLM: ");
  Controller1.Screen.print(FrontLeftMotor.temperature(fahrenheit));

  Controller1.Screen.print("FRM: ");
  Controller1.Screen.print(FrontRightMotor.temperature(fahrenheit));
  Controller1.Screen.newLine();

  Controller1.Screen.print(" RLM: ");
  Controller1.Screen.print(RearLeftMotor.temperature(fahrenheit));

  Controller1.Screen.print(" RRM: ");
  Controller1.Screen.print(RearRightMotor.temperature(fahrenheit));
}

void Drivetrain_Temperature_ControllerDisplay_Percentage() {
  /* the display on the Contoller should look like this:

               Drive Temp %
              FLM 000 FRM 000
              RLM 000 RRM 000

  */

  Controller1.Screen.print(" Drive Temp %");
  Controller1.Screen.newLine();

  Controller1.Screen.print("FLM: ");
  Controller1.Screen.print(FrontLeftMotor.temperature(percent));

  Controller1.Screen.print("FRM: ");
  Controller1.Screen.print(FrontRightMotor.temperature(percent));
  Controller1.Screen.newLine();

  Controller1.Screen.print(" RLM: ");
  Controller1.Screen.print(RearLeftMotor.temperature(percent));

  Controller1.Screen.print(" RRM: ");
  Controller1.Screen.print(RearRightMotor.temperature(percent));
}

void Othermotors_Efficiency_ControllerDisplay() {}

void Othermotors_Rotation_ControllerDisplay_Degrees() {}

void Othermotors_Rotation_ControllerDisplay_Revolutions() {}

void Othermotors_Rotation_ControllerDisplay_Rawdata() {}

void Othermotors_Torque_ControllerDisplay_InchPounds() {}

void Othermotors_Torque_ControllerDisplay_NewtonMeters() {}

void Othermotors_Current_ControllerDisplay() {}

void Othermotors_Power_ControllerDisplay() {}

void Othermotors_Voltage_ControllerDisplay_Volts() {}

void Othermotors_Temperature_ControllerDisplay_Celsius() {}

void Othermotors_Temperature_ControllerDisplay_Fahrenheit() {}

void Othermotors_Temperature_ControllerDisplay_Percentage() {}
