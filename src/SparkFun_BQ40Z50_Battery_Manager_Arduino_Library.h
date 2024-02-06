/*
  This is a library to control BQ40Z50 battery manager.

  https://github.com/sparkfun/SparkFun_BQ40Z50_Battery_Manager_Arduino_Library

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/

#ifndef _SPARKFUN_BQ40Z50_BATTERY_MANAGER_LIBRARY_H
#define _SPARKFUN_BQ40Z50_BATTERY_MANAGER_LIBRARY_H

#include "Arduino.h"
#include <Wire.h>

#define BQ40Z50_TEMPERATURE 0x08
#define BQ40Z50_VOLTAGE 0x09
#define BQ40Z50_CURRENT 0x0A
#define BQ40Z50_AVERAGE_CURRENT 0x0B
#define BQ40Z50_MAX_ERROR 0x0C
#define BQ40Z50_RELATIVE_STATE_OF_CHARGE 0x0D
#define BQ40Z50_ABSOLUTE_STATE_OF_CHARGE 0x0E
#define BQ40Z50_REMAINING_CAPACITY 0x0F
#define BQ40Z50_FULL_CHARGE_CAPACITY 0x10
#define BQ40Z50_RUNTIME_TO_EMPTY 0x11
#define BQ40Z50_AVERAGE_TIME_TO_EMPTY 0x12
#define BQ40Z50_AVERAGE_TIME_TO_FULL 0x13
#define BQ40Z50_CHARGING_CURRENT 0x14
#define BQ40Z50_CHARGING_VOLTAGE 0x15
#define BQ40Z50_CYCLE_COUNT 0x17
#define BQ40Z50_CELL_VOLTAGE_1 0x3F
#define BQ40Z50_CELL_VOLTAGE_2 0x3E
#define BQ40Z50_CELL_VOLTAGE_3 0x3D
#define BQ40Z50_CELL_VOLTAGE_4 0x3C

class BQ40Z50
{
  private:
    const uint8_t bq40z50DeviceAddress = 0x0B;
    TwoWire *_i2cPort;

    uint8_t readRegister(uint8_t addr);
    uint16_t readRegister16(uint8_t addr);

  public:
    bool begin(TwoWire &wirePort = Wire);
    bool isConnected();

    float getTemperatureC();
    float getTemperatureF();
    uint16_t getVoltageMv();
    int16_t getCurrentMa();
    int16_t getAverageCurrentMa();
    uint8_t getMaxError();
    uint8_t getRelativeStateOfCharge();
    uint8_t getAbsoluteStateOfCharge();
    uint16_t getRemainingCapacityMah();
    uint16_t getFullChargeCapacityMah();
    uint16_t getRunTimeToEmptyMin();
    uint16_t getAverageTimeToEmptyMin();
    uint16_t getAverageTimeToFullMin();
    uint16_t getChargingCurrentMa();
    uint16_t getChargingVoltageMv();
    uint16_t getCycleCount();
    uint16_t getCellVoltage1Mv();
    uint16_t getCellVoltage2Mv();
    uint16_t getCellVoltage3Mv();
    uint16_t getCellVoltage4Mv();
};

#endif //_SPARKFUN_BQ40Z50_BATTERY_MANAGER_LIBRARY_H
