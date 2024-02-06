/*
  This is a library to control BQ40Z50 battery manager.

  https://github.com/sparkfun/SparkFun_BQ40Z50_Battery_Manager_Arduino_Library

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/

#include "SparkFun_BQ40Z50_Battery_Manager_Arduino_Library.h"
#include "Arduino.h"


//Initializes the sensor with basic settings
//Returns false if sensor is not detected
bool BQ40Z50::begin(TwoWire &wirePort)
{
  _i2cPort = &wirePort;

  if (isConnected() == false)
    return (false);

  return (true);
}

bool BQ40Z50::isConnected()
{
  _i2cPort->beginTransmission(bq40z50DeviceAddress);
  if (_i2cPort->endTransmission() != 0)
    return(false); //Sensor did not ACK
  return(true); //All good
}

//Get/Set Helper Functions
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

float BQ40Z50::getTemperatureC()
{
  uint16_t temperature = readRegister16(BQ40Z50_TEMPERATURE); //In 0.1 K
  float tempC = temperature / 10.0;
  tempC -= 273.15;
  return(tempC);
}

float BQ40Z50::getTemperatureF()
{
  return((getTemperatureC() * 9.0/5) + 32.0);
}

uint16_t BQ40Z50::getVoltageMv()
{
  return(readRegister16(BQ40Z50_VOLTAGE)); //In mV
}

int16_t BQ40Z50::getCurrentMa()
{
  return(readRegister16(BQ40Z50_CURRENT)); //In mA
}

int16_t BQ40Z50::getAverageCurrentMa()
{
  return(readRegister16(BQ40Z50_AVERAGE_CURRENT)); //In mA
}

uint8_t BQ40Z50::getMaxError()
{
  uint8_t maxError = readRegister(BQ40Z50_MAX_ERROR); //In %
  return(maxError);
}

uint8_t BQ40Z50::getRelativeStateOfCharge()
{
  uint8_t relStateOfCharge = readRegister(BQ40Z50_RELATIVE_STATE_OF_CHARGE); //In %
  return(relStateOfCharge);
}

uint8_t BQ40Z50::getAbsoluteStateOfCharge()
{
  uint8_t absStateOfCharge = readRegister(BQ40Z50_ABSOLUTE_STATE_OF_CHARGE); //In %
  return(absStateOfCharge);
}

uint16_t BQ40Z50::getRemainingCapacityMah()
{
  return(readRegister16(BQ40Z50_REMAINING_CAPACITY)); //In mAh when CAPM = 0
}

uint16_t BQ40Z50::getFullChargeCapacityMah()
{
  return(readRegister16(BQ40Z50_FULL_CHARGE_CAPACITY)); //In mAh when CAPM = 0
}

uint16_t BQ40Z50::getRunTimeToEmptyMin()
{
  return(readRegister16(BQ40Z50_RUNTIME_TO_EMPTY)); //In minutes
}

uint16_t BQ40Z50::getAverageTimeToEmptyMin()
{
  return(readRegister16(BQ40Z50_AVERAGE_TIME_TO_EMPTY)); //In minutes
}

uint16_t BQ40Z50::getAverageTimeToFullMin()
{
  return(readRegister16(BQ40Z50_AVERAGE_TIME_TO_FULL)); //In minutes
}

uint16_t BQ40Z50::getChargingCurrentMa()
{
  return(readRegister16(BQ40Z50_CHARGING_CURRENT)); //In mA
}

uint16_t BQ40Z50::getChargingVoltageMv()
{
  return(readRegister16(BQ40Z50_CHARGING_VOLTAGE)); //In mV
}

uint16_t BQ40Z50::getCycleCount()
{
  return(readRegister16(BQ40Z50_CYCLE_COUNT));
}

uint16_t BQ40Z50::getCellVoltage1Mv()
{
  return(readRegister16(BQ40Z50_CELL_VOLTAGE_1));
}

uint16_t BQ40Z50::getCellVoltage2Mv()
{
  return(readRegister16(BQ40Z50_CELL_VOLTAGE_2));
}

uint16_t BQ40Z50::getCellVoltage3Mv()
{
  return(readRegister16(BQ40Z50_CELL_VOLTAGE_3));
}

uint16_t BQ40Z50::getCellVoltage4Mv()
{
  return(readRegister16(BQ40Z50_CELL_VOLTAGE_4));
}

//Reads from a given location
//Stores the result at the provided outputPointer
uint8_t BQ40Z50::readRegister(uint8_t addr)
{
  _i2cPort->beginTransmission(bq40z50DeviceAddress);
  _i2cPort->write(addr);
  if (_i2cPort->endTransmission(false) != 0) //Send a restart command. Do not release bus.
  {
    //Sensor did not ACK
    Serial.println("Error: Sensor did not ack");
  }

  _i2cPort->requestFrom((uint8_t)bq40z50DeviceAddress, (uint8_t)1);
  if (_i2cPort->available())
  {
    return (_i2cPort->read());
  }

  Serial.println("Error: Sensor did not respond");
  return (0);
}

//Reads two consecutive bytes from a given location
uint16_t BQ40Z50::readRegister16(uint8_t addr)
{
  _i2cPort->beginTransmission(bq40z50DeviceAddress);
  _i2cPort->write(addr);
  if (_i2cPort->endTransmission() != 0)
  {
    Serial.println("Sensor did not ack!");
    return (0); //Sensor did not ACK
  }

  _i2cPort->requestFrom((uint8_t)bq40z50DeviceAddress, (uint8_t)2);
  if (_i2cPort->available())
  {
    //Little endian
    uint8_t lsb = _i2cPort->read();
    uint8_t msb = _i2cPort->read();

    return ((uint16_t)msb << 8 | lsb);
  }
  return (0); //Sensor did not respond
}