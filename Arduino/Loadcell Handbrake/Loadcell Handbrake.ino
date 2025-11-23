#include <Joystick.h>

#include <HX711.h>

#include <DynamicHID.h>

#include <Joystick.h>

#include <HX711.h>

#include <DynamicHID.h>

#include <DynamicHID.h>

#include <Arduino_BuiltIn.h>

#include <HX711.h>
#include <Joystick.h>
#define calibration_factor 5000 // Loadcell: change this value to increase or decrease the range of the loadcell
#define DOUT  3
#define CLK  2
HX711 scale;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 
0, 0,                 // Button Count, Hat Switch Count
false, false, false,  // X, Y, Z
false, true, false,     // Rx , Ry, Rz
false, false,         // Rudder, throttle
false, false, false); // Accelerator, brake, steering

int LC = 0;
int lastLCValue = 0;

void setup() {
  Joystick.setRyAxisRange(0, 1023);
  
  Joystick.begin();
  Serial.begin(38400);
 
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor);
  scale.tare();
}

void loop() {
// Loadcell
Serial.println (LC);
LC = scale.get_units(); // If the value is inverted put - sign in front like -scale.get
  if (LC < 0 or LC < 1) {
    LC = 0;
  }
  if (lastLCValue != LC) {
    Joystick.setRyAxis(LC);
    lastLCValue = LC;
  }
  
} // End loop
