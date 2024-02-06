/*
  Reading the BQ40Z50 battery manager
  By: Nathan Seidle
  SparkFun Electronics
  Date: February 5th, 2024
  License: MIT. Please see LICENSE.md for more information.

  This example demonstrates all the available functions (ie, the kitchen sink).

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

  Serial.println();

  float temperatureF = myBattery.getTemperatureF();
  Serial.printf("Pack temperature: %0.1fF\r\n", temperatureF);

  float packVoltage = myBattery.getVoltageMv() / 1000.0;
  Serial.printf("Pack voltage: %0.2f\r\n", packVoltage);

  int16_t currentMa = myBattery.getCurrentMa();
  Serial.printf("Instantaneous Current: %dmA\r\n", currentMa);

  int16_t averageCurrentMa = myBattery.getAverageCurrentMa();
  Serial.printf("Average Current: %dmA\r\n", averageCurrentMa);

  uint8_t maxError = myBattery.getMaxError();
  Serial.printf("Max Error: %d%%\r\n", maxError);

  // As batteries age, they lose capacity. The BQ40Z50 learns the current pack capacity.
  // The Relative State of Charge will always be 0 to 100% and uses the current pack capacity.
  uint8_t relativeStateOfCharge = myBattery.getRelativeStateOfCharge();
  Serial.printf("Relative state of charge: %d%%\r\n", relativeStateOfCharge);

  // The Absolute State of Charge reports 0 to 100% but will never be 100% because it
  // is based on the initial manufactured capacity.
  uint8_t absoluteStateOfCharge = myBattery.getAbsoluteStateOfCharge();
  Serial.printf("Absolute state of charge: %d%%\r\n", absoluteStateOfCharge);

  uint16_t remainingCapacityMah = myBattery.getRemainingCapacityMah();
  Serial.printf("Remaining Capacity: %dmAh\r\n", remainingCapacityMah);

  uint16_t fullChargeCapacityMah = myBattery.getFullChargeCapacityMah();
  Serial.printf("Full Charge Capacity: %dmAh\r\n", fullChargeCapacityMah);

  uint16_t runTimeToEmptyMin = myBattery.getRunTimeToEmptyMin();
  Serial.printf("Run time to empty: %d min\r\n", runTimeToEmptyMin);

  uint16_t averageTimeToEmptyMin = myBattery.getAverageTimeToEmptyMin();
  Serial.printf("Average time to empty: %d min\r\n", averageTimeToEmptyMin);

  uint16_t averageTimeToFullMin = myBattery.getAverageTimeToFullMin();
  Serial.printf("Average time to full: %d min\r\n", averageTimeToFullMin);

  uint16_t chargingCurrentMa = myBattery.getChargingCurrentMa();
  Serial.printf("Charging current: %d mA\r\n", chargingCurrentMa);

  float chargingVoltage = myBattery.getChargingVoltageMv() / 1000.0;
  Serial.printf("Charging voltage: %0.2fV\r\n", chargingVoltage);

  uint16_t cycleCount = myBattery.getCycleCount();
  Serial.printf("Cycle count: %d\r\n", cycleCount);

  float cellVoltage1 = myBattery.getCellVoltage1Mv() / 1000.0;
  Serial.printf("Cell voltage 1: %0.2fV\r\n", cellVoltage1);

  float cellVoltage2 = myBattery.getCellVoltage2Mv() / 1000.0;
  Serial.printf("Cell voltage 2: %0.2fV\r\n", cellVoltage2);

  float cellVoltage3 = myBattery.getCellVoltage3Mv() / 1000.0;
  Serial.printf("Cell voltage 3: %0.2fV\r\n", cellVoltage3);

  float cellVoltage4 = myBattery.getCellVoltage4Mv() / 1000.0;
  Serial.printf("Cell voltage 4: %0.2fV\r\n", cellVoltage4);
}

void loop()
{
  if (Serial.available()) ESP.restart();
}
