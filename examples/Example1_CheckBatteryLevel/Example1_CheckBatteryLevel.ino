/*
  Reading the BQ40Z50 battery manager
  By: Nathan Seidle
  SparkFun Electronics
  Date: February 5th, 2024
  License: MIT. Please see LICENSE.md for more information.

  This example shows how to check the current battery level of the BQ40Z50 battery manager.

  These examples are written for the ESP32 but can be modified easily to be 
  used with any microcontroller that supports I2C.
*/

#include "SparkFun_BQ40Z50_Battery_Manager_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_BQ40Z50

#include <Wire.h>

BQ40Z50 myBattery;

int pin_SDA = 15;
int pin_SCL = 4;

void setup()
{
  Serial.begin(115200);
  delay(250);
  Serial.println();
  Serial.println("BQ40Z50 Battery Manager");

  Wire.begin(pin_SDA, pin_SCL);

  if (myBattery.begin() == false)
  {
    Serial.println("BQ40Z50 not detected. Freezing...");
    while (true);
  }
  Serial.println("BQ40Z50 detected!");
}

void loop()
{
  // As batteries age, they lose capacity. The BQ40Z50 learns the current pack capacity.
  // The Relative State of Charge will always be 0 to 100% and uses the current pack capacity.
  uint8_t relativeStateOfCharge = myBattery.getRelativeStateOfCharge();
  Serial.printf("Relative state of charge: %d%%\r\n", relativeStateOfCharge);

  // The Absolute State of Charge reports 0 to 100% but will never be 100% because it
  // is based on the initial manufactured capacity.
  uint8_t absoluteStateOfCharge = myBattery.getAbsoluteStateOfCharge();
  Serial.printf("Absolute state of charge: %d%%\r\n", absoluteStateOfCharge);

  if (Serial.available()) ESP.restart();

  delay(1000);
}
